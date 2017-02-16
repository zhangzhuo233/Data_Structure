/*Test.cpp
**2016.2.16
*/
#include"GraphLink.h"
#include<vld.h>
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