//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdStatic.h
//    Author:      Streamlet
//    Create Time: 2011-02-13
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSTDSTATIC_H_1715D513_4BF0_431F_BC57_C347432395BB_INCLUDED__
#define __XLSTDSTATIC_H_1715D513_4BF0_431F_BC57_C347432395BB_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class StdStatic : public Window
        {
        public:
            StdStatic()
            {

            }

            StdStatic(HWND hWnd) :
                Window(hWnd)
            {

            }

            ~StdStatic()
            {

            }

        public:
            bool Create(HWND hParent,
                        UINT nID,
                        int x,
                        int y,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle = WS_CHILD | WS_VISIBLE,
                        DWORD dwExStyle = 0)
            {
                if (!Window::Create(hParent,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    dwStyle,
                                    dwExStyle,
                                    WC_STATIC,
                                    nullptr,
                                    (HMENU)(size_t)nID,
                                    nullptr))
                {
                    return false;
                }

                return true;
            }

        public:
            HICON GetIcon() const
            {
                return (HICON)::SendMessage(m_hWnd, STM_GETICON, 0, 0);
            }

            HICON SetIcon(HICON hIcon)
            {
                return (HICON)::SendMessage(m_hWnd, STM_SETICON, (WPARAM)hIcon, 0);
            }

            HENHMETAFILE GetEnhMetaFile() const
            {
                return (HENHMETAFILE)::SendMessage(m_hWnd, STM_GETIMAGE, IMAGE_ENHMETAFILE, 0);
            }

            HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile)
            {
                return (HENHMETAFILE)::SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);
            }

            HBITMAP GetBitmap() const
            {
                return (HBITMAP)::SendMessage(m_hWnd, STM_GETIMAGE, IMAGE_BITMAP, 0);
            }

            HBITMAP SetBitmap(HBITMAP hBitmap)
            {
                return (HBITMAP)::SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
            }

            HCURSOR GetCursor() const
            {
                return (HCURSOR)::SendMessage(m_hWnd, STM_GETIMAGE, IMAGE_CURSOR, 0);
            }

            HCURSOR SetCursor(HCURSOR hCursor)
            {
                return (HCURSOR)::SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSTDSTATIC_H_1715D513_4BF0_431F_BC57_C347432395BB_INCLUDED__
