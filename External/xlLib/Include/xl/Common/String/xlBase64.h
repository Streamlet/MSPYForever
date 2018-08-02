//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBase64.h
//    Author:      Streamlet
//    Create Time: 2011-02-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLBASE64_H_928C9622_19D0_46B0_9222_152367E2F4BF_INCLUDED__
#define __XLBASE64_H_928C9622_19D0_46B0_9222_152367E2F4BF_INCLUDED__


#include "../../xlDef.h"
#include "../Containers/xlArray.h"
#include "../String/xlString.h"

namespace xl
{
    class Base64
    {
    private:
        Base64();

    public:
        static void Encode(const void *lpPlain, size_t nLength, String *pstrEncoded)
        {
            if (pstrEncoded == nullptr)
            {
                return;
            }

            pstrEncoded->Clear();

            for (size_t i = 0; i < nLength; i += 3)
            {
                pstrEncoded->AppendBack(BASE64_ALPHABET[(((unsigned char *)lpPlain)[i] >> 2) & 0x3f]);

                if (i + 1 >= nLength)
                {
                    pstrEncoded->AppendBack(BASE64_ALPHABET[(((unsigned char *)lpPlain)[i] & 0x03) << 4]);
                    pstrEncoded->AppendBack(BASE64_ALPHABET[64]);
                    pstrEncoded->AppendBack(BASE64_ALPHABET[64]);
                }
                else
                {
                    pstrEncoded->AppendBack(BASE64_ALPHABET[((((unsigned char *)lpPlain)[i] & 0x03) << 4) | ((((unsigned char *)lpPlain)[i + 1] >> 4) & 0x0f)]);

                    if (i + 2 >= nLength)
                    {
                        pstrEncoded->AppendBack(BASE64_ALPHABET[(((unsigned char *)lpPlain)[i + 1] & 0x0f) << 2]);
                        pstrEncoded->AppendBack(BASE64_ALPHABET[64]);
                    }
                    else
                    {
                        pstrEncoded->AppendBack(BASE64_ALPHABET[((((unsigned char *)lpPlain)[i + 1] & 0x0f) << 2) | ((((unsigned char *)lpPlain)[i + 2] >> 6) & 0x03)]);
                        pstrEncoded->AppendBack(BASE64_ALPHABET[((unsigned char *)lpPlain)[i + 2] & 0x3f]);
                    }
                }
            }
        }

        static void Decode(const String &strEncoded, Array<unsigned char> *parrPlain)
        {
            if (parrPlain == nullptr)
            {
                return;
            }

            int len = strEncoded.Length();
            parrPlain->Clear();

            for (int i = 0; i < len; i += 4)
            {

                if (i + 1 < len && strEncoded[i] != BASE64_ALPHABET[64] && strEncoded[i + 1] != BASE64_ALPHABET[64])
                {
                    parrPlain->PushBack((BASE64_ALPHABET_REVERSE[strEncoded[i]] << 2) | ((BASE64_ALPHABET_REVERSE[strEncoded[i + 1]] >> 4) & 0x03));
                }

                if (i + 2 < len && strEncoded[i + 2] != BASE64_ALPHABET[64])
                {
                    parrPlain->PushBack((BASE64_ALPHABET_REVERSE[strEncoded[i + 1]] << 4) | ((BASE64_ALPHABET_REVERSE[strEncoded[i + 2]] >> 2) & 0x0f));
                }

                if (i + 3 < len && strEncoded[i + 3] != BASE64_ALPHABET[64])
                {
                    parrPlain->PushBack((BASE64_ALPHABET_REVERSE[strEncoded[i + 2]] << 6) | BASE64_ALPHABET_REVERSE[strEncoded[i + 3]]);
                }
            }
        }

    private:
        static const unsigned char BASE64_ALPHABET[];
        static const unsigned char BASE64_ALPHABET_REVERSE[];
    };

    const unsigned char Base64::BASE64_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                    "abcdefghijklmnopqrstuvwxyz"
                                                    "0123456789"
                                                    "+/=";

    const unsigned char Base64::BASE64_ALPHABET_REVERSE[] =
    {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x3e, 0xff, 0xff, 0xff, 0x3f,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
        0x3c, 0x3d, 0xff, 0xff, 0xff, 0x40, 0xff, 0xff,
        0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
        0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
        0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
        0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,
        0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff
    };

} // namespace xl

#endif // #ifndef __XLBASE64_H_928C9622_19D0_46B0_9222_152367E2F4BF_INCLUDED__
