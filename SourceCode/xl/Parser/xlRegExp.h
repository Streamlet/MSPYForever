//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRegExp.h
//    Author:      Streamlet
//    Create Time: 2012-05-20
//    Description: Regular Expression
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLREGEXP_H_0FCC5122_D6F3_4E9E_AAB0_5D268E87ED44_INCLUDED__
#define __XLREGEXP_H_0FCC5122_D6F3_4E9E_AAB0_5D268E87ED44_INCLUDED__


#include <xl/Containers/xlGraph.h>
#include <xl/String/xlString.h>
#include <xl/Memory/xlSmartPtr.h>
#include <xl/Containers/xlGraph.h>

namespace xl
{
    class RegExp
    {
    public:
        RegExp()
        {
        
        }

        ~RegExp()
        {
        
        }

    private:
        struct Node
        {
        public:
            Node() : m_nIdentify(++ms_nCounter)
            {

            }

            int m_nIdentify;

            static int ms_nCounter;
        };

        struct Edge
        {
            Edge()
                : m_bEpsilon(true), m_bOpposite(false), m_chBegin(0), m_chEnd(0)
            {
            
            }

            Edge(Char ch)
                : m_bEpsilon(false), m_chBegin(ch), m_chEnd(ch)
            {

            }

            Edge(Char chBegin, Char chEnd)
                : m_bEpsilon(false), m_chBegin(chBegin), m_chEnd(chEnd)
            {

            }

            bool Match(Char ch)
            {
                if (m_bEpsilon)
                {
                    return false;
                }

                return (ch >= m_chBegin && ch <= m_chEnd);
            }

            bool m_bEpsilon;
            bool m_bOpposite;
            Char m_chBegin;
            Char m_chEnd;
        };

    private:
        typedef Graph<Node, Edge> StateMachine;
        typedef SharedPtr<StateMachine> StateMachinePtr;

    private:
        StateMachinePtr       m_spStateMachine;
        StateMachine::NodePtr m_pBegin;
        StateMachine::NodePtr m_pEnd;
        String m_strRegExp;
        int m_nCurrentPosition;

    public:
        bool Parse(const String &s)
        {
            m_strRegExp = s;
            m_nCurrentPosition = 0;
            m_spStateMachine = new StateMachine;
            m_pBegin = m_spStateMachine->AddNode(NewNode());
            m_pEnd = ParseExpression(m_pBegin);
        
            if (m_pEnd == nullptr || m_nCurrentPosition < m_strRegExp.Length())
            {
                return false;
            }

            FixStateMachine();

            return true;
        }

        bool Match(const String &s)
        {
            return Match(s, 0, m_pBegin);
        }

    private:
        void FixStateMachine()
        {

        }

        bool Match(const String &s, int i, StateMachine::NodePtr pNode)
        {
            if (pNode == nullptr || pNode->arrNext.Empty())
            {
                return true;
            }

            for (auto it = pNode->arrNext.Begin(); it != pNode->arrNext.End(); ++it)
            {
                if (Match(s, i, *it))
                {
                    return true;
                }
            }

            return false;
        }

        bool Match(const String &s, int i, StateMachine::EdgePtr pEdge)
        {
            if (i >= s.Length())
            {
                return true;
            }

            if (!pEdge->tValue.m_bEpsilon)
            {
                if (!pEdge->tValue.Match(s[i]))
                {
                    return false;
                }
            }

            return Match(s, i + 1, pEdge->pNext);
        }

    private:
        enum TokenType
        {
            TT_Error,
            TT_Eof,
            TT_OpenParen,
            TT_CloseParen,
            TT_VerticalBar ,
            TT_OpenBracket,
            TT_CloseBracket,
            TT_Hyphen,
            TT_Caret,
            TT_OrdinaryChar
        };

        struct Token 
        {
            TokenType type;
            Char ch;
            size_t length;

            Token(TokenType type = TT_OrdinaryChar, Char ch = L'\0', size_t length = 1)
                : ch(ch), type(type), length(length)
            {

            }
        };

    private:
        Token LookAhead()
        {
            if (m_nCurrentPosition > m_strRegExp.Length())
            {
                return Token(TT_Error, 0, 1);
            }

            Char ch = m_strRegExp[m_nCurrentPosition++];
            TokenType type = TT_OrdinaryChar;

            if (ch == L'\\')
            {
                Char chNext = m_strRegExp[m_nCurrentPosition];

                if (chNext != TT_Eof)
                {
                    ++m_nCurrentPosition;
                    return Token(TT_OrdinaryChar, chNext, 2);
                }
            }

            switch (ch)
            {
            case L'\0':
                type = TT_Eof;
                break;
            case L'(':
                type = TT_OpenParen;
                break;
            case L')':
                type = TT_CloseParen;
                break;
            case L'|':
                type = TT_VerticalBar ;
                break;
            case L'[':
                type = TT_OpenBracket;
                break;
            case L']':
                type = TT_CloseBracket;
                break;
            case L'-':
                type = TT_Hyphen;
                break;
            case L'^':
                type = TT_Caret;
                break;
            default:
                break;
            }

            return Token(type, ch);
        }

