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
#include <xl/Math/xlIntervalSet.h>

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
            m_nCurrentPosition -= token.length;
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
        //
        // EBNF:
        //
        // Expr             -> SubExpr { "|" SubExpr }
        // SubExpr          -> { Phrase }
        // Phrase           -> Word [ Repeater ]
        // Repeater         -> ( "?" | "+" | "*" ) [ "?" ]
        // Word             -> OrdinaryChar | "[" Collection "]" | "(" Expr ")"
        // Collection       -> [ "^" ] { OrdinaryChar | OrdinaryChar "-" OrdinaryChar }
        // OrdinaryChar     -> All ordinary characters
        //

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
            StateMachine::NodePtr pCurrent = ParseSubExpr(pNode);

            if (pCurrent == nullptr)
            {
                return nullptr;
            }

            while (true)
            {
                Token token = LookAhead();

                if (token.type != TT_VerticalBar)
                {
                    Backward(token);
                    return pCurrent;
                }

                StateMachine::NodePtr pNewNode = ParseSubExpr(pNode);
                StateMachine::EdgePtr pEdge = NewEdge();
                m_spStateMachine->AddEdge(pEdge, pNewNode, pCurrent);
            }

            return nullptr;
        }

        StateMachine::NodePtr ParseSubExpr(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = pNode;

            while (true)
            {
                StateMachine::NodePtr pNewNode = ParsePhrase(pCurrent);

                if (pNewNode == pCurrent || pNewNode == nullptr)
                {
                    return pNewNode;
                }

                pCurrent = pNewNode;
            }

            return nullptr;
        }

        StateMachine::NodePtr ParsePhrase(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pFrom = NewNode();
            StateMachine::NodePtr pCurrent = ParseWord(pFrom);

            if (pCurrent == nullptr)
            {
                delete pFrom;
                return nullptr;
            }

            if (pCurrent == pFrom)
            {
                delete pFrom;
                return pNode;
            }

            Repeator r = ParseRepeater();

            switch (r.type)
            {
            case RT_None:
                {
                    m_spStateMachine->AddNode(pFrom);
                    StateMachine::EdgePtr pEdge = NewEdge();
                    m_spStateMachine->AddEdge(pEdge, pNode, pFrom);
                }
                break;
            case RT_ZeroOrOne:
                {
                    m_spStateMachine->AddNode(pFrom);
                    StateMachine::EdgePtr pEdgeNodeToFrom    = NewEdge();
                    StateMachine::EdgePtr pEdgeNodeToCurrent = NewEdge();

                    if (r.bGreedy)
                    {
                        m_spStateMachine->AddEdge(pEdgeNodeToFrom, pNode, pFrom);
                        m_spStateMachine->AddEdge(pEdgeNodeToCurrent, pNode, pCurrent);
                    }
                    else
                    {
                        m_spStateMachine->AddEdge(pEdgeNodeToCurrent, pNode, pCurrent);
                        m_spStateMachine->AddEdge(pEdgeNodeToFrom, pNode, pFrom);
                    }
                }
                break;
            case RT_OnePlus:
                {
                    StateMachine::NodePtr pTo = NewNode();
                    m_spStateMachine->AddNode(pFrom);
                    m_spStateMachine->AddNode(pTo);

                    StateMachine::EdgePtr pEdgeNodeToFrom = NewEdge();
                    m_spStateMachine->AddEdge(pEdgeNodeToFrom, pNode, pFrom);

                    StateMachine::EdgePtr pEdgeCurrentToFrom = NewEdge();
                    StateMachine::EdgePtr pEdgeCurrentToTo   = NewEdge();

                    if (r.bGreedy)
                    {
                        m_spStateMachine->AddEdge(pEdgeCurrentToFrom, pCurrent, pFrom);
                        m_spStateMachine->AddEdge(pEdgeCurrentToTo,   pCurrent, pTo);
                    }
                    else
                    {
                        m_spStateMachine->AddEdge(pEdgeCurrentToTo,   pCurrent, pTo);
                        m_spStateMachine->AddEdge(pEdgeCurrentToFrom, pCurrent, pFrom);
                    }

                    pCurrent = pTo;
                }
                break;
            case RT_ZeroPlus:
                {
                    StateMachine::NodePtr pTo = NewNode();
                    m_spStateMachine->AddNode(pFrom);
                    m_spStateMachine->AddNode(pTo);

                    StateMachine::EdgePtr pEdgeCurrentToNode = NewEdge();
                    m_spStateMachine->AddEdge(pEdgeCurrentToNode, pCurrent, pNode);

                    StateMachine::EdgePtr pEdgeNodeToFrom = NewEdge();
                    StateMachine::EdgePtr pEdgeNodeToTo   = NewEdge();

                    if (r.bGreedy)
                    {
                        m_spStateMachine->AddEdge(pEdgeNodeToFrom, pNode, pFrom);
                        m_spStateMachine->AddEdge(pEdgeNodeToTo,   pNode, pTo);
                    }
                    else
                    {
                        m_spStateMachine->AddEdge(pEdgeNodeToTo,   pNode, pTo);
                        m_spStateMachine->AddEdge(pEdgeNodeToFrom, pNode, pFrom);
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

            bool bGreedy = true;

            if (r.type != RT_None)
            {
                token = LookAhead();

                if (token.type == TT_QuestionMark)
                {
                    r.bGreedy = false;
                }
                else
                {
                    Backward(token);
                }
            }

            return r;
        }

        StateMachine::NodePtr ParseWord(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = pNode;

            Token token = LookAhead();

            switch (token.type)
            {
            case TT_OpenParen:
                {
                    pCurrent = ParseExpr(pCurrent);

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
                    pCurrent = ParseCollection(pCurrent);

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
                    pCurrent = AddNormalNode(pCurrent, token.ch);

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
            bool bFirst = true;
            bool bInHyphen = false;
            bool bAcceptHyphen = false;
            Char chLastChar = 0;

            bool bOpposite = false;
            IntervalSet<Char> is;

            bool bContinue = true;

            while (bContinue)
            {
                Token token = LookAhead();

                switch (token.type)
                {
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
                        if (bInHyphen || !bAcceptHyphen)
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
                            is.Union(Interval<Char>(chLastChar, token.ch));
                            bInHyphen = false;
                            bAcceptHyphen = false;
                        }
                        else
                        {
                            is.Union(Interval<Char>(token.ch, token.ch));
                            chLastChar = token.ch;
                            bAcceptHyphen = true;
                        }
                    }
                    break;
                default:
                    {
                        Backward(token);
                        bContinue = false;
                    }
                    break;
                }

                bFirst = false;
            }

            if (bOpposite)
            {
                IntervalSet<Char> u;
                u.Union(Interval<Char>(0, -1));
                is = u.Exclude(is);
                is.MakeClose(1);
            }

            StateMachine::NodePtr pCurrent = pNode;

            if (is.IsEmpty())
            {
                return pCurrent;
            }

            pCurrent = NewNode();
            Set<Interval<Char>> intervals = is.GetIntervals();

            for (auto it = intervals.Begin(); it != intervals.End(); ++it)
            {
                StateMachine::EdgePtr pEdge = NewEdge(it->left, it->right);
                m_spStateMachine->AddEdge(pEdge, pNode, pCurrent);
            }

            m_spStateMachine->AddNode(pCurrent);

            return pCurrent;
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
