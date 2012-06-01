//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlInterval.h
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLINTERVAL_H_14F2C212_AFD1_4E01_8F71_60E67EACC903_INCLUDED__
#define __XLINTERVAL_H_14F2C212_AFD1_4E01_8F71_60E67EACC903_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Math/xlMathBase.h>

namespace xl
{
    template <typename T>
    struct Interval
    {
        T left;
        T right;
        bool bIncludeLeft;
        bool bIncludeRight;

        Interval(T left = 0, T right = 0, bool bIncludeLeft = false, bool bIncludeRight = false)
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

    public:
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
                r.left = that.right;
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

        bool Touched(const Interval &that)
        {
            if (this->IsEmpty() || that.IsEmpty())
            {
                return false;
            }

            if (!this->HasIntersectionWith(that))
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

        Array<Interval> Union(const Interval &that) const
        {
            Array<Interval> arrIntervals;

            if (!this->Touched(that))
            {
                if (!this->IsEmpty())
                {
                    arrIntervals.PushBack(*this);
                }

                if (!that.IsEmpty())
                {
                    arrIntervals.PushBack(that);
                }

                return arrIntervals;
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
                r.left = that.right;
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

            arrIntervals.PushBack(r);

            return arrIntervals;
        }

        Array<Interval> Complementary(const Interval &universe) const
        {
            Array<Interval> arrIntervals;

            Interval intersection = this->Intersection(universe);

            if (intersection.IsEmpty())
            {
                arrIntervals.PushBack(universe);
                return arrIntervals;
            }

            if (intersection.left != universe.left || (!intersection.bIncludeLeft && universe.bIncludeLeft))
            {
                arrIntervals.PushBack(Interval(universe.left,
                                               intersection.left,
                                               universe.bIncludeLeft,
                                               !intersection.bIncludeLeft));
            }

            if (intersection.right != universe.right || (!intersection.bIncludeRight && universe.bIncludeRight))
            {
                arrIntervals.PushBack(Interval(intersection.right,
                                               universe.right,
                                               !intersection.bIncludeRight,
                                               universe.bIncludeRight));
            }

            return arrIntervals;
        }

    };

} // namespace xl


#endif // #ifndef __XLINTERVAL_H_14F2C212_AFD1_4E01_8F71_60E67EACC903_INCLUDED__
