//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-07-23
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../Include/xl/Windows/Network/xlSocket.h"

using namespace xl::Windows;

int main()
{
    Socket s;

    bool b = s.Open(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    ULONG ulValue = 1;
    b = s.IOControl(FIONBIO, &ulValue);

    b = s.Connect(L"119.75.218.45", 80);
    Socket::SelectOption so = s.Select(Socket::SO_WRITE, INFINITE);

    const char request[] = "GET / HTTP/1.1\r\n"
                           "Host: www.baidu.com\r\n"
                           "\r\n";
    const DWORD reqSize = ARRAYSIZE(request) - 1;

    s.Send(request, reqSize);
    so = s.Select(Socket::SO_READ, INFINITE);

    const DWORD bufSize = 4096;
    char buffer[bufSize] = {};

    s.Receive(buffer, bufSize);


    return 0;
}

