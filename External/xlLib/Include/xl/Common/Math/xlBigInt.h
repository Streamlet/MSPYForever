//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBigIntT.h
//    Author:      Streamlet
//    Create Time: 2010-08-05
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLBigIntT_H_4ED560E8_F226_4D72_9016_828D1AA8696E_INCLUDED__
#define __XLBigIntT_H_4ED560E8_F226_4D72_9016_828D1AA8696E_INCLUDED__


#include "../../xlDef.h"
#include "../Containers/xlArray.h"
#include "../Containers/xlMap.h"
#include "../String/xlString.h"

namespace xl
{
    template <typename T>
    class BigIntT
    {
    public:
        BigIntT();
        BigIntT(char char_value);
        BigIntT(unsigned char uchar_value);
        BigIntT(short short_value);
        BigIntT(unsigned short ushort_value);
        BigIntT(int int_value);
        BigIntT(unsigned int uint_value);
        BigIntT(long long_value);
        BigIntT(unsigned long ulong_value);
        BigIntT(long long int64_value);
        BigIntT(unsigned long long uint64_value);
        BigIntT(unsigned char *buffer, size_t size);
        BigIntT(const wchar_t *string_value, unsigned int base = 10, const String &alphabet = L"0123456789ABCDEF");
        BigIntT(const String &string_value, unsigned int base = 10, const String &alphabet = L"0123456789ABCDEF");
        BigIntT(const BigIntT &that);
        BigIntT &operator = (const BigIntT &that);
        ~BigIntT();

    protected:
        Array<T> m_aValue;
        bool m_bPositive;

    public:
        bool IsPositive() const;
        Array<T> GetData() const;

    public:
        bool operator ==(const BigIntT &that) const;
        bool operator !=(const BigIntT &that) const;
        bool operator <(const BigIntT &that) const;
        bool operator >(const BigIntT &that) const;
        bool operator <=(const BigIntT &that) const;
        bool operator >=(const BigIntT &that) const;

    public:
        BigIntT &Neg();
        BigIntT &Inc();
        BigIntT &Dec();
        BigIntT &AddAbs(const BigIntT &addend);
        BigIntT &SubAbs(const BigIntT &subtrahend);
        BigIntT &Add(const BigIntT &addend);
        BigIntT &Sub(const BigIntT &subtrahend);
        BigIntT Mul(const BigIntT &multiplicator) const;
        BigIntT Div(const BigIntT &divisor, BigIntT &remainder) const;
        BigIntT Exp(const BigIntT &exponent) const;
        BigIntT ExpMod(const BigIntT &exponent, const BigIntT &divisor) const;

    public:
        BigIntT operator -() const;
        BigIntT &operator ++();
        BigIntT operator ++(int);
        BigIntT &operator --();
        BigIntT operator --(int);
        BigIntT operator +(const BigIntT &that) const;
        BigIntT operator -(const BigIntT &that) const;
        BigIntT operator *(const BigIntT &that) const;
        BigIntT operator /(const BigIntT &that) const;
        BigIntT operator %(const BigIntT &that) const;
        BigIntT &operator +=(const BigIntT &that);
        BigIntT &operator -=(const BigIntT &that);
        BigIntT &operator *=(const BigIntT &that);
        BigIntT &operator /=(const BigIntT &that);
        BigIntT &operator %=(const BigIntT &that);

    public:
        char ToChar() const;
        short ToShort() const;
        int ToInt() const;
        long ToLong() const;
        long long ToLongLong() const;

    public:
        BigIntT &FromString(const wchar_t *string_value, unsigned int base = 10, const String &alphabet = L"0123456789ABCDEF");
        BigIntT &FromString(const String &string_value, unsigned int base = 10, const String &alphabet = L"0123456789ABCDEF");
        String ToString(unsigned int base = 10, const String &alphabet = L"0123456789ABCDEF") const;
    };

    typedef BigIntT<unsigned int> BigInt;

    template <typename T>
    BigIntT<T>::BigIntT()
        : m_bPositive(true)
    {

    }

