#pragma once
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <functional>
#include <string.h>

// 邻接矩阵
namespace Martix
{
  // V为结点数据类型, W为权值类型, 默认为无向图
  template <class V, class W, W MAX_W = INT32_MAX, bool Direction = false>
  class Graph
  {
    typedef Graph<V, W, MAX_W, Direction> Self;

  public:
    Graph() = default;
    Graph(const V *vertexs, size_t n)
    {
      // 遍历vertexs,将其内容放入顶点集合，同时记录对应下标
      _vertexs.resize(n);
      for (size_t i = 0; i < n; ++i)
      {
        _vertexs[i] = vertexs[i];
        _vIndexMap[_vertexs[i]] = i;
      }

      // 初始化边为MAX_W
      _martix.resize(n);
      for (auto &e : _martix)
      {
        e.resize(n, MAX_W);
      }
    }

    // 根据顶点得到对应下标
    size_t GetVertexIndex(const V &v)
    {
      auto ret = _vIndexMap.find(v);
      if (ret != _vIndexMap.end())
      {
        return ret->second;
      }
      else
      {
        throw invalid_argument("不存在的顶点");
        return -1;
      }
    }

    void _AddEdge(size_t srci, size_t dsti, const W &w)
    {
      if (srci < 0 || dsti < 0 || srci >= _vertexs.size() || dsti >= _vertexs.size() || srci == dsti || _martix[srci][dsti] != MAX_W)
      {
        throw invalid_argument("插入位置非法");
        return;
      }
      _martix[srci][dsti] = w;

      // 如果是无向图，则还需要对称插入
      if (Direction == false)
      {
        _martix[dsti][srci] = w;
      }
    }

    // 插入边 src --w--> dst
    void AddEdge(const V &src, const V &dst, const W &w)
    {
      // 得到起点和终点的下标
      size_t srci = GetVertexIndex(src);
      size_t dsti = GetVertexIndex(dst);

      // 将对应边插入到边集合矩阵
      _AddEdge(srci, dsti, w);
    }

    void _DelEdge(size_t srci, size_t dsti)
    {
      if (srci < 0 || dsti < 0 || srci >= _vertexs.size() || dsti >= _vertexs.size() || srci == dsti || _martix[srci][dsti] == MAX_W)
      {
        throw invalid_argument("删除位置非法");
        return;
      }

      _martix[srci][dsti] = MAX_W;

      // 如果是无向图，则还需要对称删除
      if (Direction == false)
      {
        _martix[dsti][srci] = MAX_W;
      }
    }

    // 删除边 src --> dst
    void DelEdge(const V &src, const V &dst)
    {
      // 得到起点和终点的下标
      size_t srci = GetVertexIndex(src);
      size_t dsti = GetVertexIndex(dst);

      // 删除对应边
      _DelEdge(srci, dsti);
    }

    // 打印
    void Print()
    {
      // 打印顶点对应下标
      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        cout << _vertexs[i] << "-" << "[" << _vIndexMap[_vertexs[i]] << "]" << endl;
      }

