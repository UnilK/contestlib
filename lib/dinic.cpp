template <typename T> struct dinic{
    
    int src, sink, n, m = 0;
    T inf = 1e18, flow = 0;
    vector<vector<array<int, 2> > > g;
    vector<T> cap;
    vector<int> lvl, ptr;
    queue<int> q;

    dinic(vector<vector<pair<int, T> > > &g_, int src_, int sink_, bool directed=1)
        : src(src_), sink(sink_), n(g_.size()), g(g_.size()), lvl(g_.size()), ptr(g_.size()) {
        for(int i=0; i<n; i++){
            for(auto j : g_[i]){
                cap.push_back(j.second);
                cap.push_back(directed ? 0 : j.second);
                g[i].push_back({j.first, m++});
                g[j.first].push_back({i, m++});
            }
        }
        while(bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while(T f = dfs(src, inf)) flow += f;
        }
    }

    int bfs(){
        fill(lvl.begin(), lvl.end(), 0);
        lvl[src] = 1;
        q.push(src);
        while(!q.empty()){
            int i = q.front();
            q.pop();
            for(auto j : g[i]){
                if(lvl[j[0]] || cap[j[1]] <= 0) continue;
                lvl[j[0]] = lvl[i]+1;
                q.push(j[0]);
            }
        }
        return lvl[sink];
    }

    T dfs(int i, T f){
        if(i == sink) return f;
        for(int &j=ptr[i]; j<(int)g[i].size(); j++){
            auto &x = g[i][j];
            if(lvl[x[0]] != lvl[i]+1 || cap[x[1]] <= 0) continue;
            T ff = dfs(x[0], min(f, cap[x[1]]));
            if(ff > 0){
                cap[x[1]] -= ff;
                cap[x[1]^1] += ff;
                return ff;
            }
        }
        return 0;
    }

    vector<array<int, 2> > &operator[](int i){ return g[i]; }
    T &operator()(int i){ return cap[i]; }
};

