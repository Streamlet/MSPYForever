//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMetaBase.h
//    Author:      Streamlet
//    Create Time: 2011-01-17
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMETABASE_H_5432C693_BF0D_45B0_BB18_FA38C6913B74_INCLUDED__
#define __XLMETABASE_H_5432C693_BF0D_45B0_BB18_FA38C6913B74_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    struct NullType;

    struct EmptyType
    {

    };

#ifdef __XL_CPP11

    template <typename S, typename... T>
    class TypeConverter;

    template <typename S>
    class TypeConverter<S>
    {
    public:
        TypeConverter() : m_pData(S(0))
        {

        }

    protected:
        S m_pData;
    };

    template <typename S, typename T0, typename... T>
    class TypeConverter<S, T0, T...> : public TypeConverter<S, T...>
    {
    public:
        TypeConverter() : TypeConverter<S, T...>()
        {

        }

        TypeConverter(const T0 &t) : m_pData((S)t)
        {

        }

        operator T0() const
        {
            return (T0)m_pData;
        }
    };

#endif

} // namespace xl

#endif // #ifndef __XLMETABASE_H_5432C693_BF0D_45B0_BB18_FA38C6913B74_INCLUDED__
