/*Test.cpp
**2016.2.16
*/
#include"config.h"
#ifdef LINK
#include"GraphLink.h"
int main()
{
    GraphLink<char> gl;
    gl.ShowGraph();
    gl.InsertVertex('A');
    gl.InsertVertex('B');
    gl.InsertVertex('C');
    gl.InsertVertex('D');
    gl.ShowGraph();
    gl.InsertEdge('A', 'B');
    gl.InsertEdge('A', 'C');
    gl.InsertEdge('B', 'D');
    gl.ShowGraph();
    cout<<gl.GetFirstNeighbor('A')<<endl;
    cout<<gl.GetNextNeighbor('A', 'B')<<endl;
    gl.RemoveVertex('A');
    gl.RemoveVertex('B');
    gl.RemoveVertex('C');
    gl.RemoveVertex('D');
    gl.ShowGraph();
}
#endif
#ifdef MTX
#include"GraphMtx.h"
int main()
{
    GraphMtx<char,int> gm('#',10);
    gm.GraphShow();
    gm.InsertVertex('A');
    gm.InsertVertex('B');
    gm.InsertVertex('C');
    gm.GraphShow();
    gm.InsertEdge('A', 'B');
    gm.InsertEdge('A', 'C');
    gm.InsertEdge('C', 'B');
    gm.GraphShow();
    cout<<gm.GetFirstNeighbor('A')<<endl;
    cout<<gm.GetNextNeighbor('B', 'A')<<endl;
    gm.RemoveEdge('A', 'B');
    gm.GraphShow();
    gm.RemoveVertex('A');
    gm.GraphShow();
}
#endif
