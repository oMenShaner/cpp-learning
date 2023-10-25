#include<iostream>

using namespace std;

const int maxCapacity = 100;        //最大容量为100
int dp[11][maxCapacity] = {0, };    //dp数组,记录状态
int weight[11] = {0, };             //物品重量数组
int value[11] = {0, };              //物品价值数组
int choice[maxCapacity] = {0, };    //存放最终结果

inline int Max(int left, int right)
{
  return left > right ? left : right;
}

// 填写dp数组
void getMaxValue(int n, int m, int dp[][maxCapacity], int* weight, int* value)
{
  int i = 0;
  int j = 0;

  for (i = 1; i <= n; i++)
  {
    for (j = 1; j <= m; j++)
    {
      if (weight[i] <= j)
      {//如果当前的容量状态可以装下, 则找到max(上一状态价值+本物品价值, 不装状态价值)
        dp[i][j] = Max(dp[i-1][j-weight[i]]+value[i], dp[i-1][j]);
      }
      else 
      {//如果当前容量装不下, 直接将当前容量-1时的状态赋值
        dp[i][j] = dp[i-1][j];
      }
    }
  }
}

void printDp(int n, int m, int dp[][maxCapacity])
{
  int i = 0;
  int j = 0;

  for (i = 0; i <= n; i++)
  {
    for(j = 0; j <= m; j++)
    {
      cout << dp[i][j] << '\t';
    }
    cout << endl;
  }
}

void getResult(int n, int m, int dp[][maxCapacity], int* weight)
{
  int i = n;
  int j = m;
  
  for (i = n; i > 0; i--)
  {
    if (dp[i][j] > dp[i-1][j])
    {//如果比减一容量状态大, 说明该物品被装了
      choice[i] = 1;
      j = j - weight[i];
    }
  }
}

void printChoice(int* choice, int m)
{
  int i = 0;
  
  cout << "结果是:" << endl;
  for (i = 1; i <= m; i++)
  {
    cout << i << '\t' << choice[i] << endl;
  }
}

int main()
{
  int n, m;
  cout << "输入物品数量(最大10) 和 背包容量(最大100):" << endl;
  cin >> n >> m;
  cout << "输入每个物品的质量和价值" << endl;
  
  int i = 0;
  for (i = 1; i <= n; i++)
  {
    cin >> weight[i] >> value[i];
  }
  
  getMaxValue(n, m, dp, weight, value);
  printDp(n, m, dp);  
  getResult(n, m, dp, weight);
  printChoice(choice, m);

  return 0;
}
