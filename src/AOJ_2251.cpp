#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <numeric>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <cstdarg>
#include <sys/time.h>
#include <fstream>
//#include "cout.h"

using namespace std;

#define SZ(x) ((int)x.size())
#define MSET(x,a) memset(x, a, (int)sizeof(x))
#define PB push_back
#define VI vector < int >
#define PII pair < int, int >
#define LL long long
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(), (v).end()
#define FIT(it,v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)
#define OUT(A) cout << #A << " = "<< (A) << endl
#define OUT2(A, B) cout << "(" << #A << ", " << #B << ") = (" << (A) << ", "<< (B) << ")" << endl
template<class T> void chmin(T &t, T f) { if (t > f) t = f; } 
template<class T> void chmax(T &t, T f) { if (t < f) t = f; } 

#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())




    const int MAX_V = 2010;
    
    int V; // 左の頂点数。忘れずに設定すること。
    // ちなみに、Vは左右合わせた全部の頂点数でも問題ない。（左が終わった後に右からのをチェックしても、マッチ数は絶対増えない）
    
    
    VI G[MAX_V]; // ちゃんとGもケースごとに全部clear。
    int match[MAX_V];
    bool used[MAX_V];
    
    void add_edge(int u, int v){
        G[u].PB(v);
        G[v].PB(u);
    }
    
    bool dfs(int v){
        used[v] = true;
        REP(i, SZ(G[v])){
            int u = G[v][i], w = match[u];
            if(w < 0 || (!used[w] && dfs(w))){
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }
    
    int bipartite_matching(){
        int res = 0;
        MSET(match, -1);
        REP(v, V){
            if(match[v] < 0){
                MSET(used, 0);
                if(dfs(v)) res++;
            }
        }
        return res;
    }
    
    
    
int INF = (1<<29);

int n, m, l;
int g[110][110];
int p[1010], t[1010];

void init() {
}

void input() {
	REP(i, 110) REP(j, 110) g[i][j] = INF;
	REP(i, n) g[i][i] = 0;
	REP(i, m){
		int u, v, d;
		cin >> u >> v >> d;
		g[u][v] = d, g[v][u] = d;
	}
	REP(k, n) REP(i, n) REP(j, n) chmin(g[i][j], g[i][k]+g[k][j]);
	REP(i, l) cin >> p[i] >> t[i];
}

void solve() {
	V = l*2;
	REP(i, V) G[i].clear();
	REP(i, l) REP(j, l) if(i != j){
		if(t[i] + g[p[i]][p[j]] <= t[j]) add_edge(i, j+l);
		if(t[j] + g[p[j]][p[i]] <= t[i]) add_edge(j, i+l);
	}
	cout << l - bipartite_matching() << endl;
}

int main() {
	init();
	while(cin >> n >> m >> l){
		if(n == 0) break;
		input();
		solve();
	}
	return 0;
}






