//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMD5.h
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMD5_H_9F168AAD_4EE5_4F50_A910_E9280F1CBA2E_INCLUDED__
#define __XLMD5_H_9F168AAD_4EE5_4F50_A910_E9280F1CBA2E_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"

namespace xl
{
    class MD5
    {
    public:
        static const size_t DIGEST_LENGTH = 16;
        typedef unsigned char Digest[DIGEST_LENGTH];

    public:
        static void Calculate(const void *lpBuffer, size_t cbSize, Digest &digest)
        {
            MD5 md5;

            md5.AppendData(lpBuffer, cbSize);
            md5.GetDigest(digest);
        }

    public:
        MD5()
        {
            Initialize();
        }

    public:
        void AppendData(const void *lpBuffer, size_t cbSize)
        {
            size_t cbCopied = 0;

            while (cbCopied < cbSize)
            {
                size_t cbToCopy = cbSize - cbCopied > BUFFER_LENGTH - m_cbBufferUsed ? BUFFER_LENGTH - m_cbBufferUsed : cbSize - cbCopied;

                Memory::Copy(m_ctx.buffer + m_cbBufferUsed, (const unsigned char *)lpBuffer + cbCopied, cbToCopy);

                cbCopied += cbToCopy;
                m_cbBufferUsed += cbToCopy;

                if (m_cbBufferUsed == 64)
                {
                    Transform(m_ctx);
                    m_cbBufferUsed = 0;
                }
            }

            m_cbTotalSize += cbSize;
        }

        void MD5::GetDigest(Digest &digest)
        {
            if (m_cbBufferUsed >= BUFFER_LIMIT)
            {
                Memory::Copy(m_ctx.buffer + m_cbBufferUsed, PADDING, BUFFER_LENGTH - m_cbBufferUsed);
                Transform(m_ctx);
                Memory::Copy(m_ctx.buffer, PADDING + BUFFER_LENGTH - m_cbBufferUsed, BUFFER_LIMIT);
            }
            else
            {
                Memory::Copy(m_ctx.buffer + m_cbBufferUsed, PADDING, BUFFER_LIMIT - m_cbBufferUsed);
            }

            m_cbTotalSize *= BYTE_BITS_LENGTH;
            *(unsigned long long *)(m_ctx.buffer + BUFFER_LIMIT) = m_cbTotalSize;

            Transform(m_ctx);

            Memory::Copy(digest, m_ctx.digest, sizeof(Digest));

            Initialize();
        }

    private:
        static const size_t BUFFER_LENGTH = 64;
        typedef unsigned char Buffer[BUFFER_LENGTH];

        struct CTX
        {
            Digest digest;
            Buffer buffer;
        };

    private:
        static const size_t BYTE_BITS_LENGTH = 8;
        static const size_t BUFFER_LIMIT = BUFFER_LENGTH - sizeof(unsigned long long);

    private:
        CTX m_ctx;
        size_t m_cbBufferUsed;
        unsigned long long m_cbTotalSize;

    private:
        void Initialize()
        {
            Memory::Zero(m_ctx);
            Memory::Copy(m_ctx.digest, STATE, sizeof(m_ctx.digest));

            m_cbBufferUsed = 0;
            m_cbTotalSize = 0;
        }

