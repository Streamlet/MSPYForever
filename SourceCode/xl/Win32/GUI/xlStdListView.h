//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlStdListView.h
//    Author:      Streamlet
//    Create Time: 2011-03-06
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSTDLISTVIEW_H_B10B42A8_92B6_4122_B473_8A529A3093FF_INCLUDED__
#define __XLSTDLISTVIEW_H_B10B42A8_92B6_4122_B473_8A529A3093FF_INCLUDED__


#include <xl/Win32/GUI/xlWindow.h>

namespace xl
{
    class StdListView : public Window
    {
    public:
        StdListView()
        {

        }

        StdListView(HWND hWnd) :
            Window(hWnd)
        {

        }

        ~StdListView()
        {

        }

    private:
        StdListView(const StdListView &);
        StdListView &operator =(const StdListView &);

    protected:
        static LPCTSTR GetClassName()
        {
            return STD_CONTROL_CLASSNAME_LISTVIEW;
        }

    public:
        bool Create(UINT nID,
                    Window *pParent,
                    int x = CW_USEDEFAULT,
                    int y = CW_USEDEFAULT,
                    int nWidth = CW_USEDEFAULT,
                    int nHeight = CW_USEDEFAULT,
                    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT,
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

        COLORREF GetBkColor()
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_GETBKCOLOR, 0, 0);
        }

