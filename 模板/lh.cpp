//
// Created by ZHK on 2021/2/2.
//
#include <bits/stdc++.h>
//#pragma GCC optimize(3)
#define SZ(x) ((int)x.size())
#define uni(x) sort(all(x)),x.resize(unique(all(x))-x.begin());
#define GETPOS(c,x) (lower_bound(all(c),x)-c.begin())
#define lown1(x,val) low(in(x),val)-x
#define lowm1(x,val) low(im(x),val)-x
#define low1(x,nums,val) low(x+1,x+nums+1,val)-x
#define mst(x,val) memset((x),val,sizeof((x)))
#define ls rt<<1
#define rs rt<<1|1
#define lson rt<<1,l,M
#define rson rt<<1|1,M+1,r
#define PI acos(-1)
#define MM int M=(l+r)>>1;
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define fd(i,r,t) for(int i=r;i>=t;i--)
#define fh(i,be,e) for(int i=head[be];~i;i=e[i].next)
#define fa(i,V) for(auto i:V)
#define far(i,V) for(auto &i:V)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define lcm(a,b) ((a)*(b))/__gcd(a,b)
#define cp(i,ans) printf("%.if",ans);
#define cpp(i,ans) cout<<setprecision(i)<<fixed<<ans<<endl;
#define ppb pop_back
#define ppf pop_front
#define pb push_back
#define pf push_front
#define pq priority_queue
#define lowbit(x) ((x)&(-x))
#define all(V) V.begin(),V.end()
#define ms multiset
#define mod(x) (((x)<0)?(x)%mo_num+mo_num:(x)%mo_num)
#define vc vector
#define vct vector<int>
#define SET set<int>
#define dq deque<int>
#define out(i) cout<<(i)<<endl;
#define fi first
#define se second
#define fun(i) fu(i,1,n)
#define fut(i) fu(i,1,t)
#define fum(i) fu(i,1,m)
#define ld long double
#define umap unordered_map
#define Umap unordered_map<int,int>
#define P pair<int,int>
#define mk make_tuple
#define eps 1e-6
//Remember cancel"#define endl '\n'" in interactive questions or use "<<flush"
#define endl '\n'
#define low lower_bound
#define upp upper_bound
#define yn(key) out(key?"YES":"NO")
//#define yn(key) out(key?"Yes":"No")
#define in(i) i+1,i+1+n
#define im(i) i+1,i+1+m
#define ik(i,k) i+1,i+1+k
#define bffs(i) __builtin_ffs(i)
#define bcount(i) __builtin_popcount(i)
#define bone(i) ((1<<i)-1)
#define db double
#define ll long long
#define got(container,num) get<num-1>(container)
#define int long long
#define print(a,n) fun(i)cout<<a[i]<<(i!=n?' ':endl);
#define outcase(x) cout<<"Case #"<<(++case_of_T)<<": "<<(x)<<endl;
#define ptcase(x) printf("Case #%d: %d\n",++case_of_T,x);
#define plcase(x) printf("Case #%lld: %lld\n",++case_of_T,x);
using namespace std;
//Remember to cancel the line below and declare INT=INT_MAX/2; when you want to change long to int
const int INF=LLONG_MAX/4,SINF=0x3f3f3f3f,Lim=1<<20,MINF=LLONG_MAX;
//const int INF=INT_MAX/4,SINF=0x3f;
// use C:printf("%.16f", x);  ->  printf("%.10f", x); can accelerate the program
const int dx[]={0,0,-1,1},dy[]={-1,1,0,0};//down up left right
const int maxn=1e6+1e5;
int mo_num=1e9+7;
//const int mo_num=998244353;





二分模板1:(由中间向下取)
//注意!最后输出的l并不一定在初始的l-r之间,即最终的l可以>r!!
//多少多
int l=0,mid,r=n;
bool can(int x)
{
    int num=0;
    fun(i)num+=max((int)0,a[i]-x);
    return num>=m;
}
while(l<=r)
{
mid=(l+r)/2;
//mid=l+r>>1;
if(can(mid))//答案在中间以下
{
r=mid-1;
}else{
l=mid+1;
}
}
cout<<l;

r多（多少多）l少（少多少）
即r>l

//少多少
二分模板2:
//注意!最后二分出的l并不一定在初始的l-r之间,即最终的l可以>r!!
//所以如果要判断l是否合理还要加上 if(l<=begin_r && can(l))..
int l=0,mid,r=n;//注意,此时r不能=LLONG_MAX,因为下面会加一爆出去,所以最多LLONG_MAX-1;
while (l < r)
{
mid = l + r + 1 >> 1;
if (can(mid)) l = mid;//答案在中间以上,即第一个满足条件的传入值
else r = mid - 1;
}
cout<<l;

void solve()
{

    return ;
}
main()
{
    IOS
    int T=1;
    //cin>>T;
    while(T--)solve();
    return 0;
}
