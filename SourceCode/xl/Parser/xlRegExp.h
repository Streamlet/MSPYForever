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
            Node() : m_nIdentify(++ms_nCounter), m_nPasses(0)
            {

            }

            void ClearState()
            {
                m_nPasses = 0;
            }

            int m_nIdentify;
            int m_nPasses;

            static int ms_nCounter;
        };

        struct Edge
        {
            Edge()
                : bEpsilon(true), chBegin(0), chEnd(0), nMinNodePasses(0), nMaxNodePasses(-1)
            {

            }

            Edge(Char ch)
                : bEpsilon(false), chBegin(ch), chEnd(ch), nMinNodePasses(0), nMaxNodePasses(-1)
            {

            }

            Edge(Char chBegin, Char chEnd)
                : bEpsilon(false), chBegin(chBegin), chEnd(chEnd), nMinNodePasses(0), nMaxNodePasses(-1)
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

            bool IsMatchRule(Node *pNode)
            {
                if (nMinNodePasses < 0 || pNode->m_nPasses < nMinNodePasses)
                {
                    return false;
                }

                if (nMaxNodePasses >= 0 && pNode->m_nPasses > nMaxNodePasses)
                {
                    return false;
                }

                return true;
            }

            bool bEpsilon;
            Char chBegin;
            Char chEnd;

            // Rules
            int nMinNodePasses;
            int nMaxNodePasses;
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
            for (auto it = m_spStateMachine->GetNodes().Begin(); it != m_spStateMachine->GetNodes().End(); ++it)
            {
                (*it)->tValue.ClearState();
            }

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

            ++pNode->tValue.m_nPasses;

            for (auto it = pNode->arrNext.Begin(); it != pNode->arrNext.End(); ++it)
            {
                if (!(*it)->tValue.IsMatchRule(&pNode->tValue))
                {
                    continue;
                }

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

        struct Token 
        {
            Char type;
            size_t length;
            bool bControlChar;

            Token(Char type = -1, bool bControlChar = true,  size_t length = 1)
                : type(type), bControlChar(bControlChar), length(length)
            {

            }
        };

    private:

        bool IsSpecialCharacter(Char ch)
        {
            switch (ch)
            {
            case L'|':
            case L'[':
            case L']':
            case L'-':
            case L'^':
            case L'?':
            case L'+':
            case L'*':
            case L'(':
            case L')':
            case L'{':
            case L'}':
            case L',':
            case L'\\':
            case L'.':
                return true;
                break;
            default:
                break;
            }

            return false;
        }

        Token LookAhead()
        {
            if (m_nCurrentPosition >= m_strRegExp.Length())
            {
                return Token(L'\0', true, 0);
            }

            Char ch = m_strRegExp[m_nCurrentPosition++];

            if (ch == L'\\' &&
                m_nCurrentPosition < m_strRegExp.Length() &&
                IsSpecialCharacter(m_strRegExp[m_nCurrentPosition]))
            {
                return Token(m_strRegExp[m_nCurrentPosition++], false, 2);
            }

            return Token(ch, IsSpecialCharacter(ch));
        }

        void Backward(const Token &token)
        {
            m_nCurrentPosition -= (int)token.length;
        }

    private:
        struct Repeator
        {
            bool bGreedy;
            int iMinRepeats;
            int iMaxRepeats;

            Repeator()
                : bGreedy(true), iMinRepeats(-1), iMaxRepeats(-1)
            {

            }
        };

        enum SpecialIntegerValue
        {
            Integer_Blank   = -1,
            Integer_None    = -2,
        };

        struct Integer
        {
            int iValue; // > 0 or SpecialIntegerValue
            int iNextFactor;

            Integer()
                : iValue(Integer_Blank), iNextFactor(0)
            {

            }

            void AddHighDigit(int i)
            {
                i = i % 10;

                if (iValue < 0)
                {
                    iValue = i;
                    iNextFactor = 1;
                }
                else
                {
                    iValue += i * iNextFactor;
                    iNextFactor *= 10;
                }
            }

            operator int () const
            {
                return iValue;
            }
        };

    private:
        /*
            EBNF:
            
            Expr                -> SubExpr Expr'
            Expr'               -> "|" SubExpr Expr' | ¦Å
            SubExpr             -> Phrase SubExpr'
            SubExpr'            -> Phrase SubExpr' | ¦Å
            Phrase              -> Word Repeater
            Repeater            -> Counter Greeder | ¦Å
            Counter             -> "?" | "+" | "*" | "{" RangeCounter "}"
            RangeCounter        -> Integer RangeCounterSuffix
            RangeCounterSuffix  -> "," Integer | ¦Å
            Integer             -> Digit Integer | ¦Å
            Greeder             -> "?" | ¦Å
            Word                -> Char | "[" Collection "]" | "(" Expr ")"
            Collection          -> Reverser IntervalSet
            Reverser            -> "^" | ¦Å
            IntervalSet         -> Inverval IntervalSet ¡¤ ¦Å
            Interver            -> Char InterverSuffix
            InterverSuffix      -> "-" Char | ¦Å
        */

        StateMachine::NodePtr Parse(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = ParseExpr(pNode);

            Token token = LookAhead();

            if (token.type != L'\0')
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

            if (token.type != L'|')
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

            if (r.iMinRepeats < 0)
            {
                return pCurrent;
            }

            StateMachine::NodePtr pTo = NewNode();
            m_spStateMachine->AddNode(pTo);

            if (r.iMinRepeats == 0)
            {
                StateMachine::EdgePtr pEdgeNodeToTo = NewEdge();
                m_spStateMachine->AddEdge(pEdgeNodeToTo);
                pEdgeNodeToTo->pPrevious = pNode;
                pEdgeNodeToTo->pNext = pTo;

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
            }

            if (r.iMaxRepeats != 0)
            {
                StateMachine::EdgePtr pEdgeCurrentToNode = NewEdge();
                StateMachine::EdgePtr pEdgeCurrentToTo   = NewEdge();

                if (r.bGreedy)
                {
                    m_spStateMachine->AddEdge(pEdgeCurrentToNode, pCurrent, pNode);
                    m_spStateMachine->AddEdge(pEdgeCurrentToTo,   pCurrent, pTo);
                }
                else
                {
                    m_spStateMachine->AddEdge(pEdgeCurrentToTo, pCurrent, pTo);
                    m_spStateMachine->AddEdge(pEdgeCurrentToNode, pCurrent, pNode);
                }

                if (r.iMaxRepeats > 0)
                {
                    pEdgeCurrentToNode->tValue.nMaxNodePasses = r.iMaxRepeats - 1;
                }

                pEdgeCurrentToTo->tValue.nMinNodePasses = r.iMinRepeats;
            }

            return pTo;
        }

        Repeator ParseRepeater()
        {
            Repeator r = ParseCounter();

            if (r.iMinRepeats < 0)
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
            case L'?':
                r.iMinRepeats = 0;
                r.iMaxRepeats = 1;
                break;
            case L'+':
                r.iMinRepeats = 1;
                r.iMaxRepeats = -1;
                break;
            case L'*':
                r.iMinRepeats = 0;
                r.iMaxRepeats = -1;
                break;
            case L'{':
                r = ParseRangeCounter();
                token = LookAhead();
                if (token.type != L'}')
                {
                    Backward(token);
                    r.iMinRepeats = -1;
                    r.iMaxRepeats = -1;
                }
                break;
            default:
                Backward(token);
                break;
            }

            return r;
        }

        Repeator ParseRangeCounter()
        {
            Repeator r;

            r.iMinRepeats = ParseInteger();

            if (r.iMinRepeats == Integer_Blank)
            {
                r.iMinRepeats = 0;
            }

            r.iMaxRepeats = ParseRangeCounterSuffix();

            if (r.iMaxRepeats == Integer_None)
            {
                r.iMaxRepeats = r.iMinRepeats;
            }

            return r;
        }

        int ParseRangeCounterSuffix()
        {
            int i = Integer_Blank;
            Token token = LookAhead();

            if (!token.bControlChar || token.type != L',')
            {
                Backward(token);
                i = Integer_None;
            }
            else
            {
                i = ParseInteger();
            }

            return i;
        }

        Integer ParseInteger()
        {
            Integer i = ParseDigit();

            if (i >= 0)
            {
                Integer iSubInteger = ParseInteger();

                if (iSubInteger >= 0)
                {
                    i.AddHighDigit(iSubInteger);
                }
                else if (iSubInteger < -1)
                {
                    i.iValue = iSubInteger;
                }
            }

            return i;
        }

        Integer ParseDigit()
        {
            Token token = LookAhead();
            Integer i;

            if (!token.bControlChar && token.type >= L'0' && token.type <= L'9')
            {
                i.AddHighDigit(token.type - L'0');
            }
            else
            {
                Backward(token);
            }

            return i;
        }

        bool ParseGreeder()
        {
            bool bGreedy = true;
            Token token = LookAhead();

            if (token.type == L'?')
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

            if (token.bControlChar)
            {
                switch (token.type)
                {
                case L'(':
                    {
                        pCurrent = ParseExpr(pNode);

                        if (pCurrent == nullptr)
                        {
                            return nullptr;
                        }

                        token = LookAhead();

                        if (token.type != L')')
                        {
                            return nullptr;
                        }
                    }
                    break;
                case L'[':
                    {
                        pCurrent = ParseCollection(pNode);

                        if (pCurrent == nullptr)
                        {
                            return nullptr;
                        }

                        token = LookAhead();

                        if (token.type != L']')
                        {
                            return nullptr;
                        }
                    }
                    break;
                default:
                    Backward(token);
                    break;
                }
            }
            else
            {
                pCurrent = AddNormalNode(pNode, token.type);

                if (pCurrent == nullptr)
                {
                    return nullptr;
                }
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

            if (token.type == L'^')
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
            IntervalSet<Char> isPrime = ParseIntervalSet();
            is = is.Union(isPrime);

            return is;
        }

        Interval<Char> ParseInterval()
        {
            Interval<Char> i;
            Token token = LookAhead();

            if (token.bControlChar)
            {
                Backward(token);
                return i;
            }

            i = Interval<Char>(token.type, token.type);
            Interval<Char> iSuffix = ParseIntervalSuffix();

            if (!iSuffix.IsEmpty())
            {
                i.right = iSuffix.right;
            }

            return i;
        }

        Interval<Char> ParseIntervalSuffix()
        {
            Interval<Char> i;
            Token token = LookAhead();

            if (token.type != L'-')
            {
                Backward(token);
                return i;
            }

            token = LookAhead();

            if (token.bControlChar)
            {
                Backward(token);
                return i;
            }

            i = Interval<Char>(token.type, token.type);
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
