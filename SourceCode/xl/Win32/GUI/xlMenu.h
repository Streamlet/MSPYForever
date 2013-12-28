//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMenu.h
//    Author:      Streamlet
//    Create Time: 2011-05-08
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLMENU_H_AE31B303_4262_49A0_99BA_A03D67B0C6E5_INCLUDED__
#define __XLMENU_H_AE31B303_4262_49A0_99BA_A03D67B0C6E5_INCLUDED__


#include "xlMenuBase.h"
#include "xlWindowAPIMacroRedefine.h"

namespace xl
{
    class Menu : public MenuBase
    {
    public:
        Menu()
        {

        }

        Menu(HMENU hMenu) :
            MenuBase(hMenu)
        {

        }

        ~Menu()
        {

        }

    public: // Attributes

        HMENU GetHMENU()
        {
            return m_hMenu;
        }

        BOOL IsMenu()
        {
            return ::IsMenu(m_hMenu);
        }

    public: // Menu Operations

        BOOL DeleteMenu(UINT uPosition, UINT uFlags)
        {
            return ::DeleteMenu(m_hMenu, uPosition, uFlags);
        }

        BOOL TrackPopupMenu(UINT uFlags, int x, int y, HWND hWnd, LPCRECT lpRect = nullptr)
        {
            return ::TrackPopupMenu(m_hMenu, uFlags, x, y, 0, hWnd, lpRect);
        }

        BOOL TrackPopupMenuEx(UINT fuFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm)
        {
            return ::TrackPopupMenuEx(m_hMenu, fuFlags, x, y, hWnd, lptpm);
        }

#if(WINVER >= 0x0500)

        BOOL SetMenuInfo(LPCMENUINFO lpcmi)
        {
            return ::SetMenuInfo(m_hMenu, lpcmi);
        }

        BOOL GetMenuInfo(LPMENUINFO lpcmi)
        {
            return ::GetMenuInfo(m_hMenu, lpcmi);
        }

#endif

    public: // MenuItem Operations

        BOOL AppendMenu(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR lpNewItem)
        {
            return ::AppendMenu(m_hMenu, uFlags, uIDNewItem, lpNewItem);
        }

        DWORD CheckMenuItem(UINT uIDCheckItem, UINT uCheck)
        {
            return ::CheckMenuItem(m_hMenu, uIDCheckItem, uCheck);
        }

        BOOL EnableMenuItem(UINT uIDEnableItem, UINT uEnable)
        {
            return ::EnableMenuItem(m_hMenu, uIDEnableItem, uEnable);
        }

        int GetMenuItemCount()
        {
            return ::GetMenuItemCount(m_hMenu);
        }

        UINT GetMenuItemID(int nPos)
        {
            return ::GetMenuItemID(m_hMenu, nPos);
        }

        UINT GetMenuState(UINT uID, UINT uFlags)
        {
            return ::GetMenuState(m_hMenu, uID, uFlags);
        }

        int GetMenuString(UINT uIDItem, LPTSTR lpString, int cchMaxCount, UINT uFlags)
        {
            return ::GetMenuString(m_hMenu, uIDItem, lpString, cchMaxCount, uFlags);
        }

        BOOL GetMenuItemInfo(UINT uItem, BOOL fByPosition, LPMENUITEMINFO lpMenuItemInfo)
        {
            return ::GetMenuItemInfo(m_hMenu, uItem, fByPosition, lpMenuItemInfo);
        }

        BOOL SetMenuItemInfo(UINT uItem, BOOL fByPosition, LPMENUITEMINFO lpMenuItemInfo)
        {
            return ::SetMenuItemInfo(m_hMenu, uItem, fByPosition, lpMenuItemInfo);
        }

        HMENU GetSubMenu(int nPos)
        {
            return ::GetSubMenu(m_hMenu, nPos);
        }

        BOOL InsertMenuItem(UINT uItem, BOOL fByPosition, LPCMENUITEMINFO lpMenuItemInfo)
        {
            return ::InsertMenuItem(m_hMenu, uItem, fByPosition, lpMenuItemInfo);
        }

        BOOL ModifyMenu(UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR lpNewItem)
        {
            return ::ModifyMenu(m_hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
        }

        BOOL RemoveMenu(UINT uPosition, UINT uFlags)
        {
            return ::RemoveMenu(m_hMenu, uPosition, uFlags);
        }

        BOOL SetMenuItemBitmaps(UINT uPosition, UINT uFlags, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked)
        {
            return ::SetMenuItemBitmaps(m_hMenu, uPosition, uFlags, hBitmapUnchecked, hBitmapChecked);
        }

        BOOL CheckMenuRadioItem(UINT uIDFirst, UINT uIDLast, UINT uIDCheck, UINT uFlags)
        {
            return ::CheckMenuRadioItem(m_hMenu, uIDFirst, uIDLast, uIDCheck, uFlags);
        }

        BOOL SetMenuDefaultItem(UINT uItem, BOOL fByPos)
        {
            return ::SetMenuDefaultItem(m_hMenu, uItem, fByPos);
        }

        UINT GetMenuDefaultItem(BOOL fByPos, UINT gmdiFlags)
        {
            return ::GetMenuDefaultItem(m_hMenu, fByPos, gmdiFlags);
        }

    public: // Context Help Functions

        BOOL SetMenuContextHelpId(DWORD dwContextHelpId)
        {
            return ::SetMenuContextHelpId(m_hMenu, dwContextHelpId);
        }

        DWORD GetMenuContextHelpId()
        {
            return ::GetMenuContextHelpId(m_hMenu);
        }
    };

} // namespace xl

#endif // #ifndef __XLMENU_H_AE31B303_4262_49A0_99BA_A03D67B0C6E5_INCLUDED__
