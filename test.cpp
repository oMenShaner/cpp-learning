#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int maxSum1D(vector<int>& nums, int n)
{
  int sums = 0;
  vector<int> temp(n+1, 0);
  for (int i = 1; i <= n; i++) 
  {
    if (nums[i] >= 0) 
    { 
      temp[i] = temp[i - 1] + nums[i];
    }
    else 
    {
      temp[i] = temp[i - 1];
    }
    if (temp[i] > sums)
    {
      sums = temp[i];
    }
  }
    return sums;
}

int maxSum2D(vector<vector<int>>& nums, int n, int m) 
{
  int sums = 0;
  for (int i = 1; i <= n; i++) 
  {
    vector<int> temp(m + 1, 0);
    int j = i;
    while (j <= n)
    {
      for (int k = 1; k <= m; k++) 
      {
        temp[k] += nums[j][k];
      }
      int tempSum = maxSum1D(temp, m);
      if (tempSum > sums) 
      {
        sums = tempSum;
      }
      j++;
    }
  }
  return sums;
}

int maxSum3D(vector<vector<vector<int>>>& nums, int n, int m, int p) 
{
  int sums = 0;
  for (int i = 1; i <= p; i++) 
  {
    vector<vector<int>> temp(m + 1, vector<int>(n + 1, 0));
    int j = i;
    while (j <= p) 
    {
      for (int k = 1; k <= m; k++) 
      {
        for (int l = 1; l <= n; l++) 
        {
          temp[k][l] += nums[j][k][l];
        }
      }
      int tempSum = maxSum2D(temp, n, m);
      if (tempSum > sums) 
      {
        sums = tempSum;
      }
      j++;
    }
  }
  return sums;
}

int main()
{
  int m, n, p;
  cin >> m >> n >> p;
  vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(p + 1, 0)));
  
  // 读入数据
  for (int i = 1; i <= m; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      for (int k = 1; k <=p; k++)
      {
        cin >> dp[i][j][k];
      }
    }
  }

  cout << maxSum3D(dp, n, m, p) << endl;

  return 0;
}
