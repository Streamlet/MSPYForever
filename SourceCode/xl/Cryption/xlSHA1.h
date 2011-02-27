//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSHA1.h
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSHA1_H_2D27EEEA_B8E7_46F2_8855_0CDA1C148C4F_INCLUDED__
#define __XLSHA1_H_2D27EEEA_B8E7_46F2_8855_0CDA1C148C4F_INCLUDED__


#include <xl/Memory/xlMemory.h>

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
        static const size_t BUFFER_LIMIT = BUFFER_LENGTH - BYTE_BITS_LENGTH;

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
            unsigned int w[80];

            for (int t = 0; t < 16; ++t)
            {
                w[t] = BitSwap(x[t]);
            }

            for (int t = 16; t < 80; ++t)
            {
                w[t] = w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16];
                w[t] = ROTATE_LEFT(w[t], 1);
            }

            R1(a, b, c, d, e, w[ 0]);
            R1(e, a, b, c, d, w[ 1]);
            R1(d, e, a, b, c, w[ 2]);
            R1(c, d, e, a, b, w[ 3]);
            R1(b, c, d, e, a, w[ 4]);
            R1(a, b, c, d, e, w[ 5]);
            R1(e, a, b, c, d, w[ 6]);
            R1(d, e, a, b, c, w[ 7]);
            R1(c, d, e, a, b, w[ 8]);
            R1(b, c, d, e, a, w[ 9]);
            R1(a, b, c, d, e, w[10]);
            R1(e, a, b, c, d, w[11]);
            R1(d, e, a, b, c, w[12]);
            R1(c, d, e, a, b, w[13]);
            R1(b, c, d, e, a, w[14]);
            R1(a, b, c, d, e, w[15]);
            R1(e, a, b, c, d, w[16]);
            R1(d, e, a, b, c, w[17]);
            R1(c, d, e, a, b, w[18]);
            R1(b, c, d, e, a, w[19]);

            R2(a, b, c, d, e, w[20]);
            R2(e, a, b, c, d, w[21]);
            R2(d, e, a, b, c, w[22]);
            R2(c, d, e, a, b, w[23]);
            R2(b, c, d, e, a, w[24]);
            R2(a, b, c, d, e, w[25]);
            R2(e, a, b, c, d, w[26]);
            R2(d, e, a, b, c, w[27]);
            R2(c, d, e, a, b, w[28]);
            R2(b, c, d, e, a, w[29]);
            R2(a, b, c, d, e, w[30]);
            R2(e, a, b, c, d, w[31]);
            R2(d, e, a, b, c, w[32]);
            R2(c, d, e, a, b, w[33]);
            R2(b, c, d, e, a, w[34]);
            R2(a, b, c, d, e, w[35]);
            R2(e, a, b, c, d, w[36]);
            R2(d, e, a, b, c, w[37]);
            R2(c, d, e, a, b, w[38]);
            R2(b, c, d, e, a, w[39]);

            R3(a, b, c, d, e, w[40]);
            R3(e, a, b, c, d, w[41]);
            R3(d, e, a, b, c, w[42]);
            R3(c, d, e, a, b, w[43]);
            R3(b, c, d, e, a, w[44]);
            R3(a, b, c, d, e, w[45]);
            R3(e, a, b, c, d, w[46]);
            R3(d, e, a, b, c, w[47]);
            R3(c, d, e, a, b, w[48]);
            R3(b, c, d, e, a, w[49]);
            R3(a, b, c, d, e, w[50]);
            R3(e, a, b, c, d, w[51]);
            R3(d, e, a, b, c, w[52]);
            R3(c, d, e, a, b, w[53]);
            R3(b, c, d, e, a, w[54]);
            R3(a, b, c, d, e, w[55]);
            R3(e, a, b, c, d, w[56]);
            R3(d, e, a, b, c, w[57]);
            R3(c, d, e, a, b, w[58]);
            R3(b, c, d, e, a, w[59]);

            R4(a, b, c, d, e, w[60]);
            R4(e, a, b, c, d, w[61]);
            R4(d, e, a, b, c, w[62]);
            R4(c, d, e, a, b, w[63]);
            R4(b, c, d, e, a, w[64]);
            R4(a, b, c, d, e, w[65]);
            R4(e, a, b, c, d, w[66]);
            R4(d, e, a, b, c, w[67]);
            R4(c, d, e, a, b, w[68]);
            R4(b, c, d, e, a, w[69]);
            R4(a, b, c, d, e, w[70]);
            R4(e, a, b, c, d, w[71]);
            R4(d, e, a, b, c, w[72]);
            R4(c, d, e, a, b, w[73]);
            R4(b, c, d, e, a, w[74]);
            R4(a, b, c, d, e, w[75]);
            R4(e, a, b, c, d, w[76]);
            R4(d, e, a, b, c, w[77]);
            R4(c, d, e, a, b, w[78]);
            R4(b, c, d, e, a, w[79]);

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

        static inline void R1(unsigned int a, unsigned int &b, unsigned int c, unsigned int d, unsigned int &e, unsigned int x)
        {
            e += ROTATE_LEFT(a, 5) + F1(b, c, d) + x + K1; 
            b = ROTATE_LEFT(b, 30);
        }

        static inline void R2(unsigned int a, unsigned int &b, unsigned int c, unsigned int d, unsigned int &e, unsigned int x)
        {
            e += ROTATE_LEFT(a, 5) + F2(b, c, d) + x + K2; 
            b = ROTATE_LEFT(b, 30);
        }

        static inline void R3(unsigned int a, unsigned int &b, unsigned int c, unsigned int d, unsigned int &e, unsigned int x)
        {
            e += ROTATE_LEFT(a, 5) + F3(b, c, d) + x + K3; 
            b = ROTATE_LEFT(b, 30);
        }

        static inline void R4(unsigned int a, unsigned int &b, unsigned int c, unsigned int d, unsigned int &e, unsigned int x)
        {
            e += ROTATE_LEFT(a, 5) + F4(b, c, d) + x + K4; 
            b = ROTATE_LEFT(b, 30);
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