        BOOL SetBkColor(COLORREF cr)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETBKCOLOR, 0, cr);
        }

        HIMAGELIST GetImageList(int nImageListType)
        {
            return (HIMAGELIST)::SendMessage(m_hWnd, LVM_GETIMAGELIST, nImageListType, 0);
        }

        HIMAGELIST SetImageList(HIMAGELIST hImageList, int nImageList)
        {
            return (HIMAGELIST)::SendMessage(m_hWnd, LVM_SETIMAGELIST, nImageList, (LPARAM)hImageList);
        }

        int GetItemCount()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETITEMCOUNT, 0, 0);
        }

        BOOL SetItemCount(int nItems)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMCOUNT, nItems, 0);
        }

        BOOL GetItem(LPLVITEM pItem)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)pItem);
        }

        BOOL SetItem(const LVITEM* pItem)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)pItem);
        }

        BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
                     int nImage, UINT nState, UINT nStateMask, LPARAM lParam)
        {
            LVITEM lvi = { 0 };
            lvi.mask = nMask;
            lvi.iItem = nItem;
            lvi.iSubItem = nSubItem;
            lvi.stateMask = nStateMask;
            lvi.state = nState;
            lvi.pszText = (LPTSTR) lpszItem;
            lvi.iImage = nImage;
            lvi.lParam = lParam;
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)&lvi);
        }
        
        UINT GetItemState(int nItem, UINT nMask)
        {
            return (UINT)::SendMessage(m_hWnd, LVM_GETITEMSTATE, nItem, nMask);
        }

        BOOL SetItemState(int nItem, UINT nState, UINT nStateMask)
        {
            LVITEM lvi = { 0 };
            lvi.state = nState;
            lvi.stateMask = nStateMask;
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
        }

        BOOL SetItemState(int nItem, LPLVITEM pItem)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMSTATE, nItem, (LPARAM)pItem);
        }

        int GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen)
        {
            LVITEM lvi = {};
            lvi.iSubItem = nSubItem;
            lvi.cchTextMax = nLen;
            lvi.pszText = lpszText;
            return (int)::SendMessage(m_hWnd, LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
        }

        BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
        {
            return SetItem(nItem, nSubItem, LVIF_TEXT, lpszText, 0, 0, 0, 0);
        }

        DWORD_PTR GetItemData(int nItem)
        {
            LVITEM lvi = {};
            lvi.iItem = nItem;
            lvi.mask = LVIF_PARAM;
            BOOL bRet = (BOOL)::SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)&lvi);
            return (DWORD_PTR)(bRet ? lvi.lParam : NULL);
        }

        BOOL SetItemData(int nItem, DWORD_PTR dwData)
        {
            return SetItem(nItem, 0, LVIF_PARAM, NULL, 0, 0, 0, (LPARAM)dwData);
        }

        UINT GetCallbackMask()
        {
            return (UINT)::SendMessage(m_hWnd, LVM_GETCALLBACKMASK, 0, 0);
        }

        BOOL SetCallbackMask(UINT nMask)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETCALLBACKMASK, nMask, 0);
        }

        BOOL GetItemPosition(int nItem, LPPOINT lpPoint)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETITEMPOSITION, nItem, (LPARAM)lpPoint);
        }

        BOOL SetItemPosition(int nItem, POINT pt)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMPOSITION32, nItem, (LPARAM)&pt);
        }

        BOOL SetItemPosition(int nItem, int x, int y)
        {
            POINT pt = { x, y };
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMPOSITION32, nItem, (LPARAM)&pt);
        }

        int GetStringWidth(LPCTSTR lpsz)
        {
            return (int)::SendMessage(m_hWnd, LVM_GETSTRINGWIDTH, 0, (LPARAM)lpsz);
        }

        HWND GetEditControl()
        {
            return (HWND)::SendMessage(m_hWnd, LVM_GETEDITCONTROL, 0, 0);
        }

        BOOL GetColumn(int nCol, LVCOLUMN *pColumn)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETCOLUMN, nCol, (LPARAM)pColumn);
        }

        BOOL SetColumn(int nCol, LVCOLUMN *pColumn)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETCOLUMN, nCol, (LPARAM)pColumn);
        }

        int GetColumnWidth(int nCol)
        {
            return (int)::SendMessage(m_hWnd, LVM_GETCOLUMNWIDTH, nCol, 0);
        }

        BOOL SetColumnWidth(int nCol, int cx)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETCOLUMNWIDTH, nCol, MAKELPARAM(cx, 0));
        }

        BOOL GetViewRect(LPRECT lpRect)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETVIEWRECT, 0, (LPARAM)lpRect);
        }

        COLORREF GetTextColor()
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_GETTEXTCOLOR, 0, 0);
        }

        BOOL SetTextColor(COLORREF cr)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETTEXTCOLOR, 0, cr);
        }

        COLORREF GetTextBkColor()
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_GETTEXTBKCOLOR, 0, 0);
        }

        BOOL SetTextBkColor(COLORREF cr)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETTEXTBKCOLOR, 0, cr);
        }

        int GetTopIndex()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETTOPINDEX, 0, 0);
        }

        int GetCountPerPage()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETCOUNTPERPAGE, 0, 0);
        }

        BOOL GetOrigin(LPPOINT lpPoint)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETORIGIN, 0, (LPARAM)lpPoint);
        }

        UINT GetSelectedCount()
        {
            return (UINT)::SendMessage(m_hWnd, LVM_GETSELECTEDCOUNT, 0, 0);
        }

        BOOL GetItemRect(int nItem, LPRECT lpRect, UINT nCode)
        {
            lpRect->left = nCode;
            return (BOOL)::SendMessage(m_hWnd, LVM_GETITEMRECT, (WPARAM)nItem, (LPARAM)lpRect);
        }

        HCURSOR GetHotCursor()
        {
            return (HCURSOR)::SendMessage(m_hWnd, LVM_GETHOTCURSOR, 0, 0);
        }

        HCURSOR SetHotCursor(HCURSOR hHotCursor)
        {
            return (HCURSOR)::SendMessage(m_hWnd, LVM_SETHOTCURSOR, 0, (LPARAM)hHotCursor);
        }

        int GetHotItem()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETHOTITEM, 0, 0);
        }

        int SetHotItem(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, LVM_SETHOTITEM, nIndex, 0);
        }

        BOOL GetColumnOrderArray(int nCount, int* lpnArray)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETCOLUMNORDERARRAY, nCount, (LPARAM)lpnArray);
        }

        BOOL SetColumnOrderArray(int nCount, int* lpnArray)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETCOLUMNORDERARRAY, nCount, (LPARAM)lpnArray);
        }

        HWND GetHeader()
        {
            return (HWND)::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0);
        }

        BOOL GetSubItemRect(int nItem, int nSubItem, int nFlag, LPRECT lpRect)
        {
            lpRect->top = nSubItem;
            lpRect->left = nFlag;
            return (BOOL)::SendMessage(m_hWnd, LVM_GETSUBITEMRECT, nItem, (LPARAM)lpRect);
        }

        DWORD SetIconSpacing(int cx, int cy)
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_SETICONSPACING, 0, MAKELPARAM(cx, cy));
        }

        int GetISearchString(LPTSTR lpstr)
        {
            return (int)::SendMessage(m_hWnd, LVM_GETISEARCHSTRING, 0, (LPARAM)lpstr);
        }

        DWORD GetItemSpacing(BOOL bSmallIconView = FALSE)
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_GETITEMSPACING, bSmallIconView, 0);
        }

    public: // single-selection only

        int GetSelectedIndex()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETNEXTITEM, (WPARAM)-1, MAKELPARAM(LVNI_ALL | LVNI_SELECTED, 0));
        }

        BOOL GetSelectedItem(LPLVITEM pItem)
        {
            pItem->iItem = (int)::SendMessage(m_hWnd, LVM_GETNEXTITEM, (WPARAM)-1, MAKELPARAM(LVNI_ALL | LVNI_SELECTED, 0));
            
            if(pItem->iItem == -1)
            {
                return FALSE;
            }

            return (BOOL)::SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)pItem);
        }

    public: // extended list view styles

        DWORD GetExtendedListViewStyle()
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
        }

        // dwExMask = 0 means all styles
        DWORD SetExtendedListViewStyle(DWORD dwExStyle, DWORD dwExMask = 0)
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, dwExMask, dwExStyle);
        }

    public: // checkboxes only

        BOOL GetCheckState(int nIndex)
        {
            UINT uRet = GetItemState(nIndex, LVIS_STATEIMAGEMASK);
            return (uRet >> 12) - 1;
        }

        BOOL SetCheckState(int nItem, BOOL bCheck)
        {
            int nCheck = bCheck ? 2 : 1;   // one based index
            return SetItemState(nItem, INDEXTOSTATEIMAGEMASK(nCheck), LVIS_STATEIMAGEMASK);
        }

    public:  // view type

        DWORD GetViewType()
        {
            return (GetStyle() & LVS_TYPEMASK);
        }

        DWORD SetViewType(DWORD dwType)
        {
            DWORD dwOldType = GetViewType();
            
            if(dwType != dwOldType)
            {
                ModifyStyle(LVS_TYPEMASK, (dwType & LVS_TYPEMASK));
            }

            return dwOldType;
        }

