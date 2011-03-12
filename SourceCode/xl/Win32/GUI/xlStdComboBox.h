//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdComboBox.h
//    Author:      Streamlet
//    Create Time: 2011-02-27
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSTDCOMBOBOX_H_D16DAB9C_78E5_4C3F_89B2_6FDFC33E8B97_INCLUDED__
#define __XLSTDCOMBOBOX_H_D16DAB9C_78E5_4C3F_89B2_6FDFC33E8B97_INCLUDED__


#include <xl/Win32/GUI/xlWindow.h>

namespace xl
{
    class StdComboBox : public Window
    {
    public:
        StdComboBox()
        {

        }

        StdComboBox(HWND hWnd) :
            Window(hWnd)
        {

        }

        ~StdComboBox()
        {

        }

    private:
        StdComboBox(const StdComboBox &);
        StdComboBox &operator =(const StdComboBox &);

    protected:
        static LPCTSTR GetClassName()
        {
            return STD_CONTROL_CLASSNAME_COMBOBOX;
        }

    public:
        bool Create(UINT nID,
                    Window *pParent,
                    int x = CW_USEDEFAULT,
                    int y = CW_USEDEFAULT,
                    int nWidth = CW_USEDEFAULT,
                    int nHeight = CW_USEDEFAULT,
                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST,
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

    public: // for entire combo box

        int GetCount()
        {
            return (int)::SendMessage(m_hWnd, CB_GETCOUNT, 0, 0);
        }

        int GetCurSel()
        {
            return (int)::SendMessage(m_hWnd, CB_GETCURSEL, 0, 0);
        }

        int SetCurSel(int nSelect)
        {
            return (int)::SendMessage(m_hWnd, CB_SETCURSEL, nSelect, 0);
        }

        LCID GetLocale()
        {
            return (LCID)::SendMessage(m_hWnd, CB_GETLOCALE, 0, 0);
        }

        LCID SetLocale(LCID nNewLocale)
        {
            return (LCID)::SendMessage(m_hWnd, CB_SETLOCALE, (WPARAM)nNewLocale, 0);
        }

        int GetTopIndex()
        {
            return (int)::SendMessage(m_hWnd, CB_GETTOPINDEX, 0, 0);
        }

        int SetTopIndex(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, CB_SETTOPINDEX, nIndex, 0);
        }

        UINT GetHorizontalExtent()
        {
            return (UINT)::SendMessage(m_hWnd, CB_GETHORIZONTALEXTENT, 0, 0);
        }

        void SetHorizontalExtent(UINT nExtent)
        {
            ::SendMessage(m_hWnd, CB_SETHORIZONTALEXTENT, nExtent, 0);
        }

        int GetDroppedWidth()
        {
            return (int)::SendMessage(m_hWnd, CB_GETDROPPEDWIDTH, 0, 0);
        }

        int SetDroppedWidth(UINT nWidth)
        {
            return (int)::SendMessage(m_hWnd, CB_SETDROPPEDWIDTH, nWidth, 0);
        }

#if (WINVER >= 0x0500)
        BOOL GetComboBoxInfo(PCOMBOBOXINFO pComboBoxInfo)
        {
#if (_WIN32_WINNT >= 0x0501)
            return (BOOL)::SendMessage(m_hWnd, CB_GETCOMBOBOXINFO, 0, (LPARAM)pComboBoxInfo);
#else // !(_WIN32_WINNT >= 0x0501)
            return ::GetComboBoxInfo(m_hWnd, pComboBoxInfo);
#endif // !(_WIN32_WINNT >= 0x0501)
        }
#endif // (WINVER >= 0x0500)

    public: // for edit control

        DWORD GetEditSel()
        {
            return (DWORD)::SendMessage(m_hWnd, CB_GETEDITSEL, 0, 0);
        }

        BOOL SetEditSel(int nStartChar, int nEndChar)
        {
            return (BOOL)::SendMessage(m_hWnd, CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar));
        }

    public: // for combobox item

        DWORD_PTR GetItemData(int nIndex)
        {
            return (DWORD_PTR)::SendMessage(m_hWnd, CB_GETITEMDATA, nIndex, 0);
        }

        int SetItemData(int nIndex, DWORD_PTR dwItemData)
        {
            return (int)::SendMessage(m_hWnd, CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);
        }

