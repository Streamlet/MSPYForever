//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdButton.h
//    Author:      Streamlet
//    Create Time: 2011-02-21
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSTDBUTTON_H_A3754322_DF44_433F_847E_1A4FE4CA46F7_INCLUDED__
#define __XLSTDBUTTON_H_A3754322_DF44_433F_847E_1A4FE4CA46F7_INCLUDED__


#include "xlWindow.h"

namespace xl
{
    namespace Windows
    {
        class StdButton : public Window
        {
        public:
            StdButton()
            {

            }

            StdButton(HWND hWnd) :
                Window(hWnd)
            {

            }

            ~StdButton()
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
                                    WC_BUTTON,
                                    nullptr,
                                    (HMENU)(size_t)nID,
                                    nullptr))
                {
                    return false;
                }

                return true;
            }

        public: // Attributes

            UINT GetState() const
            {
                return (UINT)::SendMessage(m_hWnd, BM_GETSTATE, 0, 0);
            }

            void SetState(BOOL bHighlight)
            {
                ::SendMessage(m_hWnd, BM_SETSTATE, bHighlight, 0);
            }

            int GetCheck() const
            {
                return (int)::SendMessage(m_hWnd, BM_GETCHECK, 0, 0);
            }

            void SetCheck(int nCheck)
            {
                ::SendMessage(m_hWnd, BM_SETCHECK, nCheck, 0);
            }

            UINT GetButtonStyle() const
            {
                return (UINT)::GetWindowLong(m_hWnd, GWL_STYLE) & 0xFFFF;
            }

            void SetButtonStyle(UINT nStyle, BOOL bRedraw = TRUE)
            {
                ::SendMessage(m_hWnd, BM_SETSTYLE, nStyle, (LPARAM)bRedraw);
            }

            HICON GetIcon() const
            {
                return (HICON)::SendMessage(m_hWnd, BM_GETIMAGE, IMAGE_ICON, 0);
            }

            HICON SetIcon(HICON hIcon)
            {
                return (HICON)::SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
            }

            HBITMAP GetBitmap() const
            {
                return (HBITMAP)::SendMessage(m_hWnd, BM_GETIMAGE, IMAGE_BITMAP, 0);
            }

            HBITMAP SetBitmap(HBITMAP hBitmap)
            {
                return (HBITMAP)::SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
            }

#if (_WIN32_WINNT >= 0x0501)

            BOOL GetIdealSize(LPSIZE lpSize) const
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_GETIDEALSIZE, 0, (LPARAM)lpSize);
            }

            BOOL GetImageList(PBUTTON_IMAGELIST pButtonImagelist)
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_GETIMAGELIST, 0, (LPARAM)pButtonImagelist);
            }

            BOOL SetImageList(PBUTTON_IMAGELIST pButtonImagelist)
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_SETIMAGELIST, 0, (LPARAM)pButtonImagelist);
            }

            BOOL GetTextMargin(LPRECT lpRect) const
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_GETTEXTMARGIN, 0, (LPARAM)lpRect);
            }

            BOOL SetTextMargin(LPRECT lpRect)
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_SETTEXTMARGIN, 0, (LPARAM)lpRect);
            }

#endif // (_WIN32_WINNT >= 0x0501)

#if (WINVER >= 0x0600)

            void SetDontClick(BOOL bDontClick)
            {
                ::SendMessage(m_hWnd, BM_SETDONTCLICK, (WPARAM)bDontClick, 0);
            }
#endif // (WINVER >= 0x0600)

#if (_WIN32_WINNT >= 0x0600)

            BOOL SetDropDownState(BOOL bDropDown)
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_SETDROPDOWNSTATE, (WPARAM)bDropDown, 0);
            }

            BOOL GetSplitInfo(PBUTTON_SPLITINFO pSplitInfo) const
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_GETSPLITINFO, 0, (LPARAM)pSplitInfo);
            }

            BOOL SetSplitInfo(PBUTTON_SPLITINFO pSplitInfo)
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_SETSPLITINFO, 0, (LPARAM)pSplitInfo);
            }

            int GetNoteLength() const
            {
                return (int)::SendMessage(m_hWnd, BCM_GETNOTELENGTH, 0, 0);
            }

            BOOL GetNote(LPWSTR lpstrNoteText, int cchNoteText) const
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_GETNOTE, cchNoteText, (LPARAM)lpstrNoteText);
            }

            BOOL SetNote(LPCWSTR lpstrNoteText)
            {
                return (BOOL)::SendMessage(m_hWnd, BCM_SETNOTE, 0, (LPARAM)lpstrNoteText);
            }

            LRESULT SetElevationRequiredState(BOOL bSet)
            {
                return ::SendMessage(m_hWnd, BCM_SETSHIELD, 0, (LPARAM)bSet);
            }

#endif // (_WIN32_WINNT >= 0x0600)

        public: // Operations

            void Click()
            {
                ::SendMessage(m_hWnd, BM_CLICK, 0, 0);
            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSTDBUTTON_H_A3754322_DF44_433F_847E_1A4FE4CA46F7_INCLUDED__
