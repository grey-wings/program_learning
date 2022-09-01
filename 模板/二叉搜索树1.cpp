// 洛谷P5076 【深基16.例7】普通二叉树（简化版）
// 内容：二叉搜索树加入元素、按值查排名、按排名查值、查前驱和后继。

#include <bits/stdc++.h>
using namespace std;
/* 宏 */
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
typedef struct
{
    int ls,rs,siz,cnt,val;
//    ls表示左儿子的下标
//    rs表示右儿子的下标
//    siz表示该节点和子树的大小之和（数字个数）
//    cnt表示该节点的值出现了几次
//    val表示该节点的值
}Tree;
Tree a[10002];
int coun; //表示当前树中存放了几个值
void add(int x,int v)
{
    a[x].siz++;      // 显然其子树节点数需要加一
    if (a[x].val==v)
    {
        a[x].cnt++;
        return;
    }
    if (a[x].val>v)
    {
        // 放到左子树
        if (a[x].ls)
        {
            add(a[x].ls,v);
        }
        else
        {
            // 如果没有左儿子
            coun++;
            a[x].ls=coun;
            a[coun].val=v;
            a[coun].siz=a[coun].cnt=1;
        }
    }
    else
    {
        // 放到右子树
        if (a[x].rs)
        {
            add(a[x].rs,v);
        }
        else
        {
            // 如果没有右儿子
            coun++;
            a[x].rs=coun;
            a[coun].val=v;
            a[coun].siz=a[coun].cnt=1;
        }
    }
}
int findRank(int x,int v)
{
//    x是当前进行比较的节点下标，v是要查找排名的值。
    if (x==0) return 0;
    if (a[x].val==v)
        return a[a[x].ls].siz;   //如果恰好找到这个值，那比他小的数的个数就是他的左子树的siz
    if (a[x].val<v)
    {
        //如果a[x]的值比v小，那要往右子树找
        //递归的时候相当于把a[x]的右子树看做整棵树
        //那算得的一切排名应当再加上a[x]及其左子树的个数
        //这个要加上的值就等于a[a[x].ls].siz]+这个点的出现次数
        return a[a[x].ls].siz+a[x].cnt+findRank(a[x].rs,v);
    }
    else
    {
        //往左子树找就不用考虑右子树有多少个数，因为右子树都比他大。
        return findRank(a[x].ls,v);
    }
}
int findValue(int x,int rank)
{
    if (x==0) return 0;
    if (a[a[x].ls].siz+1==rank)
        return a[x].val;
    if (a[a[x].ls].siz+1<rank)
    {
//        如果a[x]的排名比rank小，那应该往右找
        return findValue(a[x].rs,rank-a[a[x].ls].siz-a[x].cnt);
        //把a[x]的右子树看作一颗新树，那么所有排名都要减去a[x]的左子树的siz和他本身(a[x].cnt)
    }
    else
    {
        return findValue(a[x].ls,rank);
    }
}
int findPrev(int x,int v)
{
    int ret=-2147483647;  // 当前找到的比v小的最大值
    while (a[x].cnt!=0)
    {
        if (v > a[x].val)
        {
            ret=a[x].val;
            x = a[x].rs;
        }
        else
        {
            x=a[x].ls;
        }
    }
    return ret;
}
int findNext(int x,int v)
{
    int ret=2147483647;
    while (a[x].cnt!=0)
    {
        if (v < a[x].val)
        {
            ret=a[x].val;
            x = a[x].ls;
        }
        else
        {
            x=a[x].rs;
        }
    }
    return ret;
}
int main()
{
    IOS
    int n,k,num;
    cin >> n;
    fu(i,1,n)
    {
        cin >> k >> num;
        switch (k)
        {
            case 1:
            {
                print(findRank(1,num)+1)
                //findRank返回的是比num小的数的个数
                //要求排名还需要+1
                break;
            }
            case 2:
            {
                print(findValue(1,num))
                break;
            }
            case 3:
            {
                print(findPrev(1,num))
                break;
            }
            case 4:
            {
                print(findNext(1,num))
                break;
            }
            case 5:
            {
                if (coun==0)
                {
                    coun++; // 如果当前没有节点，那至少coun要加一；
                            // 如果已有节点，那有可能不用加。
                            // 所以coun初值设为0，但为0时先加一。
                    a[1].val=num;
                    a[1].cnt=1;
                    a[1].siz=1;
                }
                else
                    add(1,num);
                break;
            }
        }
    }
    return 0;
}
