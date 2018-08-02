//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMathBase.h
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__
#define __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__


#include "../../xlDef.h"
#include "../Meta/xlTuple.h"

namespace xl
{
#ifdef __XL_CPP11

    template <typename T, typename U>
    auto Min(T t, U u) -> decltype(t + u)
    {
        return (t <= u ? t : u);
    }

    template <typename T, typename U>
    auto Max(T t, U u) -> decltype(t + u)
    {
        return (t >= u ? t : u);
    }

#else

    template <typename T>
    T Min(T t, T u)
    {
        return (t <= u ? t : u);
    }

    template <typename T>
    T Max(T t, T u)
    {
        return (t >= u ? t : u);
    }

#endif

#ifdef __XL_CPP11

    template <typename T>
    struct SizeT : public TupleT<SizeT<T>, T, T>
    {
        typedef TupleT<SizeT<T>, T, T> Base;

        SizeT() : Base()
        {

        }

        template <typename U>
        SizeT(U cx, U cy) : Base((T)cx, (T)cy)
        {

        }

        template <typename U>
        SizeT(const SizeT<U> &that) : Base((T)that.cx, (T)that.cy)
        {

        }

        T &CX()
        {
            return At<0>();
        }

        T &CY()
        {
            return At<1>();
        }

        const T &CX() const
        {
            return At<0>();
        }

        const T &CY() const
        {
            return At<1>();
        }

        T &Width()
        {
            return At<0>();
        }

        T &Height()
        {
            return At<1>();
        }

        const T &Width() const
        {
            return At<0>();
        }

