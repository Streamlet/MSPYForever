//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlEncoding.h
//    Author:      Streamlet
//    Create Time: 2011-06-12
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLENCODING_H_EB12014E_ED0F_4198_8DAC_37836BAD9483_INCLUDED__
#define __XLENCODING_H_EB12014E_ED0F_4198_8DAC_37836BAD9483_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"
#include "../Meta/xlNonCopyable.h"
#include "../String/xlString.h"

namespace xl
{
    class Encoding : public NonCopyable
    {
    public:
        static bool Utf32ToUtf16(const StringU32 &strUtf32, StringU16 *pstrUtf16)
        {
            if (pstrUtf16 == nullptr)
            {
                return false;
            }

            pstrUtf16->Clear();

            Char16 chUtf16[2] = {};
            int nBytes = 0;

            for (int i = 0; i < strUtf32.Length(); ++i)
            {
                if (!CharUtf32ToUtf16(strUtf32[i], chUtf16, &nBytes))
                {
                    return false;
                }

                for (int j = 0; j < nBytes; ++j)
                {
                    pstrUtf16->AppendBack(chUtf16[j]);
                }
            }

            return true;
        }

        static bool Utf16ToUtf32(const StringU16 &strUtf16, StringU32 *pstrUtf32)
        {
            if (pstrUtf32 == nullptr)
            {
                return false;
            }

            pstrUtf32->Clear();

            int i = 0;
            int n = strUtf16.Length();
            Char32 chUtf32 = 0;
            int nBytes = 0;

            while (i < n)
            {
                if (!CharUtf16ToUtf32(&strUtf16[i], n - i, &nBytes, &chUtf32))
                {
                    return false;
                }

                i += nBytes;

                pstrUtf32->AppendBack(chUtf32);
            }

            return true;
        }

        static bool Utf32ToUtf8(const StringU32 &strUtf32, StringU8 *pstrUtf8)
        {
            if (pstrUtf8 == nullptr)
            {
                return false;
            }

            pstrUtf8->Clear();

            Char8 chUtf8[6] = {};
            int nBytes = 0;

            for (int i = 0; i < strUtf32.Length(); ++i)
            {
                if (!CharUtf32ToUtf8(strUtf32[i], chUtf8, &nBytes))
                {
                    return false;
                }

                for (int j = 0; j < nBytes; ++j)
                {
                    pstrUtf8->AppendBack(chUtf8[j]);
                }
            }

            return true;
        }

        static bool Utf8ToUtf32(const StringU8 &strUtf8, StringU32 *pstrUtf32)
        {
            if (pstrUtf32 == nullptr)
            {
                return false;
            }

            pstrUtf32->Clear();

            int i = 0;
            int n = strUtf8.Length();
            Char32 chUtf32 = 0;
            int nBytes = 0;

            while (i < n)
            {
                if (!CharUtf8ToUtf32(&strUtf8[i], n - i, &nBytes, &chUtf32))
                {
                    return false;
                }

                i += nBytes;

                pstrUtf32->AppendBack(chUtf32);
            }

            return true;
        }

        static bool Utf16ToUtf8(const StringU16 &strUtf16, StringU8 *pstrUtf8)
        {
            if (pstrUtf8 == nullptr)
            {
                return false;
            }

            pstrUtf8->Clear();

            int i = 0;
            int n = strUtf16.Length();
            Char32 chUtf32 = 0;
            Char8 chUtf8[6] = {};
            int nBytes = 0;

            while (i < n)
            {
                if (!CharUtf16ToUtf32(&strUtf16[i], n - i, &nBytes, &chUtf32))
                {
                    return false;
                }

                i += nBytes;

                if (!CharUtf32ToUtf8(chUtf32, chUtf8, &nBytes))
                {
                    return false;
                }

                for (int j = 0; j < nBytes; ++j)
                {
                    pstrUtf8->AppendBack(chUtf8[j]);
                }
            }

            return true;
        }

