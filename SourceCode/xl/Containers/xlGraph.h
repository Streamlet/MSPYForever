//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlGraph.h
//    Author:      Streamlet
//    Create Time: 2011-10-15
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLGRAPH_H_B9B90B34_ED59_4649_9500_6CA42EDE704C_INCLUDED__
#define __XLGRAPH_H_B9B90B34_ED59_4649_9500_6CA42EDE704C_INCLUDED__


#include <xl/xlDef.h>
#include <xl/Containers/xlArray.h>
#include <xl/Containers/xlSet.h>

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

        GraphNode(const T &tValue) : tValue(tValue)
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

        GraphEdge(const T &tValue, NodeType *pPrevious, NodeType *pNext = nullptr) :
        tValue(tValue), pPrevious(pPrevious), pNext(pNext)
        {

        }

        GraphEdge(const GraphEdge &that), pPrevious(nullptr), pNext(nullptr)
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

        }

        ~Graph()
        {

        }

    public:
        Graph &operator = (const Graph &that)
        {

        }

        bool operator == (const Graph &that)
        {

        }

        bool operator != (const Graph &that)
        {

        }

    private:
        typedef GraphNode<NodeData, EdgeData> NodeType;
        typedef GraphEdge<EdgeType, NodeType> EdgeType;
        typedef NodeType *NodePtr;
        typedef EdgeType *EdgePtr;

    private:
        Set<NodePtr> m_setNodes;
        Set<EdgePtr> m_setEdges;

    };


} // namespace xl

#endif // #ifndef __XLGRAPH_H_B9B90B34_ED59_4649_9500_6CA42EDE704C_INCLUDED__
