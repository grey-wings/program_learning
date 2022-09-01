#include <bits/stdc++.h>
using namespace std;
/* 宏 */
#define fu(i,r,t) for(long long i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
bitset<100000010> a;
vector<long long> sb;
int main()
{
    IOS
    int n;
    cin >> n;
    a.set(); // 全部赋值成1
    a[1]=false;
    fu (i,2,n)
    {
        if (a[i])
        {
            sb.push_back(i);
        }
        for (long long j : sb)
        {
            if (i*j>n)
                break;
            a[i*j]=false;
            if (i%j==0)
                break;
        }
    }
    int q,p;
    cin >> q;
    fu (i,1,q)
    {
        cin >> p;
        print(sb[p-1])
    }
    return 0;
}
