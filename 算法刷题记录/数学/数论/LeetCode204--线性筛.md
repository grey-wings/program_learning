
[题目链接](https://leetcode-cn.com/problems/count-primes/)  

[线性筛参考](https://www.luogu.com.cn/problem/solution/P3383)  

线性筛的原则是**每个合数只被它的最小质因数筛掉**，因此时间复杂度为O(n).  
基本思想如下：  
首先建立一个isPrime数组，用于存储每个数是否为素数。  
然后建立一个prime数组存储素数，便于后面筛去合数的过程。  
建立两层循环，外层从1到n（要筛的数的范围）  
如果搜到某个数，经过前面的各种筛查还没有被筛掉，说明这个数是质数，加入prime数组中，并且开启第二层循环删掉所有以它为最小质因数的数。  
下面这一段程序保证了每个合数只被它的最小质因数筛掉：  
```cpp
if(i % Prime[j] == 0)//i中也含有Prime[j]这个因子
	break; 
```    
证明如下：（注：令i % prime[j]等于0时，j = J）    
（1）i的最小质因数是prime[J]。  
如果不是，假设是prime[k](k < J)，那么之前枚举到prime[k]的时候就会把i筛掉。  
（2）对于一切s < J，i * prime[s]的最小质因数是prime[s]。  
因为i的最小质因数是prime[j] > prime[s]  
（3）对于一切l > J，i * prime[l]的最小质因数是prime[J]。  
由于在内层循环中期望以prime[j]筛掉合数（即prime[j]应该是被筛合数的最小质因数），因此当j > J时不应该继续循环，否则是在以prime[J]筛掉合数。    
```cpp
bool isPrime[100000010];
//isPrime[i] == 1表示：i是素数
int Prime[6000010], cnt = 0;
//Prime存质数

void GetPrime(int n)//筛到n
{
	memset(isPrime, 1, sizeof(isPrime));
	//以“每个数都是素数”为初始状态，逐个删去
	isPrime[1] = 0;//1不是素数
	
	for(int i = 2; i <= n; i++)
	{
		if(isPrime[i])//没筛掉 
			Prime[++cnt] = i; //i成为下一个素数
			
		for(int j = 1; j <= cnt && i*Prime[j] <= n/*不超上限*/; j++) 
		{
        	//从Prime[1]，即最小质数2开始，逐个枚举已知的质数，并期望Prime[j]是(i*Prime[j])的最小质因数
            	//当然，i肯定比Prime[j]大，因为Prime[j]是在i之前得出的
			isPrime[i*Prime[j]] = 0;
            
			if(i % Prime[j] == 0)//i中也含有Prime[j]这个因子
				break; //重要步骤。见原理
		}
	}
}
```  
