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
            if (pNode == m_pEnd)
            {
                if (i < s.Length())
                {
                    return false;
                }

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

                return Match(s, i + 1, pEdge->pNext);
            }
            else
            {
                return Match(s, i, pEdge->pNext);
            }
        }

    private:
        enum TokenType
        {
            TT_Eof,
            TT_VerticalBar,     // |
            TT_OpenParen,       // (
            TT_CloseParen,      // )
            TT_OpenBracket,     // [
            TT_CloseBracket,    // ]
            TT_Hyphen,          // -
            TT_Caret,           // ^
            TT_OrdinaryChar
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
            case L'(':
                type = TT_OpenParen;
                break;
            case L')':
                type = TT_CloseParen;
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

    private:
        //
        // EBNF:
        //
        // Expr             -> ExprNoOr { "|" ExprNoOr }
        // ExprNoOr         -> ExprNoGroup { "(" Expr ")" ExprNoGroup }
        // ExprNoGroup      -> ExprNoCollection { "[" ExprCollection "]" ExprNoCollection }
        // ExprCollection   -> [ "^" ] { OrdinaryChar | OrdinaryChar "-" OrdinaryChar }
        // ExprNoCollection -> { OrdinaryChar }
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
            StateMachine::NodePtr pCurrent = ParseExprNoOr(pNode);

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

                StateMachine::NodePtr pNewNode = ParseExprNoOr(pNode);
                StateMachine::EdgePtr pEdge = NewEdge();
                m_spStateMachine->AddEdge(pEdge, pNewNode, pCurrent);
            }

            return nullptr;
        }

        StateMachine::NodePtr ParseExprNoOr(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = pNode;

            while (true)
            {
                pCurrent = ParseExprNoGroup(pCurrent);

                if (pCurrent == nullptr)
                {
                    return nullptr;
                }

                Token token = LookAhead();

                if (token.type != TT_OpenParen)
                {
                    Backward(token);
                    return pCurrent;
                }

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

            return nullptr;
        }

        StateMachine::NodePtr ParseExprNoGroup(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = pNode;

            while (true)
            {
                pCurrent = ParseExprNoCollection(pCurrent);

                if (pCurrent == nullptr)
                {
                    return nullptr;
                }

                Token token = LookAhead();

                if (token.type != TT_OpenBracket)
                {
                    Backward(token);
                    return pCurrent;
                }

                pCurrent = ParseExprCollection(pCurrent);

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

            return nullptr;
        }

        StateMachine::NodePtr ParseExprCollection(StateMachine::NodePtr pNode)
        {
            bool bFirst = true;
            bool bOpposite = false;
            bool bInHyphen = false;
            Char chLastChar = 0;

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
                        if (bInHyphen || chLastChar == 0)
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
                            chLastChar = 0;
                        }
                        else
                        {
                            is.Union(Interval<Char>(token.ch, token.ch));
                            chLastChar = token.ch;
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

        StateMachine::NodePtr ParseExprNoCollection(StateMachine::NodePtr pNode)
        {
            StateMachine::NodePtr pCurrent = pNode;

            while (true)
            {
                Token token = LookAhead();

                if (token.type != TT_OrdinaryChar)
                {
                    Backward(token);
                    return pCurrent;
                }

                pCurrent = AddNormalNode(pCurrent, token.ch);

                if (pCurrent == nullptr)
                {
                    return nullptr;
                }
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
