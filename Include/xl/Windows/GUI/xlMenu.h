//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMenu.h
//    Author:      Streamlet
//    Create Time: 2011-05-08
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMENU_H_C208C619_17E7_4147_BBFD_C815FAFA7324_INCLUDED__
#define __XLMENU_H_C208C619_17E7_4147_BBFD_C815FAFA7324_INCLUDED__


#include "../../Common/Meta/xlNonCopyable.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class Menu : public NonCopyable
        {
        public:
            Menu() :
                m_hMenu(nullptr)
            {

            }

            Menu(HMENU hMenu) :
                m_hMenu(nullptr)
            {
                Attach(hMenu);
            }

            ~Menu()
            {
                Destroy();
                Detach();
            }

            bool Create()
            {
                if (m_hMenu != nullptr)
                {
                    return false;
                }

                m_hMenu = CreateMenu();

                if (m_hMenu == nullptr)
                {
                    return false;
                }

                return true;
            }

            bool CreatePopup()
            {
                if (m_hMenu != nullptr)
                {
                    return false;
                }

                m_hMenu = CreatePopupMenu();

                if (m_hMenu == nullptr)
                {
                    return false;
                }

                return true;
            }

            bool Destroy()
            {
                if (m_hMenu == nullptr)
                {
                    return false;
                }

                if (!DestroyMenu(m_hMenu))
                {
                    return false;
                }

                return true;
            }

            bool Attach(HMENU hMenu)
            {
                if (m_hMenu != nullptr)
                {
                    return false;
                }

                m_hMenu = hMenu;

                return true;
            }

            HMENU Detach()
            {
                HMENU hMenu = m_hMenu;

                if (m_hMenu != nullptr)
                {
                    m_hMenu = nullptr;
                }

                return hMenu;
            }

        public: // Attributes
            operator HMENU() const
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

        protected:
            HMENU m_hMenu;
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLMENU_H_C208C619_17E7_4147_BBFD_C815FAFA7324_INCLUDED__