        void *GetItemDataPtr(int nIndex)
        {
            return (void *)GetItemData(nIndex);
        }

        int SetItemDataPtr(int nIndex, void *pData)
        {
            return SetItemData(nIndex, (DWORD_PTR)pData);
        }

        int GetLBText(int nIndex, LPTSTR lpszText)
        {
            return (int)::SendMessage(m_hWnd, CB_GETLBTEXT, nIndex, (LPARAM)lpszText);
        }

        int GetLBTextLen(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, CB_GETLBTEXTLEN, nIndex, 0);
        }

        int GetItemHeight(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, CB_GETITEMHEIGHT, nIndex, 0);
        }

        int SetItemHeight(int nIndex, UINT cyItemHeight)
        {
            return (int)::SendMessage(m_hWnd, CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));
        }

        BOOL GetExtendedUI()
        {
            return (BOOL)::SendMessage(m_hWnd, CB_GETEXTENDEDUI, 0, 0);
        }

        int SetExtendedUI(BOOL bExtended = TRUE)
        {
            return (int)::SendMessage(m_hWnd, CB_SETEXTENDEDUI, bExtended, 0);
        }

        void GetDroppedControlRect(LPRECT lprect)
        {
            ::SendMessage(m_hWnd, CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)lprect);
        }

        BOOL GetDroppedState()
        {
            return (BOOL)::SendMessage(m_hWnd, CB_GETDROPPEDSTATE, 0, 0);
        }

#if (_WIN32_WINNT >= 0x0501)

        int GetMinVisible()
        {
            return (int)::SendMessage(m_hWnd, CB_GETMINVISIBLE, 0, 0);
        }

        BOOL SetMinVisible(int nMinVisible)
        {
            return (BOOL)::SendMessage(m_hWnd, CB_SETMINVISIBLE, nMinVisible, 0);
        }

#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)

        BOOL GetCueBannerText(LPWSTR lpwText, int cchText)
        {
            return (BOOL)::SendMessage(m_hWnd, CB_GETCUEBANNER, (WPARAM)lpwText, cchText);
        }

        BOOL SetCueBannerText(LPCWSTR lpcwText)
        {
            return (BOOL)::SendMessage(m_hWnd, CB_SETCUEBANNER, 0, (LPARAM)lpcwText);
        }

#endif // (_WIN32_WINNT >= 0x0600)

    public: // Operations

        int InitStorage(int nItems, UINT nBytes)
        {
            return (int)::SendMessage(m_hWnd, CB_INITSTORAGE, (WPARAM)nItems, nBytes);
        }

        void ResetContent()
        {
            ::SendMessage(m_hWnd, CB_RESETCONTENT, 0, 0);
        }

    public: // for edit control

        BOOL LimitText(int nMaxChars)
        {
            return (BOOL)::SendMessage(m_hWnd, CB_LIMITTEXT, nMaxChars, 0);
        }

    public: // for drop-down combo boxes

        void ShowDropDown(BOOL bShowIt = TRUE)
        {
            ::SendMessage(m_hWnd, CB_SHOWDROPDOWN, bShowIt, 0);
        }

    public: // manipulating listbox items

        int AddString(LPCTSTR lpszString)
        {
            return (int)::SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)lpszString);
        }

        int DeleteString(UINT nIndex)
        {
            return (int)::SendMessage(m_hWnd, CB_DELETESTRING, nIndex, 0);
        }

        int InsertString(int nIndex, LPCTSTR lpszString)
        {
            return (int)::SendMessage(m_hWnd, CB_INSERTSTRING, nIndex, (LPARAM)lpszString);
        }

    public:  // selection helpers

        int FindString(int nStartAfter, LPCTSTR lpszString)
        {
            return (int)::SendMessage(m_hWnd, CB_FINDSTRING, nStartAfter, (LPARAM)lpszString);
        }

        int FindStringExact(int nIndexStart, LPCTSTR lpszFind)
        {
            return (int)::SendMessage(m_hWnd, CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind);
        }

        int SelectString(int nStartAfter, LPCTSTR lpszString)
        {
            return (int)::SendMessage(m_hWnd, CB_SELECTSTRING, nStartAfter, (LPARAM)lpszString);
        }

    public:  // Clipboard operations

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

#endif // #ifndef __XLSTDCOMBOBOX_H_D16DAB9C_78E5_4C3F_89B2_6FDFC33E8B97_INCLUDED__
