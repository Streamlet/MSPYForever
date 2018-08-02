//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlComLoader.h
//    Author:      Streamlet
//    Create Time: 2012-09-14
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCOMLOADER_H_7E18A233_B52A_4C75_BCF0_AD9F78C0DC2C_INCLUDED__
#define __XLCOMLOADER_H_7E18A233_B52A_4C75_BCF0_AD9F78C0DC2C_INCLUDED__


#include "../../Common/Containers/xlMap.h"
#include "../../Common/String/xlString.h"
#include "../File/xlIniFile.h"
#include "../Threads/xlCriticalSection.h"
#include "../xlWin32Ver.h"
#include "xlComClass.h"
#include "xlDispatcher.h"

namespace xl
{
    namespace Windows
    {
        typedef HRESULT(__stdcall *FnDllCanUnloadNow)();
        typedef HRESULT(__stdcall *FnDllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID *ppv);

        struct ComDllModule
        {
            String              strFileName;
            HMODULE             hModule;
            FnDllCanUnloadNow   fnDllCanUnloadNow;
            FnDllGetClassObject fnDllGetClassObject;

            ComDllModule() : hModule(nullptr), fnDllCanUnloadNow(nullptr), fnDllGetClassObject(nullptr)
            {

            }
        };

        typedef Map<String, String>       ClassIDPathMap;
        typedef Map<String, ComDllModule> PathModuleMap;

        struct __declspec(uuid("FE52639A-5B41-49B0-9A50-7A1C4FBC83E2"))
        IComLoader : public IDispatch
        {
            virtual HRESULT CoInitialize(_In_opt_ LPVOID pvReserved) PURE;
            virtual void CoUninitialize() PURE;
            virtual void CoFreeUnusedLibraries() PURE;
            virtual HRESULT CoGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID *ppv) PURE;
            virtual HRESULT CoCreateInstance(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID *ppv) PURE;
        };

        class ComLoaderFromIni : public ComClass<ComLoaderFromIni>,
                                 public Dispatcher<IComLoader>
        {
        public:
            ComLoaderFromIni(const String &strIniFile = L"xlComReg.ini") : m_strIniFile(strIniFile), m_lInitializeCount(0)
            {

            }

            ~ComLoaderFromIni()
            {
                CoUninitialize();
            }

        public:
            HRESULT CoInitialize(_In_opt_ LPVOID pvReserved)
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                if (m_lInitializeCount > 0)
                {
                    InterlockedIncrement(&m_lInitializeCount);
                    return S_FALSE;
                }

                Array<String> arrSections;

                if (!IniFile::EnumSections(m_strIniFile, &arrSections))
                {
                    return E_FAIL;
                }

                for (auto it = arrSections.Begin(); it != arrSections.End(); ++it)
                {
                    String strClass;

                    if (!IniFile::GetValue(m_strIniFile, *it, L"Class", &strClass))
                    {
                        continue;
                    }

                    String strPath;

#ifdef _WIN64
                    if (!IniFile::GetValue(m_strIniFile, *it, L"InprocServer64", &strPath))
                    {
                        continue;
                    }
#else
                    if (!IniFile::GetValue(m_strIniFile, *it, L"InprocServer32", &strPath))
                    {
                        continue;
                    }
#endif

                    m_mapClassIDToPath.Insert(*it, strPath);
                }

                InterlockedIncrement(&m_lInitializeCount);

                return S_OK;
            }

            void CoUninitialize()
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                if (m_lInitializeCount == 0)
                {
                    return;
                }

                InterlockedDecrement(&m_lInitializeCount);;

                if (m_lInitializeCount > 0)
                {
                    return;
                }

                for (auto it = m_mapPathToModule.Begin(); it != m_mapPathToModule.End(); ++it)
                {
                    FreeLibrary(it->Value.hModule);
                }