        void Transform(CTX &ctx)
        {
            unsigned int *state = (unsigned int *)ctx.digest;
            unsigned int a = state[0];
            unsigned int b = state[1];
            unsigned int c = state[2];
            unsigned int d = state[3];
            unsigned int *x = (unsigned int *)ctx.buffer;

            // Round 1
            FF(a, b, c, d, x[ 0], S11, T01);
            FF(d, a, b, c, x[ 1], S12, T02);
            FF(c, d, a, b, x[ 2], S13, T03);
            FF(b, c, d, a, x[ 3], S14, T04);
            FF(a, b, c, d, x[ 4], S11, T05);
            FF(d, a, b, c, x[ 5], S12, T06);
            FF(c, d, a, b, x[ 6], S13, T07);
            FF(b, c, d, a, x[ 7], S14, T08);
            FF(a, b, c, d, x[ 8], S11, T09);
            FF(d, a, b, c, x[ 9], S12, T10);
            FF(c, d, a, b, x[10], S13, T11);
            FF(b, c, d, a, x[11], S14, T12);
            FF(a, b, c, d, x[12], S11, T13);
            FF(d, a, b, c, x[13], S12, T14);
            FF(c, d, a, b, x[14], S13, T15);
            FF(b, c, d, a, x[15], S14, T16);

            // Round 2
            GG(a, b, c, d, x[ 1], S21, T17);
            GG(d, a, b, c, x[ 6], S22, T18);
            GG(c, d, a, b, x[11], S23, T19);
            GG(b, c, d, a, x[ 0], S24, T20);
            GG(a, b, c, d, x[ 5], S21, T21);
            GG(d, a, b, c, x[10], S22, T22);
            GG(c, d, a, b, x[15], S23, T23);
            GG(b, c, d, a, x[ 4], S24, T24);
            GG(a, b, c, d, x[ 9], S21, T25);
            GG(d, a, b, c, x[14], S22, T26);
            GG(c, d, a, b, x[ 3], S23, T27);
            GG(b, c, d, a, x[ 8], S24, T28);
            GG(a, b, c, d, x[13], S21, T29);
            GG(d, a, b, c, x[ 2], S22, T30);
            GG(c, d, a, b, x[ 7], S23, T31);
            GG(b, c, d, a, x[12], S24, T32);

            // Round 3
            HH(a, b, c, d, x[ 5], S31, T33);
            HH(d, a, b, c, x[ 8], S32, T34);
            HH(c, d, a, b, x[11], S33, T35);
            HH(b, c, d, a, x[14], S34, T36);
            HH(a, b, c, d, x[ 1], S31, T37);
            HH(d, a, b, c, x[ 4], S32, T38);
            HH(c, d, a, b, x[ 7], S33, T39);
            HH(b, c, d, a, x[10], S34, T40);
            HH(a, b, c, d, x[13], S31, T41);
            HH(d, a, b, c, x[ 0], S32, T42);
            HH(c, d, a, b, x[ 3], S33, T43);
            HH(b, c, d, a, x[ 6], S34, T44);
            HH(a, b, c, d, x[ 9], S31, T45);
            HH(d, a, b, c, x[12], S32, T46);
            HH(c, d, a, b, x[15], S33, T47);
            HH(b, c, d, a, x[ 2], S34, T48);

            // Round 4
            II(a, b, c, d, x[ 0], S41, T49);
            II(d, a, b, c, x[ 7], S42, T50);
            II(c, d, a, b, x[14], S43, T51);
            II(b, c, d, a, x[ 5], S44, T52);
            II(a, b, c, d, x[12], S41, T53);
            II(d, a, b, c, x[ 3], S42, T54);
            II(c, d, a, b, x[10], S43, T55);
            II(b, c, d, a, x[ 1], S44, T56);
            II(a, b, c, d, x[ 8], S41, T57);
            II(d, a, b, c, x[15], S42, T58);
            II(c, d, a, b, x[ 6], S43, T59);
            II(b, c, d, a, x[13], S44, T60);
            II(a, b, c, d, x[ 4], S41, T61);
            II(d, a, b, c, x[11], S42, T62);
            II(c, d, a, b, x[ 2], S43, T63);
            II(b, c, d, a, x[ 9], S44, T64);

            state[0] += a;
            state[1] += b;
            state[2] += c;
            state[3] += d;
        }

    private:
        static const unsigned char PADDING[BUFFER_LENGTH];
        static const unsigned char STATE[DIGEST_LENGTH];

        static const unsigned int S11 =  7;
        static const unsigned int S12 = 12;
        static const unsigned int S13 = 17;
        static const unsigned int S14 = 22;
        static const unsigned int S21 =  5;
        static const unsigned int S22 =  9;
        static const unsigned int S23 = 14;
        static const unsigned int S24 = 20;
        static const unsigned int S31 =  4;
        static const unsigned int S32 = 11;
        static const unsigned int S33 = 16;
        static const unsigned int S34 = 23;
        static const unsigned int S41 =  6;
        static const unsigned int S42 = 10;
        static const unsigned int S43 = 15;
        static const unsigned int S44 = 21;

