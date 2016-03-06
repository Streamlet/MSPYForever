//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlInterval.h
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLINTERVAL_H_14F2C212_AFD1_4E01_8F71_60E67EACC903_INCLUDED__
#define __XLINTERVAL_H_14F2C212_AFD1_4E01_8F71_60E67EACC903_INCLUDED__


#include "../../xlDef.h"
#include "../Containers/xlSet.h"
#include "../Math/xlMathBase.h"

namespace xl
{
    template <typename T>
    struct Interval
    {
        T left;
        T right;
        bool bIncludeLeft;
        bool bIncludeRight;

        Interval()
            : left(0), right(0), bIncludeLeft(false), bIncludeRight(false)
        {

        }

        Interval(T value)
            : left(value), right(value), bIncludeLeft(true), bIncludeRight(true)
        {

        }

        Interval(T left, T right, bool bIncludeLeft = true, bool bIncludeRight = true)
            : left(left), right(right), bIncludeLeft(bIncludeLeft), bIncludeRight(bIncludeRight)
        {

        }

        Interval(const Interval &that)
        {
            *this = that;
        }

        ~Interval()
        {

        }

        Interval &operator = (const Interval &that)
        {
            if (this != &that)
            {
                this->left          = that.left;
                this->right         = that.right;
                this->bIncludeLeft  = that.bIncludeLeft;
                this->bIncludeRight = that.bIncludeRight;
            }

            return *this;
        }

        bool operator == (const Interval &that) const
        {
            if (this->IsEmpty() && that.IsEmpty())
            {
                return true;
            }

            if (this->left == that.left &&
                this->right == that.right &&
                ((this->bIncludeLeft && that.bIncludeLeft) || (!this->bIncludeLeft && !that.bIncludeLeft)) &&
                ((this->bIncludeRight && that.bIncludeRight) || (!this->bIncludeRight && !that.bIncludeRight)))
            {
                return true;
            }

            return false;
        }

        bool operator != (const Interval &that) const
        {
            if (this->IsEmpty() && that.IsEmpty())
            {
                return false;
            }

            if (this->left == that.left &&
                this->right == that.right &&
                ((this->bIncludeLeft && that.bIncludeLeft) || (!this->bIncludeLeft && !that.bIncludeLeft)) &&
                ((this->bIncludeRight && that.bIncludeRight) || (!this->bIncludeRight && !that.bIncludeRight)))
            {
                return false;
            }

            return true;
        }

        bool operator < (const Interval &that) const
        {
            if (that.IsEmpty())
            {
                return false;
            }

            if (this->IsEmpty())
            {
                return true;
            }

            if (that.left < this->left)
            {
                return false;
            }

            if (this->left < that.left)
            {
                return true;
            }

            if (that.bIncludeLeft)
            {
                return false;
            }

            if (this->bIncludeLeft)
            {
                return true;
            }

            if (that.right < this->right)
            {
                return false;
            }

            if (this->right < that.right)
            {
                return true;
            }

            if (this->bIncludeRight)
            {
                return false;
            }

            if (that.bIncludeRight)
            {
                return true;
            }

            return false;
        }

        bool operator > (const Interval &that) const
        {
            if (this->IsEmpty())
            {
                return false;
            }

            if (that.IsEmpty())
            {
                return true;
            }

            if (this->left > that.left)
            {
                return true;
            }

            if (that.left > this->left)
            {
                return false;
            }

            if (this->bIncludeLeft)
            {
                return false;
            }

            if (that.bIncludeLeft)
            {
                return true;
            }

            if (this->right > that.right)
            {
                return true;
            }

            if (that.right > this->right)
            {
                return false;
            }

            if (that.bIncludeRight)
            {
                return false;
            }

            if (this->bIncludeRight)
            {
                return true;
            }

            return false;
        }

        bool operator <= (const Interval &that) const
        {
            return *this == that || *this < that;
        }

        bool operator >= (const Interval &that) const
        {
            return *this == that || *this > that;
        }

        bool IsEmpty() const
        {
            if (left < right)
            {
                return false;
            }

            if (left == right && (bIncludeLeft && bIncludeRight))
            {
                return false;
            }

            return true;
        }

        bool Contains(const T &v) const
        {
            if (IsEmpty())
            {
                return false;
            }

            if (v > left && v < right)
            {
                return true;
            }

            if (v == left && bIncludeLeft)
            {
                return true;
            }

            if (v == right && bIncludeRight)
            {
                return true;
            }

            return false;
        }

