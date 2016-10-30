//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMap.h
//    Author:      Streamlet
//    Create Time: 2009-11-07
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMAP_H_793F2C3D_4121_413E_B70F_E7A686081AC4_INCLUDED__
#define __XLMAP_H_793F2C3D_4121_413E_B70F_E7A686081AC4_INCLUDED__


#include "../../xlDef.h"
#include "xlPair.h"
#include "xlRBTree.h"

namespace xl
{
    template <typename K, typename V>
    class Map : public RBTree<Pair<K, V>>
    {
    public:
        inline Map()
        {

        }

        inline Map(const Map &that) : RBTree(that)
        {

        }

#ifdef __XL_CPP11

        inline Map(Map &&that) : RBTree(that)
        {

        }

#endif

        inline Map &operator = (const Map &that)
        {
            if (this == &that)
            {
                return *this;
            }

            *(RBTree *)this = (RBTree &)that;

            return *this;
        }

#ifdef __XL_CPP11

        inline Map &operator = (Map &&that)
        {
            if (this == &that)
            {
                return *this;
            }

            *(RBTree *)this = Memory::Move((RBTree &)that);

            return *this;
        }

#endif

        inline bool operator == (const Map &that) const
        {
            return *(RBTree *)this == (RBTree &)that;
        }

        inline bool operator != (const Map &that) const
        {
            return *(RBTree *)this != (RBTree &)that;
        }

        inline V &operator [] (const K &key)
        {
            Iterator it = Find(key);

            if (it == End())
            {
                it = RBTree::Insert(Pair<K, V>(key));
            }

            return it->Value;
        }

        inline const V &operator [] (const K &key) const
        {
            Iterator it = Find(key);

            if (it == End())
            {
                return V();
            }

            return it->Value;
        }

    public:
        // From Base
        inline Iterator Delete(const Iterator &itWhere);
        inline ReverseIterator Delete(const ReverseIterator &itWhere);

        inline void Delete(const K &key)
        {
            RBTree::Delete(Find(key));
        }

        inline Iterator Find(const K &key)
        {
            return RBTree::Find(Pair<K, V>(key));
        }

        inline Iterator Insert(const xl::Pair<K, V> &pair)
        {
            return RBTree::Insert(pair);
        }

        inline Iterator Insert(const K &key, const V &value)
        {
            return RBTree::Insert(Pair<K, V>(key, value));
        }
    };

} // namespace xl

#endif // #ifndef __XLMAP_H_793F2C3D_4121_413E_B70F_E7A686081AC4_INCLUDED__
