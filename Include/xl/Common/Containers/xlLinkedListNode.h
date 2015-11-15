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

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::List
// ;------------------------------------------------------------------------------
// xl::List<*>{
//     preview (
//         #(
//             "[",
//             $e.m_nSize,
//             "](",
//             #list(
//                 head: $e.m_pHead,
//                 size: $e.m_nSize,
//                 next: pNext
//             ) : $e.tValue,
//             ")"
//         )
//     )
//     children (
//         #list(
//             head: $e.m_pHead,
//             size: $e.m_nSize,
//             next: pNext
//         ) : $e.tValue
//     )
// }
// xl::List<*>::Iterator|xl::List<*>::ReverseIterator{
//     preview (
//         $e.m_pCurrent->tValue
//     )
//     children (
//         #(
//             [ptr] : &$e.m_pCurrent->tValue
//         )
//     )
// }
//

#endif // #ifndef __XLLINKEDLISTNODE_H_4E427CDC_51D0_43CB_86EE_2B0C478A8712_INCLUDED__
