#include <cstdio>
#include <queue>
#include <stack>
using namespace std;

int Index, scc, n, m, a, b, f[100005], cnt, top, Stack[100005], v[100005];
int belong[100005], sccv[100005], head[100005], low[100005], dfn[100005];
int he[100005], ans;
bool instack[100005];

struct Edge
{
    int nxt, to;
}e[100005], p[100005];

void addedge(int st, int ed) { e[++cnt].to = ed; e[cnt].nxt = head[st]; head[st] = cnt; }
void addedge2(int st, int ed) { p[++cnt].to = ed; p[cnt].nxt = he[st]; he[st] = cnt; }
void tarjan(int x)
{
    dfn[x] = low[x] = ++Index;
    Stack[++top] = x; instack[x] = true;
    for (int i = head[x]; i; i = e[i].nxt) {
        int d = e[i].to;
        if (!dfn[d]) {
            tarjan(d);
            low[x] = min(low[d], low[x]);
        } else if (instack[d]) low[x] = min(low[x], dfn[d]);
    }
    if (dfn[x] == low[x]) {
        belong[x] = ++scc;
        sccv[scc] += v[x];
        instack[x] = false;
        while (Stack[top] != x) {
            int vv = Stack[top--];
            belong[vv] = scc;
            sccv[scc] += v[vv];
            instack[vv] = false;
        }
        --top;
    }
}

int dp(int x)
{
    if (f[x]) return f[x];
    int Max = 0;
    for (int i = he[x]; i; i = p[i].nxt) {
        int d = p[i].to;
        Max = max(Max, dp(d));
    }
    return f[x] = sccv[x] + Max;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1; i <= m; i++) scanf("%d%d", &a, &b), addedge(a, b);
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j; j = e[j].nxt) {
            if (belong[i] != belong[e[j].to]) {
                addedge2(belong[i], belong[e[j].to]);
            }
        }
    }
    for (int i = 1; i <= scc; i++) {
        ans = max(ans, dp(i));
    }
    printf("%d\n", ans);
    return 0;
}

