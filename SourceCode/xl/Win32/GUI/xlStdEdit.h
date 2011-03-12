//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdEdit.h
//    Author:      Streamlet
//    Create Time: 2011-02-27
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSTDEDIT_H_5CD8BC6E_A964_41C4_B01F_18F00DBB4A0E_INCLUDED__
#define __XLSTDEDIT_H_5CD8BC6E_A964_41C4_B01F_18F00DBB4A0E_INCLUDED__


#include <xl/Win32/GUI/xlWindow.h>

namespace xl
{
    class StdEdit : public Window
    {
    public:
        StdEdit()
        {

        }

        StdEdit(HWND hWnd) :
            Window(hWnd)
        {

        }

        ~StdEdit()
        {

        }

    private:
        StdEdit(const StdEdit &);
        StdEdit &operator =(const StdEdit &);

    protected:
        static LPCTSTR GetClassName()
        {
            return STD_CONTROL_CLASSNAME_EDIT;
        }

    public:
        bool Create(UINT nID,
                    Window *pParent,
                    int x = CW_USEDEFAULT,
                    int y = CW_USEDEFAULT,
                    int nWidth = CW_USEDEFAULT,
                    int nHeight = CW_USEDEFAULT,
                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL,
                    DWORD dwExStyle = WS_EX_CLIENTEDGE,
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

        BOOL CanUndo()
        {
            return (BOOL)::SendMessage(m_hWnd, EM_CANUNDO, 0, 0);
        }

        int GetLineCount()
        {
            return (int)::SendMessage(m_hWnd, EM_GETLINECOUNT, 0, 0);
        }

        BOOL GetModify()
        {
            return (BOOL)::SendMessage(m_hWnd, EM_GETMODIFY, 0, 0);
        }

        void SetModify(BOOL bModified = TRUE)
        {
            ::SendMessage(m_hWnd, EM_SETMODIFY, bModified, 0);
        }

        void GetRect(LPRECT lpRect)
        {
            ::SendMessage(m_hWnd, EM_GETRECT, 0, (LPARAM)lpRect);
        }

        DWORD GetSel()
        {
            return (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0);
        }

        void GetSel(int *pnStartChar, int *pnEndChar) const
        {
            ::SendMessage(m_hWnd, EM_GETSEL, (WPARAM)pnStartChar, (LPARAM)pnEndChar);
        }

        DWORD GetMargins() const
        {
            return (DWORD)::SendMessage(m_hWnd, EM_GETMARGINS, 0, 0);
        }

        void SetMargins(UINT nLeft, UINT nRight)
        {
            ::SendMessage(m_hWnd, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELONG(nLeft, nRight));
        }

        UINT GetLimitText() const
        {
            return (UINT)::SendMessage(m_hWnd, EM_GETLIMITTEXT, 0, 0);
        }

        void SetLimitText(UINT nMax)
        {
            ::SendMessage(m_hWnd, EM_SETLIMITTEXT, nMax, 0);
        }

        DWORD PosFromChar(UINT nChar) const
        {
            return (DWORD)::SendMessage(m_hWnd, EM_POSFROMCHAR, nChar, 0);
        }

        DWORD CharFromPos(int x, int y) const
        {
            return (DWORD)::SendMessage(m_hWnd, EM_CHARFROMPOS, 0, MAKELPARAM(x, y));
        }

        int GetLine(int nIndex, LPTSTR lpszBuffer, int nMaxLength) const
        {
            *(LPWORD)lpszBuffer = (WORD)nMaxLength;
            return (int)::SendMessage(m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
        }

        TCHAR GetPasswordChar() const
        {
            return (TCHAR)::SendMessage(m_hWnd, EM_GETPASSWORDCHAR, 0, 0);
        }

        void SetPasswordChar(TCHAR ch)
        {
            ::SendMessage(m_hWnd, EM_SETPASSWORDCHAR, ch, 0);
        }

        int GetFirstVisibleLine() const
        {
            return (int)::SendMessage(m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0);
        }

        BOOL SetReadOnly(BOOL bReadOnly = TRUE)
        {
            return (BOOL)::SendMessage(m_hWnd, EM_SETREADONLY, bReadOnly, 0);
        }

#if (WINVER >= 0x0500)

        UINT GetImeStatus(UINT uStatus) const
        {
            return (UINT)::SendMessage(m_hWnd, EM_GETIMESTATUS, uStatus, 0);
        }

        UINT SetImeStatus(UINT uStatus, UINT uData)
        {
            return (UINT)::SendMessage(m_hWnd, EM_SETIMESTATUS, uStatus, uData);
        }

#endif // (WINVER >= 0x0500)

#if (_WIN32_WINNT >= 0x0501)

        BOOL GetCueBannerText(LPCWSTR lpstrText, int cchText) const
        {
            return (BOOL)::SendMessage(m_hWnd, EM_GETCUEBANNER, (WPARAM)lpstrText, cchText);
        }

        // bKeepWithFocus - Vista only
        BOOL SetCueBannerText(LPCWSTR lpstrText, BOOL bKeepWithFocus = FALSE)
        {
            return (BOOL)::SendMessage(m_hWnd, EM_SETCUEBANNER, (WPARAM)bKeepWithFocus, (LPARAM)(lpstrText));
        }

#endif // (_WIN32_WINNT >= 0x0501)

    public: // Operations

        void EmptyUndoBuffer()
        {
            ::SendMessage(m_hWnd, EM_EMPTYUNDOBUFFER, 0, 0);
        }

        BOOL FmtLines(BOOL bAddEOL)
        {
            return (BOOL)::SendMessage(m_hWnd, EM_FMTLINES, bAddEOL, 0);
        }

        void LimitText(int nChars = 0)
        {
            ::SendMessage(m_hWnd, EM_LIMITTEXT, nChars, 0);
        }

        int LineFromChar(int nIndex = -1) const
        {
            return (int)::SendMessage(m_hWnd, EM_LINEFROMCHAR, nIndex, 0);
        }

        int LineIndex(int nLine = -1) const
        {
            return (int)::SendMessage(m_hWnd, EM_LINEINDEX, nLine, 0);
        }

        int LineLength(int nLine = -1) const
        {
            return (int)::SendMessage(m_hWnd, EM_LINELENGTH, nLine, 0);
        }

        void LineScroll(int nLines, int nChars = 0)
        {
            ::SendMessage(m_hWnd, EM_LINESCROLL, nChars, nLines);
        }

        void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE)
        {
            ::SendMessage(m_hWnd, EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
        }

        void SetRect(LPCRECT lpRect)
        {
            ::SendMessage(m_hWnd, EM_SETRECT, 0, (LPARAM)lpRect);
        }

        void SetRectNP(LPCRECT lpRect)
        {
            ::SendMessage(m_hWnd, EM_SETRECTNP, 0, (LPARAM)lpRect);
        }

        void SetSel(DWORD dwSelection, BOOL bNoScroll = FALSE)
        {
            ::SendMessage(m_hWnd, EM_SETSEL, LOWORD(dwSelection), HIWORD(dwSelection));

            if(!bNoScroll)
            {
                ::SendMessage(m_hWnd, EM_SCROLLCARET, 0, 0);
            }
        }

        void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE)
        {
            ::SendMessage(m_hWnd, EM_SETSEL, nStartChar, nEndChar);

            if(!bNoScroll)
            {
                ::SendMessage(m_hWnd, EM_SCROLLCARET, 0, 0);
            }
        }

        void SetSelAll(BOOL bNoScroll = FALSE)
        {
            SetSel(0, -1, bNoScroll);
        }

        void SetSelNone(BOOL bNoScroll = FALSE)
        {
            SetSel(-1, 0, bNoScroll);
        }

        BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
        {
            return (BOOL)::SendMessage(m_hWnd, EM_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
        }

        BOOL SetTabStops()
        {
            return (BOOL)::SendMessage(m_hWnd, EM_SETTABSTOPS, 0, 0);
        }

        BOOL SetTabStops(const int &cxEachStop)    // takes an 'int'
        {
            return (BOOL)::SendMessage(m_hWnd, EM_SETTABSTOPS, 1, (LPARAM)(LPINT)&cxEachStop);
        }

        void ScrollCaret()
        {
            ::SendMessage(m_hWnd, EM_SCROLLCARET, 0, 0);
        }

        DWORD Scroll(int nScrollAction)
        {
            return (DWORD)::SendMessage(m_hWnd, EM_SCROLL, nScrollAction, 0);
        }

        void InsertText(int nInsertAfterChar, LPCTSTR lpstrText, BOOL bNoScroll = FALSE, BOOL bCanUndo = FALSE)
        {
            SetSel(nInsertAfterChar, nInsertAfterChar, bNoScroll);
            ReplaceSel(lpstrText, bCanUndo);
        }

        void AppendText(LPCTSTR lpstrText, BOOL bNoScroll = FALSE, BOOL bCanUndo = FALSE)
        {
            InsertText(GetWindowTextLength(), lpstrText, bNoScroll, bCanUndo);
        }

#if (_WIN32_WINNT >= 0x0501)

        BOOL ShowBalloonTip(PEDITBALLOONTIP pEditBaloonTip)
        {
            return (BOOL)::SendMessage(m_hWnd, EM_SHOWBALLOONTIP, 0, (LPARAM)pEditBaloonTip);
        }

        BOOL HideBalloonTip()
        {
            return (BOOL)::SendMessage(m_hWnd, EM_HIDEBALLOONTIP, 0, 0);
        }

#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)

        DWORD GetHilight()
        {
            return (DWORD)::SendMessage(m_hWnd, EM_GETHILITE, 0, 0);
        }

        void SetHilight(int nStartChar, int nEndChar)
        {
            ::SendMessage(m_hWnd, EM_SETHILITE, nStartChar, nEndChar);
        }

#endif // (_WIN32_WINNT >= 0x0600)

    public: // Clipboard operations

        BOOL Undo()
        {
            return (BOOL)::SendMessage(m_hWnd, EM_UNDO, 0, 0);
        }

        void Clear()
        {
            ::SendMessage(m_hWnd, WM_CLEAR, 0, 0);
        }

        void Copy()
        {
            ::SendMessage(m_hWnd, WM_COPY, 0, 0);
        }

        void Cut()
        {
            ::SendMessage(m_hWnd, WM_CUT, 0, 0);
        }

        void Paste()
        {
            ::SendMessage(m_hWnd, WM_PASTE, 0, 0);
        }
    };

} // namespace xl

#endif // #ifndef __XLSTDEDIT_H_5CD8BC6E_A964_41C4_B01F_18F00DBB4A0E_INCLUDED__
