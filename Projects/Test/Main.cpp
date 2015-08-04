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


#include <stdio.h>
#include "../../Include/xl/Common/Meta/xlTuple.h"
#include "../../Include/xl/Win32/Rendering/xlGraphics.h"
#include "../../Include/xl/Win32/Rendering/GDI/xlBitmapGDI.h"
#include <Windows.h>


int main()
{
    using namespace xl;

    BitmapGDI bmp;
    bmp.CreateBlank(10, 10);

    ColorX *pColor = bmp.Lock(BitmapLockFlag_Write);

    for (int i = 0; i < 10 * 10; ++i)
    {
        pColor[i] = ColorX(150 + i, 0xff, 0x00, 0x00);
    }

    bmp.SaveToFile(_T("a.png"));

    for (int i = 0; i < 10 * 10; ++i)
    {
        pColor[i] = ColorX(150 + i, 0x00, 0xff, 0x00);
    }

    bmp.SaveToFile(_T("b.png"));

    bmp.LoadFromFile(_T("a.png"));
    bmp.SaveToFile(_T("c.png"));

    size_t cbSize = 0;
    void *lpBuffer = bmp.SaveToMemory(cbSize);

    bmp.LoadFromFile(_T("b.png"));
    bmp.SaveToFile(_T("d.png"));

    bmp.LoadFromMemory(lpBuffer, cbSize);
    bmp.SaveToFile(_T("e.png"));

    return 0;
}
