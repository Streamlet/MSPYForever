//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlPair.h
//    Author:      Streamlet
//    Create Time: 2009-11-07
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLPAIR_H_E7935E32_4626_4FB9_B582_4D3DA2D9CF69_INCLUDED__
#define __XLPAIR_H_E7935E32_4626_4FB9_B582_4D3DA2D9CF69_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    template <typename K, typename V>
    class Pair
    {
    public:
        K Key;
        V Value;

    public:
        Pair();
        Pair(const K &key);
        Pair(const K &key, const V &value);
        Pair(const Pair &that);
        Pair &operator = (const Pair &that);

    public:
        bool operator == (const Pair &that) const;
        bool operator != (const Pair &that) const;
        bool operator < (const Pair &that) const;
        bool operator > (const Pair &that) const;
        bool operator <= (const Pair &that) const;
        bool operator >= (const Pair &that) const;
    };

    template <typename K, typename V>
    Pair<K, V>::Pair()
    {

    }

    template <typename K, typename V>
    Pair<K, V>::Pair(const K &key)
        : Key(key)
    {

    }

    template <typename K, typename V>
    Pair<K, V>::Pair(const K &key, const V &value)
        : Key(key), Value(value)
    {

    }

    template <typename K, typename V>
    Pair<K, V>::Pair(const Pair<K, V> &that)
        : Key(that.Key), Value(that.Value)
    {

    }

    template <typename K, typename V>
    Pair<K, V> &Pair<K, V>::operator = (const Pair<K, V> &that)
    {
        if (this != &that)
        {
            this->Key = that.Key;
            this->Value = that.Value;
        }

        return *this;
    }

    template <typename K, typename V>
    bool Pair<K, V>::operator == (const Pair &that) const
    {
        return this->Key == that.Key;
    }

    template <typename K, typename V>
    bool Pair<K, V>::operator != (const Pair &that) const
    {
        return this->Key != that.Key;
    }

    template <typename K, typename V>
    bool Pair<K, V>::operator < (const Pair &that) const
    {
        return this->Key < that.Key;
    }

    template <typename K, typename V>
    bool Pair<K, V>::operator > (const Pair &that) const
    {
        return this->Key > that.Key;
    }

    template <typename K, typename V>
    bool Pair<K, V>::operator <= (const Pair &that) const
    {
        return this->Key <= that.Key;
    }

    template <typename K, typename V>
    bool Pair<K, V>::operator >= (const Pair &that) const
    {
        return this->Key >= that.Key;
    }

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::Pair
// ;------------------------------------------------------------------------------
// xl::Pair<*>{
//     preview (
//         #(
//             $e.Key,
//             "->",
//             $e.Value
//         )
//     )
// }
//

#endif // #ifndef __XLPAIR_H_E7935E32_4626_4FB9_B582_4D3DA2D9CF69_INCLUDED__
