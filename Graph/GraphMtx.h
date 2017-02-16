//GraphMtx.h
//邻接矩阵方式
//2017-2-15 12:00
#pragma once

#include<iostream>
#include<malloc.h>
using namespace std;

#define DEFAULT_VERLIST_SIZE 10

template<class T, class E>
class GraphMtx
{
public:
    GraphMtx(T x,int sz=DEFAULT_VERLIST_SIZE)
    {
        maxVertices = sz > DEFAULT_VERLIST_SIZE ? sz : DEFAULT_VERLIST_SIZE;
        VerticesList = new T[maxVertices];
        for(int i=0; i<maxVertices; ++i)     //顶点置为#
        {
            VerticesList[i] = x;
        }
        Edge =new E*[maxVertices];
        for(int i=0; i<maxVertices; ++i)
        {
            Edge[i] = new E[maxVertices];
            for(int j=0; j<maxVertices; ++j)//边的条数置为0
            {
                Edge[i][j] = 0;
            }
        }
        numVertices = numEdges = 0;
    }
    ~GraphMtx()
    {
        delete VerticesList;
        VerticesList = NULL;
        for(int i=0; i<maxVertices; ++i)
        {
            delete Edge[i];
            Edge[i] = NULL;
        }
        delete Edge;
        Edge = NULL;
        numVertices = numEdges = 0;
    }
public:
    bool InsertVertex(const T vertex);      //插入顶点vertex
    bool InsertEdge(const T vertex1, const T vertex2);//插入一条边(vertex1,vertex2)
    int NumberOfVertex()const;              //获取顶点总数
    int NumberOfEdge()const;                //获取边数
    int GetFirstNeighbor(const T vertex)const;//获取顶点vertex的第一个邻接顶点的位置
    int GetNextNeighbor(const T vertex1, const T vertex2)const;//获取顶点vertex1的某邻接顶点vertex2的下一个邻接顶点的位置
    bool RemoveVertex(const T vertex);      //删除顶点vertex
    bool RemoveEdge(const T vertex1, const T vertex2);//删除边(vertex1, vertex2)
public:
    int GetPosVertex(T vertex)const
    {
        for(int i=0; i<numVertices; ++i)
        {
            if(VerticesList[i] == vertex)
                return i;
        }
        return -1;
    }
    void GraphShow()
    {
        cout<<"  ";
        for(int i=0; i<numVertices; ++i)
        {
            cout<<VerticesList[i]<<' ';
        }
        cout<<endl;
        for(int i=0; i<numVertices; ++i)
        {
            cout<<VerticesList[i]<<' ';
            for(int j=0; j<numVertices; ++j)
                cout<<Edge[i][j]<<' ';
            cout<<endl;
        }
    }
private:
    T *VerticesList;//顶点表向量
    E **Edge;       //边的存储空间
    int maxVertices;//顶点容量
    int numVertices;//当前顶点个数
    int numEdges;   //当前边数
};
template<class T, class E>
bool GraphMtx<T,E>::InsertVertex(const T vertex)
{
    if(numVertices >= maxVertices)
        return false;
    VerticesList[numVertices++] = vertex;
    return true;
}
template<class T, class E>
bool GraphMtx<T,E>::InsertEdge(const T vertex1, const T vertex2)
{
    int v1 = GetPosVertex(vertex1);
    int v2 = GetPosVertex(vertex2);
    if(v1 == -1 || v2 == -1)
        return false;
    Edge[v1][v2] = Edge[v2][v1] = 1;
    numEdges++;
}
template<class T, class E>
int GraphMtx<T,E>::NumberOfVertex()const
{return numVertices;}
template<class T, class E>
int GraphMtx<T,E>::NumberOfEdge()const
{return numEdges;}
template<class T, class E>
int GraphMtx<T,E>::GetFirstNeighbor(const T vertex)const
{
    int v = GetPosVertex(vertex);
    if(v == -1)
        return -1;
    for (int i = 0; i < numVertices; ++i)
    {
        if(Edge[v][i] == 1)
            return i;
    }
    return -1;
}
template<class T, class E>
int GraphMtx<T,E>::GetNextNeighbor(const T vertex1, const T vertex2)const
{
    int v1 = GetPosVertex(vertex1);
    int v2 = GetPosVertex(vertex2);
    if(v1 == -1 || v2 == -1)
        return -1;
    for (int i = v2+1; i < numVertices; ++i)
    {
        if(Edge[v1][i] == 1)
            return i;
    }
    return -1;
}
template<class T, class E>
bool GraphMtx<T,E>::RemoveVertex(const T vertex)
{
    //消耗空间的做法：用后一行/列覆盖要删除的行/列，后面的往前移动;
    //时间复杂度低的做法：用最后一行/列覆盖要删除的顶点行/列,会改变顶点的顺序
    //选用后者做法
    int xnumedge = 0;
    int v = GetPosVertex(vertex);
    if(v == -1)
        return false;
    for (int i = v; i < numVertices; i++)
    {
        if(Edge[v][i] == 1)
            xnumedge++;
    }
    //顶点覆盖
    VerticesList[v] = VerticesList[numVertices-1];
    //行覆盖
    for (int i = v; i < numVertices; i++)
        Edge[v][i] = Edge[numVertices-1][i];
    //列覆盖
    for (int i = v; i < numVertices; i++)
        Edge[i][v] = Edge[i][numVertices-1];
    //顶点减少，边减少
    numVertices--;
    numEdges -= xnumedge;
}
template<class T, class E>
bool GraphMtx<T,E>::RemoveEdge(const T vertex1, const T vertex2)
{
    int v1 = GetPosVertex(vertex1);
    int v2 = GetPosVertex(vertex2);
    if(v1 == -1 || v2 == -1)
        return false;
    if(Edge[v1][v2] == 0)
        return false;
    Edge[v1][v2] = Edge[v2][v1] = 0;
    numEdges--;
}