        bool Contains(const Interval &that) const
        {
            if (that.IsEmpty())
            {
                return true;
            }

            if ((this->Contains(that.left) || (this->left == that.left && !that.bIncludeLeft)) &&
                (this->Contains(that.right) || (this->right == that.right && !that.bIncludeRight)))
            {
                return true;
            }

            return false;
        }

        bool ContainedBy(const Interval &that) const
        {
            return that.Contains(*this);
        }

        Interval Intersection(const Interval &that) const
        {
            Interval r;

            if (this->left < that.left)
            {
                r.left = that.left;
                r.bIncludeLeft = that.bIncludeLeft;
            }
            else if (this->left > that.left)
            {
                r.left = this->left;
                r.bIncludeLeft = this->bIncludeLeft;
            }
            else
            {
                r.left = left;
                r.bIncludeLeft = (this->bIncludeLeft && that.bIncludeLeft);
            }

            if (this->right < that.right)
            {
                r.right = this->right;
                r.bIncludeRight = this->bIncludeRight;
            }
            else if (this->right > that.right)
            {
                r.right = that.right;
                r.bIncludeRight = that.bIncludeRight;
            }
            else
            {
                r.right = right;
                r.bIncludeRight = (this->bIncludeRight && that.bIncludeRight);
            }

            return r;
        }

        bool HasIntersectionWith(const Interval &that) const
        {
            return !this->Intersection(that).IsEmpty();
        }

        bool Touched(const Interval &that) const
        {
            if (this->IsEmpty() || that.IsEmpty())
            {
                return true;
            }

            if (this->HasIntersectionWith(that))
            {
                return true;
            }

            if (this->left == that.right && (this->bIncludeLeft || that.bIncludeRight))
            {
                return true;
            }

            if (this->right == that.left && (this->bIncludeRight || that.bIncludeLeft))
            {
                return true;
            }

            return false;
        }

        Interval UnionTouched(const Interval &that) const
        {
            if (!this->Touched(that))
            {
                return *this;
            }

            if (that.IsEmpty())
            {
                return *this;
            }

            if (this->IsEmpty())
            {
                return that;
            }

            Interval r;

            if (this->left < that.left)
            {
                r.left = this->left;
                r.bIncludeLeft = this->bIncludeLeft;
            }
            else if (this->left > that.left)
            {
                r.left = that.left;
                r.bIncludeLeft = that.bIncludeLeft;
            }
            else
            {
                r.left = left;
                r.bIncludeLeft = (this->bIncludeLeft || that.bIncludeLeft);
            }

            if (this->right < that.right)
            {
                r.right = that.right;
                r.bIncludeRight = that.bIncludeRight;
            }
            else if (this->right > that.right)
            {
                r.right = this->right;
                r.bIncludeRight = this->bIncludeRight;
            }
            else
            {
                r.right = right;
                r.bIncludeRight = (this->bIncludeRight || that.bIncludeRight);
            }

            return r;
        }

        Set<Interval> Union(const Interval &that) const
        {
            Set<Interval> setIntervals;

            if (this->Touched(that))
            {
                setIntervals.Insert(UnionTouched(that));
            }
            else
            {
                setIntervals.Insert(*this);
                setIntervals.Insert(that);
            }

            return setIntervals;
        }

        Set<Interval> Exclude(const Interval &that) const
        {
            Set<Interval> setIntervals;

            Interval intersection = this->Intersection(that);

            if (intersection.IsEmpty())
            {
                setIntervals.Insert(*this);
                return setIntervals;
            }

            if (intersection.left != this->left || (!intersection.bIncludeLeft && this->bIncludeLeft))
            {
                setIntervals.Insert(Interval(this->left,
                                             intersection.left,
                                             this->bIncludeLeft,
                                             !intersection.bIncludeLeft));
            }

            if (intersection.right != this->right || (!intersection.bIncludeRight && this->bIncludeRight))
            {
                setIntervals.Insert(Interval(intersection.right,
                                             this->right,
                                             !intersection.bIncludeRight,
                                             this->bIncludeRight));
            }

            return setIntervals;
        }

        Interval CloseInterval(const T step)
        {
            Interval r = *this;

            if (!r.bIncludeLeft)
            {
                r.left += step;
                r.bIncludeLeft = true;
            }

            if (!r.bIncludeRight)
            {
                r.right -= step;
                r.bIncludeRight = true;
            }

            return r;
        }
    };

} // namespace xl


#endif // #ifndef __XLINTERVAL_H_14F2C212_AFD1_4E01_8F71_60E67EACC903_INCLUDED__
