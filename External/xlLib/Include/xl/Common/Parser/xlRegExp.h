//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRegExp.h
//    Author:      Streamlet
//    Create Time: 2012-05-20
//    Description: Regular Expression
//
//------------------------------------------------------------------------------

#ifndef __XLREGEXP_H_0FCC5122_D6F3_4E9E_AAB0_5D268E87ED44_INCLUDED__
#define __XLREGEXP_H_0FCC5122_D6F3_4E9E_AAB0_5D268E87ED44_INCLUDED__


#include "../../xlDef.h"
#include "../Containers/xlGraph.h"
#include "../Containers/xlArray.h"
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
                : bReverse(false), bEpsilon(true), chBegin(0), chEnd(0), nMinNodePasses(0), nMaxNodePasses(-1), nRollbackChars(0)
            {

            }

            Edge(Char ch)
                : bReverse(false), bEpsilon(false), chBegin(ch), chEnd(ch), nMinNodePasses(0), nMaxNodePasses(-1), nRollbackChars(0)
            {

            }

            Edge(Char chBegin, Char chEnd)
                : bReverse(false), bEpsilon(false), chBegin(chBegin), chEnd(chEnd), nMinNodePasses(0), nMaxNodePasses(-1), nRollbackChars(0)
            {

            }

            bool MatchNoReverse(Char ch)
            {
                if (bEpsilon)
                {
                    return false;
                }

                return (ch >= chBegin && ch <= chEnd);
            }

            bool Match(Char ch)
            {
                bool bMatched = MatchNoReverse(ch);
                return bReverse ? !bMatched : bMatched;
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

            bool bReverse;
            bool bEpsilon;
            Char chBegin;
            Char chEnd;

            // Rules
            int nMinNodePasses;
            int nMaxNodePasses;

            int nRollbackChars;
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

                return Match(s, i + 1 - pEdge->tValue.nRollbackChars, pEdge->pNext, pnPos);
            }
            else
            {
                return Match(s, i, pEdge->pNext, pnPos);
            }
        }

    private:

        static const Char InvalidChar = -1;

        struct Token 
        {
            Char type;
            Char ch;
            size_t length;

            Token(Char type = InvalidChar, Char ch = InvalidChar, size_t length = 1)
                : type(type), ch(ch), length(length)
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
            default:
                break;
            }

            return false;
        }

        Token LookAhead()
        {
            if (m_nCurrentPosition >= m_strRegExp.Length())
            {
                return Token(L'\0', InvalidChar, 0);
            }

            Char ch = m_strRegExp[m_nCurrentPosition++];

            if (ch == L'\\' &&
                m_nCurrentPosition < m_strRegExp.Length() &&
                IsSpecialCharacter(m_strRegExp[m_nCurrentPosition]))
            {
                return Token(InvalidChar, m_strRegExp[m_nCurrentPosition++], 2);
            }

            if (IsSpecialCharacter(ch))
            {
                return Token(ch);
            }
            else
            {
                return Token(InvalidChar, ch);
            }
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

        enum GroupType
        {
            GroupType_Error,
            GroupType_Priority,
            GroupType_Capture,
            GroupType_LookAhead_Positive,
            GroupType_LookAhead_Negative,
            GroupType_LookBehind_Positive,
            GroupType_LookBehind_Negative,
        };

        struct Group
        {
            GroupType eType;
            String strName;

            Group(GroupType eType, String strName = L"")
                : eType(eType), strName(strName)
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
            Word                -> "(" GroupFlag Expr ")" | Collection | Char
            GroupFlag           -> "?" GroupFlagContent | ¦Å
            GroupFlagContent    -> "=" | "!" | "<=" | "<!" | ":" | "<" GroupName ">"
            GroupName           -> IdChar GroupName | ¦Å
            Collection          -> "[" Reverser IntervalSet "]" | "." | "\" CharSetDescriptor
            Reverser            -> "^" | ¦Å
            IntervalSet         -> IntervalSetItem IntervalSet | ¦Å
            IntervalSetItem     -> "." | "\" CharSetDescriptor | Interver
            Interver            -> Char InterverSuffix
            InterverSuffix      -> "-" Char | ¦Å
            CharSetDescriptor   -> "d" | "D" | "f" | "n" | "r" | "s" | "S" | "t" | "v" | "w" | "W" | "x" Hex02 | "u" Hex04

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

            if (token.type != L',')
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

            if (token.ch >= L'0' && token.ch <= L'9')
            {
                i.AddHighDigit(token.ch - L'0');
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

            if (token.type != InvalidChar)
            {
                if (token.type == L'(')
                {
                    Group group = ParseGroup();
                    pCurrent = ParseExpr(pNode);

                    if (pCurrent == nullptr)
                    {
                        return nullptr;
                    }

                    token = LookAhead();

                    if (token.type != L')')
                    {
                        Backward(token);
                        return nullptr;
                    }
                }
                else
                {
                    Backward(token);

                    pCurrent = ParseCollection(pNode);

                    if (pCurrent == nullptr)
                    {
                        return nullptr;
                    }
                }
            }
            else
            {
                pCurrent = AddNormalNode(pNode, token.ch);

                if (pCurrent == nullptr)
                {
                    return nullptr;
                }
            }

            return pCurrent;
        }

        Group ParseGroup()
        {
            Group group(GroupType_Error);
            Token token = LookAhead();

            if (token.type == L'?')
            {
                token = LookAhead();

                switch (token.type)
                {
                case ':':
                    group.eType = GroupType_Priority;
                    break;
                case '=':
                    group.eType = GroupType_LookAhead_Positive;
                    break;
                case '!':
                    group.eType = GroupType_LookAhead_Negative;
                    break;
                case '<':

                    token = LookAhead();

                    switch (token.type)
                    {
                    case '=':
                        group.eType = GroupType_LookBehind_Positive;
                        break;
                    case '!':
                        group.eType = GroupType_LookBehind_Negative;
                        break;
                    default:

                        group.strName = ParseGroupName();

                        if (group.strName.Length() <= 0)
                        {
                            group.eType = GroupType_Error;
                        }
                        else
                        {
                            token = LookAhead();

                            if (token.type != L'>')
                            {
                                group.eType = GroupType_Error;
                                Backward(token);
                            }
                        }

                        group.eType = GroupType_Capture;

                        break;
                    }

                    break;
                default:
                    Backward(token);
                    break;
                }
            }
            else
            {
                Backward(token);
                group.eType = GroupType_Capture;
            }

            return group;
        }

        String ParseGroupName()
        {
            String strName;

            while (true)
            {
                Token token = LookAhead();

                if (token.length != 1 || token.type != InvalidChar ||
                    !(token.ch >= L'a' && token.ch <= 'z' || token.ch >= L'A' && token.ch <= 'Z' || token.ch >= L'0' && token.ch <= '9' || token.ch == L'_'))
                {
                    Backward(token);
                    break;
                }

                strName.AppendBack(token.ch);
            }

            return strName;
        }

        StateMachine::NodePtr ParseCollection(StateMachine::NodePtr pNode)
        {
            IntervalSet<Char> is;
            bool bReverse = false;
            Token token = LookAhead();

            switch (token.type)
            {
            case L'.':
                {
                    is.Union(Interval<Char>(0, -1));
                    is.Exclude(Interval<Char>(L'\n'));
                    is.MakeClose(1);
                }
                break;
            case L'\\':
                {
                    IntervalSet<Char> isCharSet = ParseCharSetDescriptor();

                    if (isCharSet.IsEmpty())
                    {
                        return nullptr;
                    }
                    else
                    {
                        is = is.Union(isCharSet);
                    }
                }
                break;
            case L'[':
                {
                    bReverse = ParseReverser();
                    is = ParseIntervalSet();

                    token = LookAhead();

                    if (token.type != L']')
                    {
                        Backward(token);
                        return nullptr;
                    }

                    if (is.IsEmpty())
                    {
                        return nullptr;
                    }
                }
                break;
            default:
                Backward(token);
                return nullptr;
            }

            StateMachine::NodePtr pCurrent = nullptr;
            Set<Interval<Char>> intervals = is.GetIntervals();

            if (bReverse)
            {
                StateMachine::EdgePtr pLastEdge = nullptr;

                for (auto it = intervals.Begin(); it != intervals.End(); ++it)
                {
                    pLastEdge = NewEdge(it->left, it->right);
                    pLastEdge->tValue.bReverse = true;
                    pLastEdge->tValue.nRollbackChars = 1;

                    pCurrent = NewNode();
                    m_spStateMachine->AddEdge(pLastEdge, pNode, pCurrent);
                    pNode = pCurrent;
                }

                pLastEdge->tValue.nRollbackChars = 0;
            }
            else
            {
                pCurrent = NewNode();

                for (auto it = intervals.Begin(); it != intervals.End(); ++it)
                {
                    StateMachine::EdgePtr pEdge = NewEdge(it->left, it->right);
                    m_spStateMachine->AddEdge(pEdge, pNode, pCurrent);
                }
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

            IntervalSet<Char> isItem = ParseIntervalSetItem();

            if (isItem.IsEmpty())
            {
                return is;
            }

            is = is.Union(isItem);

            IntervalSet<Char> isPrime = ParseIntervalSet();
            is = is.Union(isPrime);

            return is;
        }

        IntervalSet<Char> ParseIntervalSetItem()
        {
            IntervalSet<Char> is;
            Token token = LookAhead();

            switch (token.type)
            {
            case L'.':
                {
                    is.Union(Interval<Char>(0, -1));
                    is.Exclude(Interval<Char>(L'\n'));
                    is.MakeClose(1);
                }
                break;
            case L'\\':
                {
                    IntervalSet<Char> isCharSet = ParseCharSetDescriptor();

                    if (isCharSet.IsEmpty())
                    {
                        Backward(token);
                    }
                    else
                    {
                        is = is.Union(isCharSet);
                    }
                }
                break;
            default:
                {
                    Backward(token);
                    Interval<Char> i = ParseInterval();
                    is.Union(i);
                }
                break;
            }

            return is;
        }

        IntervalSet<Char> ParseCharSetDescriptor()
        {
            IntervalSet<Char> is;
            Token token = LookAhead();

            switch (token.ch)
            {
            case L'd':
                is.Union(Interval<Char>(L'0', L'9'));
                break;
            case L'D':
                is.Union(Interval<Char>(0, -1));
                is.Exclude(Interval<Char>(L'0', L'9'));
                is.MakeClose(1);
                break;
            case L'f':
                is.Union(Interval<Char>(L'\x0c'));
                break;
            case L'n':
                is.Union(Interval<Char>(L'\x0a'));
                break;
            case L'r':
                is.Union(Interval<Char>(L'\x0d'));
                break;
            case L's':
                is.Union(Interval<Char>(L'\x09', L'\x0d'));
                break;
            case L'S':
                is.Union(Interval<Char>(0, -1));
                is.Exclude(Interval<Char>(L'\x09', L'\x0d'));
                is.MakeClose(1);
                break;
            case L't':
                is.Union(Interval<Char>(L'\x09'));
                break;
            case L'v':
                is.Union(Interval<Char>(L'\x0b'));
                break;
            case L'w':
                is.Union(Interval<Char>(L'a', L'z'));
                is.Union(Interval<Char>(L'A', L'Z'));
                is.Union(Interval<Char>(L'0', L'9'));
                is.Union(Interval<Char>(L'_'));
                break;
            case L'W':
                is.Union(Interval<Char>(0, -1));
                is.Exclude(Interval<Char>(L'a', L'z'));
                is.Exclude(Interval<Char>(L'A', L'Z'));
                is.Exclude(Interval<Char>(L'0', L'9'));
                is.Exclude(Interval<Char>(L'_'));
                is.MakeClose(1);
                break;
            case L'x':
                {
                    int iValue = ParseHex0x(2);
                    if (iValue >= 0)
                    {
                        is.Union(Interval<Char>((Char)iValue));
                    }
                    else
                    {
                        Backward(token);
                    }
                }
                break;
            case L'u':
                {
                    int iValue = ParseHex0x(4);
                    if (iValue >= 0)
                    {
                        is.Union(Interval<Char>((Char)iValue));
                    }
                    else
                    {
                        Backward(token);
                    }
                }
                break;
                break;
            default:
                Backward(token);
                break;
            }

            return is;
        }

        Interval<Char> ParseInterval()
        {
            Interval<Char> i;
            Token token = LookAhead();

            if (token.type != InvalidChar)
            {
                Backward(token);
                return i;
            }

            i = Interval<Char>(token.ch);
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

            if (token.type != InvalidChar)
            {
                Backward(token);
                return i;
            }

            i = Interval<Char>(token.ch);
            return i;
        }

        int ParseHex0x(int x)
        {
            int iValue = 0;
            Array<Token> arrBackwards;

            for (int i = 0; i < x; ++i)
            {
                Token token = LookAhead();
                arrBackwards.PushFront(token);

                if (token.ch >= L'0' && token.ch <= L'9')
                {
                    iValue = iValue * 0x10 + (token.ch - L'0');
                }
                else if (token.ch >= L'a' && token.ch <= L'f')
                {
                    iValue = iValue * 0x10 + (token.ch - L'a' + 10);
                }
                else if (token.ch >= L'A' && token.ch <= L'F')
                {
                    iValue = iValue * 0x10 + (token.ch - L'A' + 10);
                }
                else
                {
                    iValue = -1;
                    break;
                }
            }

            if (iValue < 0)
            {
                for (auto it = arrBackwards.Begin(); it != arrBackwards.End(); ++it)
                {
                    Backward(*it);
                }
            }

            return iValue;
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