                m_mapClassIDToPath.Clear();
                m_mapPathToModule.Clear();
            }

            void CoFreeUnusedLibraries()
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                for (auto it = m_mapPathToModule.Begin(); it != m_mapPathToModule.End(); )
                {
                    if (it->Value.fnDllCanUnloadNow() == S_OK)
                    {
                        FreeLibrary(it->Value.hModule);
                        it = m_mapPathToModule.Delete(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }

            HRESULT CoGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID *ppv)
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                const ComDllModule *pModule = nullptr;
                HRESULT hr = FindComDllModule(rclsid, &pModule);

                if (FAILED(hr))
                {
                    return hr;
                }

                return pModule->fnDllGetClassObject(rclsid, riid, ppv);
            }

            HRESULT CoCreateInstance(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID *ppv)
            {
                IClassFactory *pClassFactory = nullptr;
                HRESULT hr = CoGetClassObject(rclsid, __uuidof(IClassFactory), (LPVOID *)&pClassFactory);

                if (FAILED(hr))
                {
                    return hr;
                }

                hr = pClassFactory->CreateInstance(NULL, riid, ppv);
                pClassFactory->Release();

                return hr;
            }

        private:
            HRESULT FindComDllModule(REFCLSID rclsid, const ComDllModule **ppModule)
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                if (ppModule == nullptr)
                {
                    return E_INVALIDARG;
                }

                *ppModule = nullptr;

                wchar_t szClassID[40] = {};
                StringFromGUID2(rclsid, szClassID, ARRAYSIZE(szClassID));

                auto itPath = m_mapClassIDToPath.Find(szClassID);

                if (itPath == m_mapClassIDToPath.End())
                {
                    return REGDB_E_CLASSNOTREG;
                }

                auto itModule = m_mapPathToModule.Find(itPath->Value);

                if (itModule == m_mapPathToModule.End())
                {
                    if (!LoadComDll(itPath->Value))
                    {
                        return E_FAIL;
                    }

                    itModule = m_mapPathToModule.Find(itPath->Value);
                }

                if (itModule == m_mapPathToModule.End())
                {
                    return E_FAIL;
                }

                *ppModule = &itModule->Value;

                return S_OK;
            }

            bool LoadComDll(const String &strFileName)
            {
                XL_SCOPED_CRITICAL_SECTION(m_cs);

                HMODULE hModule = LoadLibrary(strFileName);

                if (hModule == nullptr)
                {
                    return false;
                }

                ScopeGuard sgFreeLibrary = MakeGuard(Bind(FreeLibrary, hModule));

                FnDllCanUnloadNow fnDllCanUnloadNow = (FnDllCanUnloadNow)GetProcAddress(hModule, "DllCanUnloadNow");

                if (fnDllCanUnloadNow == nullptr)
                {
                    return false;
                }

                FnDllGetClassObject fnDllGetClassObject = (FnDllGetClassObject)GetProcAddress(hModule, "DllGetClassObject");

                if (fnDllGetClassObject == nullptr)
                {
                    return false;
                }

                ComDllModule &module = m_mapPathToModule[strFileName];
                module.strFileName = strFileName;
                module.hModule = hModule;
                module.fnDllCanUnloadNow = fnDllCanUnloadNow;
                module.fnDllGetClassObject = fnDllGetClassObject;

                sgFreeLibrary.Dismiss();

                return true;
            }

        private:
            String          m_strIniFile;
            LONG            m_lInitializeCount;
            ClassIDPathMap  m_mapClassIDToPath;
            PathModuleMap   m_mapPathToModule;
            CriticalSection m_cs;

        public:
            XL_COM_INTERFACE_BEGIN(ComLoaderFromIni)
                XL_COM_INTERFACE(IComLoader)
                XL_COM_INTERFACE(IDispatch)
            XL_COM_INTERFACE_END()
        };

        enum ComLoadType
        {
            CLT_FROM_INI,
        };

        inline IComLoader *CreateComLoader(ComLoadType type, const String &strData = L"xlComReg.ini")
        {
            IComLoader *pLoader = nullptr;

            switch (type)
            {
            case CLT_FROM_INI:
                pLoader = new ComLoaderFromIni(strData);
                pLoader->AddRef();
                break;
            default:
                break;
            }

            return pLoader;
        }

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLCOMLOADER_H_7E18A233_B52A_4C75_BCF0_AD9F78C0DC2C_INCLUDED__
