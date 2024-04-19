#include <iostream>
using namespace std;

#include "stack.h"
#include "queue.h"

using namespace wr;

int main()
{
  // stack<int> st;
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

  // queue<int> q;
  // q.push(1);
  // q.push(2);
  // q.push(3);
  // q.push(4);
  // q.push(5);
  // q.push(6);

  // while (!q.empty())
  // {
  //   cout << q.front() << ' ';
  //   q.pop();
  // }
  // cout << endl;

  int arr[] = {5, 4, 6, 4, 8, 4, 9, 1};
  wr::priority_queue<int, vector<int>, wr::greater<int>> pq(arr, arr + sizeof(arr) / sizeof(int));

  while (!pq.empty())
  {
    cout << pq.top() << ' ';
    pq.pop();
  }
  cout << endl;

  return 0;
}