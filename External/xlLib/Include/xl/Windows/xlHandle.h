//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlHandle.h
//    Author:      Streamlet
//    Create Time: 2013-05-15
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLHANDLE_H_39C0A466_0EB3_4D32_879B_1984722D3AED_INCLUDED__
#define __XLHANDLE_H_39C0A466_0EB3_4D32_879B_1984722D3AED_INCLUDED__



namespace xl
{
    namespace Windows
    {
        struct DefaultHandleCloser
        {
            static bool CloseHandle(HANDLE hHandle)
            {
                return !!::CloseHandle(hHandle);
            }
        };

        template <bool bManaged = true, typename HandleCloser = DefaultHandleCloser>
        class HandleT
        {
        public:
            HandleT(HANDLE hHandle = nullptr) :
                m_hHandle(hHandle)
            {

            }

            virtual ~HandleT()
            {
                if (bManaged)
                {
                    Close();
                }
                else
                {
                    Detach();
                }
            }

        public:
            HANDLE Attach(HANDLE hHandle)
            {
                HANDLE hPrevious = m_hHandle;
                m_hHandle = hHandle;
                return hPrevious;
            }

            HANDLE Detach()
            {
                return Attach(nullptr);
            }

            bool Close()
            {
                if (m_hHandle == nullptr)
                {
                    return true;
                }

                if (!HandleCloser::CloseHandle(m_hHandle))
                {
                    return false;
                }

                m_hHandle = nullptr;

                return true;
            }

        public:
            operator HANDLE() const
            {
                return m_hHandle;
            }

            bool IsValid() const
            {
                return m_hHandle != nullptr && m_hHandle != INVALID_HANDLE_VALUE;
            }

        protected:
            HANDLE m_hHandle;
        };

        typedef HandleT<> Handle;

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLHANDLE_H_39C0A466_0EB3_4D32_879B_1984722D3AED_INCLUDED__
