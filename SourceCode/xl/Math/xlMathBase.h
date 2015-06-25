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


#include "../Containers/xlTuple.h"


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

    template <typename T>
    struct SizeT : public Tuple<T, T>
    {
        T &CX()
        {
            return At<0>();
        }

        T &CY()
        {
            return At<1>();
        }

        const T &&CX() const
        {
            return At<0>();
        }

        const T &&CY() const
        {
            return At<1>();
        }

        SizeT() : Tuple<T, T>()
        {

        }

        template <typename U>
        SizeT(U cx, U cy) : Tuple<T, T>(cx, cy)
        {

        }

        template <typename U>
        SizeT(const SizeT<U> &that) : Tuple<T, T>(that.cx, that.cy)
        {

        }

        template <typename U>
        SizeT &Inflate(U delta)
        {
            return *this += delta;
        }

        template <typename U>
        SizeT &Deflate(U delta)
        {
            return *this -= delta;
        }

        template <typename U>
        SizeT &Inflate(U dx, U dy)
        {
            return *this += SizeT<U>(dx, dy);
        }

        template <typename U>
        SizeT &Deflate(U dx, U dy)
        {
            return *this -= SizeT<U>(dx, dy);
        }
    };

    template <typename T>
    struct PointT : public Tuple<T, T>
    {
        T &X()
        {
            return At<0>();
        }

        T &Y()
        {
            return At<1>();
        }

        const T &&X() const
        {
            return At<0>();
        }

        const T &&Y() const
        {
            return At<1>();
        }

        PointT() : x(), y()
        {

        }

        template <typename U>
        PointT(U x, U y) : Tuple<T, T>(x, y)
        {

        }

        template <typename U>
        PointT(const PointT<U> &that) : Tuple<T, T>(that.cx, that.cy)
        {

        }

        template <typename U>
        PointT(const SizeT<U> &that) : Tuple<T, T>(that.cx, that.cy)
        {

        }

        PointT &Offset(T delta)
        {
            return *this += delta;
        }

        PointT &Offset(T dx, T dy)
        {
            return *this += SizeT(dx, dy);
        }
    };

    template <typename T>
    struct RectT : Tuple<T, T, T, T>
    {
        T &X()
        {
            return At<0>();
        }

        T &Y()
        {
            return At<1>();
        }

        T &W()
        {
            return At<2>();
        }

        T &H()
        {
            return At<3>();
        }

        const T &&X() const
        {
            return At<0>();
        }

        const T &&Y() const
        {
            return At<1>();
        }

        const T &&W() const
        {
            return At<2>();
        }

        const T &&H() const
        {
            return At<3>();
        }

        const T &&Left() const
        {
            return X();
        }

        const T &&Top() const
        {
            return Y();
        }

        const T &&Right() const
        {
            return X() + W();
        }

        const T &&Bottom() const
        {
            return Y() + H();
        }

        RectT() : Tuple<T, T, T, T>()
        {

        }

        RectT(T x, T y, T w, T h) : Tuple<T, T, T, T>(x, y, w, h)
        {

        }

        RectT(const RectT &that) : Tuple<T, T, T, T>(that.x, that.y, that.w, that.h)
        {

        }

        RectT(const PointT<T> &pt, const SizeT<T> &sz) : Tuple<T, T, T, T>(pt.x, pt.y, sz.cx, sz.cy)
        {

        }

        RectT &Offset(T delta)
        {
            X() += delta;
            Y() += delta;

            return *this;
        }

        RectT &Offset(T dx, T dy)
        {
            X() += dx;
            Y() += dy;

            return *this;
        }

        RectT Offset(T delta) const
        {
            RectT r(*this);
            r.Offset(delta);
            return r;
        }

        RectT Offset(T dx, T dy) const
        {
            RectT r(*this);
            r.Offset(dx, dy);
            return r;
        }

        RectT &Inflate(T delta)
        {
            X() -= delta;
            Y() -= delta;
            W() += delta + delta;
            H() += delta + delta;

            return *this;
        }

        RectT &Deflate(T delta)
        {
            X() += delta;
            Y() += delta;
            W() -= delta + delta;
            H() -= delta + delta;

            return *this;
        }

        RectT &Inflate(T dx, T dy)
        {
            X() -= dx;
            Y() -= dy;
            W() += dx + dx;
            H() += dy + dy;

            return *this;
        }

        RectT &Deflate(T dx, T dy)
        {
            X() -= dx;
            Y() -= dy;
            W() += dx + dx;
            H() += dy + dy;

            return *this;
        }

        RectT &Inflate(T dl, T dt, T dr, T db)
        {
            X() -= dl;
            Y() -= dt;
            W() += dl + dr;
            H() += dt + db;

            return *this;
        }

        RectT &Deflate(T dl, T dt, T dr, T db)
        {
            X() += dl;
            Y() += dt;
            W() -= dl + dr;
            H() -= dt + db;

            return *this;
        }

        RectT Inflate(T delta) const
        {
            RectT r(*this);
            r.Inflate(delta);
            return r;
        }

        RectT Deflate(T delta) const
        {
            RectT r(*this);
            r.Deflate(delta);
            return r;
        }

        RectT Inflate(T dx, T dy) const
        {
            RectT r(*this);
            r.Inflate(dx, dy);
            return r;
        }

        RectT Deflate(T dx, T dy) const
        {
            RectT r(*this);
            r.Deflate(dx, dy);
            return r;
        }

        RectT Inflate(T dl, T dt, T dr, T db) const
        {
            RectT r(*this);
            r.Inflate(dl, dt, dr, db);
            return r;
        }

        RectT Deflate(T dl, T dt, T dr, T db) const
        {
            RectT r(*this);
            r.Deflate(dl, dt, dr, db);
            return r;
        }
    };

    typedef SizeT <int> Size;
    typedef PointT<int> Point;
    typedef RectT <int> Rect;

    typedef SizeT <unsigned int> SizeU;
    typedef PointT<unsigned int> PointU;
    typedef RectT <unsigned int> RectU;

    typedef SizeT <float> SizeF;
    typedef PointT<float> PointF;
    typedef RectT <float> RectF;

} // namespace xl

#endif // #ifndef __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__