      cout << endl
           << endl;
      // 打印邻接矩阵
      cout << "  ";
      for (size_t i = 0; i < _vertexs.size(); ++i)
        cout << i << " ";
      cout << endl;

      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        cout << i << " ";
        for (size_t j = 0; j < _vertexs.size(); ++j)
        {
          if (_martix[i][j] != MAX_W)
            cout << _martix[i][j] << " ";
          else
            cout << "∞" << " ";
        }
        cout << endl;
      }
      cout << endl
           << endl;
    }

    void _DFS(size_t starti, vector<bool> &visited)
    {
      // 打印start结点
      if (visited[starti] == false)
      {
        cout << _vertexs[starti] << " ";
        visited[starti] = true;
      }

      // 依次遍历start邻接的顶点
      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        // 如果与start有边并且未被访问，dfs该顶点
        if (_martix[starti][i] != MAX_W && !visited[i])
        {
          _DFS(i, visited);
        }
      }
    }

    // DFS 深度优先遍历
    void DFS()
    {
      // 创建visited数组并初始化
      vector<bool> visited;
      visited.resize(_vertexs.size(), false);

      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        if (!visited[i])
          _DFS(i, visited);
      }

      cout << endl
           << endl;
    }

    void _BFS(size_t starti, vector<bool> &visited)
    {
      // 创建队列用于广度优先遍历
      queue<int> q;
      q.push(starti);
      visited[starti] = true;
      int level = 1;
      int levelSize = 1;

      while (!q.empty())
      {
        cout << level << ": ";
        while (levelSize--)
        {
          size_t cur = q.front();
          cout << _vertexs[q.front()] << " ";
          q.pop();

          // 遍历得到cur的所有邻接顶点
          for (size_t i = 0; i < _vertexs.size(); ++i)
          {
            if (_martix[cur][i] != MAX_W && !visited[i])
            {
              q.push(i);
              visited[i] = true;
            }
          }
        }

        levelSize = q.size();
        cout << endl;
        level++;
      }
    }

    // BFS 广度优先遍历
    void BFS()
    {
      // 创建visited数组并初始化
      vector<bool> visited;
      visited.resize(_vertexs.size(), false);

      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        if (!visited[i])
          _BFS(i, visited);
      }

      cout << endl
           << endl;
    }

    // 为了方便边进行比较，创建一个类
    struct Edge
    {
      size_t _srci;
      size_t _dsti;
      W _w;

      Edge(size_t srci, size_t dsti, const W &w)
          : _srci(srci), _dsti(dsti), _w(w)
      {
      }

      // 运算符重载大于号用于优先级队列内部的比较
      bool operator>(const Edge &e) const
      {
        return _w > e._w;
      }
    };

    // 克鲁斯卡尔算法
    // 1. 只能使用图中权值最小的边构造最小生成树
    // 2. 只能用恰好n-1条边来连接图中的n个结点
    // 3. 选用的n-1条边不能构成回路
    W Kruskal(Self &minTree)
    {
      // 对minTree进行初始化
      size_t n = _vertexs.size();

      minTree._vertexs = _vertexs;
      minTree._vIndexMap = _vIndexMap;
      minTree._martix.resize(n);

      for (size_t i = 0; i < n; ++i)
      {
        minTree._martix[i].resize(n, MAX_W);
      }

      // 创建小堆，将所有边排序
      priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
      for (size_t i = 0; i < n; ++i)
      {
        for (size_t j = 0; j < n; ++j)
        {
          if (i < j && _martix[i][j] != MAX_W)
          {
            minque.push(Edge(i, j, _martix[i][j]));
          }
        }
      }

      // 选n-1条边
      int size = 0;        // 记录当前选的边数
      W totalW = W();      // 记录当前选的边权值之和
      UnionFindSet ufs(n); // 使用并查集来判环

      // 循环取出优先级队列的top，判环，加入最小生成树
      while (!minque.empty())
      {
        Edge min = minque.top();
        minque.pop();

        if (!ufs.Inset(min._srci, min._dsti))
        {
          cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
          minTree._AddEdge(min._srci, min._dsti, min._w);
          ufs.Union(min._srci, min._dsti);
          size++;
          totalW += min._w;
        }
        else
        {
          cout << "构成环：";
          cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
        }
      }

      if (size == n - 1)
      {
        return totalW;
      }
      else
      {
        return W();
      }
    }

    // 普利姆算法
    // 有两个集合X和Y，每次从Y集合中寻找与X集合中结点路径最短且不构成环的结点
    // 虽然天然避环，但是为了方便查找最小边使用优先级队列，同时要判环
    W Prim(Self &minTree, const W &src)
    {
      // 初始化最小生成树
      size_t srci = GetVertexIndex(src);
      size_t n = _vertexs.size();
      minTree._vertexs = _vertexs;
      minTree._vIndexMap = _vIndexMap;
      minTree._martix.resize(n);

      for (size_t i = 0; i < n; ++i)
      {
        minTree._martix[i].resize(n, MAX_W);
      }

      // 将以src为起点的边集合生成优先级队列
      priority_queue<Edge, vector<Edge>, greater<Edge>> minque;

      for (size_t i = 0; i < n; ++i)
      {
        if (_martix[srci][i] != MAX_W)
        {
          minque.push(Edge(srci, i, _martix[srci][i]));
        }
      }

      // 初始化X和Y集合
      vector<bool> X(n, false);
      vector<bool> Y(n, true);
      X[srci] = true;
      Y[srci] = false;

      // 插入n-1条边
      size_t size = 0;
      W totalW = W();
      while (!minque.empty())
      {
        // 挑选X集合中到Y集合中最短边
        Edge min = minque.top();
        minque.pop();

        // 1.终点在X集合，必然构成环
        // 2.该边起点在X集合，终点在Y集合，必然不构成环
        if (X[min._dsti])
        {
          cout << "构成环：";
          cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
        }
        else
        {
          // 插入边，并且将终点插入集合
          minTree._AddEdge(min._srci, min._dsti, min._w);
          size++;
          totalW += min._w;
          X[min._dsti] = true;
          Y[min._dsti] = false;

          // 如果满足n-1条边，最小生成树已经生成
          if (size == n - 1)
            break;

          // 将新插入顶点所邻接的边也插入优先级队列中
          for (size_t i = 0; i < n; ++i)
          {
            // 如果该顶点不在X集合并且其邻接的边不为无穷大
            if (X[i] == false && _martix[min._dsti][i] != MAX_W)
            {
              minque.push(Edge(min._dsti, i, _martix[min._dsti][i]));
            }
          }
        }
      }
      if (size == n - 1)
      {
        return totalW;
      }
      else
      {
        return W();
      }
    }

    // 迪杰斯特拉算法
    // dist[i] 用于记录src到i顶点的最短路径长度
    // pPath[i] 用于记录最短路径下i的前驱顶点的下标，方便得到最短路径
    // 顶点个数为N，时间复杂度O(N^2)，空间复杂度O(N)
    // 每次从dist中取出最短的路径长度，将路径终点确认已更新，随后进行其余未更新结点的dist
    void Dijkstra(const W &src, vector<int> &dist, vector<int> &pPath)
    {
      // 得到src下标，初始化操作
      size_t srci = GetVertexIndex(src);
      size_t n = _vertexs.size();
      dist.resize(n, MAX_W); // 所有路径长度初始化为无穷大
      pPath.resize(n, -1);   // 默认-1

      // 创建一个数组用于记录src到该顶点的路径是否更新完毕
      // 将src插入S集合
      vector<bool> S(n, false);
      dist[srci] = 0;
      pPath[srci] = srci;

      // 将n个结点按照贪心原则插入S集合
      for (size_t i = 0; i < n; ++i)
      {
        // 找到dist中的最短路径 i->u
        int u = 0;
        W min = MAX_W;
        for (size_t j = 0; j < n; ++j)
        {
          // 如果j没有插入S集合并且i->j路径比min还短
          if (!S[j] && dist[j] < min)
          {
            u = j;         // 更新为i->u
            min = dist[j]; // 更新最短路径
          }
        }

        // 将u插入S集合，同时进行松弛操作，更新srci到剩余没有在S集合的路径长度(小于才更新)
        // srci->u + u->v = srci->v
        S[u] = true;
        for (size_t v = 0; v < n; ++v)
        {
          // v不在S集合并且u->v有路径并且
          if (!S[v] && _martix[u][v] != MAX_W && dist[u] + _martix[u][v] < dist[v])
          {
            dist[v] = dist[u] + _martix[u][v];
            pPath[v] = u;
          }
        }
      }
    }

    // 打印路径
    void PrintShortPath(const V &src, const vector<W> &dist, const vector<int> &pPath)
    {
      // 得到起点下标
      size_t srci = GetVertexIndex(src);
      size_t n = _vertexs.size();

      // 遍历pPath，打印每条路径
      for (size_t i = 0; i < n; ++i)
      {
        if (i != srci)
        {
          vector<int> path;
          size_t parenti = i;
          while (parenti != srci)
          {
            path.push_back(parenti);
            parenti = pPath[parenti];
          }
          // 将起点插入
          path.push_back(srci);
          reverse(path.begin(), path.end()); // 逆置

          // 打印路径
          for (auto index : path)
          {
            cout << _vertexs[index] << "->";
          }
          cout << "权值和：" << dist[i] << endl;
        }
      }
    }

  private:
    map<V, int> _vIndexMap;    // 记录顶点对应下标(直接映射)
    vector<V> _vertexs;        // 顶点集合
    vector<vector<W>> _martix; // 存储边集合的矩阵
  };

  void TestGraph()
  {
    Graph<char, int, INT32_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    g.Print();

    g.DelEdge('0', '1');
    g.DelEdge('2', '3');

    g.Print();
  }

  void TestGraphDBFS()
  {
    string a[] = {"张三", "李四", "王五", "赵六", "周七", "孙八"};
    Graph<string, int, true> g1(a, sizeof(a) / sizeof(string));
    g1.AddEdge("张三", "李四", 100);
    g1.AddEdge("张三", "王五", 200);
    g1.AddEdge("王五", "赵六", 30);
    g1.AddEdge("王五", "周七", 30);
    g1.AddEdge("赵六", "孙八", 60);

    g1.BFS();
    g1.DFS();
  }

  void TestGraphMinTree()
  {
    const char *str = "abcdefghi";
    Graph<char, int> g(str, strlen(str));
    g.AddEdge('a', 'b', 4);
    // g.AddEdge('a', 'h', 8);
    g.AddEdge('a', 'h', 9);
    g.AddEdge('b', 'c', 8);
    g.AddEdge('b', 'h', 11);
    g.AddEdge('c', 'i', 2);
    g.AddEdge('c', 'f', 4);
    g.AddEdge('c', 'd', 7);
    g.AddEdge('d', 'f', 14);
    g.AddEdge('d', 'e', 9);
    g.AddEdge('e', 'f', 10);
    g.AddEdge('f', 'g', 2);
    g.AddEdge('g', 'h', 1);
    g.AddEdge('g', 'i', 6);
    g.AddEdge('h', 'i', 7);

    Graph<char, int> kminTree;
    cout << "Kruskal:" << endl
         << g.Kruskal(kminTree) << endl;
    kminTree.Print();

    Graph<char, int> pminTree;
    cout << "Prim:" << endl
         << g.Prim(pminTree, 'a') << endl;
    pminTree.Print();
    cout << endl;

    for (size_t i = 0; i < strlen(str); ++i)
    {
      Graph<char, int> pminTree1;
      cout << "Prim:" << g.Prim(pminTree1, str[i]) << endl;
    }
  }

  void TestGraphDijkstra()
  {
    const char *str = "syztx";
    Graph<char, int, INT32_MAX, true> g(str, strlen(str));
    g.AddEdge('s', 't', 10);
    g.AddEdge('s', 'y', 5);
    g.AddEdge('y', 't', 3);
    g.AddEdge('y', 'x', 9);
    g.AddEdge('y', 'z', 2);
    g.AddEdge('z', 's', 7);
    g.AddEdge('z', 'x', 6);
    g.AddEdge('t', 'y', 2);
    g.AddEdge('t', 'x', 1);
    g.AddEdge('x', 'z', 4);

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('s', dist, parentPath);
    g.PrintShortPath('s', dist, parentPath);

    // 图中带有负权路径时，贪心策略则失效了。
    // 测试结果可以看到s->t->y之间的最短路径没更新出来
    /*const char* str = "sytx";
    Graph<char, int, INT_MAX, true> g(str, strlen(str));
    g.AddEdge('s', 't', 10);
    g.AddEdge('s', 'y', 5);
    g.AddEdge('t', 'y', -7);
    g.AddEdge('y', 'x', 3);
    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('s', dist, parentPath);
    g.PrintShortPath('s', dist, parentPath);*/

    // const char* str = "syztx";
    // Graph<char, int, INT_MAX, true> g(str, strlen(str));
    // g.AddEdge('s', 't', 6);
    // g.AddEdge('s', 'y', 7);
    // g.AddEdge('y', 'z', 9);
    // g.AddEdge('y', 'x', -3);
    // g.AddEdge('z', 's', 2);
    // g.AddEdge('z', 'x', 7);
    // g.AddEdge('t', 'x', 5);
    // g.AddEdge('t', 'y', 8);
    // g.AddEdge('t', 'z', -4);
    // g.AddEdge('x', 't', -2);
    // vector<int> dist;
    // vector<int> parentPath;
    // g.Dijkstra('s', dist, parentPath);
    // g.PrintShortPath('s', dist, parentPath);
  }
}