#if (_WIN32_IE >= 0x0400)

        BOOL GetBkImage(LPLVBKIMAGE plvbki)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETBKIMAGE, 0, (LPARAM)plvbki);
        }

        BOOL SetBkImage(LPLVBKIMAGE plvbki)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETBKIMAGE, 0, (LPARAM)plvbki);
        }

        int GetSelectionMark()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETSELECTIONMARK, 0, 0);
        }

        int SetSelectionMark(int nIndex)
        {
            return (int)::SendMessage(m_hWnd, LVM_SETSELECTIONMARK, 0, nIndex);
        }

        BOOL GetWorkAreas(int nWorkAreas, LPRECT lpRect)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETWORKAREAS, nWorkAreas, (LPARAM)lpRect);
        }

        BOOL SetWorkAreas(int nWorkAreas, LPRECT lpRect)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETWORKAREAS, nWorkAreas, (LPARAM)lpRect);
        }

        DWORD GetHoverTime()
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_GETHOVERTIME, 0, 0);
        }

        DWORD SetHoverTime(DWORD dwHoverTime)
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_SETHOVERTIME, 0, dwHoverTime);
        }

        BOOL GetNumberOfWorkAreas(int* pnWorkAreas)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)pnWorkAreas);
        }

        BOOL SetItemCountEx(int nItems, DWORD dwFlags)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMCOUNT, nItems, dwFlags);
        }

        HWND GetToolTips()
        {
            return (HWND)::SendMessage(m_hWnd, LVM_GETTOOLTIPS, 0, 0);
        }

        HWND SetToolTips(HWND hWndTT)
        {
            return (HWND)::SendMessage(m_hWnd, LVM_SETTOOLTIPS, (WPARAM)hWndTT, 0);
        }

        BOOL GetUnicodeFormat()
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETUNICODEFORMAT, 0, 0);
        }

        BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETUNICODEFORMAT, bUnicode, 0);
        }

#endif // (_WIN32_IE >= 0x0400)