        static bool Utf8ToUtf16(const StringU8 &strUtf8, StringU16 *pstrUtf16)
        {
            if (pstrUtf16 == nullptr)
            {
                return false;
            }

            pstrUtf16->Clear();

            int i = 0;
            int n = strUtf8.Length();
            Char32 chUtf32 = 0;
            Char16 chUtf16[2] = {};
            int nBytes = 0;

            while (i < n)
            {
                if (!CharUtf8ToUtf32(&strUtf8[i], n - i, &nBytes, &chUtf32))
                {
                    return false;
                }

                i += nBytes;

                if (!CharUtf32ToUtf16(chUtf32, chUtf16, &nBytes))
                {
                    return false;
                }

                for (int j = 0; j < nBytes; ++j)
                {
                    pstrUtf16->AppendBack(chUtf16[j]);
                }
            }

            return true;
        }

    private:
        static bool CharUtf32ToUtf8(Char32 chUtf32, Char8 chUtf8[6], int *pnCount)
        {
            if (chUtf8 == nullptr || pnCount == nullptr)
            {
                return false;
            }

            //
            // UTF-8 Definition:
            //
            // UTF-32 Value         UTF-8 Value
            // 00000000 - 0000007F: 0xxxxxxx (1 byte)
            // 00000080 - 000007FF: 110xxxxx 10xxxxxx (2 bytes)
            // 00000800 - 0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx (3 bytes)
            // 00010000 - 001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (4 bytes)
            // (UCS-4 Value)
            // 00200000 - 03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (5 bytes)
            // 04000000 - 7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (6 bytes)
            //
            // The place holder "x" should be filled by the original bits of the Unicode value by order
            //

            Char32 chMaskValueBits;     // To traits the "x" in the first byte of UTF-8
            Char8 chMaskLeadingBits;    // To Traits the leading "1" in the first byte of UTF-8

            if (chUtf32 <= 0x7f)            // 00000000 00000000 - 00000000 01111111
            {
                *pnCount = 1;
                chMaskValueBits = 0x7f;     // 01111111
                chMaskLeadingBits = '\x00'; // 00000000
            }
            else if (chUtf32 <= 0x7ff)      // 00000000 10000000 - 00000111 11111111
            {
                *pnCount = 2;
                chMaskValueBits = 0x1f;     // 00011111
                chMaskLeadingBits = '\xc0'; // 11000000
            }
            else if (chUtf32 <= 0xffff)     // 00001000 00000000 - 11111111 11111111
            {
                *pnCount = 3;
                chMaskValueBits = 0x0f;     // 00001111
                chMaskLeadingBits = '\xe0'; // 11100000
            }
            else if (chUtf32 <= 0x1fffff)
            {
                *pnCount = 4;
                chMaskValueBits = 0x07;     // 00000111
                chMaskLeadingBits = '\xf0'; // 11110000
            }
            else if (chUtf32 <= 0x3ffffff)
            {
                *pnCount = 5;
                chMaskValueBits = 0x03;     // 00000011
                chMaskLeadingBits = '\xf8'; // 11111000
            }
            else if (chUtf32 <= 0x7fffffff)
            {
                *pnCount = 6;
                chMaskValueBits = 0x01;     // 00000001
                chMaskLeadingBits = '\xfc'; // 11111100
            }
            else
            {
                return false;
            }

            for (int j = *pnCount - 1; j > 0; --j)
            {
                chUtf8[j] = (CharA)(chUtf32 & 0x3f) | 0x80;    // Get the lower 6 bits, and set the high 2 bits to "10"
                chUtf32 >>= 6;
            }

            // Solve the first byte. Get the lower value bits, and the set the high bits to "1...10"
            chUtf8[0] = (Char8)(chUtf32 & chMaskValueBits) | chMaskLeadingBits;

            return true;
        }

