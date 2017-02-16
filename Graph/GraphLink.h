/*GraphLink.h
**2016.2.16
*/
#pragma once

#include<iostream>
#include<malloc.h>
using namespace std;

#define DEFAULT_VERTEX_SIZE 10
template<class Type> class GraphLink;
template<class Type>
class Edge
{
    friend class GraphLink<Type>;
public:
    Edge(int num=0):dest(num),link(NULL)
    {}
    ~Edge()
    {}
private:
    int dest;
    Edge *link;
};
template<class Type>
class Vertex
{
    friend class GraphLink<Type>;
public:
    Vertex():data(),adj(NULL)
    {}
    ~Vertex()
    {}
private:
    Type data;
    Edge<Type> *adj;
};
template<class Type>
class GraphLink
{
public:
    GraphLink(int sz = DEFAULT_VERTEX_SIZE)
    {
        maxVertices = sz > DEFAULT_VERTEX_SIZE ? sz : DEFAULT_VERTEX_SIZE;
        numEdges = numVertices = 0;
        NodeTable = new Vertex<Type>[maxVertices];
    }
    ~GraphLink()
    {
        delete []NodeTable;
    }
public:
    bool InsertVertex(const Type &v);               //插入顶点v
    bool InsertEdge(const Type &vertex1, const Type &vertex2);//插入vertex1-->vertex2边
    int NumberOfVertice()const;                     //获取顶点总数
    int NumberOfEdge()const;                        //获取边总数
    int GetFirstNeighbor(const Type &vertex)const;  //获取vertex的第一个邻接顶点
    int GetNextNeighbor(const Type &vertex1, const Type &vertex2)const;//获取vertex1的邻接顶点vertex2的下一个邻接顶点
    bool RemoveVertex(const Type &vertex);          //删除顶点vertex
    bool RemoveEdge(const Type &vertex1, const Type &vertex2);//删除vertex1和vertex2构成的边
public:
    void ShowGraph()const
    {
        for (int i = 0; i < numVertices; ++i)
        {
            cout<<NodeTable[i].data<<"-->";
            Edge<Type> *e = NodeTable[i].adj;
            while(e != NULL)
            {
                cout<<e->dest<<"-->";
                e = e->link;
            }
            cout<<"Nul"<<endl;
        }
    }
private:
    int GetPosVertex(const Type v)const
    {
        for (int i = 0; i < numVertices; ++i)
        {
            if(NodeTable[i].data == v)
                return i;
        }
        return -1;
    }

    Vertex<Type> *NodeTable;//顶点表
    int maxVertices;
    int numVertices;
    int numEdges;
};
template<class Type>
bool GraphLink<Type>::InsertVertex(const Type &v)
{
    if(numVertices > maxVertices)
        return false;
    NodeTable[numVertices++].data = v;
    return true;
}
template<class Type>
bool GraphLink<Type>::InsertEdge(const Type &vertex1, const Type &vertex2)
{
    int v1 = GetPosVertex(vertex1);
    int v2 = GetPosVertex(vertex2);
    if(v1 == -1 || v2 == -1)
        return false;
    //采用单链表的头插方式
    //v1-->v2
    Edge<Type> *e = new Edge<Type>(v2);
    e->link = NodeTable[v1].adj;
    NodeTable[v1].adj = e;
    //v2-->v1
    e = new Edge<Type>(v1);
    e->link = NodeTable[v2].adj;
    NodeTable[v2].adj = e;
    numEdges++;
}
template<class Type>
int GraphLink<Type>::NumberOfVertice()const
{return numVertices;}
template<class Type>
int GraphLink<Type>::NumberOfEdge()const
{return numEdges;}
template<class Type>
int GraphLink<Type>::GetFirstNeighbor(const Type &vertex)const
{
    int v = GetPosVertex(vertex);
    if(v == -1)
        return -1;
    if(NodeTable[v].adj != NULL)
        return NodeTable[v].adj->dest;
    return -1;
}
template<class Type>
int GraphLink<Type>::GetNextNeighbor(const Type &vertex1, const Type &vertex2)const
{
    int v1 = GetPosVertex(vertex1);
    int v2 = GetPosVertex(vertex2);
    if(v1 == -1 || v2 == -1)
        return -1;
    Edge<Type> *p = NodeTable[v1].adj;
    while(p != NULL && p->dest != v2)
        p = p->link;
    if(NULL == p)
        return -1;
    if(p->link != NULL)
        return p->link->dest;
    return -1;
}
template<class Type>
bool GraphLink<Type>::RemoveEdge(const Type &vertex1, const Type &vertex2)
{
    int v1 = GetPosVertex(vertex1);
    int v2 = GetPosVertex(vertex2);
    if(v1 == -1 || v2 == -1)
        return false;
    //删除v1-->v2
    Edge<Type> *p = NodeTable[v1].adj;
    Edge<Type> *q = NULL;
    while(p != NULL && p->dest != v2)
    {
        q = p;
        p = p->link;
    }
    if(NULL == p)
        return false;
    if(q == NULL)//说明删除的是头结点
        NodeTable[v1].adj = p->link;
    else
        q->link = p->link;
    free(p);
    p == NULL;
    //删除v2-->v1
    p = NodeTable[v2].adj;
    q = NULL;
    while(p != NULL && p->dest != v1)
    {
        q = p;
        p = p->link;
    }
    if(NULL == p)
        return false;
    if(q == NULL)//说明删除的是头结点
        NodeTable[v2].adj = p->link;
    else
        q->link = p->link;
    free(p);
    p == NULL;
    numEdges--;
}
template<class Type>
bool GraphLink<Type>::RemoveVertex(const Type &vertex)
{
/*思路：
**  1.剔除顶点vertex边链表中所包含顶点中的关于vertex的结点(可以借用RemoveEdage())
**  2.最后一行覆盖所删除行
        （1）顶点覆盖顶点
                  1）p保存最后一行的单链表，删除行的顶点指向最后一行的边链表，tmp保存numVertices-1
                  2）覆盖顶点
                  3）与最后一行所关联的结点，将他们所包含的最后一个结点的下标更改成所删除的下标
        (2)边链表覆盖边链表（指向tmp）
**  3.减少顶点数
*/
    int v = GetPosVertex(vertex);
    if(v == -1)
        return false;
    //1.
    Edge<Type> *p = NodeTable[v].adj;
    while(p != NULL)
    {
        RemoveEdge(vertex, NodeTable[p->dest].data);
        p = NodeTable[v].adj;
    }
    //2.
        //1)
    p = NodeTable[numVertices-1].adj;
    NodeTable[v].adj = NodeTable[numVertices-1].adj;
    int tmp = numVertices-1;
        //2)
    NodeTable[v].data = NodeTable[numVertices-1].data;
        //3)
    Edge<Type> *q = NULL;
    while(p != NULL)
    {
        q = NodeTable[p->dest].adj;
        while(q != NULL && q->dest != tmp)
            q = q->link;
        q->dest = v;
        p = p->link;
    }
    //3.
    numVertices--;
}