        static const unsigned int T01 = 0xd76aa478;
        static const unsigned int T02 = 0xe8c7b756;
        static const unsigned int T03 = 0x242070db;
        static const unsigned int T04 = 0xc1bdceee;
        static const unsigned int T05 = 0xf57c0faf;
        static const unsigned int T06 = 0x4787c62a;
        static const unsigned int T07 = 0xa8304613;
        static const unsigned int T08 = 0xfd469501;
        static const unsigned int T09 = 0x698098d8;
        static const unsigned int T10 = 0x8b44f7af;
        static const unsigned int T11 = 0xffff5bb1;
        static const unsigned int T12 = 0x895cd7be;
        static const unsigned int T13 = 0x6b901122;
        static const unsigned int T14 = 0xfd987193;
        static const unsigned int T15 = 0xa679438e;
        static const unsigned int T16 = 0x49b40821;
        static const unsigned int T17 = 0xf61e2562;
        static const unsigned int T18 = 0xc040b340;
        static const unsigned int T19 = 0x265e5a51;
        static const unsigned int T20 = 0xe9b6c7aa;
        static const unsigned int T21 = 0xd62f105d;
        static const unsigned int T22 = 0x02441453;
        static const unsigned int T23 = 0xd8a1e681;
        static const unsigned int T24 = 0xe7d3fbc8;
        static const unsigned int T25 = 0x21e1cde6;
        static const unsigned int T26 = 0xc33707d6;
        static const unsigned int T27 = 0xf4d50d87;
        static const unsigned int T28 = 0x455a14ed;
        static const unsigned int T29 = 0xa9e3e905;
        static const unsigned int T30 = 0xfcefa3f8;
        static const unsigned int T31 = 0x676f02d9;
        static const unsigned int T32 = 0x8d2a4c8a;
        static const unsigned int T33 = 0xfffa3942;
        static const unsigned int T34 = 0x8771f681;
        static const unsigned int T35 = 0x6d9d6122;
        static const unsigned int T36 = 0xfde5380c;
        static const unsigned int T37 = 0xa4beea44;
        static const unsigned int T38 = 0x4bdecfa9;
        static const unsigned int T39 = 0xf6bb4b60;
        static const unsigned int T40 = 0xbebfbc70;
        static const unsigned int T41 = 0x289b7ec6;
        static const unsigned int T42 = 0xeaa127fa;
        static const unsigned int T43 = 0xd4ef3085;
        static const unsigned int T44 = 0x04881d05;
        static const unsigned int T45 = 0xd9d4d039;
        static const unsigned int T46 = 0xe6db99e5;
        static const unsigned int T47 = 0x1fa27cf8;
        static const unsigned int T48 = 0xc4ac5665;
        static const unsigned int T49 = 0xf4292244;
        static const unsigned int T50 = 0x432aff97;
        static const unsigned int T51 = 0xab9423a7;
        static const unsigned int T52 = 0xfc93a039;
        static const unsigned int T53 = 0x655b59c3;
        static const unsigned int T54 = 0x8f0ccc92;
        static const unsigned int T55 = 0xffeff47d;
        static const unsigned int T56 = 0x85845dd1;
        static const unsigned int T57 = 0x6fa87e4f;
        static const unsigned int T58 = 0xfe2ce6e0;
        static const unsigned int T59 = 0xa3014314;
        static const unsigned int T60 = 0x4e0811a1;
        static const unsigned int T61 = 0xf7537e82;
        static const unsigned int T62 = 0xbd3af235;
        static const unsigned int T63 = 0x2ad7d2bb;
        static const unsigned int T64 = 0xeb86d391;

        // F, G, H and I are basic MD5 functions.

        static inline unsigned int F(unsigned int x, unsigned int y, unsigned int z)
        {
            return (x & y) | ((~x) & z);
        }

        static inline unsigned int G(unsigned int x, unsigned int y, unsigned int z)
        {
            return (x & z) | (y & (~z));
        }

        static inline unsigned int H(unsigned int x, unsigned int y, unsigned int z)
        {
            return x ^ y ^ z;
        }

        static inline unsigned int I(unsigned int x, unsigned int y, unsigned int z)
        {
            return y ^ (x | (~z));
        }

        // ROTATE_LEFT rotates x left n bits.

        static inline unsigned int ROTATE_LEFT(unsigned int x, unsigned int n)
        {
            return (x << n) | (x >> (32 - n));
        }

        // FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
        // Rotation is separate from addition to prevent recomputation.
        // Here ti (T(i)) is the 32-bit integer part of 0x100000000 * abs(sin(i)).

        static inline void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ti)
        {
            a += F(b, c, d) + x + (unsigned int)(ti);
            a = ROTATE_LEFT(a, s);
            a += b;
        }

        static inline void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ti)
        {
            a += G(b, c, d) + x + (unsigned int)(ti);
            a = ROTATE_LEFT(a, s);
            a += b;
        }

        static inline void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ti)
        {
            a += H(b, c, d) + x + (unsigned int)(ti);
            a = ROTATE_LEFT(a, s);
            a += b;
        }

        static inline void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ti)
        {
            a += I(b, c, d) + x + (unsigned int)(ti);
            a = ROTATE_LEFT(a, s);
            a += b;
        }
    };

    const unsigned char MD5::PADDING[BUFFER_LENGTH] =
    {
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    const unsigned char MD5::STATE[DIGEST_LENGTH] =
    {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
    };

} // namespace xl

#endif // #ifndef __XLMD5_H_9F168AAD_4EE5_4F50_A910_E9280F1CBA2E_INCLUDED__
