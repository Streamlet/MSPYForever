//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDllHelper.h
//    Author:      Streamlet
//    Create Time: 2015-03-15
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLDLLHELPER_H_0B8EA1C6_DE7D_4131_8096_3FCB72FAB3B9_INCLUDED__
#define __XLDLLHELPER_H_0B8EA1C6_DE7D_4131_8096_3FCB72FAB3B9_INCLUDED__


#include <Windows.h>


namespace xl
{

    template <typename S, typename R, typename ... Args>
    R DllHelperCallFunctionStrict(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
    {
        static HMODULE hModule = nullptr;

        if (hModule == nullptr)
        {
            hModule = LoadLibrary(lpLibFileName);
        }

        if (hModule == nullptr)
        {
            return R();
        }

        S f = (S)GetProcAddress(hModule, lpProcName);

        if (f == nullptr)
        {
            return R();
        }

        return f(args...);
    }

    template <typename S>
    struct DllHelper;

#ifdef _M_X64

    template <typename R, typename ... Args>
    struct DllHelper<R(&)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__stdcall &)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

    template <typename R, typename ... Args>
    struct DllHelper<R(*)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__cdecl *)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

#else

    template <typename R, typename ... Args>
    struct DllHelper<R(__cdecl &)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__cdecl &)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

    template <typename R, typename ... Args>
    struct DllHelper<R(__cdecl *)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__cdecl *)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

    template <typename R, typename ... Args>
    struct DllHelper<R(__stdcall &)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__stdcall &)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

    template <typename R, typename ... Args>
    struct DllHelper<R(__stdcall *)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__stdcall *)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

    template <typename R, typename ... Args>
    struct DllHelper<R(__fastcall &)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__fastcall &)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

    template <typename R, typename ... Args>
    struct DllHelper<R(__fastcall *)(Args...)>
    {
        static R CallFunction(LPCTSTR lpLibFileName, LPCSTR lpProcName, Args ... args)
        {
            return DllHelperCallFunctionStrict<R(__fastcall *)(Args...), R, Args...>(lpLibFileName, lpProcName, args...);
        }
    };

#endif

} // namespace xl

#endif // #ifndef __XLDLLHELPER_H_0B8EA1C6_DE7D_4131_8096_3FCB72FAB3B9_INCLUDED__