#if (_WIN32_WINNT >= 0x0501)

        int GetSelectedColumn()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETSELECTEDCOLUMN, 0, 0);
        }

        void SetSelectedColumn(int nColumn)
        {
            ::SendMessage(m_hWnd, LVM_SETSELECTEDCOLUMN, nColumn, 0);
        }

        DWORD GetView()
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_GETVIEW, 0, 0);
        }

        int SetView(DWORD dwView)
        {
            return (int)::SendMessage(m_hWnd, LVM_SETVIEW, dwView, 0);
        }

        BOOL IsGroupViewEnabled()
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_ISGROUPVIEWENABLED, 0, 0);
        }

        int GetGroupInfo(int nGroupID, PLVGROUP pGroup)
        {
            return (int)::SendMessage(m_hWnd, LVM_GETGROUPINFO, nGroupID, (LPARAM)pGroup);
        }

        int SetGroupInfo(int nGroupID, PLVGROUP pGroup)
        {
            return (int)::SendMessage(m_hWnd, LVM_SETGROUPINFO, nGroupID, (LPARAM)pGroup);
        }

        void GetGroupMetrics(PLVGROUPMETRICS pGroupMetrics)
        {
            ::SendMessage(m_hWnd, LVM_GETGROUPMETRICS, 0, (LPARAM)pGroupMetrics);
        }

        void SetGroupMetrics(PLVGROUPMETRICS pGroupMetrics)
        {
            ::SendMessage(m_hWnd, LVM_SETGROUPMETRICS, 0, (LPARAM)pGroupMetrics);
        }

        void GetTileViewInfo(PLVTILEVIEWINFO pTileViewInfo)
        {
            ::SendMessage(m_hWnd, LVM_GETTILEVIEWINFO, 0, (LPARAM)pTileViewInfo);
        }

        BOOL SetTileViewInfo(PLVTILEVIEWINFO pTileViewInfo)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETTILEVIEWINFO, 0, (LPARAM)pTileViewInfo);
        }

        void GetTileInfo(PLVTILEINFO pTileInfo)
        {
            ::SendMessage(m_hWnd, LVM_GETTILEINFO, 0, (LPARAM)pTileInfo);
        }

        BOOL SetTileInfo(PLVTILEINFO pTileInfo)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETTILEINFO, 0, (LPARAM)pTileInfo);
        }

        BOOL GetInsertMark(LPLVINSERTMARK pInsertMark)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETINSERTMARK, 0, (LPARAM)pInsertMark);
        }

        BOOL SetInsertMark(LPLVINSERTMARK pInsertMark)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETINSERTMARK, 0, (LPARAM)pInsertMark);
        }

        int GetInsertMarkRect(LPRECT lpRect)
        {
            return (int)::SendMessage(m_hWnd, LVM_GETINSERTMARKRECT, 0, (LPARAM)lpRect);
        }

        COLORREF GetInsertMarkColor()
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_GETINSERTMARKCOLOR, 0, 0);
        }

        COLORREF SetInsertMarkColor(COLORREF clr)
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_SETINSERTMARKCOLOR, 0, clr);
        }

        COLORREF GetOutlineColor()
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_GETOUTLINECOLOR, 0, 0);
        }

        COLORREF SetOutlineColor(COLORREF clr)
        {
            return (COLORREF)::SendMessage(m_hWnd, LVM_SETOUTLINECOLOR, 0, clr);
        }