// 邻接表
namespace LinkTable
{
  // 邻接表结点结构
  template <class W>
  struct LinkEdge
  {
    int _srcIndex; // 指向该结点的结点下标
    int _dstIndex; // 该结点指向结点的下标
    W _w;          // 边权值
    LinkEdge<W> *_next;

    LinkEdge(const W &w)
        : _srcIndex(-1), _dstIndex(-1), _w(w), _next(nullptr)
    {
    }
  };

  // 邻接表存储的图结构
  template <class V, class W, bool Direction = false>
  class Graph
  {
    typedef LinkEdge<W> Edge;

  public:
    Graph() = default;
    Graph(const V *vertexs, size_t n)
    {
      // 将顶点存放到集合中，同时得到对应映射下标
      _vertexs.resize(n);
      for (size_t i = 0; i < n; ++i)
      {
        _vertexs[i] = vertexs[i];
        _vIndexMap[_vertexs[i]] = i;
      }

      // 初始化邻接表为空
      _linkTable.resize(n, nullptr);
    }

    ~Graph()
    {
      // 遍历邻接表，将邻接表链接的链表销毁
      for (size_t i = 0; i < _linkTable.size(); ++i)
      {
        Edge *cur = _linkTable[i], *next = nullptr;
        while (cur)
        {
          next = cur->_next;
          delete cur;
          cur = next;
        }
        _linkTable[i] = nullptr;
      }
    }

