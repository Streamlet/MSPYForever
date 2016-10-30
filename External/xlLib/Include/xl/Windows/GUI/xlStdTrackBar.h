//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdTrackBar.h
//    Author:      Streamlet
//    Create Time: 2016-02-29
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSTDTRACKBAR_H_29188AB7_A7B8_4A70_9A7D_C4D30EE58540_INCLUDED__
#define __XLSTDTRACKBAR_H_29188AB7_A7B8_4A70_9A7D_C4D30EE58540_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class StdTrackBar : public Window
        {
        public:
            StdTrackBar()
            {

            }

            StdTrackBar(HWND hWnd) :
                Window(hWnd)
            {

            }

            ~StdTrackBar()
            {

            }

        protected:
            static LPCTSTR GetClassName()
            {
                return TRACKBAR_CLASS;
            }

        public:
            bool Create(HWND hParent,
                        UINT nID,
                        int x,
                        int y,
                        int nWidth,
                        int nHeight,
                        DWORD dwStyle = WS_CHILD | WS_VISIBLE | TBS_NOTICKS,
                        DWORD dwExStyle = 0)
            {
                if (!Window::Create(hParent,
                                    x,
                                    y,
                                    nWidth,
                                    nHeight,
                                    dwStyle,
                                    dwExStyle,
                                    TRACKBAR_CLASS,
                                    nullptr,
                                    (HMENU)(size_t)nID,
                                    nullptr))
                {
                    return false;
                }

                return true;
            }

        public:
            int GetLineSize() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETLINESIZE, 0, 0);
            }

            int SetLineSize(int nSize)
            {
                return (int)::SendMessage(m_hWnd, TBM_SETLINESIZE, 0, nSize);
            }

            int GetPageSize() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETPAGESIZE, 0, 0);
            }

            int SetPageSize(int nSize)
            {
                return (int)::SendMessage(m_hWnd, TBM_SETPAGESIZE, 0, nSize);
            }

            int GetRangeMin() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETRANGEMIN, 0, 0);
            }

            void SetRangeMin(int nMin, BOOL bRedraw = FALSE)
            {
                ::SendMessage(m_hWnd, TBM_SETRANGEMIN, bRedraw, nMin);
            }

            int GetRangeMax() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETRANGEMAX, 0, 0);
            }

            void SetRangeMax(int nMax, BOOL bRedraw = FALSE)
            {
                ::SendMessage(m_hWnd, TBM_SETRANGEMAX, bRedraw, nMax);
            }

            void GetRange(int& nMin, int& nMax) const
            {
                nMin = GetRangeMin();
                nMax = GetRangeMax();
            }

            void SetRange(int nMin, int nMax, BOOL bRedraw = TRUE)
            {
                ::SendMessage(m_hWnd, TBM_SETRANGE, bRedraw, MAKELPARAM(nMin, nMax));
            }

            int GetSelStart() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETSELSTART, 0, 0);
            }

            void SetSelStart(int nMin, BOOL bRedraw = FALSE)
            {
                ::SendMessage(m_hWnd, TBM_SETSELSTART, bRedraw, (LPARAM)nMin);
            }

            int GetSelEnd() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETSELEND, 0, 0);
            }

            void SetSelEnd(int nMax, BOOL bRedraw = FALSE)
            {
                ::SendMessage(m_hWnd, TBM_SETSELEND, bRedraw, (LPARAM)nMax);
            }

            void GetSelection(int& nMin, int& nMax) const
            {
                nMin = GetSelStart();
                nMax = GetSelEnd();
            }

            void SetSelection(int nMin, int nMax, BOOL bRedraw = TRUE)
            {
                SetSelStart(nMin, FALSE);
                SetSelEnd(nMax, bRedraw);
            }

            void GetChannelRect(LPRECT lprc) const
            {
                ::SendMessage(m_hWnd, TBM_GETCHANNELRECT, 0, (LPARAM)lprc);
            }

            void GetThumbRect(LPRECT lprc) const
            {
                ::SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)lprc);
            }

            int GetPos() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETPOS, 0, 0);
            }

            void SetPos(int nPos)
            {
                ::SendMessage(m_hWnd, TBM_SETPOS, TRUE, nPos);
            }

            UINT GetNumTics() const
            {
                return (UINT)::SendMessage(m_hWnd, TBM_GETNUMTICS, 0, 0);
            }

            DWORD* GetTicArray() const
            {
                return (DWORD*)::SendMessage(m_hWnd, TBM_GETPTICS, 0, 0);
            }

            int GetTic(int nTic) const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETTIC, nTic, 0);
            }

            BOOL SetTic(int nTic)
            {
                return (BOOL)::SendMessage(m_hWnd, TBM_SETTIC, 0, nTic);
            }

            int GetTicPos(int nTic) const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETTICPOS, nTic, 0);
            }

            void SetTicFreq(int nFreq)
            {
                ::SendMessage(m_hWnd, TBM_SETTICFREQ, nFreq, 0);
            }

            int GetThumbLength() const
            {
                return (int)::SendMessage(m_hWnd, TBM_GETTHUMBLENGTH, 0, 0);
            }

            void SetThumbLength(int nLength)
            {
                ::SendMessage(m_hWnd, TBM_SETTHUMBLENGTH, nLength, 0);
            }

            void SetSel(int nStart, int nEnd, BOOL bRedraw = TRUE)
            {
                ::SendMessage(m_hWnd, TBM_SETSEL, bRedraw, MAKELPARAM(nStart, nEnd));
            }

            HWND GetBuddy(BOOL bLeft = TRUE) const
            {
                return (HWND)::SendMessage(m_hWnd, TBM_GETBUDDY, bLeft, 0);
            }

            HWND SetBuddy(HWND hWndBuddy, BOOL bLeft = TRUE)
            {
                return (HWND)::SendMessage(m_hWnd, TBM_SETBUDDY, bLeft, (LPARAM)hWndBuddy);
            }

#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
            BOOL GetUnicodeFormat() const
            {
                return (BOOL)::SendMessage(m_hWnd, TBM_GETUNICODEFORMAT, 0, 0);
            }

            BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
            {
                return (BOOL)::SendMessage(m_hWnd, TBM_SETUNICODEFORMAT, bUnicode, 0);
            }
#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

            // Operations
            void ClearSel(BOOL bRedraw = FALSE)
            {
                ::SendMessage(m_hWnd, TBM_CLEARSEL, bRedraw, 0);
            }

            void VerifyPos()
            {
                ::SendMessage(m_hWnd, TBM_SETPOS, FALSE, 0L);
            }

            void ClearTics(BOOL bRedraw = FALSE)
            {
                ::SendMessage(m_hWnd, TBM_CLEARTICS, bRedraw, 0);
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSTDTRACKBAR_H_29188AB7_A7B8_4A70_9A7D_C4D30EE58540_INCLUDED__