#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)

        int GetGroupCount()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETGROUPCOUNT, 0, 0);
        }

        BOOL GetGroupInfoByIndex(int nIndex, PLVGROUP pGroup)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETGROUPINFOBYINDEX, nIndex, (LPARAM)pGroup);
        }

        BOOL GetGroupRect(int nGroupID, int nType, LPRECT lpRect)
        {
            if(lpRect != NULL)
            {
                lpRect->top = nType;
            }

            return (BOOL)::SendMessage(m_hWnd, LVM_GETGROUPRECT, nGroupID, (LPARAM)lpRect);
        }

        UINT GetGroupState(int nGroupID, UINT uMask)
        {
            return (UINT)::SendMessage(m_hWnd, LVM_GETGROUPSTATE, nGroupID, (LPARAM)uMask);
        }

        int GetFocusedGroup()
        {
            return (int)::SendMessage(m_hWnd, LVM_GETFOCUSEDGROUP, 0, 0);
        }

        BOOL GetEmptyText(LPWSTR lpstrText, int cchText)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETEMPTYTEXT, cchText, (LPARAM)lpstrText);
        }

        BOOL GetFooterRect(LPRECT lpRect)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETFOOTERRECT, 0, (LPARAM)lpRect);
        }

        BOOL GetFooterInfo(LPLVFOOTERINFO lpFooterInfo)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETFOOTERINFO, 0, (LPARAM)lpFooterInfo);
        }

        BOOL GetFooterItemRect(int nItem, LPRECT lpRect)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETFOOTERITEMRECT, nItem, (LPARAM)lpRect);
        }

        BOOL GetFooterItem(int nItem, LPLVFOOTERITEM lpFooterItem)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETFOOTERITEM, nItem, (LPARAM)lpFooterItem);
        }

        BOOL GetItemIndexRect(PLVITEMINDEX pItemIndex, int nSubItem, int nType, LPRECT lpRect)
        {
            if(lpRect != NULL)
            {
                lpRect->top = nSubItem;
                lpRect->left = nType;
            }

            return (BOOL)::SendMessage(m_hWnd, LVM_GETITEMINDEXRECT, (WPARAM)pItemIndex, (LPARAM)lpRect);
        }

        BOOL SetItemIndexState(PLVITEMINDEX pItemIndex, UINT uState, UINT dwMask)
        {
            LVITEM lvi = { 0 };
            lvi.state = uState;
            lvi.stateMask = dwMask;
            return (BOOL)::SendMessage(m_hWnd, LVM_SETITEMINDEXSTATE, (WPARAM)pItemIndex, (LPARAM)&lvi);
        }

        BOOL GetNextItemIndex(PLVITEMINDEX pItemIndex, WORD wFlags)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_GETNEXTITEMINDEX, (WPARAM)pItemIndex, MAKELPARAM(wFlags, 0));
        }

