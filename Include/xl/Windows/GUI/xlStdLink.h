//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdLink.h
//    Author:      Streamlet
//    Create Time: 2011-03-07
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSTDLINK_H_FEA6F574_15DC_4178_8DFA_83C8226EC770_INCLUDED__
#define __XLSTDLINK_H_FEA6F574_15DC_4178_8DFA_83C8226EC770_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class StdLink : public Window
        {
        public:
            StdLink()
            {

            }

            StdLink(HWND hWnd) :
                Window(hWnd)
            {

            }

            ~StdLink()
            {

            }

            bool Create(HWND hParent,
                        UINT nID,
                        int x,
                        int y,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                        DWORD dwExStyle = 0)
            {
                if (!Window::Create(hParent,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    dwStyle,
                                    dwExStyle,
                                    WC_LINK,
                                    nullptr,
                                    (HMENU)(size_t)nID,
                                    nullptr))
                {
                    return false;
                }

                return true;
            }

        public: // Attributes

            int GetIdealHeight(int cxMaxWidth = 0)
            {
                return (int)::SendMessage(m_hWnd, LM_GETIDEALHEIGHT, cxMaxWidth, 0L);
            }

            BOOL GetItem(PLITEM pLItem)
            {
                return (BOOL)::SendMessage(m_hWnd, LM_GETITEM, 0, (LPARAM)pLItem);
            }

            BOOL SetItem(PLITEM pLItem)
            {
                return (BOOL)::SendMessage(m_hWnd, LM_SETITEM, 0, (LPARAM)pLItem);
            }

        public: // Vista only

            int GetIdealSize(SIZE& size, int cxMaxWidth = 0) const
            {
                return (int)::SendMessage(m_hWnd, LM_GETIDEALSIZE, cxMaxWidth, (LPARAM)&size);
            }

        public: // Operations

            BOOL HitTest(PLHITTESTINFO pLHitTestInfo) const
            {
                return (BOOL)::SendMessage(m_hWnd, LM_HITTEST, 0, (LPARAM)pLHitTestInfo);
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSTDLINK_H_FEA6F574_15DC_4178_8DFA_83C8226EC770_INCLUDED__
