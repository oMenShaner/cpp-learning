#include <iostream>
#include <stdlib.h>

using namespace std;
void InsertSort(int n, double w[], double v[])
{
	int max1;
	double t[20];

  for(int i = 1; i <= n; i++)
  {
		t[i] = v[i] / w[i];
	}
	for(int i = 1; i <= n; i++)
  {
		max1 = i;
		for(int j = i+1; j <= n; j++)
    {
			if(t[j] > t[max1]) 
      {
				max1 = j;
			}
		}
		swap(t[i], t[max1]);
		swap(w[i], w[max1]);
		swap(v[i], v[max1]);
	}
	for(int i = 1; i <= n; i++)
  {
		cout<<t[i]<<endl;
	}
}

void knapsack_greedy(int n,double c,double w[],double v[],double b[]){
	int j;
	InsertSort(n,w,v);
	for(int i = 1; i <= n; i++)//初始化背包b[]
		b[i] = 0;
	for(j = 1; j <= n; j++) 
  {
		if(c < w[j]) 
      break;
		b[j] = 1;
		c = c - w[j];
	} 
	if(j <= n)
		b[j] = c / w[j];
	cout << "输出：" <<endl;
	for(int i = 1;i <= n; i++)
  {
		cout << "物品重量为：" << w[i] << " " << "物品比例" << b[i] << endl;
	}
}

int main()
{
	int n,c;
	double b[20],w[20],v[20];
	cout<<"输入物品数量和背包容量：";
	cin>>n>>c;
	cout<<"输入物品重量（如：30 10 20）："; 
	for(int i=1;i<=n;i++)
		cin>>w[i];
	cout<<"输入物品的价值（如：120 60 100）："; 
	for(int i=1;i<=n;i++)
		cin>>v[i];
	knapsack_greedy(n,c,w,v,b);	
	return 0;
}
