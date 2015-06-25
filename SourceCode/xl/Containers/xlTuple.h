//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTuple.h
//    Author:      Streamlet
//    Create Time: 2011-04-23
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTUPLE_H_4720D247_760A_43F2_9611_6673153C5C68_INCLUDED__
#define __XLTUPLE_H_4720D247_760A_43F2_9611_6673153C5C68_INCLUDED__


#include "../Meta/xlStaticAssert.h"
#include "../Meta/xlTypeTraits.h"
#include "../xlDef.h"

namespace xl
{
// #ifndef XL_TUPLE_DEFINE_MAX
// #define XL_TUPLE_DEFINE_MAX  20
// #endif
// 
// #define XL_TUPLE_TYPENAME_DECLARE_NT_PATTERN(n)     typename T##n = NullType
// #define XL_TUPLE_TYPENAME_DECLARE_NT(n)             XL_REPZ(XL_TUPLE_TYPENAME_DECLARE_NT_PATTERN, n, XL_COMMA)
// 
// #define XL_TUPLE_TYPENAME_DECLARE_PATTERN(n)        typename T##n
// #define XL_TUPLE_TYPENAME_DECLARE(n)                XL_REPZ(XL_TUPLE_TYPENAME_DECLARE_PATTERN, n, XL_COMMA)
// 
// #define XL_TUPLE_MEMBER_DECLARE_PATTERN(n)          T##n _##n;
// #define XL_TUPLE_MEMBER_DECLARE(n)                  XL_REPZ(XL_TUPLE_MEMBER_DECLARE_PATTERN, n, XL_NIL)
// 
// #define XL_TUPLE_TYPENAME_LIST_PATTERN(n)           T##n
// #define XL_TUPLE_TYPENAME_LIST(n)                   XL_REPZ(XL_TUPLE_TYPENAME_LIST_PATTERN, n, XL_COMMA)
// 
// #define XL_TUPLE_TYPENAME_VARIABLE_PATTERN(n)       T##n _##n
// #define XL_TUPLE_TYPENAME_VARIABLE(n)               XL_REPZ(XL_TUPLE_TYPENAME_VARIABLE_PATTERN, n, XL_COMMA)
// 
// #define XL_TUPLE_INITIALIZE_LIST_PATTERN(n)         _##n(_##n)
// #define XL_TUPLE_INITIALIZE_LIST(n)                 XL_REPZ(XL_TUPLE_INITIALIZE_LIST_PATTERN, n, XL_COMMA)
// 
// #define XL_TUPLE_INITIALIZE_LIST_COPY_PATTERN(n)    _##n(that._##n)
// #define XL_TUPLE_INITIALIZE_LIST_COPY(n)            XL_REPZ(XL_TUPLE_INITIALIZE_LIST_COPY_PATTERN, n, XL_COMMA)
// 
// #define XL_TUPLE_ASSIGN_PATTERN(n)                  this->_##n = that._##n;
// #define XL_TUPLE_ASSIGN(n)                          XL_REPZ(XL_TUPLE_ASSIGN_PATTERN, n, XL_NIL)
// 
// #define XL_TUPLE_EQUAL_PATTERN(n)                   this->_##n == that._##n
// #define XL_TUPLE_EQUAL(n)                           XL_REPZ(XL_TUPLE_EQUAL_PATTERN, n, &&)
// 
// #define XL_TUPLE_NOT_EQUAL_PATTERN(n)               this->_##n != that._##n
// #define XL_TUPLE_NOT_EQUAL(n)                       XL_REPZ(XL_TUPLE_NOT_EQUAL_PATTERN, n, ||)
// 
// #define XL_TUPLE_LITTER_PATTERN(n)                  if (this->_##n < that._##n)         \
//                                                     {                                   \
//                                                         return true;                    \
//                                                     }                                   \
//                                                     else if (that._##n < this->_##n)    \
//                                                     {                                   \
//                                                         return false;                   \
//                                                     }
// #define XL_TUPLE_LITTER(n)                          XL_REPZ(XL_TUPLE_LITTER_PATTERN, n, XL_NIL)
// 
// #define XL_TUPLE_GREATER_PATTERN(n)                 if (this->_##n > that._##n)         \
//                                                     {                                   \
//                                                         return true;                    \
//                                                     }                                   \
//                                                     else if (that._##n > this->_##n)    \
//                                                     {                                   \
//                                                         return false;                   \
//                                                     }
// #define XL_TUPLE_GREATER(n)                         XL_REPZ(XL_TUPLE_GREATER_PATTERN, n, XL_NIL)
// 
//     template <XL_TUPLE_TYPENAME_DECLARE_NT(XL_INC(XL_TUPLE_DEFINE_MAX))>
//     class Tuple;
// 
// #define XL_TUPLE_IMPLEMENT_PATTERN(n)               \
//                                                     \
//     template <XL_TUPLE_TYPENAME_DECLARE(n)>         \
//     class Tuple<XL_TUPLE_TYPENAME_LIST(n)>          \
//     {                                               \
//     public:                                         \
//         XL_TUPLE_MEMBER_DECLARE(n)                  \
//                                                     \
//     public:                                         \
//         Tuple()                                     \
//         {                                           \
//                                                     \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         Tuple(const T &that)                        \
//             : XL_TUPLE_INITIALIZE_LIST_COPY(n)      \
//         {                                           \
//                                                     \
//         }                                           \
//                                                     \
//         Tuple(XL_TUPLE_TYPENAME_VARIABLE(n))        \
//             : XL_TUPLE_INITIALIZE_LIST(n)           \
//         {                                           \
//                                                     \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         Tuple &operator = (const T &that)           \
//         {                                           \
//             XL_STATIC_ASSERT(Size <= T::Size);      \
//             XL_TUPLE_ASSIGN(n)                      \
//                                                     \
//             return *this;                           \
//         }                                           \
//                                                     \
//         Tuple &operator = (const Tuple &that)       \
//         {                                           \
//             if (this != &that)                      \
//             {                                       \
//                 XL_TUPLE_ASSIGN(n)                  \
//             }                                       \
//                                                     \
//             return *this;                           \
//         }                                           \
//                                                     \
//     public:                                         \
//         static const size_t Size = n;               \
//                                                     \
//     public:                                         \
//         template <typename T>                       \
//         bool operator == (const T &that) const      \
//         {                                           \
//             XL_STATIC_ASSERT(Size == T::Size);      \
//             return XL_TUPLE_EQUAL(n);               \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         bool operator != (const T &that) const      \
//         {                                           \
//             XL_STATIC_ASSERT(Size == T::Size);      \
//             return XL_TUPLE_NOT_EQUAL(n);           \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         bool operator < (const T &that) const       \
//         {                                           \
//             XL_STATIC_ASSERT(Size == T::Size);      \
//             XL_TUPLE_LITTER(n)                      \
//             return false;                           \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         bool operator > (const T &that) const       \
//         {                                           \
//             XL_STATIC_ASSERT(Size == T::Size);      \
//             XL_TUPLE_GREATER(n)                     \
//             return false;                           \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         bool operator <= (const T &that) const      \
//         {                                           \
//             XL_STATIC_ASSERT(Size == T::Size);      \
//             XL_TUPLE_LITTER(n)                      \
//             return true;                            \
//         }                                           \
//                                                     \
//         template <typename T>                       \
//         bool operator >= (const T &that) const      \
//         {                                           \
//             XL_STATIC_ASSERT(Size == T::Size);      \
//             XL_TUPLE_GREATER(n)                     \
//             return true;                            \
//         }                                           \
//     };                                              \
// 
// #define XL_TUPLE_IMPLEMENT(n)    XL_REPY(XL_TUPLE_IMPLEMENT_PATTERN, n, XL_NIL)
// 
// XL_TUPLE_IMPLEMENT(XL_TUPLE_DEFINE_MAX)

