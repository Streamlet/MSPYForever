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

        operator HMENU() const
        {
            return m_hMenu;
        }
    };

} // namespace xl

#endif // #ifndef __XLMENU_H_AE31B303_4262_49A0_99BA_A03D67B0C6E5_INCLUDED__