    size_t GetVertexIndex(const V &v)
    {
      auto ret = _vIndexMap.find(v);
      if (ret != _vIndexMap.end())
      {
        return ret->second;
      }
      else
      {
        throw invalid_argument("不存在的顶点");
        return -1;
      }
    }

    // 判断对应边是否存在
    bool Exist(size_t srci, size_t dsti)
    {
      if (srci < 0 || dsti < 0 || srci >= _vertexs.size() || dsti >= _vertexs.size() || srci == dsti)
      {
        throw invalid_argument("对应位置非法");
        return false;
      }

      Edge *cur = _linkTable[srci];
      while (cur)
      {
        // 如果找到srci->dsti 该边存在
        if (cur->_dstIndex == dsti)
          return true;
        cur = cur->_next;
      }

      return false; // 运行到此处说明该边不存在
    }

    void _AddEdge(size_t srci, size_t dsti, const W &w)
    {
      if (srci < 0 || dsti < 0 || srci >= _vertexs.size() || dsti >= _vertexs.size() || srci == dsti || Exist(srci, dsti))
      {
        throw invalid_argument("插入位置非法");
        return;
      }

      // 头插
      Edge *sd_edge = new Edge(w);
      sd_edge->_srcIndex = srci;
      sd_edge->_dstIndex = dsti;
      sd_edge->_next = _linkTable[srci];
      _linkTable[srci] = sd_edge;

      // 无向图还需要对称插入边
      if (Direction == false)
      {
        Edge *ds_edge = new Edge(w);
        ds_edge->_srcIndex = dsti;
        ds_edge->_dstIndex = srci;
        ds_edge->_next = _linkTable[dsti];
        _linkTable[dsti] = ds_edge;
      }
    }