        static bool CharUtf8ToUtf32(const Char8 *pchUtf8, int nMax, int *pnCount, Char32 *pchUtf32)
        {
            if (pchUtf8 == nullptr || pnCount == nullptr || pchUtf32 == nullptr)
            {
                return false;
            }

            Char8 ch = pchUtf8[0];
            Char8 chMaskValueBits;          // To traits the "x" in the first byte of UTF-8

            if ((ch & 0x80) == 0)           // 0xxxxxxx
            {
                *pnCount = 1;
                chMaskValueBits = '\x7f';   // 01111111
            }
            else if ((ch & 0x40) == 0)      // 10xxxxxx
            {
                return false;
            }
            else if ((ch & 0x20) == 0)      // 110xxxxx
            {
                *pnCount = 2;
                chMaskValueBits = '\x1f';   // 00011111
            }
            else if ((ch & 0x10) == 0)      // 1110xxxx
            {
                *pnCount = 3;
                chMaskValueBits = '\x0f';   // 00001111
            }
            else if ((ch & 0x08) == 0)      // 11110xxx
            {
                *pnCount = 4;
                chMaskValueBits = '\x07';   // 00000111
            }
            else if ((ch & 0x04) == 0)      // 111110xx
            {
                *pnCount = 5;
                chMaskValueBits = '\x03';   // 00000011
            }
            else if ((ch & 0x02) == 0)      // 1111110x
            {
                *pnCount = 6;
                chMaskValueBits = '\x01';   // 00000001
            }
            else
            {
                return false;
            }

            if (nMax < *pnCount)
            {
                return false;
            }

            *pchUtf32 = 0;

            // Solve the first byte. Get the lower value bits.
            *pchUtf32 |= (ch & chMaskValueBits);

            for (int i = 1; i < *pnCount; ++i)
            {
                if ((pchUtf8[i] & 0xc0) != 0x80)
                {
                    return false;
                }

                *pchUtf32 <<= 6;
                *pchUtf32 |= (pchUtf8[i] & 0x3f);    // Get the lower 6 bits
            }

            return true;
        }

        static bool CharUtf32ToUtf16(Char32 chUtf32, Char16 chUtf16[2], int *pnCount)
        {
            if (chUtf16 == nullptr || pnCount == nullptr)
            {
                return false;
            }

            //
            // UTF-16 Definition:
            //
            // UTF-32 Value         UTF-16 Value
            // 00000000 - 0000FFFF: xxxxxxxx xxxxxxxx (1 word)
            // 00000000 - 0010FFFF: 110110xx xxxxxxxx 110111xx xxxxxxxx (2 words)
            //
            // The place holder "x" should be filled by the original bits of the Unicode value by order
            //

            if (chUtf32 <= 0xffff)
            {
                *pnCount = 1;
                chUtf16[0] = (Char16)chUtf32;

                return true;
            }

            chUtf32 -= 0x10000;

            if (chUtf32 <= 0xffff)
            {
                *pnCount = 2;

                chUtf16[1] = (Char16)chUtf32 & 0x3ff;
                chUtf16[1] |= 0xdc00; // 110111xx xxxxxxxx
                chUtf32 >>= 10;
                chUtf16[0] = (Char16)chUtf32 & 0x3ff;
                chUtf16[0] |= 0xd800; // 110110xx xxxxxxxx

                return true;
            }

            return false;
        }

        static bool CharUtf16ToUtf32(const Char16 *pchUtf16, int nMax, int *pnCount, Char32 *pchUtf32)
        {
            if (pchUtf16 == nullptr || pnCount == nullptr || pchUtf32 == nullptr)
            {
                return false;
            }

            Char16 ch = pchUtf16[0];

            if (ch < 0xd800 || ch > 0xdfff)
            {
                *pnCount = 1;
                *pchUtf32 = ch;

                return true;
            }

            if (nMax < 2)
            {
                return false;
            }

            *pnCount = 2;

            Char16 chLower = pchUtf16[1];

            if (ch > 0xdbff)
            {
                if (chLower <= 0xdbff)
                {
                    Memory::Swap(ch, chLower);
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (chLower <= 0xdbff)
                {
                    return false;
                }
            }

            *pchUtf32 = ch & 0x03ff;
            *pchUtf32 <<= 10;
            *pchUtf32 |= chLower & 0x03ff;
            *pchUtf32 += 0x10000;

            return true;
        }
    };

} // namespace xl

#endif // #ifndef __XLENCODING_H_EB12014E_ED0F_4198_8DAC_37836BAD9483_INCLUDED__
