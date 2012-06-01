//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIntervalSet.h
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLINTERVALSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__
#define __XLINTERVALSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Math/xlInterval.h>

namespace xl
{
    template <typename T>
    class IntervalSet
    {
    public:
        typedef Interval<T> IntervalType;

    private:
        Array<IntervalType> arrIntervals;

    public:
        IntervalSet()
        {

        }

        IntervalSet(const IntervalSet &that)
        {
            this->arrRanges = that.arrRanges;
        }

        ~IntervalSet()
        {

        }

    public:
        IntervalSet &operator = (const IntervalSet &that)
        {
            if (this != &that)
            {
                this->arrRanges = that.arrRanges;
            }

            return *this;
        }

        bool operator == (IntervalSet &that) const
        {
            return this->arrRanges == that.arrRanges;
        }

        bool operator != (IntervalSet &that) const
        {
            return this->arrRanges != that.arrRanges;
        }

    public:
        Array<IntervalType> GetRanges()
        {
            return arrRanges;
        }

    public:
        bool IsEmpty() const
        {
            return arrRanges.Empty();
        }

        bool IsUniverse() const
        {

        }

        IntervalSet Complementary(const IntervalType &universe) const
        {

        }

        IntervalSet Intersection(const IntervalSet &that) const
        {

        }

        IntervalSet Union(const IntervalSet &that) const
        {

        }

    public:
        void Union(const IntervalType &interval)
        {

        }

        void Exclude(const IntervalType &that)
        {

        }
    };

} // namespace xl



#endif // #ifndef __XLINTERVALSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__
