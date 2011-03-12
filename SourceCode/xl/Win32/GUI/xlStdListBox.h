//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdListBox.h
//    Author:      Streamlet
//    Create Time: 2011-03-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSTDLISTBOX_H_76D859F1_40EE_4ABE_B0F0_6A0CFB8865F8_INCLUDED__
#define __XLSTDLISTBOX_H_76D859F1_40EE_4ABE_B0F0_6A0CFB8865F8_INCLUDED__


#include <xl/Win32/GUI/xlWindow.h>

namespace xl
{
    class StdListBox : public Window
    {
    public:
        StdListBox()
        {

        }

        StdListBox(HWND hWnd) :
            Window(hWnd)
        {

        }

        ~StdListBox()
        {

        }

    private:
        StdListBox(const StdListBox &);
        StdListBox &operator =(const StdListBox &);

    protected:
        static LPCTSTR GetClassName()
        {
            return STD_CONTROL_CLASSNAME_LISTBOX;
        }

    public:
        bool Create(UINT nID,
                    Window *pParent,
                    int x = CW_USEDEFAULT,
                    int y = CW_USEDEFAULT,
                    int nWidth = CW_USEDEFAULT,
                    int nHeight = CW_USEDEFAULT,
                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | LBS_NOTIFY | WS_VSCROLL,
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

    public: // for entire listbox

        int GetCount()
        {
            return (int)::SendMessage(m_hWnd, LB_GETCOUNT, 0, 0);
        }

        int GetHorizontalExtent()
        {
            return (int)::SendMessage(m_hWnd, LB_GETHORIZONTALEXTENT, 0, 0);
        }

        void SetHorizontalExtent(int cxExtent)
        {
            ::SendMessage(m_hWnd, LB_SETHORIZONTALEXTENT, cxExtent, 0);
        }

        int GetTopIndex()
        {
            return (int)::SendMessage(m_hWnd, LB_GETTOPINDEX, 0, 0);
        }

        int SetTopIndex(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, LB_SETTOPINDEX, nIndex, 0);
        }

        LCID GetLocale()
        {
            return (LCID)::SendMessage(m_hWnd, LB_GETLOCALE, 0, 0);
        }

        LCID SetLocale(LCID nNewLocale)
        {
            return (LCID)::SendMessage(m_hWnd, LB_SETLOCALE, (WPARAM)nNewLocale, 0);
        }

#if (WINVER >= 0x0500)

        DWORD GetListBoxInfo()
        {
#if (_WIN32_WINNT >= 0x0501)
            return (DWORD)::SendMessage(m_hWnd, LB_GETLISTBOXINFO, 0, 0);
#else // !(_WIN32_WINNT >= 0x0501)
            return ::GetListBoxInfo(m_hWnd);
#endif // !(_WIN32_WINNT >= 0x0501)
        }

#endif // (WINVER >= 0x0500)

    public: // for single-selection listboxes

        int GetCurSel()
        {
            return (int)::SendMessage(m_hWnd, LB_GETCURSEL, 0, 0);
        }

        int SetCurSel(int nSelect)
        {
            return (int)::SendMessage(m_hWnd, LB_SETCURSEL, nSelect, 0);
        }

    public: // for multiple-selection listboxes

        int GetSel(int nIndex)  // also works for single-selection
        {
            return (int)::SendMessage(m_hWnd, LB_GETSEL, nIndex, 0);
        }

        int SetSel(int nIndex, BOOL bSelect = TRUE)
        {
            return (int)::SendMessage(m_hWnd, LB_SETSEL, bSelect, nIndex);
        }

        int GetSelCount()
        {
            return (int)::SendMessage(m_hWnd, LB_GETSELCOUNT, 0, 0);
        }

        int GetSelItems(int nMaxItems, LPINT rgIndex)
        {
            return (int)::SendMessage(m_hWnd, LB_GETSELITEMS, nMaxItems, (LPARAM)rgIndex);
        }

        int GetAnchorIndex()
        {
            return (int)::SendMessage(m_hWnd, LB_GETANCHORINDEX, 0, 0);
        }

        void SetAnchorIndex(int nIndex)
        {
            ::SendMessage(m_hWnd, LB_SETANCHORINDEX, nIndex, 0);
        }

        int GetCaretIndex()
        {
            return (int)::SendMessage(m_hWnd, LB_GETCARETINDEX, 0, 0);
        }

        int SetCaretIndex(int nIndex, BOOL bScroll = TRUE)
        {
            return (int)::SendMessage(m_hWnd, LB_SETCARETINDEX, nIndex, MAKELONG(bScroll, 0));
        }

