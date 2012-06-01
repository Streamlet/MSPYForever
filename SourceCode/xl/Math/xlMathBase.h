//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMathBase.h
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__
#define __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__


namespace xl
{
    template <typename T, typename U>
    auto Min(T t, U u) -> decltype(t <= u ? t : u)
    {
        return (t <= u ? t : u);
    }

    template <typename T, typename U>
    auto Max(T t, U u) -> decltype(t >= u ? t : u)
    {
        return (t >= u ? t : u);
    }

} // namespace xl

#endif // #ifndef __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__
