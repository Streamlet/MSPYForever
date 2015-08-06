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


#include "../../Include/xl/AppHelper/xlUnitTest.h"
#include <stdlib.h>
#include <locale>
#include <tchar.h>


int _tmain(int argc, TCHAR * argv[])
{
    setlocale(LC_ALL, "");

    const TCHAR *lpFilter = _T(".*");

    if (argc > 1)
    {
        lpFilter = argv[1];
    }

    int iRet = XL_RUN_TEST_CASES(lpFilter);

    system("pause");
    return iRet;
}