    // 添加边，src --w--> dst
    void AddEdge(const V &src, const V &dst, const W &w)
    {
      // 得到起点和终点的下标
      int srci = GetVertexIndex(src);
      int dsti = GetVertexIndex(dst);

      // 添加对应边
      _AddEdge(srci, dsti, w);
    }

    void _DelEdge(size_t srci, size_t dsti)
    {
      if (srci < 0 || dsti < 0 || srci >= _vertexs.size() || dsti >= _vertexs.size() || srci == dsti)
      {
        throw invalid_argument("删除位置非法");
        return;
      }

      // 按照链表删除结点逻辑进行删除
      Edge *cur = _linkTable[srci], *prev = nullptr;
      while (cur)
      {
        if (cur->_dstIndex == dsti)
        {
          if (prev == nullptr)
          {
            // 头删
            _linkTable[srci] = cur->_next;
            delete cur;
            break;
          }
          else
          {
            prev->_next = cur->_next;
            delete cur;
            break;
          }
        }
        prev = cur;
        cur = cur->_next;
      }

      // 如果是无向图，还需要对称删除
      if (Direction == false)
      {
        Edge *cur = _linkTable[dsti], *prev = nullptr;
        while (cur)
        {
          if (cur->_dstIndex == srci)
          {
            if (prev == nullptr)
            {
              // 头删
              _linkTable[dsti] = cur->_next;
              delete cur;
              break;
            }
            else
            {
              prev->_next = cur->_next;
              delete cur;
              break;
            }
          }
          prev = cur;
          cur = cur->_next;
        }
      }
    }

