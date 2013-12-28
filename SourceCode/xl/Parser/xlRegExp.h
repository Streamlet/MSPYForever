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


#include "../Containers/xlGraph.h"
#include "../Math/xlIntervalSet.h"
#include "../Memory/xlSmartPtr.h"
#include "../String/xlString.h"

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
            Node() : m_nIdentify(++ms_nCounter)
            {

            }

            int m_nIdentify;

            static int ms_nCounter;
        };

        struct Edge
        {
            Edge()
                : bEpsilon(true), chBegin(0), chEnd(0)
            {

            }

            Edge(Char ch)
                : bEpsilon(false), chBegin(ch), chEnd(ch)
            {

            }

            Edge(Char chBegin, Char chEnd)
                : bEpsilon(false), chBegin(chBegin), chEnd(chEnd)
            {

            }

            bool Match(Char ch)
            {
                if (bEpsilon)
                {
                    return false;
                }

                return (ch >= chBegin && ch <= chEnd);
            }

            bool bEpsilon;
            Char chBegin;
            Char chEnd;
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
            m_pEnd = Parse(m_pBegin);

            if (m_pEnd == nullptr)
            {
                return false;
            }

            FixStateMachine();

            return true;
        }

        bool Match(const String &s, int *pnPos = nullptr)
        {
            return Match(s, 0, m_pBegin, pnPos);
        }

    private:
        void FixStateMachine()
        {

        }

        bool Match(const String &s, int i, StateMachine::NodePtr pNode, int *pnPos = nullptr)
        {
            if (pNode == m_pEnd)
            {
                if (pnPos != nullptr)
                {
                    *pnPos = i;
                    return true;
                }

                if (i < s.Length())
                {
                    return false;
                }

                return true;
            }

            for (auto it = pNode->arrNext.Begin(); it != pNode->arrNext.End(); ++it)
            {
                if (Match(s, i, *it, pnPos))
                {
                    return true;
                }
            }

            return false;
        }

        bool Match(const String &s, int i, StateMachine::EdgePtr pEdge, int *pnPos = nullptr)
        {
            if (!pEdge->tValue.bEpsilon)
            {
                if (i >= s.Length())
                {
                    return false;
                }

                if (!pEdge->tValue.Match(s[i]))
                {
                    return false;
                }

                return Match(s, i + 1, pEdge->pNext, pnPos);
            }
            else
            {
                return Match(s, i, pEdge->pNext, pnPos);
            }
        }

    private:
        enum TokenType
        {
            TT_Eof,
            TT_VerticalBar,     // |
            TT_QuestionMark,    // ?
            TT_Plus,            // +
            TT_Star,            // *
            TT_OpenBracket,     // [
            TT_CloseBracket,    // ]
            TT_Hyphen,          // -
            TT_Caret,           // ^
            TT_OpenParen,       // (
            TT_CloseParen,      // )
            TT_OrdinaryChar,
        };

        struct Token 
        {
            TokenType type;
            Char ch;
            size_t length;

            Token(TokenType type = TT_OrdinaryChar, Char ch = 0, size_t length = 1)
                : ch(ch), type(type), length(length)
            {

            }
        };

    private:
        Token LookAhead()
        {
            if (m_nCurrentPosition >= m_strRegExp.Length())
            {
                return Token(TT_Eof, 0, 0);
            }

            Char ch = m_strRegExp[m_nCurrentPosition++];
            TokenType type = TT_OrdinaryChar;

            if (ch == L'\\')
            {
                if (m_nCurrentPosition < m_strRegExp.Length())
                {
                    return Token(TT_OrdinaryChar, m_strRegExp[m_nCurrentPosition++], 2);
                }
            }

            switch (ch)
            {
            case L'|':
                type = TT_VerticalBar;
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
            case L'?':
                type = TT_QuestionMark;
                break;
            case L'+':
                type = TT_Plus;
                break;
            case L'*':
                type = TT_Star;
                break;
            case L'(':
                type = TT_OpenParen;
                break;
            case L')':
                type = TT_CloseParen;
                break;
            default:
                break;
            }

            return Token(type, ch);
        }

        void Backward(const Token &token)
        {
            m_nCurrentPosition -= (int)token.length;
        }

    private:
        enum RepeatorType
        {
            RT_None,
            RT_ZeroOrOne,
            RT_OnePlus,
            RT_ZeroPlus
        };

        struct Repeator
        {
            RepeatorType type;
            bool bGreedy;

            Repeator()
                : type(RT_None), bGreedy(true)
            {

            }
        };

    private:
        /*
            EBNF:
            
            Expr         -> SubExpr Expr'
            Expr'        -> "|" SubExpr Expr' | ¦Å
            SubExpr      -> Phrase SubExpr'
            SubExpr'     -> Phrase SubExpr' | ¦Å
            Phrase       -> Word Repeater
            Repeater     -> Counter Greeder | ¦Å
            Counter      -> "?" | "+" | "*"
            Greeder      -> "?" | ¦Å
            Word         -> Char | "[" Collection "]" | "(" Expr ")"
            Collection   -> Reverser InvervalSet
            Reverser     -> "^" | ¦Å
            InvervalSet  -> Inverval IntervalSet'
            IntervalSet' -> Interval IntervalSet' | ¦Å
            Interver     -> Char RangeSuffix
            RangeSuffix  -> "-" Char | ¦Å
        */

        StateMachine::NodePtr Parse(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = ParseExpr(pNode);

            Token token = LookAhead();

            if (token.type != TT_Eof)
            {
                return nullptr;
            }

            return pCurrent;
        }

        StateMachine::NodePtr ParseExpr(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pSubExpr = ParseSubExpr(pNode);

            if (pSubExpr == nullptr)
            {
                return nullptr;
            }

            StateMachine::NodePtr pExprPrime = ParseExprPrime(pNode);

            if (pExprPrime == nullptr)
            {
                return nullptr;
            }

            StateMachine::NodePtr pCurrent = NewNode();
            m_spStateMachine->AddNode(pCurrent);
            m_spStateMachine->AddEdge(NewEdge(), pSubExpr, pCurrent);

            if (pExprPrime != pNode)
            {
                m_spStateMachine->AddEdge(NewEdge(), pExprPrime, pCurrent);
            }

            return pCurrent;
        }

        StateMachine::NodePtr ParseExprPrime(StateMachine::NodePtr pNode)
        {
            Token token = LookAhead();

            if (token.type != TT_VerticalBar)
            {
                Backward(token);
                return pNode;
            }

            StateMachine::NodePtr pSubExpr = ParseSubExpr(pNode);

            if (pSubExpr == nullptr)
            {
                return nullptr;
            }

            StateMachine::NodePtr pExprPrime = ParseExprPrime(pNode);

            if (pExprPrime == nullptr)
            {
                return nullptr;
            }

            StateMachine::NodePtr pCurrent = NewNode();
            m_spStateMachine->AddNode(pCurrent);
            m_spStateMachine->AddEdge(NewEdge(), pSubExpr, pCurrent);

            if (pExprPrime != pNode)
            {
                m_spStateMachine->AddEdge(NewEdge(), pExprPrime, pCurrent);
            }

            return pCurrent;
        }

        StateMachine::NodePtr ParseSubExpr(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pPhrase = ParsePhrase(pNode);

            if (pPhrase == nullptr)
            {
                return nullptr;
            }

            StateMachine::NodePtr pSubExprPrime = ParseSubExprPrime(pPhrase);

            if (pSubExprPrime == nullptr)
            {
                return nullptr;
            }

            return pSubExprPrime;
        }

        StateMachine::NodePtr ParseSubExprPrime(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pPhrase = ParsePhrase(pNode);

            if (pPhrase == nullptr)
            {
                return pNode;
            }
        
            StateMachine::NodePtr pSubExprPrime = ParseSubExprPrime(pPhrase);

            if (pSubExprPrime == nullptr)
            {
                return nullptr;
            }

            return pSubExprPrime;
        }

        StateMachine::NodePtr ParsePhrase(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = ParseWord(pNode);

            if (pCurrent == nullptr)
            {
                return nullptr;
            }

            Repeator r = ParseRepeater();

            switch (r.type)
            {
            case RT_None:
                break;
            case RT_ZeroOrOne:
                {
                    StateMachine::EdgePtr pEdgeNodeToCurrent = NewEdge();
                    m_spStateMachine->AddEdge(pEdgeNodeToCurrent);
                    pEdgeNodeToCurrent->pPrevious = pNode;
                    pEdgeNodeToCurrent->pNext     = pCurrent;

                    if (r.bGreedy)
                    {
                        pNode->arrNext.PushBack(pEdgeNodeToCurrent);
                        pCurrent->arrPrevious.PushBack(pEdgeNodeToCurrent);
                    }
                    else
                    {
                        pNode->arrNext.PushFront(pEdgeNodeToCurrent);
                        pCurrent->arrPrevious.PushFront(pEdgeNodeToCurrent);
                    }
                }
                break;
            case RT_OnePlus:
                {
                    StateMachine::NodePtr pTo = NewNode();
                    m_spStateMachine->AddNode(pTo);

                    StateMachine::EdgePtr pEdgeCurrentToNode = NewEdge();
                    StateMachine::EdgePtr pEdgeCurrentToTo   = NewEdge();

                    if (r.bGreedy)
                    {
                        m_spStateMachine->AddEdge(pEdgeCurrentToNode, pCurrent, pNode);
                        m_spStateMachine->AddEdge(pEdgeCurrentToTo,   pCurrent, pTo);
                    }
                    else
                    {
                        m_spStateMachine->AddEdge(pEdgeCurrentToTo,   pCurrent, pTo);
                        m_spStateMachine->AddEdge(pEdgeCurrentToNode, pCurrent, pNode);
                    }

                    pCurrent = pTo;
                }
                break;
            case RT_ZeroPlus:
                {
                    StateMachine::NodePtr pTo = NewNode();
                    m_spStateMachine->AddNode(pTo);

                    StateMachine::EdgePtr pEdgeCurrentToNode = NewEdge();
                    m_spStateMachine->AddEdge(pEdgeCurrentToNode, pCurrent, pNode);

                    StateMachine::EdgePtr pEdgeNodeToTo = NewEdge();
                    m_spStateMachine->AddEdge(pEdgeNodeToTo);
                    pEdgeNodeToTo->pPrevious = pNode;
                    pEdgeNodeToTo->pNext     = pTo;

                    if (r.bGreedy)
                    {
                        pNode->arrNext.PushBack(pEdgeNodeToTo);
                        pTo->arrPrevious.PushBack(pEdgeNodeToTo);
                    }
                    else
                    {
                        pNode->arrNext.PushFront(pEdgeNodeToTo);
                        pTo->arrPrevious.PushFront(pEdgeNodeToTo);
                    }

                    pCurrent = pTo;
                }
                break;
            default:
                break;
            }

            return pCurrent;
        }

        Repeator ParseRepeater()
        {
            Repeator r = ParseCounter();

            if (r.type == RT_None)
            {
                return r;
            }

            r.bGreedy = ParseGreeder();

            return r;
        }

        Repeator ParseCounter()
        {
            Repeator r;
            Token token = LookAhead();

            switch (token.type)
            {
            case TT_QuestionMark:
                r.type = RT_ZeroOrOne;
                break;
            case TT_Plus:
                r.type = RT_OnePlus;
                break;
            case TT_Star:
                r.type = RT_ZeroPlus;
                break;
            default:
                Backward(token);
                break;
            }

            return r;
        }

        bool ParseGreeder()
        {
            bool bGreedy = true;
            Token token = LookAhead();

            if (token.type == TT_QuestionMark)
            {
                bGreedy = false;
            }
            else
            {
                Backward(token);
            }

            return bGreedy;
        }

        StateMachine::NodePtr ParseWord(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = nullptr;

            Token token = LookAhead();

            switch (token.type)
            {
            case TT_OpenParen:
                {
                    pCurrent = ParseExpr(pNode);

                    if (pCurrent == nullptr)
                    {
                        return nullptr;
                    }

                    token = LookAhead();

                    if (token.type != TT_CloseParen)
                    {
                        return nullptr;
                    }
                }
                break;
            case TT_OpenBracket:
                {
                    pCurrent = ParseCollection(pNode);

                    if (pCurrent == nullptr)
                    {
                        return nullptr;
                    }

                    token = LookAhead();

                    if (token.type != TT_CloseBracket)
                    {
                        return nullptr;
                    }
                }
                break;
            case TT_OrdinaryChar:
                {
                    pCurrent = AddNormalNode(pNode, token.ch);

                    if (pCurrent == nullptr)
                    {
                        return nullptr;
                    }
                }
                break;
            default:
                Backward(token);
                return pCurrent;
            }

            return pCurrent;
        }

        StateMachine::NodePtr ParseCollection(StateMachine::NodePtr pNode)
        {
            bool bReverse = ParseReverser();
            IntervalSet<Char> is = ParseIntervalSet();

            if (is.IsEmpty())
            {
                return nullptr;
            }

            if (bReverse)
            {
                IntervalSet<Char> u;
                u.Union(Interval<Char>(0, -1));
                is = u.Exclude(is);
                is.MakeClose(1);
            }

            StateMachine::NodePtr pCurrent = NewNode();
            Set<Interval<Char>> intervals = is.GetIntervals();

            for (auto it = intervals.Begin(); it != intervals.End(); ++it)
            {
                StateMachine::EdgePtr pEdge = NewEdge(it->left, it->right);
                m_spStateMachine->AddEdge(pEdge, pNode, pCurrent);
            }

            m_spStateMachine->AddNode(pCurrent);

            return pCurrent;
        }

        bool ParseReverser()
        {
            bool bReverse = false;
            Token token = LookAhead();

            if (token.type == TT_Caret)
            {
                bReverse = true;
            }
            else
            {
                Backward(token);
            }

            return bReverse;
        }

        IntervalSet<Char> ParseIntervalSet()
        {
            IntervalSet<Char> is;
            Interval<Char> i = ParseInterval();

            if (i.IsEmpty())
            {
                return is;
            }

            is.Union(i);
            IntervalSet<Char> isPrime = ParseIntervalSetPrime();
            is = is.Union(isPrime);

            return is;
        }

        IntervalSet<Char> ParseIntervalSetPrime()
        {
            IntervalSet<Char> is;
            Interval<Char> i = ParseInterval();

            if (i.IsEmpty())
            {
                return is;
            }

            is.Union(i);
            IntervalSet<Char> isPrime = ParseIntervalSetPrime();
            is = is.Union(isPrime);

            return is;
        }

        Interval<Char> ParseInterval()
        {
            Interval<Char> i;
            Token token = LookAhead();

            if (token.type != TT_OrdinaryChar)
            {
                Backward(token);
                return i;
            }

            i = Interval<Char>(token.ch, token.ch);
            Interval<Char> iSuffix = ParseRangseSuffix();

            if (!iSuffix.IsEmpty())
            {
                i.right = iSuffix.right;
            }

            return i;
        }

        Interval<Char> ParseRangseSuffix()
        {
            Interval<Char> i;
            Token token = LookAhead();

            if (token.type != TT_Hyphen)
            {
                Backward(token);
                return i;
            }

            token = LookAhead();

            if (token.type != TT_OrdinaryChar)
            {
                Backward(token);
                return i;
            }

            i = Interval<Char>(token.ch, token.ch);
            return i;
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
