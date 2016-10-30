//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSocket.h
//    Author:      Streamlet
//    Create Time: 2011-07-23
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSOCKET_H_49FA92F6_46FC_4CB6_A9D2_924EF442467D_INCLUDED__
#define __XLSOCKET_H_49FA92F6_46FC_4CB6_A9D2_924EF442467D_INCLUDED__


#include <WinSock2.h>   // Must include WinSock2.h before Windows.h
#pragma comment(lib, "Ws2_32.lib")
#include "../../Common/Memory/xlMemory.h"
#include "../../Common/String/xlString.h"
#include "../Memory/xlSafeSmartPtr.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class Socket
        {
        public:
            Socket() :
                m_bInitialized(false), m_hSocket(INVALID_SOCKET), m_nAddressFamily(AF_UNSPEC)
            {
                Memory::Zero(m_addr);

                Initialize();
            }

            ~Socket()
            {
                UnInitialize();
            }

        public:
            typedef DWORD SelectOption;
            static const SelectOption SO_NULL = 0;
            static const SelectOption SO_READ = 1;
            static const SelectOption SO_WRITE = 2;
            static const SelectOption SO_EXCEPT = 4;

        protected:
            bool Initialize()
            {
                if (m_bInitialized)
                {
                    return true;
                }

                WSADATA wsaData = {};
                int nRes = WSAStartup(MAKEWORD(2, 2), &wsaData);

                if (nRes != 0)
                {
                    return false;
                }

                m_bInitialized = true;

                return true;
            }

            void UnInitialize()
            {
                if (!m_bInitialized)
                {
                    return;
                }

                WSACleanup();

                m_bInitialized = false;
            }

        public:
            bool Open(int nAddressFamily, int nType, int nProtocol)
            {
                Close();

                m_hSocket = socket(nAddressFamily, nType, nProtocol);

                if (m_hSocket == INVALID_SOCKET)
                {
                    return false;
                }

                m_nAddressFamily = nAddressFamily;

                return true;
            }

            bool IOControl(LONG nCommand, ULONG *puValue)
            {
                int nRes = ioctlsocket(m_hSocket, nCommand, puValue);

                if (nRes != 0)
                {
                    return false;
                }

                return true;
            }

            bool Bind(const String &strAddress, WORD wPort)
            {
                SafeSharedArray<Char> szAddress = new Char[strAddress.Length() + 1];
                Memory::Copy(szAddress.RawPointer(), (const wchar_t *)strAddress, (strAddress.Length() + 1) * sizeof(Char));

                sockaddr_in &sin = (sockaddr_in &)m_addr;
                int sinSize = sizeof(sin);
                int nRes = WSAStringToAddress(szAddress.RawPointer(), m_nAddressFamily, NULL, (LPSOCKADDR)&sin, &sinSize);

                if (nRes != 0)
                {
                    return false;
                }

                sin.sin_port = htons(wPort);

                nRes = bind(m_hSocket, (LPSOCKADDR)&sin, sizeof(sin));

                if (nRes != 0)
                {
                    return false;
                }

                return true;
            }

            bool Listen()
            {
                int nRes = listen(m_hSocket, SOMAXCONN);

                if (nRes != 0)
                {
                    return false;
                }

                return true;
            }

            bool Accept(Socket &socket)
            {
                SOCKET s = accept(m_hSocket, &socket.m_addr, NULL);

                if (s == INVALID_SOCKET)
                {
                    return false;
                }

                socket.m_hSocket = s;
                socket.m_nAddressFamily = m_nAddressFamily;

                return true;
            }

            bool Connect(const String &strAddress, WORD wPort)
            {
                SafeSharedArray<Char> szAddress = new Char[strAddress.Length() + 1];
                Memory::Copy(szAddress.RawPointer(), (const wchar_t *)strAddress, (strAddress.Length() + 1) * sizeof(Char));

                sockaddr_in &sin = (sockaddr_in &)m_addr;
                int sinSize = sizeof(sin);
                int nRes = WSAStringToAddress(szAddress.RawPointer(), m_nAddressFamily, NULL, (LPSOCKADDR)&sin, &sinSize);

                if (nRes != 0)
                {
                    return false;
                }

                sin.sin_port = htons(wPort);

                nRes = connect(m_hSocket, (LPSOCKADDR)&sin, sizeof(sin));

                if (nRes != 0)
                {
                    return false;
                }

                return true;
            }

            DWORD Send(LPCVOID lpBuffer, DWORD cbSize)
            {
                return (DWORD)send(m_hSocket, (const char *)lpBuffer, (int)cbSize, 0);
            }

            DWORD Receive(LPVOID lpBuffer, DWORD cbSize)
            {
                return (DWORD)recv(m_hSocket, (char *)lpBuffer, (int)cbSize, 0);
            }

            SelectOption Select(SelectOption so, DWORD dwTimeout)
            {
                fd_set fsRead = {}, fsWrite = {}, fsExcept = {};

                FD_SET(m_hSocket, &fsRead);
                FD_SET(m_hSocket, &fsWrite);
                FD_SET(m_hSocket, &fsExcept);

                timeval timeout = { (long)dwTimeout / 1000, (long)dwTimeout % 1000 };
                int nRes = select((int)m_hSocket + 1,
                    (so & SO_READ) != 0 ? &fsRead : NULL,
                    (so & SO_WRITE) != 0 ? &fsWrite : NULL,
                    (so & SO_EXCEPT) != 0 ? &fsExcept : NULL,
                    dwTimeout != INFINITE ? &timeout : NULL);

                SelectOption soResult = SO_NULL;

                if (nRes == 0 || nRes == SOCKET_ERROR)
                {
                    return soResult;
                }

                if ((so & SO_READ) != 0 && FD_ISSET(m_hSocket, &fsRead))
                {
                    soResult |= SO_READ;
                }

                if ((so & SO_WRITE) != 0 && FD_ISSET(m_hSocket, &fsWrite))
                {
                    soResult |= SO_WRITE;
                }

                if ((so & SO_EXCEPT) != 0 && FD_ISSET(m_hSocket, &fsExcept))
                {
                    soResult |= SO_EXCEPT;
                }

                return soResult;
            }

            bool ShutDown(int nOperation)
            {
                int nRes = shutdown(m_hSocket, nOperation);

                if (nRes != 0)
                {
                    return false;
                }

                return true;
            }

            void Close()
            {
                if (m_hSocket == INVALID_SOCKET)
                {
                    return;
                }

                ShutDown(SD_BOTH);

                closesocket(m_hSocket);

                m_nAddressFamily = AF_UNSPEC;
                m_hSocket = INVALID_SOCKET;
            }

        private:
            bool     m_bInitialized;
            SOCKET   m_hSocket;
            int      m_nAddressFamily;
            sockaddr m_addr;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSOCKET_H_49FA92F6_46FC_4CB6_A9D2_924EF442467D_INCLUDED__