    template <typename T>
    BigIntT<T>::BigIntT(char char_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)char_value;

        if (char_value < 0)
        {
            val = (unsigned long long)-char_value;
            m_bPositive = false;
        }

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(unsigned char uchar_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)uchar_value;

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(short short_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)short_value;

        if (short_value < 0)
        {
            val = (unsigned long long)-short_value;
            m_bPositive = false;
        }

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(unsigned short ushort_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)ushort_value;

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(int int_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)int_value;

        if (int_value < 0)
        {
            val = (unsigned long long)-int_value;
            m_bPositive = false;
        }

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(unsigned int uint_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)uint_value;

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(long long_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)long_value;

        if (long_value < 0)
        {
            val = (unsigned long long)-long_value;
            m_bPositive = false;
        }

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(unsigned long ulong_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)ulong_value;

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(long long int64_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)int64_value;

        if (int64_value < 0)
        {
            val = (unsigned long long)-int64_value;
            m_bPositive = false;
        }

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(unsigned long long uint64_value)
        : m_bPositive(true)
    {
        unsigned long long val = (unsigned long long)uint64_value;

        while (val > 0)
        {
            m_aValue.PushBack((T)val);
            val >>= sizeof(T) * 8;
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(unsigned char *buffer, size_t size)
        : m_bPositive(true)
    {
        for (size_t i = 0; i < size / sizeof(T); ++i, buffer += sizeof(T))
        {
            m_aValue.PushBack(*(T *)buffer);
        }

        size_t rest = size % sizeof(T);

        if (rest > 0)
        {
            T val = 0;
            unsigned char *p = (unsigned char *)&val;

            for (size_t i = 0; i < rest; ++i)
            {
                p[i] = buffer[i];
            }

            m_aValue.PushBack(val);
        }
    }

    template <typename T>
    BigIntT<T>::BigIntT(const wchar_t *string_value, unsigned int base /*= 10*/, const String &alphabet /*= L"0123456789ABCDEF"*/)
    {
        FromString(string_value, base, alphabet);
    }

    template <typename T>
    BigIntT<T>::BigIntT(const String &string_value, unsigned int base /*= 10*/, const String &alphabet /*= L"0123456789ABCDEF"*/)
    {
        FromString(string_value, base, alphabet);
    }

    template <typename T>
    BigIntT<T>::BigIntT(const BigIntT &that)
        : m_bPositive(true)
    {
        this->m_bPositive = that.m_bPositive;
        this->m_aValue = that.m_aValue;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator = (const BigIntT<T> &that)
    {
        if (this != &that)
        {
            this->m_aValue = that.m_aValue;
            this->m_bPositive = that.m_bPositive;
        }

        return *this;
    }

    template <typename T>
    BigIntT<T>::~BigIntT()
    {

    }

    template <typename T>
    bool BigIntT<T>::IsPositive() const
    {
        return m_bPositive;
    }

    template <typename T>
    Array<T> BigIntT<T>::GetData() const
    {
        return m_aValue;
    }

    template <typename T>
    bool BigIntT<T>::operator ==(const BigIntT<T> &that) const
    {
        return (this->m_bPositive == that.m_bPositive) && (this->m_aValue == that.m_aValue);
    }

    template <typename T>
    bool BigIntT<T>::operator !=(const BigIntT<T> &that) const
    {
        return !(*this == that);
    }

    template <typename T>
    bool BigIntT<T>::operator <(const BigIntT<T> &that) const
    {
        if (this->m_bPositive != that.m_bPositive)
        {
            return !this->m_bPositive;
        }

        if (this->m_aValue.Size() != that.m_aValue.Size())
        {
            return this->m_aValue.Size() < that.m_aValue.Size();
        }

        if (!this->m_aValue.Empty())
        {
            for (size_t i = this->m_aValue.Size() - 1; true; --i)
            {
                if (this->m_aValue[i] != that.m_aValue[i])
                {
                    return this->m_aValue[i] < that.m_aValue[i];
                }

                if (i == 0)
                {
                    break;
                }
            }
        }

        return false;
    }

    template <typename T>
    bool BigIntT<T>::operator >(const BigIntT<T> &that) const
    {
        if (this->m_bPositive != that.m_bPositive)
        {
            return this->m_bPositive;
        }

        if (this->m_aValue.Size() != that.m_aValue.Size())
        {
            return this->m_aValue.Size() > that.m_aValue.Size();
        }

        if (!this->m_aValue.Empty())
        {
            for (size_t i = this->m_aValue.Size() - 1; true; --i)
            {
                if (this->m_aValue[i] != that.m_aValue[i])
                {
                    return this->m_aValue[i] > that.m_aValue[i];
                }

                if (i == 0)
                {
                    break;
                }
            }
        }

        return false;
    }

    template <typename T>
    bool BigIntT<T>::operator <=(const BigIntT<T> &that) const
    {
        if (this->m_bPositive != that.m_bPositive)
        {
            return !this->m_bPositive;
        }

        if (this->m_aValue.Size() != that.m_aValue.Size())
        {
            return this->m_aValue.Size() < that.m_aValue.Size();
        }

        if (!this->m_aValue.Empty())
        {
            for (size_t i = this->m_aValue.Size() - 1; true; --i)
            {
                if (this->m_aValue[i] != that.m_aValue[i])
                {
                    return this->m_aValue[i] < that.m_aValue[i];
                }

                if (i == 0)
                {
                    break;
                }
            }
        }

        return true;
    }

    template <typename T>
    bool BigIntT<T>::operator >=(const BigIntT<T> &that) const
    {
        if (this->m_bPositive != that.m_bPositive)
        {
            return this->m_bPositive;
        }

        if (this->m_aValue.Size() != that.m_aValue.Size())
        {
            return this->m_aValue.Size() > that.m_aValue.Size();
        }

        if (!this->m_aValue.Empty())
        {
            for (size_t i = this->m_aValue.Size() - 1; true; --i)
            {
                if (this->m_aValue[i] != that.m_aValue[i])
                {
                    return this->m_aValue[i] > that.m_aValue[i];
                }

                if (i == 0)
                {
                    break;
                }
            }
        }

        return true;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::Neg()
    {
        m_bPositive = !m_bPositive;
        return *this;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::Inc()
    {
        Add(1u);
        return *this;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::Dec()
    {
        Sub(1u);
        return *this;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::AddAbs(const BigIntT<T> &addend)
    {
        const Array<T> &rhs = addend.m_aValue;
        Array<T> &res = this->m_aValue;

        for (size_t i = 0; i < rhs.Size(); ++i)
        {
            T overflow = 0;

            while (res.Size() <= i)
            {
                res.PushBack((T)0);
            }

            res[i] += rhs[i];

            if (res[i] < rhs[i])
            {
                ++overflow;
            }

            for (size_t j = i + 1; overflow > 0; ++j)
            {
                if (res.Size() <= j)
                {
                    res.PushBack((T)0);
                }

                res[j] += overflow;

                if (res[j] < overflow)
                {
                    overflow = 1;
                }
                else
                {
                    overflow = 0;
                }
            }
        }

        return *this;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::SubAbs(const BigIntT<T> &subtrahend)
    {
        if (*this == subtrahend)
        {
            m_bPositive = true;
            m_aValue.Clear();
            return *this;
        }

        if (*this < subtrahend)
        {
            BigIntT<T> minuend = subtrahend;
            minuend.Sub(*this);
            minuend.Neg();
            *this = minuend;
            return *this;
        }

        const Array<T> &rhs = subtrahend.m_aValue;
        Array<T> &res = this->m_aValue;

        for (size_t i = 0; i < rhs.Size(); ++i)
        {
            T overflow = 0;
            T original = res[i];

            res[i] -= rhs[i];

            if (res[i] > original)
            {
                ++overflow;
            }

            for (size_t j = i + 1; overflow > 0; ++j)
            {
                original = res[j];
                res[j] -= overflow;

                if (res[j] > original)
                {
                    overflow = 1;
                }
                else
                {
                    overflow = 0;
                }
            }
        }

        while (!res.Empty() && *res.ReverseBegin() == 0)
        {
            res.Delete(res.ReverseBegin());
        }

        return *this;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::Add(const BigIntT<T> &addend)
    {
        if (this->m_bPositive != addend.m_bPositive)
        {
            return SubAbs(addend);
        }

        return AddAbs(addend);
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::Sub(const BigIntT<T> &subtrahend)
    {
        if (this->m_bPositive != subtrahend.m_bPositive)
        {
            return AddAbs(subtrahend);
        }

        return SubAbs(subtrahend);
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::Mul(const BigIntT<T> &multiplicator) const
    {
        BigIntT<T> product;

        const Array<T> &lhs = this->m_aValue, &rhs = multiplicator.m_aValue;
        Array<T> &res = product.m_aValue;

        if (lhs.Empty() || rhs.Empty())
        {
            return product;
        }

        res.Resize(lhs.Size() + rhs.Size(), 0);

        for (size_t i = 0; i < lhs.Size(); ++i)
        {
            for (size_t j = 0; j < rhs.Size(); ++j)
            {
                unsigned long long temp = lhs[i];
                temp *= rhs[j];

                for (size_t k = 0; temp > 0; ++k)
                {
                    res[i + j + k] += (T)temp;

                    if (res[i + j + k] < (T)temp)
                    {
                        temp >>= sizeof(T) * 8;
                        ++temp;
                    }
                    else
                    {
                        temp >>= sizeof(T) * 8;
                    }
                }
            }
        }

        while (!res.Empty() && *res.ReverseBegin() == 0)
        {
            res.PopBack();
        }

        if ((this->m_bPositive != multiplicator.m_bPositive) && !res.Empty())
        {
            product.m_bPositive = !product.m_bPositive;
        }

        return product;
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::Div(const BigIntT<T> &divisor, BigIntT<T> &remainder) const
    {
        if (divisor.m_aValue.Empty())
        {
            return 0;
        }

        BigIntT<T> dividend(*this), div(divisor);

        dividend.m_bPositive = true;
        div.m_bPositive = true;

        BigIntT<T> quotient;

        while (dividend >= div)
        {
            size_t zeros = dividend.m_aValue.Size() - div.m_aValue.Size();

            BigIntT<T> temp;
            temp.m_aValue.Insert(temp.m_aValue.Begin(), dividend.m_aValue.Begin() + (int)zeros, dividend.m_aValue.End());

            unsigned long long a = temp.m_aValue[temp.m_aValue.Size() - 1];
            unsigned long long b = div.m_aValue[div.m_aValue.Size() - 1];

            if (temp < div)
            {
                --zeros;
                temp.m_aValue.Insert(temp.m_aValue.Begin(), dividend.m_aValue.Begin() + (int)zeros, dividend.m_aValue.Begin() + (int)zeros + 1);
                a <<= sizeof(T) * 8;
                a += temp.m_aValue[temp.m_aValue.Size() - 2];
            }

            unsigned long long test = a / b;

            if (div.m_aValue.Size() >= 2)
            {
                while (b * test + ((div.m_aValue[div.m_aValue.Size() - 2] * test) >> sizeof(T) * 8) > a)
                {
                    --test;
                }
            }

            BigIntT<T> product = div.Mul(test);

            while (product > temp)
            {
                --test;
                product -= div;
            }

            BigIntT<T> res(test);

            for (size_t i = 0; i < zeros; ++i)
            {
                res.m_aValue.PushFront((T)0);
                product.m_aValue.PushFront((T)0);
            }

            quotient.Add(res);
            dividend.Sub(product);
        }

        remainder = dividend;

        remainder.m_bPositive = this->m_bPositive;
        quotient.m_bPositive = (this->m_bPositive == divisor.m_bPositive);

        return quotient;
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::Exp(const BigIntT<T> &exponent) const
    {
        if (!exponent.m_bPositive)
        {
            return 0u;
        }

        if (exponent.m_aValue.Empty())
        {
            return 1u;
        }

        BigIntT<T> power(1u);

        for (size_t i = exponent.m_aValue.Size() - 1; true; --i)
        {
            T n = exponent.m_aValue[i];

            for (T mask = (1u << (sizeof(T) * 8 - 1)); mask > 0; mask >>= 1)
            {
                power = power.Mul(power);

                if ((n & mask) != 0)
                {
                    power = power.Mul(*this);
                }
            }

            if (i == 0)
            {
                break;
            }
        }

        return power;
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::ExpMod(const BigIntT<T> &exponent, const BigIntT<T> &divisor) const
    {
        if (!exponent.m_bPositive)
        {
            return 0u;
        }

        if (exponent.m_aValue.Empty())
        {
            return 1u;
        }

        BigIntT<T> power(1u);

        for (size_t i = exponent.m_aValue.Size() - 1; true; --i)
        {
            T n = exponent.m_aValue[i];

            for (T mask = (1u << (sizeof(T) * 8 - 1)); mask > 0; mask >>= 1)
            {
                power = power.Mul(power);
                power.Div(divisor, power);

                if ((n & mask) != 0)
                {
                    power = power.Mul(*this);
                    power.Div(divisor, power);
                }
            }

            if (i == 0)
            {
                break;
            }
        }

        return power;
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator -() const
    {
        BigIntT<T> ret(*this);
        return ret.Neg();
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator ++()
    {
        return Inc();
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator ++(int)
    {
        BigIntT<T> ret(*this);
        Inc();
        return ret;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator --()
    {
        return Dec();
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator --(int)
    {
        BigIntT<T> ret(*this);
        Dec();
        return ret;
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator +(const BigIntT<T> &that) const
    {
        BigIntT<T> ret(*this);
        return ret.Add(that);
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator -(const BigIntT<T> &that) const
    {
        BigIntT<T> ret(*this);
        return  ret.Sub(that);
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator *(const BigIntT<T> &that) const
    {
        return Mul(that);
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator /(const BigIntT<T> &that) const
    {
        BigIntT<T> reminder;
        return Div(that, reminder);
    }

    template <typename T>
    BigIntT<T> BigIntT<T>::operator %(const BigIntT<T> &that) const
    {
        BigIntT<T> reminder;
        Div(that, reminder);
        return reminder;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator +=(const BigIntT<T> &that)
    {
        return Add(that);
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator -=(const BigIntT<T> &that)
    {
        return Sub(that);
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator *=(const BigIntT<T> &that)
    {
        return *this = Mul(that);
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator /=(const BigIntT<T> &that)
    {
        BigIntT<T> reminder;
        return *this = Div(that, reminder);
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::operator %=(const BigIntT<T> &that)
    {
        BigIntT<T> reminder;
        Div(that, reminder);
        return *this = reminder;
    }

    template <typename T>
    char BigIntT<T>::ToChar() const
    {
        long long ret = 0, temp = 0;
        size_t i = 0;

        while (i * sizeof(T) < sizeof(char) && m_aValue.Size() > i)
        {
            temp = m_aValue[i];
            temp <<= i * sizeof(T) * 8;
            ret |= temp;
            ++i;
        }

        if (!m_bPositive)
        {
            ret = - ret;
        }

        return (char)ret;
    }

    template <typename T>
    short BigIntT<T>::ToShort() const
    {
        long long ret = 0, temp = 0;
        size_t i = 0;

        while (i * sizeof(T) < sizeof(short) && m_aValue.Size() > i)
        {
            temp = m_aValue[i];
            temp <<= i * sizeof(T) * 8;
            ret |= temp;
            ++i;
        }

        if (!m_bPositive)
        {
            ret = - ret;
        }

        return (short)ret;
    }

    template <typename T>
    int BigIntT<T>::ToInt() const
    {
        long long ret = 0, temp = 0;
        size_t i = 0;

        while (i * sizeof(T) < sizeof(int) && m_aValue.Size() > i)
        {
            temp = m_aValue[i];
            temp <<= i * sizeof(T) * 8;
            ret |= temp;
            ++i;
        }

        if (!m_bPositive)
        {
            ret = - ret;
        }

        return (int)ret;
    }

    template <typename T>
    long BigIntT<T>::ToLong() const
    {
        long long ret = 0, temp = 0;
        size_t i = 0;

        while (i * sizeof(T) < sizeof(long) && m_aValue.Size() > i)
        {
            temp = m_aValue[i];
            temp <<= i * sizeof(T) * 8;
            ret |= temp;
            ++i;
        }

        if (!m_bPositive)
        {
            ret = - ret;
        }

        return (long)ret;
    }

    template <typename T>
    long long BigIntT<T>::ToLongLong() const
    {
        long long ret = 0, temp = 0;
        size_t i = 0;

        while (i * sizeof(T) < sizeof(long long) && m_aValue.Size() > i)
        {
            temp = m_aValue[i];
            temp <<= i * sizeof(T) * 8;
            ret |= temp;
            ++i;
        }

        if (!m_bPositive)
        {
            ret = - ret;
        }

        return (long long)ret;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::FromString(const wchar_t *string_value, unsigned int base /*= 10*/, const String &alphabet /*= L"0123456789ABCDEF"*/)
    {
        m_aValue.Clear();
        m_bPositive = true;

        if (base < 2 || base > (unsigned int)alphabet.Length())
        {
            return *this;
        }

        size_t begin = 0;
        bool positive = true;

        if (string_value[begin] == L'-')
        {
            positive = false;
            ++begin;
        }

        Map<wchar_t, unsigned char> alphabet_reverse;

        for (unsigned char i = 0; i < alphabet.Length(); ++i)
        {
            alphabet_reverse.Insert(alphabet[i], i);
        }

        for (size_t i = begin; string_value[i] != '\0'; ++i)
        {
            wchar_t ch = string_value[i];

            Map<wchar_t, unsigned char>::Iterator it = alphabet_reverse.Find(ch);

            if (it == alphabet_reverse.End())
            {
                break;
            }

            *this = (*this) * base + it->Value;
        }

        this->m_bPositive = positive;

        return *this;
    }

    template <typename T>
    BigIntT<T> &BigIntT<T>::FromString(const String &string_value, unsigned int base /*= 10*/, const String &alphabet /*= L"0123456789ABCDEF"*/)
    {
        return FromString(string_value, base, alphabet);
    }

    template <typename T>
    String BigIntT<T>::ToString(unsigned int base /*= 10*/, const String &alphabet /*= L"0123456789ABCDEF"*/) const
    {
        if (base < 2 || base > (unsigned int)alphabet.Length())
        {
            return L"";
        }

        BigIntT<T> temp(*this);
        temp.m_bPositive = true;

        String ret;

        const unsigned int EXP[] = { 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 };
        unsigned int exp = 0;

        if (base <= 16 && ((exp = EXP[base]) != 0))
        {
            for (size_t i = m_aValue.Size() - 1; true; --i)
            {
                T val = m_aValue[i];
                T mask = base - 1;
                unsigned int bits = 0;

                while ((mask & (1 << (sizeof(T) * 8 - 1))) == 0)
                {
                    mask *= base;
                    bits += exp;
                }

                if (i == m_aValue.Size() - 1)
                {
                    while ((mask & val) == 0)
                    {
                        mask /= base;
                        bits -= exp;
                    }
                }

                while (mask != 0)
                {
                    ret.AppendBack(alphabet[(val & mask) >> bits]);
                    mask /= base;
                    bits -= exp;
                }

                if (i == 0)
                {
                    break;
                }
            }
        }
        else
        {
            do 
            {
                BigIntT<T> reminder;
                temp = temp.Div(base, reminder);

                ret.AppendFront(alphabet[reminder.ToChar()]);

            } while (temp > 0u);
        }

        if (!this->m_bPositive)
        {
            ret.AppendFront(L'-');
        }

        return ret;
    }

} // namespace xl

#endif // #ifndef __XLBigIntT_H_4ED560E8_F226_4D72_9016_828D1AA8696E_INCLUDED__
