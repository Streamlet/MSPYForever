//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlUTF8.h
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLUTF8_H_A533AF6F_F5C2_4575_B2AC_B7A320C7C9C8_INCLUDED__
#define __XLUTF8_H_A533AF6F_F5C2_4575_B2AC_B7A320C7C9C8_INCLUDED__


#include <xl/String/xlString.h>

namespace xl
{
    class UTF8
    {
    private:
        UTF8();

    public:
        static void Encode(const StringW &strUCS2, StringA *pstrUTF8)
        {
            if (pstrUTF8 == nullptr)
            {
                return;
            }

            pstrUTF8->Clear();

            //
            // UTF-8 Definition:
            //
            // UCS-2 Value          UTF-8 Value
            // 00000000 - 0000007F: 0xxxxxxx (1 byte)
            // 00000080 - 000007FF: 110xxxxx 10xxxxxx (2 bytes)
            // 00000800 - 0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx (3 bytes)
            // (UCS-4 Value)
            // 00010000 - 001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (4 bytes)
            // 00200000 - 03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (5 bytes)
            // 04000000 - 7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (6 bytes)
            //
            // The place holder "x" should be filled by the original bits of the UCS value by order
            //

            for (int i = 0; i < strUCS2.Length(); ++i)
            {
                CharW ch = strUCS2[i];

                int nBytes = 0;             // How many bytes will the char cost
                CharW chMaskValueBits;      // To traits the "x" in the first byte of UTF-8
                CharA chMaskLeadingBits;    // To Traits the leading "1" in the first byte of UTF-8

                if (ch <= 0x7f)                        // 00000000 00000000 - 00000000 01111111
                {
                    nBytes = 1;
                    chMaskValueBits = 0x7f;            // 01111111
                    chMaskLeadingBits = '\x00';     // 00000000
                }
                else if (ch <= 0x7ff)                // 00000000 10000000 - 00000111 11111111
                {
                    nBytes = 2;
                    chMaskValueBits = 0x1f;            // 00011111
                    chMaskLeadingBits = '\xc0';        // 11000000
                }
                else if (ch <= 0xffff)                // 00001000 00000000 - 11111111 11111111
                {
                    nBytes = 3;
                    chMaskValueBits = 0x0f;            // 00001111
                    chMaskLeadingBits = '\xe0';        // 11100000
                }

                CharA temp[3];

                for (int i = nBytes - 1; i > 0; --i)
                {
                    temp[i] = (CharA)(ch & 0x3f) | 0x80;    // Get the lower 6 bits, and set the high 2 bits to "10"
                    ch >>= 6;
                }

                // Solve the first byte. Get the lower value bits, and the set the high bits to "1...10"
                temp[0] = (CharA)(ch & chMaskValueBits) | chMaskLeadingBits;

                for (int i = 0; i < nBytes; ++i)
                {
                    pstrUTF8->AppendBack(temp[i]);
                }
            }
        }

        static bool Decode(const StringA &strUTF8, StringW *pstrUCS2)
        {
            if (pstrUCS2 == nullptr && !strUTF8.Empty())
            {
                return false;
            }

            pstrUCS2->Clear();

            int i = 0;
            int n = strUTF8.Length();

            while (i < n)
            {
                CharA ch = strUTF8[i];

                int nBytes = 0;             // How many bytes will the char cost
                CharW chMaskValueBits;      // To traits the "x" in the first byte of UTF-8

                if ((ch & 0x80) == 0)       // 0xxxxxxx
                {
                    nBytes = 1;
                    chMaskValueBits = 0x7f;    // 01111111
                }
                else if ((ch & 0x40) == 0)  // 10xxxxxx
                {
                    return false;
                }
                else if ((ch & 0x20) == 0)  // 110xxxxx
                {
                    nBytes = 2;
                    chMaskValueBits = 0x1f;    // 00011111
                }
                else if ((ch & 0x10) == 0)  // 1110xxxx
                {
                    nBytes = 3;
                    chMaskValueBits = 0x0f;    // 00001111
                }
                else
                {
                    return false;
                }

                CharW temp = 0;

                // Solve the first byte. Get the lower value bits.
                temp |= (strUTF8[i] & chMaskValueBits);

                for (int j = 1; j < nBytes; ++j)
                {
                    temp <<=6;
                    temp |= (strUTF8[i + j] & 0x3f);    // Get the lower 6 bits
                }

                pstrUCS2->AppendBack(temp);

                i += nBytes;
            }

            return true;
        }
    };

} // namespace xl

#endif // #ifndef __XLUTF8_H_A533AF6F_F5C2_4575_B2AC_B7A320C7C9C8_INCLUDED__