    template <typename... T>
    struct Tuple;

    template <typename ImplType, typename... T>
    struct TupleT;

    template <typename ImplType, size_t Index, typename... T>
    class TupleImpl;

    template <typename ImplType, typename... T>
    struct TupleT<ImplType, T...> : public TupleImpl<ImplType, 0, T...>
    {
        typedef TupleImpl<ImplType, 0, T...> Base;

        static const size_t Size = sizeof...(T);

        template <typename... U>
        TupleT(U... u) : Base(u...)
        {

        }

        template <typename I, typename... U>
        TupleT(const TupleT<I, U...> &that) : Base(that)
        {

        }
    };

    template <typename ImplType>
    struct TupleT<ImplType> : public TupleImpl<ImplType, 0>
    {
        typedef TupleImpl<ImplType, 0> Base;

        static const size_t Size = 0;

        TupleT() : Base()
        {

        }

        template <typename I, size_t Index, typename... U>
        TupleT(const TupleImpl<I, Index, U...> &that) : Base(that)
        {

        }
    };

    template <typename ImplType, size_t Index>
    class TupleImpl<ImplType, Index>
    {
    public:
        TupleImpl()
        {

        }

        template <typename I, typename... U>
        TupleImpl(const TupleT<I, U...> &that)
        {

        }

