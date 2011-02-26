//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/String/xlUTF8.h>


int main()
{
    xl::String s = L"ÄãºÃ";
    xl::StringA utf8;
    xl::UTF8::Encode(s, &utf8);

    xl::String ucs2;
    bool b = xl::UTF8::Decode(utf8, &ucs2);


    return 0;
}