    // 删除边，src --> dst
    void DelEdge(const V &src, const V &dst)
    {
      // 得到起点和终点的下标
      int srci = GetVertexIndex(src);
      int dsti = GetVertexIndex(dst);

      // 删除对应边
      _DelEdge(srci, dsti);
    }

    // 打印
    void Print()
    {
      // 打印顶点及其映射下标
      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        cout << _vertexs[i] << "-[" << _vIndexMap[_vertexs[i]] << "]" << endl;
      }

      cout << endl
           << endl;

      // 打印邻接表
      for (size_t i = 0; i < _linkTable.size(); ++i)
      {
        cout << "[" << i << "]->";
        // 遍历每个链表
        Edge *cur = _linkTable[i];
        while (cur)
        {
          cout << "([" << cur->_dstIndex << "]:" << cur->_w << ")->";
          cur = cur->_next;
        }
        cout << "nullptr" << endl;
      }

      cout << endl
           << endl;
    }

    void _DFS(size_t starti, vector<bool> &visited)
    {
      if (!visited[starti])
      {
        cout << _vertexs[starti] << " ";
        visited[starti] = true;
      }

      // 遍历邻接表
      for (Edge *cur = _linkTable[starti]; cur; cur = cur->_next)
      {
        if (!visited[cur->_dstIndex])
          _DFS(cur->_dstIndex, visited);
      }
    }

    // DFS
    void DFS()
    {
      vector<bool> visited;
      visited.resize(_vertexs.size(), false);

      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        if (!visited[i])
          _DFS(i, visited);
      }

      cout << endl
           << endl;
    }

    void _BFS(size_t starti, vector<bool> &visited)
    {
      // 创建队列
      queue<int> q;
      q.push(starti);
      visited[starti] = true;

      while (!q.empty())
      {
        Edge *cur = _linkTable[q.front()];
        cout << _vertexs[q.front()] << " ";
        q.pop();

        while (cur)
        {
          if (!visited[cur->_dstIndex])
          {
            q.push(cur->_dstIndex);
            visited[cur->_dstIndex] = true;
          }
          cur = cur->_next;
        }
      }
    }

    // BFS
    void BFS()
    {
      vector<bool> visited;
      visited.resize(_vertexs.size(), false);

      for (size_t i = 0; i < _vertexs.size(); ++i)
      {
        if (!visited[i])
          _BFS(i, visited);
      }

      cout << endl
           << endl;
    }

  private:
    map<V, int> _vIndexMap;    // 顶点对应下标(直接映射)
    vector<V> _vertexs;        // 顶点集合
    vector<Edge *> _linkTable; // 边的集合的邻接表
  };

  void TestGraph()
  {
    Graph<char, int, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    g.Print();

    g.DelEdge('0', '1');
    g.DelEdge('2', '3');

    g.Print();
  }

  void TestGraphDBFS()
  {
    string a[] = {"张三", "李四", "王五", "赵六", "周七", "孙八"};
    Graph<string, int> g1(a, sizeof(a) / sizeof(string));
    g1.AddEdge("张三", "李四", 100);
    g1.AddEdge("张三", "王五", 200);
    g1.AddEdge("王五", "赵六", 30);
    g1.AddEdge("王五", "周七", 30);
    g1.AddEdge("赵六", "孙八", 60);

    g1.BFS();
    g1.DFS();
  }
}