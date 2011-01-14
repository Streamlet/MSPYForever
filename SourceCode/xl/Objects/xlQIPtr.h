//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlQIPtr.h
//    Author:      Streamlet
//    Create Time: 2009-03-22
//    Description: Smart pointer
//
//    Version history:
//        2009-03-22 Created by Streamlet.
//        2009-03-27 Released first version.
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLQIPTR_H_E6B64B03_95F8_4C7D_BC72_C3CE917F3DEF_INCLUDED__
#define __XLQIPTR_H_E6B64B03_95F8_4C7D_BC72_C3CE917F3DEF_INCLUDED__


#include <xl/xlDef.h>

namespace xl
{
    template <typename T>
    class QIPtr
    {
    public:
        QIPtr();
        QIPtr(T *pData);
        QIPtr(const QIPtr<T> &that);
        QIPtr<T> &operator=(const QIPtr<T> &that);
        ~QIPtr();

    public:
        bool operator==(const QIPtr<T> &that) const;
        bool operator!=(const QIPtr<T> &that) const;
        bool operator==(const T *pThat) const;
        bool operator!=(const T *pThat) const;

    public:
        T &operator*() const;
        T *operator->() const;

    private:
        void AddRef();
        void Release();

    private:
        T *m_pData;
        size_t *m_pcRefs;
    };

    template <typename T>
    inline QIPtr<T>::QIPtr() : m_pData(nullptr), m_pcRefs(nullptr)
    {
    }

    template <typename T>
    inline QIPtr<T>::QIPtr(T *pData) : m_pData(pData), m_pcRefs(nullptr)
    {
        AddRef();
    }

    template <typename T>
    inline QIPtr<T>::QIPtr(const QIPtr<T> &that) : m_pData(nullptr), m_pcRefs(nullptr)
    {
        this->m_pData = that.m_pData;
        this->m_pcRefs = that.m_pcRefs;
        this->AddRef();
    }

    template <typename T>
    inline QIPtr<T> &QIPtr<T>::operator=(const QIPtr<T> &that)
    {
        if (this != &that && this->m_pData != that.m_pData)
        {
            this->Release();

            this->m_pData = that.m_pData;
            this->m_pcRefs = that.m_pcRefs;
            this->AddRef();    
        }
        
        return *this;
    }

    template <typename T>
    inline QIPtr<T>::~QIPtr()
    {
        Release();
    }

    template <typename T>
    inline void QIPtr<T>::AddRef()
    {
        if (m_pcRefs == nullptr)
        {
            m_pcRefs = new size_t;
            *m_pcRefs = 0;
        }

        ++*m_pcRefs;
    }

    template <typename T>
    inline void QIPtr<T>::Release()
    {
        if (m_pcRefs != nullptr && --*m_pcRefs == 0)
        {
            delete m_pcRefs;
            delete m_pData;
        }
    }

    template <typename T>
    inline bool QIPtr<T>::operator==(const QIPtr<T> &that) const
    {
        return this->m_pData == that.m_pData;
    }

    template <typename T>
    inline bool QIPtr<T>::operator!=(const QIPtr<T> &that) const
    {
        return this->m_pData != that.m_pData;
    }

    template <typename T>
    inline bool QIPtr<T>::operator==(const T *pThat) const
    {
        return this->m_pData == pThat;
    }

    template <typename T>
    inline bool QIPtr<T>::operator!=(const T *pThat) const
    {
        return this->m_pData != pThat;
    }

    template <typename T>
    inline T &QIPtr<T>::operator*() const
    {
        return *this->m_pData;
    }

    template <typename T>
    inline T *QIPtr<T>::operator->() const
    {
        return this->m_pData;
    }

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::QIPtr
// ;------------------------------------------------------------------------------
// xl::QIPtr<*>{
//     preview (
//         #(
//             "[",
//             #if ($e.m_pcRefs == 0) ( 0 ) #else ( *$e.m_pcRefs ),
//             "] ",
//             $e.m_pData
//         )
//     )
//     children (
//         #(
//             [ref] : #if ($e.m_pcRefs == 0) ( 0 ) #else ( *$e.m_pcRefs ),
//             [val] : *$e.m_pData
//         )
//     )
// }
//

#endif // #ifndef __XLQIPTR_H_E6B64B03_95F8_4C7D_BC72_C3CE917F3DEF_INCLUDED__
