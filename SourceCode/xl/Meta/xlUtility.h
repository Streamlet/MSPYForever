//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlUtility.h
//    Author:      Streamlet
//    Create Time: 2011-05-08
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLUTILITY_H_03E2673E_60F5_4875_BC62_73D1FAA5E5E2_INCLUDED__
#define __XLUTILITY_H_03E2673E_60F5_4875_BC62_73D1FAA5E5E2_INCLUDED__


namespace xl
{
    class NonInstantiable
    {
    private:
        NonInstantiable();
    };

    class NonCopyable
    {
    public:
        NonCopyable()
        {

        }

        ~NonCopyable()
        {

        }

    private:
        NonCopyable(const NonCopyable &);
        NonCopyable &operator = (const NonCopyable &);
    };

} // namespace xl

#endif // #ifndef __XLUTILITY_H_03E2673E_60F5_4875_BC62_73D1FAA5E5E2_INCLUDED__
