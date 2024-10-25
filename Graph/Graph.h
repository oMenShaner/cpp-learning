#pragma once

// 邻接矩阵
namespace Martix
{
  // V为结点数据类型, W为权值类型, 默认为无向图
  template <class V, class W, W MAX_W = INT32_MAX, bool Direction = false>
  class Graph
  {
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

    // g.DelEdge('0', '1');
    // g.DelEdge('2', '3');

    // g.Print();
  }
}