        template <typename I, typename... U>
        ImplType &operator = (const TupleT<I, U...> &that)
        {
            return (ImplType &)*this;
        }

        template <typename I, typename... U>
        bool operator == (const TupleT<I, U...> &that) const
        {
            return true;
        }

        template <typename I, typename... U>
        bool operator != (const TupleT<I, U...> &that) const
        {
            return false;
        }

        template <typename I, typename... U>
        bool operator < (const TupleT<I, U...> &that) const
        {
            return false;
        }

        template <typename I, typename... U>
        bool operator > (const TupleT<I, U...> &that) const
        {
            return false;
        }

        template <typename I, typename... U>
        bool operator <= (const TupleT<I, U...> &that) const
        {
            return false;
        }

        template <typename I, typename... U>
        bool operator >= (const TupleT<I, U...> &that) const
        {
            return false;
        }

        template <typename U>
        ImplType &operator += (U delta)
        {
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator -= (U delta)
        {
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator *= (U factor)
        {
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator /= (U factor)
        {
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator %= (U factor)
        {
            return (ImplType &)*this;
        }

        template <typename I, typename... U>
        ImplType &operator += (const TupleT<I, U...> &that)
        {
            return (ImplType &)*this;
        }

        template <typename I, typename... U>
        ImplType &operator -= (const TupleT<I, U...> &that)
        {
            return (ImplType &)*this;
        }

        ImplType &operator += (const ImplType &that)
        {
            return (ImplType &)*this;
        }

        ImplType &operator -= (const ImplType &that)
        {
            return (ImplType &)*this;
        }

        template <typename... U>
        ImplType &operator += (const Tuple<U...> &that)
        {
            return (ImplType &)*this;
        }

        template <typename... U>
        ImplType &operator -= (const Tuple<U...> &that)
        {
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType operator + (U delta) const
        {
            ImplType r(*this);
            r += delta;
            return r;
        }

        template <typename U>
        ImplType operator - (U delta) const
        {
            ImplType r(*this);
            r -= delta;
            return r;
        }

        template <typename U>
        ImplType operator * (U factor) const
        {
            ImplType r(*this);
            r *= factor;
            return r;
        }

        template <typename U>
        ImplType operator / (U factor) const
        {
            ImplType r(*this);
            r /= factor;
            return r;
        }

        template <typename U>
        ImplType operator % (U factor) const
        {
            ImplType r(*this);
            r %= factor;
            return r;
        }

        template <typename I, typename... U>
        ImplType operator + (const TupleT<I, U...> &that) const
        {
            ImplType r(*this);
            r += that;
            return r;
        }

        template <typename I, typename... U>
        ImplType operator - (const TupleT<I, U...> &that) const
        {
            ImplType r(*this);
            r -= that;
            return r;
        }

        template <typename... U>
        ImplType operator + (const Tuple<U...> &that) const
        {
            ImplType r(*this);
            r += that;
            return r;
        }

        template <typename... U>
        ImplType operator - (const Tuple<U...> &that) const
        {
            ImplType r(*this);
            r -= that;
            return r;
        }

        ImplType operator + (const ImplType &that) const
        {
            ImplType r(*this);
            r += that;
            return r;
        }

        ImplType operator - (const ImplType &that) const
        {
            ImplType r(*this);
            r -= that;
            return r;
        }

        template <int N>
        const int &&At() const
        {
            static_assert(false, "Invalid index.");
            return 0;
        }

        template <int N>
        int Get() const
        {
            static_assert(false, "Invalid index.");
            return 0;
        }

        template <int N>
        void Set(int i)
        {
            static_assert(false, "Invalid index.");
        }
    };

    template <typename ImplType, size_t Index, typename Ti, typename... T>
    class TupleImpl<ImplType, Index, Ti, T...> : public TupleImpl<ImplType, Index + 1, T...>
    {
    public:
        typedef TupleImpl<ImplType, Index + 1, T...> Base;

        TupleImpl() : m_tValue(), Base()
        {

        }

        TupleImpl(Ti ti, T... t) : m_tValue((Ti)ti), Base(t...)
        {

        }

        template <typename I, typename... U>
        TupleImpl(const TupleT<I, U...> &that) : m_tValue((Ti)that.At<Index>()), Base(that)
        {

        }

        template <typename I, typename... U>
        ImplType &operator = (const TupleT<I, U...> &that)
        {
            if (this != &that)
            {
                m_tValue = (Ti)that.At<Index>();
                Base::operator = (that);
            }

            return (ImplType &)*this;
        }

        template <typename I, typename... U>
        bool operator == (const TupleT<I, U...> &that) const
        {
            if (!(m_tValue == that.At<Index>()))
            {
                return false;
            }

            return Base::operator == (that);
        }

        template <typename I, typename... U>
        bool operator != (const TupleT<I, U...> &that) const
        {
            if (m_tValue != that.At<Index>())
            {
                return true;
            }

            return Base::operator != (that);
        }

        template <typename I, typename... U>
        bool operator < (const TupleT<I, U...> &that) const
        {
            if (m_tValue < that.At<Index>())
            {
                return true;
            }

            return Base::operator < (that);
        }

        template <typename I, typename... U>
        bool operator > (const TupleT<I, U...> &that) const
        {
            if (m_tValue > that.At<Index>())
            {
                return true;
            }

            return Base::operator > (that);
        }

        template <typename I, typename... U>
        bool operator <= (const TupleT<I, U...> &that) const
        {
            if (m_tValue <= that.At<Index>())
            {
                return true;
            }

            return Base::operator <= (that);
        }

        template <typename I, typename... U>
        bool operator >= (const TupleT<I, U...> &that) const
        {
            if (m_tValue >= that.At<Index>())
            {
                return true;
            }

            return Base::operator >= (that);
        }

        template <typename U>
        ImplType &operator += (U delta)
        {
            m_tValue = (Ti)(m_tValue + delta);
            Base::operator += (delta);
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator -= (U delta)
        {
            m_tValue = (Ti)(m_tValue - delta);
            Base::operator -= (delta);
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator *= (U factor)
        {
            m_tValue = (Ti)(m_tValue * factor);
            Base::operator *= (factor);
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator /= (U factor)
        {
            m_tValue = (Ti)(m_tValue / factor);
            Base::operator /= (factor);
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType &operator %= (U factor)
        {
            m_tValue = (Ti)(m_tValue % factor);
            Base::operator %= (factor);
            return (ImplType &)*this;
        }

        template <typename I, typename... U>
        ImplType &operator += (const TupleT<I, U...> &that)
        {
            m_tValue = (Ti)(m_tValue + that.At<Index>());
            Base::operator += (that);
            return (ImplType &)*this;
        }

        template <typename I, typename... U>
        ImplType &operator -= (const TupleT<I, U...> &that)
        {
            m_tValue = (Ti)(m_tValue - that.At<Index>());
            Base::operator += (that);
            return (ImplType &)*this;
        }

        template <typename... U>
        ImplType &operator += (const Tuple<U...> &that)
        {
            m_tValue = (Ti)(m_tValue + that.At<Index>());
            Base::operator += (that);
            return (ImplType &)*this;
        }

        template <typename... U>
        ImplType &operator -= (const Tuple<U...> &that)
        {
            m_tValue = (Ti)(m_tValue - that.At<Index>());
            Base::operator += (that);
            return (ImplType &)*this;
        }

        ImplType &operator += (const ImplType &that)
        {
            m_tValue = (Ti)(m_tValue + that.At<Index>());
            Base::operator += (that);
            return (ImplType &)*this;
        }

        ImplType &operator -= (const ImplType &that)
        {
            m_tValue = (Ti)(m_tValue - that.At<Index>());
            Base::operator += (that);
            return (ImplType &)*this;
        }

        template <typename U>
        ImplType operator + (U delta) const
        {
            ImplType r(*this);
            r += delta;
            return r;
        }

        template <typename U>
        ImplType operator - (U delta) const
        {
            ImplType r(*this);
            r -= delta;
            return r;
        }

        template <typename U>
        ImplType operator * (U factor) const
        {
            ImplType r(*this);
            r *= factor;
            return r;
        }

        template <typename U>
        ImplType operator / (U factor) const
        {
            ImplType r(*this);
            r /= factor;
            return r;
        }

        template <typename U>
        ImplType operator % (U factor) const
        {
            ImplType r(*this);
            r %= factor;
            return r;
        }

        template <typename I, typename... U>
        ImplType operator + (const TupleT<I, U...> &that) const
        {
            ImplType r(*this);
            r += that;
            return r;
        }

        template <typename I, typename... U>
        ImplType operator - (const TupleT<I, U...> &that) const
        {
            ImplType r(*this);
            r -= that;
            return r;
        }

        ImplType operator + (const ImplType &that) const
        {
            ImplType r(*this);
            r += that;
            return r;
        }

        ImplType operator - (const ImplType &that) const
        {
            ImplType r(*this);
            r -= that;
            return r;
        }

        template <int N>
        Ti &At()
        {
            return Base::At<N>();
        }

        template <>
        Ti &At<Index>()
        {
            return m_tValue;
        }

        template <int N>
        const Ti &At() const
        {
            return Base::At<N>();
        }

        template <>
        const Ti &At<Index>() const
        {
            return m_tValue;
        }

        template <int N>
        const Ti &&Get() const
        {
            return Base::Get<N>();
        }

        template <>
        const Ti &&Get<Index>() const
        {
            return m_tValue;
        }

        template <int N>
        void Set(const Ti &ti)
        {
            return Base::Set<N>(ti);
        }

        template <>
        void Set<Index>(const Ti &ti)
        {
            m_tValue = ti;
        }

    protected:
        Ti m_tValue;
    };

    template <typename... T>
    struct Tuple<T...> : public TupleT<Tuple<T...>, T...>
    {
        typedef TupleT<Tuple<T...>, T...> Base;

        Tuple() : Base()
        {

        }

        Tuple(T... t) : Base(t...)
        {

        }

        template <typename... U>
        Tuple(const Tuple<U...> &that) : Base(that)
        {

        }
    };

    template <>
    struct Tuple<> : public TupleT<Tuple<>>
    {
        typedef TupleT<Tuple<>> Base;

        Tuple() : Base()
        {

        }

        template <typename... U>
        Tuple(const Tuple<U...> &that) : Base(that)
        {

        }
    };

} // namespace xl


#endif // #ifndef __XLTUPLE_H_4720D247_760A_43F2_9611_6673153C5C68_INCLUDED__
