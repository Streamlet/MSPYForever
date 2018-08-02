//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlGraph.h
//    Author:      Streamlet
//    Create Time: 2011-10-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLGRAPH_H_B9B90B34_ED59_4649_9500_6CA42EDE704C_INCLUDED__
#define __XLGRAPH_H_B9B90B34_ED59_4649_9500_6CA42EDE704C_INCLUDED__


#include "../../xlDef.h"
#include "xlArray.h"
#include "xlMap.h"
#include "xlSet.h"

namespace xl
{
    template <typename NodeData, typename EdgeData>
    struct GraphNode;

    template <typename EdgeData, typename NodeData>
    struct GraphEdge;

    template <typename NodeData, typename EdgeData>
    struct GraphNode
    {
        typedef GraphEdge<EdgeData, NodeData> EdgeType;

        NodeData tValue;

        Array<EdgeType *> arrPrevious;
        Array<EdgeType *> arrNext;

        GraphNode()
        {

        }

        GraphNode(const NodeData &tValue) : tValue(tValue)
        {

        }

        GraphNode(const GraphNode &that)
        {
            *this = that;
        }

        GraphNode &operator = (const NodeData &that)
        {
            if (this == &that)
            {
                return *this;
            }

            arrPrevious.Clear();
            arrNext.Clear();
            this->tValue = that.tValue;

            return *this;
        }

        bool operator == (const GraphNode &that)
        {
            if (this == &that)
            {
                return true;
            }

            return this->tValue == that.tValue;
        }

        bool operator != (const GraphNode &that)
        {
            if (this == &that)
            {
                return false;
            }

            return this->tValue != that.tValue;
        }

        bool operator < (const GraphNode &that)
        {
            if (this == &that)
            {
                return false;
            }

            return this->tValue < that.tValue;
        }

        bool operator > (const GraphNode &that)
        {
            if (this == &that)
            {
                return false;
            }

            return this->tValue > that.tValue;
        }

        bool operator <= (const GraphNode &that)
        {
            if (this == &that)
            {
                return true;
            }

            return this->tValue <= that.tValue;
        }

        bool operator >= (const GraphNode &that)
        {
            if (this == &that)
            {
                return true;
            }

            return this->tValue >= that.tValue;
        }
    };

    template <typename EdgeData, typename NodeData>
    struct GraphEdge
    {
        typedef GraphNode<NodeData, EdgeData> NodeType;

        EdgeData tValue;

        NodeType *pPrevious;
        NodeType *pNext;

        GraphEdge() : pPrevious(nullptr), pNext(nullptr)
        {

        }

        GraphEdge(const EdgeData &tValue, NodeType *pPrevious = nullptr, NodeType *pNext = nullptr) :
            tValue(tValue), pPrevious(pPrevious), pNext(pNext)
        {

        }

        GraphEdge(const GraphEdge &that) : pPrevious(nullptr), pNext(nullptr)
        {
            *this = that;
        }

        GraphEdge &operator = (const GraphEdge &that)
        {
            if (this == &that)
            {
                return *this;
            }

            this->pPrevious = nullptr;
            this->pNext = nullptr;
            this->tValue = that.tValue;

            return *this;
        }

        bool operator == (const GraphEdge &that)
        {
            if (this == &that)
            {
                return true;
            }

            return this->tValue == that.tValue;
        }

        bool operator != (const GraphEdge &that)
        {
            if (this == &that)
            {
                return false;
            }

            return this->tValue != that.tValue;
        }

        bool operator < (const GraphEdge &that)
        {
            if (this == &that)
            {
                return false;
            }

            return this->tValue < that.tValue;
        }

        bool operator > (const GraphEdge &that)
        {
            if (this == &that)
            {
                return false;
            }

            return this->tValue > that.tValue;
        }

        bool operator <= (const GraphEdge &that)
        {
            if (this == &that)
            {
                return true;
            }

            return this->tValue <= that.tValue;
        }

        bool operator >= (const GraphEdge &that)
        {
            if (this == &that)
            {
                return true;
            }

            return this->tValue >= that.tValue;
        }
    };

    template <typename NodeData, typename EdgeData>
    class Graph
    {
    public:
        Graph()
        {

        }

        Graph(const Graph &that)
        {
            *this = that;
        }

        ~Graph()
        {
            Release();
        }

    public:
        Graph &operator = (const Graph &that)
        {
            if (this == &that)
            {
                return *this;
            }

            Release();

            Map<NodePtr, NodePtr> mapNodes;

            for (auto it = that.m_setNodes.Begin(); it != that.m_setNodes.End(); ++it)
            {
                NodePtr pOldNode = *it;
                NodePtr pNewNode = new NodeType(pOldNode->tValue);
                pNewNode->arrPrevious = pOldNode->arrPrevious;
                pNewNode->arrNext = pOldNode->arrNext;
                this->m_setNodes.Insert(pNewNode);
                mapNodes.Insert(pNewNode, pOldNode);
            }

            Map<EdgePtr, EdgePtr> mapEdges;

            for (auto it = that.m_setEdges.Begin(); it != that.m_setEdges.End(); ++it)
            {
                EdgePtr pOldEdge = *it;
                EdgePtr pNewEdge = new EdgeType(pOldNode->tValue);
                pNewEdge->pPrevious = pOldEdge->pPrevious;
                pNewEdge->pNext = pOldEdge->pNext;
                this->m_setEdges.Insert(pNewNode);
                mapEdges.Insert(pNewNode, pOldEdge);
            }

            for (auto it = this->m_setNodes.Begin(); it != this->m_setNodes.End(); ++it)
            {
                NodePtr pNode = *it;

                for (auto itPrevious = pNode->arrPrevious.Begin(); itPrevious != pNode->arrPrevious.End(); ++itPrevious)
                {
                    *itPrevious = mapEdges[*itPrevious];
                }

                for (auto itNext = pNode->arrNext.Begin(); itNext != pNode->arrNext.End(); ++itNext)
                {
                    *itNext = mapEdges[*itNext];
                }
            }

            for (auto it = this->m_setEdges.Begin(); it != this->m_setEdges.End(); ++it)
            {
                EdgePtr pEdge = *it;

                pEdge->pPrevious = mapNodes[pEdge->pPrevious];
                pEdge->pNext = mapNodes[pEdge->pNext];
            }

            return *this;
        }

