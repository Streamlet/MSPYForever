//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlConsole.h
//    Author:      Streamlet
//    Create Time: 2015-08-09
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCONSOLE_H_75B32231_0DCF_442D_8644_01DC76C5E217_INCLUDED__
#define __XLCONSOLE_H_75B32231_0DCF_442D_8644_01DC76C5E217_INCLUDED__


#include "../../Common/String/xlString.h"

namespace xl
{
    namespace Windows
    {
        template <int nStdHandle>   // STD_INPUT_HANDLE / STD_OUTPUT_HANDLE / STD_ERROR_HANDLE
        class ConsoleT
        {
        public:
            ConsoleT() : m_hConsole(nullptr)
            {
                AllocConsole();
                m_hConsole = GetStdHandle(nStdHandle);
            }

            ~ConsoleT()
            {

            }

        public:

            void SetTextAttribute(WORD wAttributes)
            {
                SetConsoleTextAttribute(m_hConsole, wAttributes);
            }

        protected:
            HANDLE m_hConsole;
        };

        typedef ConsoleT<STD_INPUT_HANDLE>  StdInput;
        typedef ConsoleT<STD_OUTPUT_HANDLE> StdOutput;
        typedef ConsoleT<STD_ERROR_HANDLE>  StdError;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLCONSOLE_H_75B32231_0DCF_442D_8644_01DC76C5E217_INCLUDED__