#endif // (_WIN32_WINNT >= 0x0600)

    public: // Operations

        int InsertColumn(int nCol, LVCOLUMN* pColumn)
        {
            return (int)::SendMessage(m_hWnd, LVM_INSERTCOLUMN, nCol, (LPARAM)pColumn);
        }

        int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, 
            int nWidth = -1, int nSubItem = -1, int iImage = -1, int iOrder = -1)
        {
            LVCOLUMN column = { 0 };
            column.mask = LVCF_TEXT|LVCF_FMT;
            column.pszText = (LPTSTR)lpszColumnHeading;
            column.fmt = nFormat;

            if (nWidth != -1)
            {
                column.mask |= LVCF_WIDTH;
                column.cx = nWidth;
            }

            if (nSubItem != -1)
            {
                column.mask |= LVCF_SUBITEM;
                column.iSubItem = nSubItem;
            }

            if (iImage != -1)
            {
                column.mask |= LVCF_IMAGE;
                column.iImage = iImage;
            }

            if (iOrder != -1)
            {
                column.mask |= LVCF_ORDER;
                column.iOrder = iOrder;
            }

            return InsertColumn(nCol, &column);
        }

        BOOL DeleteColumn(int nCol)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_DELETECOLUMN, nCol, 0);
        }

        int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam)
        {
            LVITEM item = { 0 };
            item.mask = nMask;
            item.iItem = nItem;
            item.iSubItem = 0;
            item.pszText = (LPTSTR)lpszItem;
            item.state = nState;
            item.stateMask = nStateMask;
            item.iImage = nImage;
            item.lParam = lParam;
            return InsertItem(&item);
        }

        int InsertItem(const LVITEM* pItem)
        {
            return (int)::SendMessage(m_hWnd, LVM_INSERTITEM, 0, (LPARAM)pItem);
        }

        int InsertItem(int nItem, LPCTSTR lpszItem)
        {
            return InsertItem(LVIF_TEXT, nItem, lpszItem, 0, 0, 0, 0);
        }

        int InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
        {
            return InsertItem(LVIF_TEXT|LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, 0);
        }

        int GetNextItem(int nItem, int nFlags)
        {
            return (int)::SendMessage(m_hWnd, LVM_GETNEXTITEM, nItem, MAKELPARAM(nFlags, 0));
        }

        BOOL DeleteItem(int nItem)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_DELETEITEM, nItem, 0);
        }

        BOOL DeleteAllItems()
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_DELETEALLITEMS, 0, 0);
        }

        int FindItem(LVFINDINFO *pFindInfo, int nStart)
        {
            return (int)::SendMessage(m_hWnd, LVM_FINDITEM, nStart, (LPARAM)pFindInfo);
        }

        int HitTest(LVHITTESTINFO *pHitTestInfo)
        {
            return (int)::SendMessage(m_hWnd, LVM_HITTEST, 0, (LPARAM)pHitTestInfo);
        }

        int HitTest(POINT pt, UINT *pFlags)
        {
            LVHITTESTINFO hti = { 0 };
            hti.pt = pt;
            int nRes = (int)::SendMessage(m_hWnd, LVM_HITTEST, 0, (LPARAM)&hti);

            if (pFlags != NULL)
            {
                *pFlags = hti.flags;
            }

            return nRes;
        }

        BOOL EnsureVisible(int nItem, BOOL bPartialOK)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_ENSUREVISIBLE, nItem, MAKELPARAM(bPartialOK, 0));
        }

        BOOL Scroll(SIZE size)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SCROLL, size.cx, size.cy);
        }

        BOOL RedrawItems(int nFirst, int nLast)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_REDRAWITEMS, nFirst, nLast);
        }

        BOOL Arrange(UINT nCode)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_ARRANGE, nCode, 0);
        }

        HWND EditLabel(int nItem)
        {
            return (HWND)::SendMessage(m_hWnd, LVM_EDITLABEL, nItem, 0);
        }

        BOOL Update(int nItem)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_UPDATE, nItem, 0);
        }

        BOOL SortItems(PFNLVCOMPARE pfnCompare, LPARAM lParamSort)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SORTITEMS, (WPARAM)lParamSort, (LPARAM)pfnCompare);
        }

        HIMAGELIST RemoveImageList(int nImageList)
        {
            return (HIMAGELIST)::SendMessage(m_hWnd, LVM_SETIMAGELIST, (WPARAM)nImageList, NULL);
        }

        HIMAGELIST CreateDragImage(int nItem, LPPOINT lpPoint)
        {
            return (HIMAGELIST)::SendMessage(m_hWnd, LVM_CREATEDRAGIMAGE, nItem, (LPARAM)lpPoint);
        }

        DWORD ApproximateViewRect(int cx = -1, int cy = -1, int nCount = -1)
        {
            return (DWORD)::SendMessage(m_hWnd, LVM_APPROXIMATEVIEWRECT, nCount, MAKELPARAM(cx, cy));
        }

        int SubItemHitTest(LPLVHITTESTINFO lpInfo)
        {
            return (int)::SendMessage(m_hWnd, LVM_SUBITEMHITTEST, 0, (LPARAM)lpInfo);
        }

        int AddColumn(LPCTSTR strItem, int nItem, int nSubItem = -1,
            int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
            int nFmt = LVCFMT_LEFT)
        {
            int cxOffset = 15;

            LVCOLUMN lvc = { 0 };
            lvc.mask = nMask;
            lvc.fmt = nFmt;
            lvc.pszText = (LPTSTR)strItem;
            lvc.cx = GetStringWidth(lvc.pszText) + cxOffset;
            if(nMask & LVCF_SUBITEM)
            {
                lvc.iSubItem = (nSubItem != -1) ? nSubItem : nItem;
            }
            return InsertColumn(nItem, &lvc);
        }

        int AddItem(int nItem, int nSubItem, LPCTSTR strItem, int nImageIndex = -1)
        {
            LVITEM lvItem = { 0 };
            lvItem.mask = LVIF_TEXT;
            lvItem.iItem = nItem;
            lvItem.iSubItem = nSubItem;
            lvItem.pszText = (LPTSTR)strItem;

            if(nImageIndex != -1)
            {
                lvItem.mask |= LVIF_IMAGE;
                lvItem.iImage = nImageIndex;
            }

            if(nSubItem == 0)
            {
                return InsertItem(&lvItem);
            }

            return SetItem(&lvItem) ? nItem : -1;
        }

#if (_WIN32_IE >= 0x0500)

        BOOL SortItemsEx(PFNLVCOMPARE pfnCompare, LPARAM lParamSort)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SORTITEMSEX, (WPARAM)lParamSort, (LPARAM)pfnCompare);
        }

