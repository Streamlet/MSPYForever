//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlLinkedListNode.h
//    Author:      Streamlet
//    Create Time: 2015-11-13
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLLINKEDLISTNODE_H_4E427CDC_51D0_43CB_86EE_2B0C478A8712_INCLUDED__
#define __XLLINKEDLISTNODE_H_4E427CDC_51D0_43CB_86EE_2B0C478A8712_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    template <typename T>
    struct LinkedListNode
    {
        T tValue;
        LinkedListNode *pPrev;
        LinkedListNode *pNext;

        LinkedListNode() : tValue(), pPrev(nullptr), pNext(nullptr)
        {

        }

        LinkedListNode(const T &tValue) : tValue(tValue), pPrev(nullptr), pNext(nullptr)
        {

        }

        LinkedListNode(const T &tValue, LinkedListNode *pPrev, LinkedListNode *pNext) : tValue(tValue), pPrev(pPrev), pNext(pNext)
        {

        }
    };

} // namespace xl

#endif // #ifndef __XLLINKEDLISTNODE_H_4E427CDC_51D0_43CB_86EE_2B0C478A8712_INCLUDED__
