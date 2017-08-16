#include <cstdio>
#include <cstring>
using namespace std;

int head[100010],dfn[100010],low[100010],cnt,n,m,x,y,Index,ans;

int min(int a,int b){return a < b ? a : b;}

struct Edge{
	int nxt,to;
}e[200010];

void addedge(int st,int ed){
	e[++cnt].to = ed;e[cnt].nxt = head[st];head[st] = cnt;
	e[++cnt].to = st;e[cnt].nxt = head[ed];head[ed] = cnt;
}

bool vis[100010],po[100010];

void tarjan(int u,int f)
{
	int son = 0;
	vis[u] = true;low[u] = dfn[u] = ++Index;
	for (int i = head[u];i;i = e[i].nxt)
	{
		int d = e[i].to;
		if (vis[d] && d != f) low[u] = min(low[u],dfn[d]);
		else if (!vis[d])
		{
			tarjan(d,u);
			son++;
			low[u] = min(low[u],low[d]);
			if ((u == f && son > 1) || (u != f && dfn[u] <= low[d]))
			{
				if (!po[u]) ans++;
				po[u] = true; 
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= m;i++)
	{
		scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	for(int i = 1;i <= n;i++) if (!dfn[i]) tarjan(i,i);
	printf("%d\n",ans);
	for (int i = 1;i <= n;i++) if (po[i]) printf("%d ",i);
	putchar('\n');
	return 0;
} 
