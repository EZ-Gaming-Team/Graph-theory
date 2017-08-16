#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n,m,s,x,y,a,b;

struct Edge{
    int nxt,to;
}e[1100005];

int head[500005],cnt,f[500005][20],dep[500005];

void read(int &x)
{
    char c = getchar();x = 0;
    while(c < '0'|| c > '9')c = getchar();
    while(c >= '0'&& c <= '9')x = x * 10 + c - 48,c=getchar();
}

void addedge(int st,int ed)
{
    e[++cnt].to = ed;e[cnt].nxt = head[st];head[st] = cnt;
    e[++cnt].to = st;e[cnt].nxt = head[ed];head[ed] = cnt;
}

void build(int u)
{
    for (int i = head[u];i;i = e[i].nxt)
    {
        int v = e[i].to;
        if (!dep[v])
        {
            dep[v] = dep[u] + 1;
            f[v][0] = u;
            build(v);
        }
    }
}

int LCA(int a,int b)
{
    if (dep[a] < dep[b]) swap(a,b);
    for (int i = 19;i >= 0;i--)
        if (dep[f[a][i]] >= dep[b]) a = f[a][i];
    if (a == b) return b;
    for (int i = 19;i >= 0;i--)
    {
        if (f[a][i] != f[b][i]) a = f[a][i],b = f[b][i];
    }
    return f[a][0];
}

void initialize()
{
    for (int i = 1;i <= 19;i++)
      for (int j = 1;j <= n;j++)
      f[j][i] = f[f[j][i - 1]][i - 1];
}
int main()
{
    read(n);read(m);read(s);
    for (int i = 1;i < n;i++)
    {
        read(x);read(y);
        addedge(x,y);
    }
    dep[s] = 1;build(s);initialize();
    while(m--){
        read(a);read(b);
        printf("%d\n",LCA(a,b));
    }
    return 0;
}