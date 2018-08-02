//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdScrollBar.h
//    Author:      Streamlet
//    Create Time: 2011-03-04
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSTDSCROLLBAR_H_CE421D01_3A90_4DFA_A59F_74C911033E2A_INCLUDED__
#define __XLSTDSCROLLBAR_H_CE421D01_3A90_4DFA_A59F_74C911033E2A_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class StdScrollBar : public Window
        {
        public:
            StdScrollBar()
            {

            }

            StdScrollBar(HWND hWnd) :
                Window(hWnd)
            {

            }

            ~StdScrollBar()
            {

            }

            bool Create(HWND hParent,
                        UINT nID,
                        int x,
                        int y,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle = WS_CHILD | WS_VISIBLE | SBS_VERT,
                        DWORD dwExStyle = 0)
            {
                if (!Window::Create(hParent,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    dwStyle,
                                    dwExStyle,
                                    WC_SCROLLBAR,
                                    nullptr,
                                    (HMENU)(size_t)nID,
                                    nullptr))
                {
                    return false;
                }

                return true;
            }

        public: // Attributes

            int SetScrollPos(int nPos, BOOL bRedraw = TRUE)
            {
                return ::SetScrollPos(m_hWnd, SB_CTL, nPos, bRedraw);
            }

            void SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE)
            {
                ::SetScrollRange(m_hWnd, SB_CTL, nMinPos, nMaxPos, bRedraw);
            }

            BOOL GetScrollInfo(LPSCROLLINFO lpScrollInfo) const
            {
                return ::GetScrollInfo(m_hWnd, SB_CTL, lpScrollInfo);
            }

            int SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE)
            {
                return ::SetScrollInfo(m_hWnd, SB_CTL, lpScrollInfo, bRedraw);
            }

#if (WINVER >= 0x0500)

            BOOL GetScrollBarInfo(PSCROLLBARINFO pScrollBarInfo) const
            {
#if (_WIN32_WINNT >= 0x0501)
                return (BOOL)::SendMessage(m_hWnd, SBM_GETSCROLLBARINFO, 0, (LPARAM)pScrollBarInfo);
#else // !(_WIN32_WINNT >= 0x0501)
                return ::GetScrollBarInfo(m_hWnd, OBJID_CLIENT, pScrollBarInfo);
#endif // !(_WIN32_WINNT >= 0x0501)
            }

#endif // (WINVER >= 0x0500)

        public: // Operations

            void ShowScrollBar(BOOL bShow = TRUE)
            {
                ::ShowScrollBar(m_hWnd, SB_CTL, bShow);
            }

            BOOL EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH)
            {
                return ::EnableScrollBar(m_hWnd, SB_CTL, nArrowFlags);
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSTDSCROLLBAR_H_CE421D01_3A90_4DFA_A59F_74C911033E2A_INCLUDED__
