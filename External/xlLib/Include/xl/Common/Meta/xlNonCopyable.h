//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlNonCopyable.h
//    Author:      Streamlet
//    Create Time: 2015-11-13
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLNONCOPYABLE_H_C3075108_9FDA_4F7A_93C9_17A61FDA75A3_INCLUDED__
#define __XLNONCOPYABLE_H_C3075108_9FDA_4F7A_93C9_17A61FDA75A3_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    class NonCopyable
    {
    public:
        NonCopyable()
        {

        }

        ~NonCopyable()
        {

        }

    private:
        NonCopyable(const NonCopyable &);
        NonCopyable &operator = (const NonCopyable &);
    };

} // namespace xl

#endif // #ifndef __XLNONCOPYABLE_H_C3075108_9FDA_4F7A_93C9_17A61FDA75A3_INCLUDED__
