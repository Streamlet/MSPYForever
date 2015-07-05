//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlPath.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLPATH_H_14B3352D_18F0_4659_AAB7_ED4630B1C004_INCLUDED__
#define __XLPATH_H_14B3352D_18F0_4659_AAB7_ED4630B1C004_INCLUDED__


#include "../../String/xlString.h"
#include <Windows.h>
#include <tchar.h>

namespace xl
{
    namespace Path
    {
        String GetFileDir(const String &strFilePath)
        {
            int iSlashPos = strFilePath.LastIndexOf(_T("\\"));

            if (iSlashPos < 0)
            {
                return String();
            }

            return strFilePath.SubString(0, iSlashPos);
        }

        String GetFileName(const String &strFilePath)
        {
            int iSlashPos = strFilePath.LastIndexOf(_T("\\"));

            if (iSlashPos < 0)
            {
                return strFilePath;
            }

            ++iSlashPos;

            return strFilePath.SubString(iSlashPos, strFilePath.Length() - iSlashPos);
        }

        String GetFileBaseName(const String &strFileName)
        {
            int iDotPos = strFileName.LastIndexOf(_T("."));

            if (iDotPos < 0)
            {
                return strFileName;
            }

            return strFileName.SubString(0, iDotPos);
        }

        String GetFileExtName(const String &strFileName)
        {
            int iDotPos = strFileName.LastIndexOf(_T("."));

            if (iDotPos < 0)
            {
                return String();
            }

            ++iDotPos;

            return strFileName.SubString(iDotPos, strFileName.Length() - iDotPos);
        }
    }

} // namespace xl

#endif // #ifndef __XLPATH_H_14B3352D_18F0_4659_AAB7_ED4630B1C004_INCLUDED__