        const T &Height() const
        {
            return At<1>();
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
    struct PointT : public TupleT<PointT<T>, T, T>
    {
        typedef TupleT<PointT<T>, T, T> Base;

        PointT() : Base()
        {

        }

        template <typename U>
        PointT(U x, U y) : Base((T)x, (T)y)
        {

        }

        template <typename U>
        PointT(const PointT<U> &that) : Base((T)that.cx, (T)that.cy)
        {

        }

        template <typename U>
        PointT(const SizeT<U> &that) : Base((T)that.cx, (T)that.cy)
        {

        }

        T &X()
        {
            return At<0>();
        }

        T &Y()
        {
            return At<1>();
        }

        const T &X() const
        {
            return At<0>();
        }

        const T &Y() const
        {
            return At<1>();
        }

        template <typename U>
        PointT &Offset(U delta)
        {
            return *this += delta;
        }

        template <typename U>
        PointT &Offset(U dx, U dy)
        {
            return *this += SizeT(dx, dy);
        }
    };

    template <typename U>
    struct RectT : TupleT<RectT<U>, U, U, U, U>
    {
        typedef TupleT<RectT<U>, U, U, U, U> Base;

        RectT() : Base()
        {

        }

        template <typename V>
        RectT(V left, V top, V right, V bottom) : Base((U)left, (U)top, (U)right, (U)bottom)
        {

        }

        template <typename V>
        RectT(const RectT<V> &that) : Base((U)that.Left(), (U)that.Top(), (U)that.Right(), (U)that.Bottom())
        {

        }

        template <typename V>
        RectT(const PointT<V> &pt, const SizeT<V> &sz) : Base((U)pt.x, (U)pt.y, (U)(pt.x + sz.cx), (U)(pt.y + sz.cy))
        {

        }

        U &L()
        {
            return At<0>();
        }

        U &T()
        {
            return At<1>();
        }

        U &R()
        {
            return At<2>();
        }

        U &B()
        {
            return At<3>();
        }

        const U &L() const
        {
            return At<0>();
        }

        const U &T() const
        {
            return At<1>();
        }

        const U &R() const
        {
            return At<2>();
        }

        const U &B() const
        {
            return At<3>();
        }

        U &Left()
        {
            return At<0>();
        }

        U &Top()
        {
            return At<1>();
        }

        U &Right()
        {
            return At<2>();
        }

        U &Bottom()
        {
            return At<3>();
        }

        const U &Left() const
        {
            return At<0>();
        }

        const U &Top() const
        {
            return At<1>();
        }

        const U &Right() const
        {
            return At<2>();
        }

        const U &Bottom() const
        {
            return At<3>();
        }

        const U &X() const
        {
            return L();
        }

        const U &Y() const
        {
            return T();
        }

        const U &&Width() const
        {
            return R() - L();
        }

        const U &&Height() const
        {
            return B() - T();
        }

        template <typename V>
        RectT &Offset(V delta)
        {
            return *this += delta;
        }

        template <typename V>
        RectT &Offset(V dx, V dy)
        {
            return *this += RectT(dx, dy, dx, dy);
        }

        template <typename V>
        RectT Offset(V delta) const
        {
            RectT r(*this);
            r.Offset(delta);
            return r;
        }

        template <typename V>
        RectT Offset(V dx, V dy) const
        {
            RectT r(*this);
            r.Offset(dx, dy);
            return r;
        }

        template <typename V>
        RectT &Inflate(V delta)
        {
            return *this += RectT(-delta, -delta, delta, delta);
        }

        template <typename V>
        RectT &Deflate(V delta)
        {
            return *this -= RectT(-delta, -delta, delta, delta);
        }

        template <typename V>
        RectT &Inflate(V dx, V dy)
        {
            return *this += RectT(-dx, -dy, dx, dy);
        }

        template <typename V>
        RectT &Deflate(V dx, V dy)
        {
            return *this -= RectT(-dx, -dy, dx, dy);
        }

        template <typename V>
        RectT &Inflate(V dl, V dt, V dr, V db)
        {
            return *this += RectT(-dl, -dt, dr, db);
        }

        template <typename V>
        RectT &Deflate(V dl, V dt, V dr, V db)
        {
            return *this -= RectT(-dl, -dt, dr, db);
        }

        template <typename V>
        RectT Inflate(V delta) const
        {
            RectT r(*this);
            r.Inflate(delta);
            return r;
        }

        template <typename V>
        RectT Deflate(V delta) const
        {
            RectT r(*this);
            r.Deflate(delta);
            return r;
        }

        template <typename V>
        RectT Inflate(V dx, V dy) const
        {
            RectT r(*this);
            r.Inflate(dx, dy);
            return r;
        }

        template <typename V>
        RectT Deflate(V dx, V dy) const
        {
            RectT r(*this);
            r.Deflate(dx, dy);
            return r;
        }

        template <typename V>
        RectT Inflate(V dl, V dt, V dr, V db) const
        {
            RectT r(*this);
            r.Inflate(dl, dt, dr, db);
            return r;
        }

        template <typename V>
        RectT Deflate(V dl, V dt, V dr, V db) const
        {
            RectT r(*this);
            r.Deflate(dl, dt, dr, db);
            return r;
        }
    };

    template <typename T>
    struct ColorT : public TupleT<ColorT<T>, T, T, T, T>
    {
        typedef TupleT<ColorT<T>, T, T, T, T> Base;

        ColorT() : Base()
        {

        }

        ColorT(T a, T r, T g, T b) : Base(a, r, g, b)
        {

        }

        ColorT(const ColorT<T> &that) : Base(that.A(), that.R(), that.G(), that.B())
        {

        }

        T &A()
        {
            return At<0>();
        }

        T &R()
        {
            return At<1>();
        }

        T &G()
        {
            return At<2>();
        }

        T &B()
        {
            return At<3>();
        }

        const T &A() const
        {
            return At<0>();
        }

        const T &R() const
        {
            return At<1>();
        }

        const T &G() const
        {
            return At<2>();
        }

        const T &B() const
        {
            return At<3>();
        }

        T &Alpha()
        {
            return At<3>();
        }

        T &Red()
        {
            return At<2>();
        }

        T &Green()
        {
            return At<1>();
        }

        T &Blue()
        {
            return At<0>();
        }

        const T &Alpha() const
        {
            return At<3>();
        }

        const T &Red() const
        {
            return At<2>();
        }

        const T &Green() const
        {
            return At<1>();
        }

        const T &Blue() const
        {
            return At<0>();
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

    typedef ColorT<unsigned char> Color;
    typedef ColorT<float>         ColorF;

#endif

} // namespace xl

#endif // #ifndef __XLMATHBASE_H_C306B62C_2117_45D0_A98E_11BE64AFC603_INCLUDED__
