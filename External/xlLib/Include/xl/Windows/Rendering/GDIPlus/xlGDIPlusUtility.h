//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlGDIPlusUtility.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLGDIPLUSUTILITY_H_636F1550_10BE_4B64_B780_66C41ACA77BD_INCLUDED__
#define __XLGDIPLUSUTILITY_H_636F1550_10BE_4B64_B780_66C41ACA77BD_INCLUDED__


#include "xlGDIPlusImports.h"

namespace xl
{
    namespace Windows
    {
        class GDIPlusStartupShutDown
        {
        public:
            GDIPlusStartupShutDown() : m_uToken(0)
            {
                Startup();
            }

            ~GDIPlusStartupShutDown()
            {
                Shutdown();
            }

        private:
            bool Startup()
            {
                Gdiplus::GdiplusStartupInput gdiplusStartupInput = {};

                if (_GdiplusStartup(&m_uToken, &gdiplusStartupInput, nullptr) != Gdiplus::Ok)
                {
                    return false;
                }

                return true;
            }

            void Shutdown()
            {
                _GdiplusShutdown(m_uToken);
                m_uToken = 0;
            }

        private:
            ULONG_PTR m_uToken;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLGDIPLUSUTILITY_H_636F1550_10BE_4B64_B780_66C41ACA77BD_INCLUDED__
