#pragma once
#include <vector>
#include <map>

namespace UFS
{
  // 如果为负数，说明该位置是根，绝对值为该树的结点个数
  // 如果为正数，为其双亲结点的下标
  class UnionFindSet
  {
  public:
    UnionFindSet() = default;
    UnionFindSet(size_t n)
    {
      _ufs.resize(n, -1); // 初始化全为-1
    }

    // 将x1与x2，并到一个集合中
    void Union(int x1, int x2)
    {
      // 找到x1和x2的根
      int root1 = FindRoot(x1);
      int root2 = FindRoot(x2);

      if (root1 == root2)
        return;

      // 合并到一个集合中
      _ufs[root2] += _ufs[root1];
      _ufs[root1] = root2;
    }

    // 找到x所在树的根的下标
    int FindRoot(int x)
    {
      int parent = x;
      while (_ufs[parent] >= 0)
      {
        parent = _ufs[parent];
      }

      return parent;
    }

    bool Inset(int x1, int x2)
    {
      return FindRoot(x1) == FindRoot(x2);
    }

    int SetSize()
    {
      size_t size = 0;
      for (size_t i = 0; i < _ufs.size(); ++i)
      {
        if (_ufs[i] < 0)
          ++size;
      }

      return size;
    }

  private:
    vector<int> _ufs;
  };

  void TestUnionFindSet()
  {
    UnionFindSet ufs(10);
    ufs.Union(8, 9);
    ufs.Union(7, 8);
    ufs.Union(6, 7);
    ufs.Union(5, 6);
    ufs.Union(4, 5);

    cout << ufs.FindRoot(6) << endl;
    cout << ufs.FindRoot(9) << endl;
  }
}