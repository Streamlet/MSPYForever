//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdScrollBar.h
//    Author:      Streamlet
//    Create Time: 2011-03-04
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSTDSCROLLBAR_H_CE421D01_3A90_4DFA_A59F_74C911033E2A_INCLUDED__
#define __XLSTDSCROLLBAR_H_CE421D01_3A90_4DFA_A59F_74C911033E2A_INCLUDED__


#include <xl/Win32/GUI/xlWindow.h>

namespace xl
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

    private:
        StdScrollBar(const StdScrollBar &);
        StdScrollBar &operator =(const StdScrollBar &);

    protected:
        static LPCTSTR GetClassName()
        {
            return STD_CONTROL_CLASSNAME_SCROLLBAR;
        }

    public:
        bool Create(UINT nID,
                    Window *pParent,
                    int x = CW_USEDEFAULT,
                    int y = CW_USEDEFAULT,
                    int nWidth = CW_USEDEFAULT,
                    int nHeight = CW_USEDEFAULT,
                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | SBS_VERT,
                    DWORD dwExStyle = 0,
                    HINSTANCE hInstance = nullptr)
        {
            if (!Window::Create(x,
                                y,
                                nWidth,
                                nHeight,
                                pParent,
                                GetClassName(),
                                dwStyle,
                                dwExStyle,
                                (HMENU)nID,
                                hInstance))
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

} // namespace xl

#endif // #ifndef __XLSTDSCROLLBAR_H_CE421D01_3A90_4DFA_A59F_74C911033E2A_INCLUDED__
