//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMathSet.h
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLMATHSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__
#define __XLMATHSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Math/xlInterval.h>

namespace xl
{
    template <typename T>
    class MathSet
    {
    public:
        typedef Interval<T> IntervalType;

    private:
        Array<IntervalType> arrIntervals;

    public:
        MathSet()
        {

        }

        MathSet(const MathSet &that)
        {
            this->arrRanges = that.arrRanges;
        }

        ~MathSet()
        {

        }

    public:
        MathSet &operator = (const MathSet &that)
        {
            if (this != &that)
            {
                this->arrRanges = that.arrRanges;
            }

            return *this;
        }

        bool operator == (MathSet &that) const
        {
            return this->arrRanges == that.arrRanges;
        }

        bool operator != (MathSet &that) const
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

        MathSet Complementary(const IntervalType &universe) const
        {

        }

        MathSet Intersection(const MathSet &that) const
        {

        }

        MathSet Union(const MathSet &that) const
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



#endif // #ifndef __XLMATHSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__