        void Backward(const Token &token)
        {
            m_nCurrentPosition -= token.length;
        }

        StateMachine::NodePtr ParseExpression(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = pNode;

            while (pCurrent != nullptr)
            {
                Token token = LookAhead();

                if (token.type == TT_Error)
                {
                    return nullptr;
                }

                if (token.type == TT_Eof)
                {
                    return pCurrent;
                }
    
                switch (token.type)
                {
                case TT_OpenParen:
                    {
                        pCurrent = ParseExpression(pCurrent);
                    }
                    break;
                case TT_VerticalBar:
                    {
                        StateMachine::NodePtr pNewNode = ParseExpression(pNode);
                        StateMachine::EdgePtr pEdge = NewEdge();
                        m_spStateMachine->AddEdge(pEdge, pNewNode, pCurrent);
                    }
                    break;
                case TT_OpenBracket:
                    {
                        pCurrent = ParseCollection(pCurrent);
                    }
                    break;
                case TT_OrdinaryChar:
                    {
                        pCurrent = AddNormalNode(pCurrent, token.ch);
                    }
                    break;
                default:
                    return nullptr;
                }
            }

            return pCurrent;
        }

        struct RangeCalc
        {
            struct Range
            {
                Char chFrom;
                Char chTo;

                Range() : chFrom(0), chTo(0)
                {

                }

                Range(Char chFrom, Char chTo) : chFrom(chFrom), chTo(chTo)
                {

                }
            };

            Array<Range> arrRanges;

            void Append(Char chFrom, Char chTo)
            {
                size_t nFrom = -1;
                size_t nTo = -1;

                for (size_t i = 0; i < arrRanges.Size(); ++i)
                {
                    if (chFrom <= arrRanges[i].chFrom && nFrom != -1)
                    {
                        nFrom = i;
                    }

                    if (chTo >= arrRanges[i].chTo && nTo != -1)
                    {
                        nTo = i;
                    }

                    if (chFrom >= arrRanges[i].chFrom && chFrom <= arrRanges[i].chTo)
                    {
                        chFrom = arrRanges[i].chFrom;
                    }

                    if (nTo >= arrRanges[i].chFrom && nTo <= arrRanges[i].chTo)
                    {
                        chTo = arrRanges[i].chTo;
                    }
                }

                arrRanges.Delete(nFrom, (int)(nTo - nFrom));
                arrRanges.Insert((nFrom == -1 ? 0 : nFrom), Range(nFrom, nTo));
            }
            void Reverse();
        };

        StateMachine::NodePtr ParseCollection(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pNext = nullptr;
            StateMachine::EdgePtr pLastEdge = nullptr;

            bool bFirst = true;
            bool bOpposite = false;
            bool bInHyphen = false;

            while (true)
            {
                Token token = LookAhead();

                switch (token.type)
                {
                case TT_CloseBracket:
                    {
                        if (bFirst)
                        {
                            return pNode;
                        }
                        else
                        {
                            return pNext;
                        }
                    }
                    break;
                case TT_Caret:
                    {
                        if (!bFirst)
                        {
                            return nullptr;
                        }
                        else
                        {
                            bOpposite = true;
                        }
                    }
                    break;
                case TT_Hyphen:
                    {
                        if (bFirst || bInHyphen)
                        {
                            return nullptr;
                        }
                        else
                        {
                            bInHyphen = true;
                        }
                    }
                    break;
                case TT_OrdinaryChar:
                    {
                        if (bInHyphen)
                        {
                            pLastEdge->tValue.m_chEnd = token.ch;
                            bInHyphen = false;
                        }
                        else
                        {
                            if (pNext == nullptr)
                            {
                                pNext = NewNode();
                            }

                            pLastEdge = NewEdge(token.ch, bOpposite);
                            m_spStateMachine->AddEdge(pLastEdge, pNode, pNext);
                        }
                    }
                    break;
                default:
                    return nullptr;
                }

                bFirst = false;
            }

            return nullptr;
        }

    private:
        StateMachine::NodePtr AddNormalNode(StateMachine::NodePtr pNodeFrom, Char chEdgeChar)
        {
            StateMachine::EdgePtr pEdge = NewEdge(chEdgeChar);
            StateMachine::NodePtr pNode = NewNode();

            m_spStateMachine->AddNode(pNode);
            m_spStateMachine->AddEdge(pEdge, pNodeFrom, pNode);

            return pNode;
        }

    private:
        StateMachine::NodePtr NewNode()
        {
            return new StateMachine::NodeType();
        }

        StateMachine::EdgePtr NewEdge()
        {
            return new StateMachine::EdgeType();
        }

        StateMachine::EdgePtr NewEdge(Char ch)
        {
            return new StateMachine::EdgeType(Edge(ch));
        }

        StateMachine::EdgePtr NewEdge(Char chBegin, Char chEnd)
        {
            return new StateMachine::EdgeType(Edge(chBegin, chEnd));
        }
    };

    __declspec(selectany) int RegExp::Node::ms_nCounter = 0;

} // namespace xl









#endif // #ifndef __XLREGEXP_H_0FCC5122_D6F3_4E9E_AAB0_5D268E87ED44_INCLUDED__
