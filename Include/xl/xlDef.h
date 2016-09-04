//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlDef.h
//    Author:      Streamlet
//    Create Time: 2010-10-14
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLDEF_H_1C304B99_7B3A_4BDB_9BE7_0C76AD3C1126_INCLUDED__
#define __XLDEF_H_1C304B99_7B3A_4BDB_9BE7_0C76AD3C1126_INCLUDED__


namespace xl
{

#ifndef NULL
#define NULL 0
#endif

#if defined(_MSC_VER)

#if _MSC_VER >= 1900
#define __XL_CPP11
#endif

#if _MSC_VER < 1600
#define nullptr 0
#endif

#elif defined(__GNUC__)

#  if !defined(size_t)
    typedef unsigned int size_t;
#  endif

#endif

} // namespace xl

#endif // #ifndef __XLDEF_H_1C304B99_7B3A_4BDB_9BE7_0C76AD3C1126_INCLUDED__
