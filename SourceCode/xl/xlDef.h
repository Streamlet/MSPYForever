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

#if defined(_MSC_VER)
#    define XL_SIZE_T_DEFINED
#  if _MSC_VER >= 1600
#    define XL_NULLPTR_DEFINED
#  endif
#elif defined(__GNUC__)
#  if !defined(size_t)
typedef unsigned int size_t;
#  endif
#endif

#ifndef XL_NULLPTR_DEFINED
#define nullptr 0
#endif

} // namespace xl

#endif // #ifndef __XLDEF_H_1C304B99_7B3A_4BDB_9BE7_0C76AD3C1126_INCLUDED__
