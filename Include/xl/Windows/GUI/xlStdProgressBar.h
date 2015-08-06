//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdScrollBar.h
//    Author:      Streamlet
//    Create Time: 2012-12-08
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLSTDSCROLLBAR_H_6214D57B_C7F1_4DE7_81E9_FB36D836F744_INCLUDED__
#define __XLSTDSCROLLBAR_H_6214D57B_C7F1_4DE7_81E9_FB36D836F744_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class StdProgressBar : public Window
        {
        public:
            StdProgressBar()
            {

            }

            StdProgressBar(HWND hWnd) :
                Window(hWnd)
            {

            }

            ~StdProgressBar()
            {

            }

            bool Create(HWND hParent,
                        UINT nID,
                        int x,
                        int y,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER,
                        DWORD dwExStyle = 0)
            {
                if (!Window::Create(hParent,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    dwStyle,
                                    dwExStyle,
                                    PROGRESS_CLASS,
                                    nullptr,
                                    (HMENU)(size_t)nID,
                                    nullptr))
                {
                    return false;
                }

                return true;
            }

        public: // Attributes
            DWORD SetRange(int nLower, int nUpper)
            {
                return (DWORD)::SendMessage(m_hWnd, PBM_SETRANGE, 0, MAKELPARAM(nLower, nUpper));
            }

            int SetPos(int nPos)
            {
                return (int)(short)LOWORD(::SendMessage(m_hWnd, PBM_SETPOS, nPos, 0));
            }

            int OffsetPos(int nPos)
            {
                return (int)(short)LOWORD(::SendMessage(m_hWnd, PBM_DELTAPOS, nPos, 0));
            }

            int SetStep(int nStep)
            {
                return (int)(short)LOWORD(::SendMessage(m_hWnd, PBM_SETSTEP, nStep, 0));
            }

            UINT GetPos() const
            {
                return (UINT)::SendMessage(m_hWnd, PBM_GETPOS, 0, 0);
            }

            void GetRange(PPBRANGE pPBRange) const
            {
                ::SendMessage(m_hWnd, PBM_GETRANGE, TRUE, (LPARAM)pPBRange);
            }

            void GetRange(int &nLower, int &nUpper) const
            {
                PBRANGE range = { 0 };
                ::SendMessage(m_hWnd, PBM_GETRANGE, TRUE, (LPARAM)&range);
                nLower = range.iLow;
                nUpper = range.iHigh;
            }

            int GetRangeLimit(BOOL bLowLimit) const
            {
                return (int)::SendMessage(m_hWnd, PBM_GETRANGE, bLowLimit, (LPARAM)NULL);
            }

            DWORD SetRange32(int nMin, int nMax)
            {
                return (DWORD)::SendMessage(m_hWnd, PBM_SETRANGE32, nMin, nMax);
            }

#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
            COLORREF SetBarColor(COLORREF clr)
            {
                return (COLORREF)::SendMessage(m_hWnd, PBM_SETBARCOLOR, 0, (LPARAM)clr);
            }

            COLORREF SetBkColor(COLORREF clr)
            {
                return (COLORREF)::SendMessage(m_hWnd, PBM_SETBKCOLOR, 0, (LPARAM)clr);
            }
#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0501) && defined(PBM_SETMARQUEE)
            BOOL SetMarquee(BOOL bMarquee, UINT uUpdateTime = 0)
            {
                return (BOOL)::SendMessage(m_hWnd, PBM_SETMARQUEE, (WPARAM)bMarquee, (LPARAM)uUpdateTime);
            }
#endif // (_WIN32_WINNT >= 0x0501) && defined(PBM_SETMARQUEE)

#if (_WIN32_WINNT >= 0x0600)
            int GetStep() const
            {
                return (int)::SendMessage(m_hWnd, PBM_GETSTEP, 0, 0);
            }

            COLORREF GetBkColor() const
            {
                return (COLORREF)::SendMessage(m_hWnd, PBM_GETBKCOLOR, 0, 0);
            }

            COLORREF GetBarColor() const
            {
                return (COLORREF)::SendMessage(m_hWnd, PBM_GETBARCOLOR, 0, 0);
            }

            int GetState() const
            {
                return (int)::SendMessage(m_hWnd, PBM_GETSTATE, 0, 0);
            }

            int SetState(int nState)
            {
                return (int)::SendMessage(m_hWnd, PBM_SETSTATE, nState, 0);
            }
#endif // (_WIN32_WINNT >= 0x0600)

        public: // Operations
            int StepIt()
            {
                return (int)(short)LOWORD(::SendMessage(m_hWnd, PBM_STEPIT, 0, 0));
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSTDSCROLLBAR_H_6214D57B_C7F1_4DE7_81E9_FB36D836F744_INCLUDED__
