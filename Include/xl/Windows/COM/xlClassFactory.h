//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlClassFactory.h
//    Author:      Streamlet
//    Create Time: 2012-09-09
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCLASSFACTORY_H_30C5A972_4508_453D_AC45_B489268F1183_INCLUDED__
#define __XLCLASSFACTORY_H_30C5A972_4508_453D_AC45_B489268F1183_INCLUDED__


#include "xlComClass.h"
#include "InterfaceHelper/xlIClassFactoryImpl.h"

namespace xl
{
    namespace Windows
    {
        template <typename T>
        class ClassFactory : public ComClass<ClassFactory<T>>,
                             public IClassFactoryImpl<>
        {
        public:
            static IClassFactory *CreateFactory(bool bAddObjRefCount = true)
            {
                return new ClassFactory(bAddObjRefCount);
            }

        public:
            ClassFactory(bool bAddObjRefCount = true) :
                ComClass<ClassFactory<T>>(bAddObjRefCount)
            {

            }

            ~ClassFactory()
            {

            }

        public:
            STDMETHOD(CreateInstance)(IUnknown *pUnkOuter,
                                      REFIID riid,
                                      void **ppvObject)
            {
                T *p = new T;
                return p->QueryInterface(riid, ppvObject);
            }

            STDMETHOD(LockServer)(BOOL fLock)
            {
                if (g_pComModule == nullptr)
                {
                    return E_NOTIMPL;
                }

                if (fLock)
                {
                    g_pComModule->LockAddRef();
                }
                else
                {
                    g_pComModule->LockAddRef();
                }

                return S_OK;
            }

        public:
            XL_COM_INTERFACE_BEGIN(ClassFactory<T>)
                XL_COM_INTERFACE(IClassFactory)
            XL_COM_INTERFACE_END()
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLCLASSFACTORY_H_30C5A972_4508_453D_AC45_B489268F1183_INCLUDED__
