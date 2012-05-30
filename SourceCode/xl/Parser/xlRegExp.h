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
        class Node
        {
        public:
            Node() : m_nIdentify(++ms_nCounter)
            {

            }

            ~Node()
            {

            }

        private:
            int m_nIdentify;

        private:
            static int ms_nCounter;
        };

        class Edge
        {
        public:
            Edge(Char ch) : m_chBegin(ch), m_chEnd(ch)
            {

            }

            Edge(Char chBegin, Char chEnd) : m_chBegin(chBegin), m_chEnd(chEnd)
            {

            }

            ~Edge()
            {

            }

        public:
            bool Match(Char ch)
            {
                return ch >= m_chBegin && ch <= m_chEnd;
            }

        private:
            Char m_chBegin;
            Char m_chEnd;
        };

    private:
        typedef Graph<Node, Edge> StateMachine;
        typedef SharedPtr<StateMachine> StateMachinePtr;

    private:
        StateMachinePtr       m_spStateMachine;
		StateMachine::NodePtr m_spBegin;
		StateMachine::NodePtr m_spEnd;
        String m_strRegExp;
        int m_nCurrentPosition;

    public:
        bool Parse(const String &s)
        {
            m_strRegExp = s;
            m_nCurrentPosition = 0;
            m_spStateMachine = new StateMachine;
            m_spBegin = m_spStateMachine->AddNode(NewNode());
			m_spEnd = MatchExpression(m_spBegin);
        
            if (m_spEnd == nullptr)
            {
                return false;
            }

            return true;
        }

		bool Test(const String &s)
		{
			StateMachine::NodePtr spCurrent = m_spBegin;

			for (int i = 0; i < s.Length(); ++i)
			{
				bool bFound = false;

				for (auto it = spCurrent->arrNext.Begin(); it != spCurrent->arrNext.End(); ++it)
				{
					StateMachine::EdgePtr &spEdge = *it;

					if (spEdge->tValue.Match(s[i]))
					{
						spCurrent = spEdge->pNext;
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					return false;
				}
			}

			if (spCurrent != m_spEnd)
			{
				return false;
			}

			return true;
		}

	private:
		enum TokenType
		{
			TT_EOF,
			TT_GROUP_BEGIN,
			TT_GROUP_END,
			TT_OR,
			TT_COLLECTION_BEGIN,
			TT_COLLECTION_END,
			TT_COLLECTION_REVERSE,
			TT_REPEAT_BEGIN,
			TT_REPEAT_END,
			TT_REPEAT_SEPARATOR,
			TT_REPEAT_ZERO_PLUS,
			TT_REPEAT_ONE_PLUS,
			TT_REPEAT_ZERO_ONE,
			TT_CHAR
		};

		struct Token 
		{
			Char ch;
			TokenType type;
			bool escaped;

			Token(Char ch = L'\0', TokenType type = TT_CHAR, bool escaped = false)
				: ch(ch), type(type), escaped(escaped)
			{

			}
		};

    private:
        Token LookAhead()
        {
			Char ch = m_strRegExp[m_nCurrentPosition++];
			TokenType type = TT_CHAR;

			if (ch == L'\\')
			{
				Char chNext = m_strRegExp[m_nCurrentPosition];

				if (chNext != TT_EOF)
				{
					++m_nCurrentPosition;
					return Token(chNext, TT_CHAR, true);
				}
			}

			switch (ch)
			{
			case L'\0':
				type = TT_EOF;
				break;
			case L'(':
				type = TT_GROUP_BEGIN;
				break;
			case L')':
				type = TT_GROUP_END;
				break;
			case L'|':
				type = TT_OR;
				break;
			case L'[':
				type = TT_COLLECTION_BEGIN;
				break;
			case L']':
				type = TT_COLLECTION_END;
				break;
			case L'^':
				type = TT_COLLECTION_REVERSE;
				break;
			case L'{':
				type = TT_REPEAT_BEGIN;
				break;
			case L'}':
				type = TT_REPEAT_END;
				break;
			case L',':
				type = TT_REPEAT_SEPARATOR;
				break;
			case L'*':
				type = TT_REPEAT_ZERO_PLUS;
				break;
			case L'+':
				type = TT_REPEAT_ONE_PLUS;
				break;
			case L'?':
				type = TT_REPEAT_ZERO_ONE;
				break;
			default:
				break;
			}

			return Token(ch, type);
        }

        void Backward(const Token &token)
        {
            --m_nCurrentPosition;

			if (token.escaped)
			{
				--m_nCurrentPosition;
			}
        }

        StateMachine::NodePtr MatchExpression(StateMachine::NodePtr spNode)
        {
            StateMachine::NodePtr spCurrent = spNode;
            bool bContinue = true;

            while (bContinue)
            {
                Token token = LookAhead();

                if (token.type == TT_EOF)
                {
                    return spCurrent;
                }

                switch (token.type)
                {
                case TT_GROUP_BEGIN:
                    {

					}
                    break;
                case TT_GROUP_END:
                    {

					}
                    break;
                case TT_OR:
                    {

                    }
                    break;
                case TT_COLLECTION_BEGIN:
                    {
						spCurrent = MatchCollection(spCurrent);

						if (spCurrent == nullptr)
                        {
                            return nullptr;
                        }
                    }
                    break;
                case TT_COLLECTION_END:
                    {
						return nullptr;
                    }
                    break;
				case TT_COLLECTION_REVERSE:
					{
						return nullptr;
					}
					break;
                case TT_REPEAT_BEGIN:
                    {

                    }
                    break;
                case TT_REPEAT_END:
                    {

					}
                    break;
                case TT_REPEAT_ZERO_PLUS:
                    {

                    }
                    break;
                case TT_REPEAT_ONE_PLUS:
                    {

                    }
                    break;
                case TT_REPEAT_ZERO_ONE:
                    {

                    }
                    break;
                default:
                    {
                        spCurrent = AddNormalNode(spCurrent, token.ch);
                    }
                    break;
                }
            }

            return spCurrent;
        }

        StateMachine::NodePtr MatchCollection(StateMachine::NodePtr spNode)
        {
			bool bReverse = false;

			Token token = LookAhead();

			if (token.type == TT_COLLECTION_REVERSE)
			{
				bReverse = true;
			}
			else
			{
				Backward(token);
			}

			Set<Char> setChar;

			while (true)
			{
				token = LookAhead();

				if (token.type == TT_COLLECTION_END)
				{
					break;
				}

				if (token.type != TT_CHAR)
				{
					return nullptr;
				}

				setChar.Insert(token.ch);
			}

			if (setChar.Empty())
			{
				return spNode;
			}

			StateMachine::NodePtr spNext = NewNode();

			if (bReverse)
			{
				Char chCurrent = (Char)0;

				for (auto it = setChar.Begin(); it != setChar.End(); ++it)
				{
					if (*it == chCurrent)
					{
						++chCurrent;
						continue;
					}

					StateMachine::EdgePtr spEdge = NewEdge(chCurrent, *it - 1);
					m_spStateMachine->AddEdge(spEdge, spNode, spNext);

					chCurrent = *it + 1;
				}

				if (chCurrent != 0 || setChar.Empty())
				{
					StateMachine::EdgePtr spEdge = NewEdge(chCurrent, (Char)-1);
					m_spStateMachine->AddEdge(spEdge, spNode, spNext);
				}
			}
			else
			{
				for (auto it = setChar.Begin(); it != setChar.End(); ++it)
				{
					StateMachine::EdgePtr spEdge = NewEdge(*it);
					m_spStateMachine->AddEdge(spEdge, spNode, spNext);
				}
			}

			m_spStateMachine->AddNode(spNext);

			return spNext;
        }

		StateMachine::NodePtr MatchRepeatZeroPlus(StateMachine::NodePtr spNode)
		{
			return nullptr;
		}

		StateMachine::NodePtr MatchRepeatOnePlus(StateMachine::NodePtr spNode)
		{
			return nullptr;
		}

		StateMachine::NodePtr MatchRepeatZeroOne(StateMachine::NodePtr spNode)
		{
			return nullptr;
		}
    
    private:
        StateMachine::NodePtr AddNormalNode(StateMachine::NodePtr spNodeFrom, Char chEdgeChar)
        {
            StateMachine::EdgePtr spEdge = NewEdge(chEdgeChar);
            StateMachine::NodePtr spNode = NewNode();

            m_spStateMachine->AddNode(spNode);
            m_spStateMachine->AddEdge(spEdge, spNodeFrom, spNode);

            return spNode;
        }

    private:
        StateMachine::NodePtr NewNode()
        {
            return new StateMachine::NodeType();
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
