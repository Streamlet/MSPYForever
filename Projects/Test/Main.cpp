//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Win32/Timer/xlTimer.h>
#include <stdio.h>

int main()
{
    xl::Timer t;
    t.Set(1000, [&t](DWORD dwTime)
        {
            printf("%u\n", dwTime);
            t.Kill();
        });

    MSG msg = {};

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
