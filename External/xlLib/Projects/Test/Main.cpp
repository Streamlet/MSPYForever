//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//------------------------------------------------------------------------------


#include <stdio.h>
#include "../../Include/xl/Common/Meta/xlTuple.h"
#include "../../Include/xl/Windows/Rendering/xlGraphics.h"
#include "../../Include/xl/Windows/Rendering/GDI/xlBitmapGDI.h"
#include <Windows.h>


int main()
{
    using namespace xl;
    using namespace xl::Windows;

    BitmapGDI bmp;
    bmp.CreateBlank(10, 10);

    ColorX *pColor = bmp.Lock(BitmapLockFlag_Write);

    for (int i = 0; i < 10 * 10; ++i)
    {
        pColor[i] = ColorX(150 + i, 0xff, 0x00, 0x00);
    }

    bmp.SaveToFile(L"a.png");

    for (int i = 0; i < 10 * 10; ++i)
    {
        pColor[i] = ColorX(150 + i, 0x00, 0xff, 0x00);
    }

    bmp.SaveToFile(L"b.png");

    bmp.LoadFromFile(L"a.png");
    bmp.SaveToFile(L"c.png");

    size_t cbSize = 0;
    void *lpBuffer = bmp.SaveToMemory(cbSize);

    bmp.LoadFromFile(L"b.png");
    bmp.SaveToFile(L"d.png");

    bmp.LoadFromMemory(lpBuffer, cbSize);
    bmp.SaveToFile(L"e.png");

    return 0;
}
