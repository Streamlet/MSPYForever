//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlCommCtrlInitializer.h
//    Author:      Streamlet
//    Create Time: 2011-03-04
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLCOMMCTRLINITIALIZER_H_D4ADA173_6B10_43C9_A817_E1BB6F16BC5F_INCLUDED__
#define __XLCOMMCTRLINITIALIZER_H_D4ADA173_6B10_43C9_A817_E1BB6F16BC5F_INCLUDED__


#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

namespace xl
{
    class CommCtrlInitializer
    {
    public:
        CommCtrlInitializer()
        {
            INITCOMMONCONTROLSEX iccx = { sizeof(INITCOMMONCONTROLSEX), 0xffffffff };
            InitCommonControlsEx(&iccx);
        }

        ~CommCtrlInitializer()
        {

        }
    };

} // namespace xl

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#endif // #ifndef __XLCOMMCTRLINITIALIZER_H_D4ADA173_6B10_43C9_A817_E1BB6F16BC5F_INCLUDED__