    public: // for listbox items

        DWORD_PTR GetItemData(int nIndex)
        {
            return (DWORD_PTR)::SendMessage(m_hWnd, LB_GETITEMDATA, nIndex, 0);
        }

        int SetItemData(int nIndex, DWORD_PTR dwItemData)
        {
            return (int)::SendMessage(m_hWnd, LB_SETITEMDATA, nIndex, (LPARAM)dwItemData);
        }

        void *GetItemDataPtr(int nIndex)
        {
            return (void *)::SendMessage(m_hWnd, LB_GETITEMDATA, nIndex, 0);
        }

        int SetItemDataPtr(int nIndex, void* pData)
        {
            return SetItemData(nIndex, (DWORD_PTR)pData);
        }

        int GetItemRect(int nIndex, LPRECT lpRect)
        {
            return (int)::SendMessage(m_hWnd, LB_GETITEMRECT, nIndex, (LPARAM)lpRect);
        }

        int GetText(int nIndex, LPTSTR lpszBuffer)
        {
            return (int)::SendMessage(m_hWnd, LB_GETTEXT, nIndex, (LPARAM)lpszBuffer);
        }

        int GetTextLen(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, LB_GETTEXTLEN, nIndex, 0);
        }

        int GetItemHeight(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, LB_GETITEMHEIGHT, nIndex, 0);
        }

        int SetItemHeight(int nIndex, UINT cyItemHeight)
        {
            return (int)::SendMessage(m_hWnd, LB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));
        }

    public: // Settable only attributes

        void SetColumnWidth(int cxWidth)
        {
            ::SendMessage(m_hWnd, LB_SETCOLUMNWIDTH, cxWidth, 0);
        }

        BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
        {
            return (BOOL)::SendMessage(m_hWnd, LB_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
        }

        BOOL SetTabStops()
        {
            return (BOOL)::SendMessage(m_hWnd, LB_SETTABSTOPS, 0, 0);
        }

        BOOL SetTabStops(const int &cxEachStop)    // takes an 'int'
        {
            return (BOOL)::SendMessage(m_hWnd, LB_SETTABSTOPS, 1, (LPARAM)(LPINT)&cxEachStop);
        }

    public: // Operations

        int InitStorage(int nItems, UINT nBytes)
        {
            return (int)::SendMessage(m_hWnd, LB_INITSTORAGE, (WPARAM)nItems, nBytes);
        }

        void ResetContent()
        {
            ::SendMessage(m_hWnd, LB_RESETCONTENT, 0, 0);
        }

        DWORD ItemFromPoint(int x, int y)
        {
            return (DWORD)::SendMessage(m_hWnd, LB_ITEMFROMPOINT, 0, MAKELPARAM(x, y));
        }

    public: // manipulating listbox items

        int AddString(LPCTSTR lpszItem)
        {
            return (int)::SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)lpszItem);
        }

        int DeleteString(UINT nIndex)
        {
            return (int)::SendMessage(m_hWnd, LB_DELETESTRING, nIndex, 0);
        }

        int InsertString(int nIndex, LPCTSTR lpszItem)
        {
            return (int)::SendMessage(m_hWnd, LB_INSERTSTRING, nIndex, (LPARAM)lpszItem);
        }

    public: // selection helpers

        int FindString(int nStartAfter, LPCTSTR lpszItem)
        {
            return (int)::SendMessage(m_hWnd, LB_FINDSTRING, nStartAfter, (LPARAM)lpszItem);
        }

        int FindStringExact(int nIndexStart, LPCTSTR lpszFind)
        {
            return (int)::SendMessage(m_hWnd, LB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind);
        }

        int SelectString(int nStartAfter, LPCTSTR lpszItem)
        {
            return (int)::SendMessage(m_hWnd, LB_SELECTSTRING, nStartAfter, (LPARAM)lpszItem);
        }

        int SelItemRange(BOOL bSelect, int nFirstItem, int nLastItem)
        {
            return bSelect ? (int)::SendMessage(m_hWnd, LB_SELITEMRANGEEX, nFirstItem, nLastItem) : (int)::SendMessage(m_hWnd, LB_SELITEMRANGEEX, nLastItem, nFirstItem);
        }
    };

} // namespace xl

#endif // #ifndef __XLSTDLISTBOX_H_76D859F1_40EE_4ABE_B0F0_6A0CFB8865F8_INCLUDED__
