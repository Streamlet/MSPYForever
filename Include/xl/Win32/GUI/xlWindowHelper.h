//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWindow.h
//    Author:      Streamlet
//    Create Time: 2011-02-11
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLWINDOWHELPER_H_0646591E_8D6A_44AA_A773_084A53A0B190_INCLUDED__
#define __XLWINDOWHELPER_H_0646591E_8D6A_44AA_A773_084A53A0B190_INCLUDED__


#include "../../Common/Memory/xlSmartPtr.h"
#include "../../Common/String/xlString.h"
#include "../xlWin32Ver.h"
#include <ShellAPI.h>

//
// Controls TODO List:
//
// _T("RichEdit")
// _T("RICHEDIT_CLASS")
// _T("MDICLIENT")
// WC_HEADER
// WC_TREEVIEW
// WC_COMBOBOXEX
// WC_TABCONTROL
// WC_IPADDRESS
// WC_PAGESCROLLER
// WC_NATIVEFONTCTL
//

namespace xl
{
    class WindowHelper
    {
    public:
        WindowHelper(HWND hWnd) : m_hWnd(hWnd)
        {

        }

        ~WindowHelper()
        {

        }

        operator HWND() const
        {
            return m_hWnd;
        }

        DWORD GetStyle()
        {
            return (DWORD)::GetWindowLong(m_hWnd, GWL_STYLE);
        }

        DWORD SetStyle(DWORD dwStyle)
        {
            return (DWORD)::SetWindowLong(m_hWnd, GWL_STYLE, (LONG)dwStyle);
        }

        DWORD GetExStyle()
        {
            return (DWORD)::GetWindowLong(m_hWnd, GWL_EXSTYLE);
        }

        DWORD SetExStyle(DWORD dwExStyle)
        {
            return (DWORD)::SetWindowLong(m_hWnd, GWL_EXSTYLE, (LONG)dwExStyle);
        }

        HFONT GetFont()
        {
            return (HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0);
        }

        void SetFont(HFONT hFont, BOOL bRedraw = TRUE)
        {
            ::SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
        }

        BOOL ClientToScreen(LPPOINT lpPoint)
        {
            return ::ClientToScreen(m_hWnd, lpPoint);
        }

        BOOL ClientToScreen(LPRECT lpRect)
        {
            if(!::ClientToScreen(m_hWnd, (LPPOINT)lpRect))
            {
                return FALSE;
            }

            if(!::ClientToScreen(m_hWnd, (LPPOINT)lpRect) + 1)
            {
                return FALSE;
            }

            return TRUE;
        }

        BOOL ScreenToClient(LPPOINT lpPoint)
        {
            return ::ScreenToClient(m_hWnd, lpPoint);
        }

        BOOL ScreenToClient(LPRECT lpRect)
        {
            if(!::ScreenToClient(m_hWnd, (LPPOINT)lpRect))
            {
                return FALSE;
            }

            if(!::ScreenToClient(m_hWnd, (LPPOINT)lpRect) + 1)
            {
                return FALSE;
            }

            return TRUE;
        }

        void SetRedraw(BOOL bRedraw = TRUE)
        {
            ::SendMessage(m_hWnd, WM_SETREDRAW, (WPARAM)bRedraw, 0);
        }

        HICON SetIcon(HICON hIcon, BOOL bBigIcon = TRUE)
        {
            return (HICON)::SendMessage(m_hWnd, WM_SETICON, bBigIcon, (LPARAM)hIcon);
        }

        HICON GetIcon(BOOL bBigIcon = TRUE)
        {
            return (HICON)::SendMessage(m_hWnd, WM_GETICON, bBigIcon, 0);
        }

        int SetHotKey(WORD wVirtualKeyCode, WORD wModifiers)
        {
            return (int)::SendMessage(m_hWnd, WM_SETHOTKEY, MAKEWORD(wVirtualKeyCode, wModifiers), 0);
        }

        DWORD GetHotKey()
        {
            return (DWORD)::SendMessage(m_hWnd, WM_GETHOTKEY, 0, 0);
        }

        BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd)
        {
            DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
            DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;

            if(dwStyle == dwNewStyle)
            {
                return FALSE;
            }

            ::SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);

            return TRUE;
        }

        BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd)
        {
            DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
            DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;

            if(dwStyle == dwNewStyle)
            {
                return FALSE;
            }

            ::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewStyle);

            return TRUE;
        }

        protected:
            HWND m_hWnd;

    };

} // namespace xl

#endif // #ifndef __XLWINDOWHELPER_H_0646591E_8D6A_44AA_A773_084A53A0B190_INCLUDED__
