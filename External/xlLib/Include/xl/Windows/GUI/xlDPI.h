//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDPI.h
//    Author:      Streamlet
//    Create Time: 2016-03-04
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLDPI_H_7D8F7574_55C0_4AAD_A5D1_347D8FF393CD_INCLUDED__
#define __XLDPI_H_7D8F7574_55C0_4AAD_A5D1_347D8FF393CD_INCLUDED__


#include "../../xlDef.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class Dpi
        {
        public:
            inline Dpi() : m_nDpiX(0), m_nDpiY(0)
            {
                Update();
            }

            inline ~Dpi()
            {

            }

        public:
            inline bool Update()
            {
                HDC hDC = GetDC(nullptr);
                if (hDC == nullptr)
                {
                    return false;
                }

                m_nDpiX = GetDeviceCaps(hDC, LOGPIXELSX);
                m_nDpiY = GetDeviceCaps(hDC, LOGPIXELSY);

                ReleaseDC(nullptr, hDC);

                return true;
            }

        public:
            inline int TransformX(int x)
            {
                return x * m_nDpiX / 96;
            }

            inline int TransformY(int y)
            {
                return y * m_nDpiY / 96;
            }

        private:
            int m_nDpiX;
            int m_nDpiY;
        };

        __declspec(selectany) Dpi g_dpi;

#define XL_DPI_UPDATE() (xl::Windows::g_dpi.Update())
#define XL_DPI_X(x)     (xl::Windows::g_dpi.TransformX(x))
#define XL_DPI_Y(y)     (xl::Windows::g_dpi.TransformY(y))

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLDPI_H_7D8F7574_55C0_4AAD_A5D1_347D8FF393CD_INCLUDED__
