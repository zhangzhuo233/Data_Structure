#include"SeqStack.h"
int main()
{
    SeqStack<char> st(0,20);
    st.Push('h');
    st.Push('e');
    st.Push('l');
    st.GetTop();
    cout<<endl;
    st.Show();
    cout<<endl;
    st.Pop();
    st.Pop();
    st.Pop();
    st.Pop();
    st.Show();
    return 0;
}
