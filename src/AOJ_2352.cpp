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

int n, x[110];

    const int MAX_V = 210;
    
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

void init() {
}

void input() {
	cin >> n;
	REP(i, n) cin >> x[i];
	
}

bool g[110][110];
VI res;

int cnt(VI used, int a){
	bool canuse[n]; REP(i, n) canuse[i] = true;
	REP(i, a) canuse[i] = false;
	REP(i, SZ(used)){
		canuse[used[i]] = false;
		REP(j, n) if(g[used[i]][j] || g[j][used[i]]) canuse[j] = false;
	}
	
	map<int, int> idx;
	V = 0;
	REP(i, MAX_V) G[i].clear();
	REP(i, n) if(canuse[i]) idx[i] = V++;
	REP(i, n) REP(j, n) if(i != j && canuse[i] && canuse[j] && g[i][j]) add_edge(idx[i], idx[j]+V);
	return V - bipartite_matching();
}

void solve() {
	REP(i, 110) REP(j, 110) g[i][j] = false;
	REP(i, n) REP(j, n) if(i != j && x[i]%x[j] == 0) g[i][j] = true;
	
	res.clear();
	REP(i, n){
		int cnt1 = cnt(res, i+1);
		int cnt2 = 0;
		bool test = true;
		REP(j, SZ(res)) if(g[res[j]][i] || g[i][res[j]]) test = false;
		VI tmp = res; tmp.push_back(i);
		if(test) cnt2 = cnt(tmp, i+1) + 1;
		if(cnt2 >= cnt1 && cnt2 != 0) res.push_back(i);
	}
	REP(i, SZ(res)) cout << res[i]+1 << (i == SZ(res)-1 ? "" : " ");
	cout << endl;
}

int main() {
	init();
    input();
    solve();
	return 0;
}






