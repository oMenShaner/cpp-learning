#include <iostream>
#include <vector>

using namespace std;

void Test1_vector()
{
  vector<int> first;
  vector<int> second(10, 4);
  vector<int> third(second.begin(), second.end());
  vector<int> forth(third);

  for (vector<int>::iterator it = second.begin(); it != second.end(); ++it)
  {
    cout << *it << ' ';
  }
  cout << endl;

  for (auto &e: third)
  {
    cout << e << ' ';
  }
  cout << endl;

  for (size_t i = 0; i < forth.size(); ++i)
  {
    cout << forth[i] << ' ';
  }
  cout << endl;
}

void Test2_vector() 
{
  vector<int> v;
  v.push_back(100);
  v.push_back(200);
  v.push_back(300);
  v.push_back(400);
  v.push_back(500);

  
}

int main()
{
  Test1_vector();

  return 0;
}
