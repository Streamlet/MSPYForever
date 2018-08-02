//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIShockwaveFlash.h
//    Author:      Streamlet
//    Create Time: 2016-01-03
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLISHOCKWAVEFLASH_H_D88345FC_80C8_4D14_8925_FB6E9ED46F0A_INCLUDED__
#define __XLISHOCKWAVEFLASH_H_D88345FC_80C8_4D14_8925_FB6E9ED46F0A_INCLUDED__


#include "../../xlWin32Ver.h"
#include "xlIDispatchExImpl.h"
#include "ShockwaveFlash.tlh"

namespace xl
{
    namespace Windows
    {
        template <typename T = ShockwaveFlashObjects::IShockwaveFlash>
        class IShockwaveFlashImpl : public IDispatchImpl<T>
        {
        public: // IShockwaveFlash Methods
            STDMETHOD(get_ReadyState)(long *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_TotalFrames)(long *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Playing)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Playing)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Quality)(int *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Quality)(int pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_ScaleMode)(int *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_ScaleMode)(int pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_AlignMode)(int *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_AlignMode)(int pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_BackgroundColor)(long *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_BackgroundColor)(long pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Loop)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Loop)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Movie)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Movie)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_FrameNum)(long *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_FrameNum)(long pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_SetZoomRect)(long left, long top, long right, long bottom)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Zoom)(int factor)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Pan)(long x, long y, int mode)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Play)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Stop)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Back)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Forward)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_Rewind)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_StopPlay)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_GotoFrame)(long FrameNum)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_CurrentFrame)(long *FrameNum)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_IsPlaying)(VARIANT_BOOL *Playing)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_PercentLoaded)(long *percent)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_FrameLoaded)(long FrameNum, VARIANT_BOOL *loaded)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_FlashVersion)(long *version)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_WMode)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_WMode)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_SAlign)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_SAlign)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Menu)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Menu)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Base)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Base)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Scale)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Scale)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_DeviceFont)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_DeviceFont)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_EmbedMovie)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_EmbedMovie)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_BGColor)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_BGColor)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Quality2)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Quality2)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_LoadMovie)(int layer, BSTR url)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TGotoFrame)(BSTR target, long FrameNum)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TGotoLabel)(BSTR target, BSTR label)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TCurrentFrame)(BSTR target, long *FrameNum)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TCurrentLabel)(BSTR target, BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TPlay)(BSTR target)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TStopPlay)(BSTR target)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_SetVariable)(BSTR name, BSTR value)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_GetVariable)(BSTR name, BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TSetProperty)(BSTR target, int property, BSTR value)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TGetProperty)(BSTR target, int property, BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TCallFrame)(BSTR target, int FrameNum)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TCallLabel)(BSTR target, BSTR label)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TSetPropertyNum)(BSTR target, int property, double value)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TGetPropertyNum)(BSTR target, int property, double *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_TGetPropertyAsNumber)(BSTR target, int property, double *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_SWRemote)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_SWRemote)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_FlashVars)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_FlashVars)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_AllowScriptAccess)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_AllowScriptAccess)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_MovieData)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_MovieData)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_InlineData)(IUnknown **ppIUnknown)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_InlineData)(IUnknown *ppIUnknown)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_SeamlessTabbing)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_SeamlessTabbing)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_EnforceLocalSecurity)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_Profile)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_Profile)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_ProfileAddress)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_ProfileAddress)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_ProfilePort)(long *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_ProfilePort)(long pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_CallFunction)(BSTR request, BSTR *response)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_SetReturnValue)(BSTR returnValue)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(raw_DisableLocalSecurity)()
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_AllowNetworking)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_AllowNetworking)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_AllowFullScreen)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_AllowFullScreen)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_AllowFullScreenInteractive)(BSTR *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_AllowFullScreenInteractive)(BSTR pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(get_IsDependent)(VARIANT_BOOL *pVal)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(put_IsDependent)(VARIANT_BOOL pVal)
            {
                return E_NOTIMPL;
            }
        };

        template <typename T = ShockwaveFlashObjects::_IShockwaveFlashEvents>
        class _IShockwaveFlashEventsImpl : public IDispatchImpl<T>
        {
        public: // _IShockwaveFlashEvents Methods
            STDMETHOD(OnReadyStateChange)(long newState)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(OnProgress)(long percentDone)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(FSCommand)(BSTR bstrCommand, BSTR bstrArgs)
            {
                return E_NOTIMPL;
            }

            STDMETHOD(FlashCall)(BSTR bstrRequest)
            {
                return E_NOTIMPL;
            }
        };

        template <typename T = ShockwaveFlashObjects::IFlashFactory>
        class IFlashFactoryImpl : public IUnknownImpl<T>
        {

        };

        template <typename T = ShockwaveFlashObjects::IFlashObjectInterface>
        class IFlashObjectInterfaceImpl : public IDispatchExImpl<T>
        {

        };

        template <typename T = ShockwaveFlashObjects::IFlashObject>
        class IFlashObjectImpl : public IDispatchExImpl<T>
        {

        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLISHOCKWAVEFLASH_H_D88345FC_80C8_4D14_8925_FB6E9ED46F0A_INCLUDED__