#endif // (_WIN32_IE >= 0x0500)

#if (_WIN32_WINNT >= 0x0501)

        int InsertGroup(int nItem, PLVGROUP pGroup)
        {
            return (int)::SendMessage(m_hWnd, LVM_INSERTGROUP, nItem, (LPARAM)pGroup);
        }

        int AddGroup(PLVGROUP pGroup)
        {
            return InsertGroup(-1, pGroup);
        }

        int RemoveGroup(int nGroupID)
        {
            return (int)::SendMessage(m_hWnd, LVM_REMOVEGROUP, nGroupID, 0);
        }

        void MoveGroup(int nGroupID, int nItem)
        {
            ::SendMessage(m_hWnd, LVM_MOVEGROUP, nGroupID, nItem);
        }

        void MoveItemToGroup(int nItem, int nGroupID)
        {
            ::SendMessage(m_hWnd, LVM_MOVEITEMTOGROUP, nItem, nGroupID);
        }

        int EnableGroupView(BOOL bEnable)
        {
            return (int)::SendMessage(m_hWnd, LVM_ENABLEGROUPVIEW, bEnable, 0);
        }

        int SortGroups(PFNLVGROUPCOMPARE pCompareFunc, LPVOID lpVoid = NULL)
        {
            return (int)::SendMessage(m_hWnd, LVM_SORTGROUPS, (WPARAM)pCompareFunc, (LPARAM)lpVoid);
        }

        void InsertGroupSorted(PLVINSERTGROUPSORTED pInsertGroupSorted)
        {
            ::SendMessage(m_hWnd, LVM_INSERTGROUPSORTED, (WPARAM)pInsertGroupSorted, 0);
        }

        void RemoveAllGroups()
        {
            ::SendMessage(m_hWnd, LVM_REMOVEALLGROUPS, 0, 0);
        }

        BOOL HasGroup(int nGroupID)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_HASGROUP, nGroupID, 0);
        }

        BOOL InsertMarkHitTest(LPPOINT lpPoint, LPLVINSERTMARK pInsertMark)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_INSERTMARKHITTEST, (WPARAM)lpPoint, (LPARAM)pInsertMark);
        }

        BOOL SetInfoTip(PLVSETINFOTIP pSetInfoTip)
        {
            return (BOOL)::SendMessage(m_hWnd, LVM_SETINFOTIP, 0, (LPARAM)pSetInfoTip);
        }

        void CancelEditLabel()
        {
            ::SendMessage(m_hWnd, LVM_CANCELEDITLABEL, 0, 0);
        }

        UINT MapIndexToID(int nIndex)
        {
            return (UINT)::SendMessage(m_hWnd, LVM_MAPINDEXTOID, nIndex, 0);
        }

        int MapIDToIndex(UINT uID)
        {
            return (int)::SendMessage(m_hWnd, LVM_MAPIDTOINDEX, uID, 0);
        }

#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)
        int HitTestEx(LPLVHITTESTINFO lpHitTestInfo)
        {
            return (int)::SendMessage(m_hWnd, LVM_HITTEST, (WPARAM)-1, (LPARAM)lpHitTestInfo);
        }

        int HitTestEx(POINT pt, UINT* pFlags)
        {
            LVHITTESTINFO hti = { 0 };
            hti.pt = pt;
            int nRes = (int)::SendMessage(m_hWnd, LVM_HITTEST, (WPARAM)-1, (LPARAM)&hti);
            
            if (pFlags != NULL)
            {
                *pFlags = hti.flags;
            }

            return nRes;
        }

        int SubItemHitTestEx(LPLVHITTESTINFO lpHitTestInfo)
        {
            return (int)::SendMessage(m_hWnd, LVM_SUBITEMHITTEST, (WPARAM)-1, (LPARAM)lpHitTestInfo);
        }

#endif // (_WIN32_WINNT >= 0x0600)

    public: // single-selection only

        BOOL SelectItem(int nIndex)
        {
            BOOL bRet = SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
            
            if(bRet)
            {
                bRet = EnsureVisible(nIndex, FALSE);
            }

            return bRet;
        }
    };

} // namespace xl

#endif // #ifndef __XLSTDLISTVIEW_H_B10B42A8_92B6_4122_B473_8A529A3093FF_INCLUDED__
