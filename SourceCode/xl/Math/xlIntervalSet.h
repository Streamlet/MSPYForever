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


#include <xl/Containers/xlSet.h>
#include <xl/Math/xlInterval.h>

namespace xl
{
    template <typename T>
    class IntervalSet
    {
    public:
        typedef Interval<T> IntervalType;

    private:
        Set<IntervalType> m_setIntervals;

    public:
        IntervalSet()
        {

        }

        IntervalSet(const IntervalSet &that)
        {
            this->m_setIntervals = that.m_setIntervals;
        }

        ~IntervalSet()
        {

        }

    public:
        IntervalSet &operator = (const IntervalSet &that)
        {
            if (this != &that)
            {
                this->m_setIntervals = that.m_setIntervals;
            }

            return *this;
        }

        bool operator == (IntervalSet &that) const
        {
            return this->m_setIntervals == that.m_setIntervals;
        }

        bool operator != (IntervalSet &that) const
        {
            return this->m_setIntervals != that.m_setIntervals;
        }

    public:
        Set<IntervalType> GetIntervals()
        {
            return m_setIntervals;
        }

    public:
        bool IsEmpty() const
        {
            return m_setIntervals.Empty();
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
            IntervalType i = interval;

            for (auto it = m_setIntervals.Begin(); it != m_setIntervals.End(); )
            {
                if (interval.Touched(*it))
                {
                    i = i.UnionTouched(*it);
                    it = it->Delete(it);
                }
                else
                {
                    ++it;
                }                
            }

            m_setIntervals.Insert(i);
        }

        void Exclude(const IntervalType &interval)
        {
            for (auto it = m_setIntervals.Begin(); it != m_setIntervals.End(); )
            {
                *it = interval.Complementary(*it);

                if (it->IsEmpty())
                {
                    it = m_setIntervals.Delete(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    };

} // namespace xl



#endif // #ifndef __XLINTERVALSET_H_0D40B708_46DD_4421_A698_83BFE8AA4066_INCLUDED__
