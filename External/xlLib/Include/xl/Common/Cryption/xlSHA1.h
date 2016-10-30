//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSHA1.h
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSHA1_H_2D27EEEA_B8E7_46F2_8855_0CDA1C148C4F_INCLUDED__
#define __XLSHA1_H_2D27EEEA_B8E7_46F2_8855_0CDA1C148C4F_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"

namespace xl
{
    class SHA1
    {
    public:
        static const size_t DIGEST_LENGTH = 5;
        typedef unsigned int Digest[DIGEST_LENGTH];

    public:
        static void Calculate(const void *lpBuffer, size_t cbSize, Digest &digest)
        {
            SHA1 sha1;

            sha1.AppendData(lpBuffer, cbSize);
            sha1.GetDigest(digest);
        }

    public:
        SHA1()
        {
            Initialize();
        }

    public:
        void SHA1::AppendData(const void *lpBuffer, size_t cbSize)
        {
            size_t cbCopied = 0;

            while (cbCopied < cbSize)
            {
                size_t cbToCopy = cbSize - cbCopied > BUFFER_LENGTH - m_cbBufferUsed ? BUFFER_LENGTH - m_cbBufferUsed : cbSize - cbCopied;

                Memory::Copy(m_ctx.buffer + m_cbBufferUsed, (const unsigned char *)lpBuffer + cbCopied, cbToCopy);

                cbCopied += cbToCopy;
                m_cbBufferUsed += cbToCopy;

                if (m_cbBufferUsed == BUFFER_LENGTH)
                {
                    Transform(m_ctx);
                    m_cbBufferUsed = 0;
                }
            }

            m_cbTotalSize += cbSize;
        }

        void SHA1::GetDigest(Digest &digest)
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
            *(unsigned int *)&m_ctx.buffer[BUFFER_LENGTH - sizeof(unsigned int) * 2] =
                BitSwap((unsigned char)(m_cbTotalSize >> (BYTE_BITS_LENGTH * sizeof(unsigned int))));
            *(unsigned int *)&m_ctx.buffer[BUFFER_LENGTH - sizeof(unsigned int)] =
                BitSwap((unsigned char)m_cbTotalSize);
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
        void SHA1::Initialize()
        {
            Memory::Zero(m_ctx);
            Memory::Copy(m_ctx.digest, STATE, sizeof(m_ctx.digest));

            m_cbTotalSize = 0;
            m_cbBufferUsed = 0;
        }

        void Transform(CTX &ctx)
        {
            unsigned int *h = ctx.digest;
            unsigned int a = h[0];
            unsigned int b = h[1];
            unsigned int c = h[2];
            unsigned int d = h[3];
            unsigned int e = h[4];
            unsigned int *x = (unsigned int *)ctx.buffer;
            unsigned int w[80] = {};

            for (int i = 0; i < 80; ++i)
            {
                if (i < 16)
                {
                    w[i] = BitSwap(x[i]);
                }
                else
                {
                    w[i] = w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16];
                    w[i] = ROTATE_LEFT(w[i], 1);
                }

                int t = e + ROTATE_LEFT(a, 5) + w[i];

                if (i < 20)
                {
                    t += F1(b, c, d) + K1;
                }
                else if (i < 40)
                {
                    t += F2(b, c, d) + K2;
                }
                else if (i < 60)
                {
                    t += F3(b, c, d) + K3;
                }
                else /*if (i < 80)*/
                {
                    t += F4(b, c, d) + K4;
                }

                e = d;
                d = c;
                c = ROTATE_LEFT(b, 30);
                b = a;
                a = t;
            }

            h[0] += a;
            h[1] += b;
            h[2] += c;
            h[3] += d;
            h[4] += e;
        }

    private:
        static const unsigned char PADDING[BUFFER_LENGTH];
        static const unsigned char STATE[DIGEST_LENGTH * sizeof(unsigned int)];

        static const unsigned int K1 = 0x5A827999;
        static const unsigned int K2 = 0x6ED9EBA1;
        static const unsigned int K3 = 0x8F1BBCDC;
        static const unsigned int K4 = 0xCA62C1D6;

        // FTx are basic SHA1 functions.

        static inline unsigned int F1(unsigned int x, unsigned int y, unsigned int z)
        {
            return (x & y) | ((~x) & z);
        }

        static inline unsigned int F2(unsigned int x, unsigned int y, unsigned int z)
        {
            return x ^ y ^ z;
        }

        static inline unsigned int F3(unsigned int x, unsigned int y, unsigned int z)
        {
            return (x & y) | (x & z) | (y & z);
        }

        static inline unsigned int F4(unsigned int x, unsigned int y, unsigned int z)
        {
            return x ^ y ^ z;
        }

        // ROTATE_LEFT rotates x left n bits.

        static inline unsigned int ROTATE_LEFT(unsigned int x, unsigned int n)
        {
            return (x << n) | (x >> (32 - n));
        }

        static inline unsigned int BitSwap(unsigned int x)
        {
#ifdef _WIN64
            unsigned int result = 0;

            for (size_t i = 0; i < sizeof(unsigned int); ++i)
            {
                result <<= 8;
                result |= x & 0xff;
                x >>= 8;
            }

            return result;
#else
            __asm
            {
                mov eax, x
                bswap eax
            }
#endif
        }


    };

    const unsigned char SHA1::PADDING[BUFFER_LENGTH] =
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

    const unsigned char SHA1::STATE[DIGEST_LENGTH * sizeof(unsigned int)] =
    {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98,
        0x76, 0x54, 0x32, 0x10,
        0xf0, 0xe1, 0xd2, 0xc3
    };

} // namespace xl

#endif // #ifndef __XLSHA1_H_2D27EEEA_B8E7_46F2_8855_0CDA1C148C4F_INCLUDED__
