#include <iostream>
#include <vector>
#include <list>
using namespace std;

#include "stack.h"
#include "queue.h"

using namespace wr;
int main()
{
  // stack<int, list<int>> st;
  // st.push(1);
  // st.push(2);
  // st.push(3);
  // st.push(4);
  // st.push(5);
  // st.push(6);

  // while (!st.empty())
  // {
  //   cout << st.top() << ' ';
  //   st.pop();
  // }
  // cout << endl;

  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);
  q.push(6);
  q.push(7);
  q.push(8);

  while (!q.empty())
  {
    cout << q.front() << ' ';
    q.pop();
  }
  cout << endl;

  return 0;
}