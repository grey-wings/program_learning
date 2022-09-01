/* 看毛片算法模板 洛谷P3375题解 */
#include <bits/stdc++.h>
using namespace std;
/* 宏 */
#define fu(i,r,t) for(long long i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
#define ll long long
#define ull unsigned long long
#define fix(X) (X>0)?X:0

void getNext(string s,int next[])
{
    int i, j = 0;
//  j指向前缀末尾位置，i指向后缀末尾位置。、
//  j还代表了s[i]及其以前的s的子串的最长相等前后缀的长度。
//  next[i]表示了由s[0]到s[i]组成的子串的最长相等前后缀的长度。
//  next[0]设为0，在其他写法中可能有不同的取值。
    next[0] = 0;
    for (i = 1; i < s.length(); i++)
    {
        while (s[i] != s[j] && j > 0)
            j = next[j - 1];
//      如果不匹配那么就回退。显然不是一个一个的回退，那么如果匹配不上，
//      就回退到j的前一个的最长相等前缀的后面一位去。
//      例如,"abcabd",next[0:6](python表示法)依次为：0,0,0,1,2,；
//      那么当i=5时，j=2(见函数顶部的第二行注释)，s[i]!=s[j],
//      那么j变为next[1]即为0.
        if (s[i] == s[j])
            j++;
        next[i] = j;
    }
}

int kmp(string s,string t)
{
    // s是主串，t是要在主串里面寻找的子串,next是t的next数组，用上面那个函数求出。
    int next[t.length()];
    getNext(t,next);
    int i,j=0;
    // i是s的一个指针，j是t的一个指针,begin表示匹配成功的串开始的位置
    for (i=0;i<s.length();i++)
    {
//       采用和getNext函数相似的方法。
        while (s[i]!=t[j] && j>0)
            j=next[j-1];
        if (s[i]==t[j])
            j++;
        if (j==t.length())
            break;
    }
    if (j>=t.length())
        return i-(int)t.length()+1;
    else
        return -1;
    // 如果因为i到了s的边界而溢出，说明s中不包含t，以-1代表没有找到。
}

/* 洛谷P3375 看毛片匹配所有位置 */
string s,t;
    char ch;
    cin >> s >> t;
    int i,j=0;
    int next[t.length()];
    getNext(t,next);
    for (i=0;i<s.length();i++)
    {
        while (s[i]!=t[j] && j>0)
            j=next[j-1];
        if (s[i]==t[j])
            j++;
        if (j==t.length())
        {
            a.push_back(i-(int)t.length()+1);
            j=next[j-1];
        }
    }