    public:
        typedef GraphNode<NodeData, EdgeData> NodeType;
        typedef GraphEdge<EdgeData, NodeData> EdgeType;
        typedef NodeType *NodePtr;
        typedef EdgeType *EdgePtr;
        typedef Set<NodePtr> NodeSet;
        typedef Set<EdgePtr> EdgeSet;

    public:
        NodePtr AddNode(NodePtr pNode)
        {
            if (pNode == nullptr)
            {
                return nullptr;
            }

            if (m_setNodes.Find(pNode) != m_setNodes.End())
            {
                return false;
            }

            m_setNodes.Insert(pNode);

            return pNode;
        }

        EdgePtr AddEdge(EdgePtr pEdge, NodePtr pFromNode = nullptr, NodePtr pToNode = nullptr)
        {
            if (pEdge == nullptr)
            {
                return nullptr;
            }

            if (m_setEdges.Find(pEdge) != m_setEdges.End())
            {
                return nullptr;
            }

            pEdge->pPrevious = pFromNode;
            pEdge->pNext = pToNode;

            if (pFromNode != nullptr)
            {
                pFromNode->arrNext.PushBack(pEdge);
            }

            if (pToNode != nullptr)
            {
                pToNode->arrPrevious.PushBack(pEdge);
            }

            m_setEdges.Insert(pEdge);

            return pEdge;
        }

        void DeleteNode(NodePtr pNode)
        {
            auto itNode = m_setNodes.Find(pNode);

            if (itNode == m_setNodes.End())
            {
                return;
            }

            for (auto itEdge = pNode->arrPrevious.Begin(); itEdge != pNode->arrPrevious.End(); ++itEdge)
            {
                EdgePtr pEdge = *itEdge;

                if (pEdge->pPrevious != nullptr)
                {
                    NodePtr pNode = pEdge->pPrevious;

                    for (auto it = pNode->arrNext.Begin(); it != pNode->arrNext.End(); ++it)
                    {
                        if (*it == pEdge)
                        {
                            pNode->arrNext.Delete(it);
                            break;
                        }
                    }
                }

                delete pEdge;
            }

            for (auto itEdge = pNode->arrNext.Begin(); itEdge != pNode->arrNext.End(); ++itEdge)
            {
                EdgePtr pEdge = *itEdge;

                if (pEdge->pNext != nullptr)
                {
                    NodePtr pNode = pEdge->pNext;

                    for (auto it = pNode->arrPrevious.Begin(); it != pNode->arrPrevious.End(); ++it)
                    {
                        if (*it == pEdge)
                        {
                            pNode->arrPrevious.Delete(it);
                            break;
                        }
                    }
                }

                delete pEdge;
            }

            m_setNodes.Delete(itNode);
            delete pNode;
        }

        void DeleteEdge(EdgePtr pEdge)
        {
            auto itEdge = m_setEdges.Find(pEdge);

            if (itEdge == m_setEdges.End())
            {
                return;
            }

            if (pEdge->pPrevious != nullptr)
            {
                NodePtr pNode = pEdge->pPrevious;

                for (auto it = pNode->arrNext.Begin(); it != pNode->arrNext.End(); ++it)
                {
                    if (*it == pEdge)
                    {
                        pNode->arrNext.Delete(it);
                        break;
                    }
                }
            }

            if (pEdge->pNext != nullptr)
            {
                NodePtr pNode = pEdge->pNext;

                for (auto it = pNode->arrPrevious.Begin(); it != pNode->arrPrevious.End(); ++it)
                {
                    if (*it == pEdge)
                    {
                        pNode->arrPrevious.Delete(it);
                        break;
                    }
                }
            }

            m_setEdges.Delete(itEdge);
            delete pEdge;
        }

        const NodeSet &GetNodes()
        {
            return m_setNodes;
        }

        const EdgeSet &GetEdges()
        {
            return m_setEdges;
        }

    private:
        void Release()
        {
            for (auto it = m_setNodes.Begin(); it != m_setNodes.End(); ++it)
            {
                delete *it;
            }

            for (auto it = m_setEdges.Begin(); it != m_setEdges.End(); ++it)
            {
                delete *it;
            }
        }

    private:
        NodeSet m_setNodes;
        EdgeSet m_setEdges;
    };


} // namespace xl

#endif // #ifndef __XLGRAPH_H_B9B90B34_ED59_4649_9500_6CA42EDE704C_INCLUDED__
