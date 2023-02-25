vector<int> epath(vector<array<int, 2> > &e, int n){
    
    vector<vector<array<int, 2>>> g(n+1);
 
    for(int i=0; i<(int)e.size(); i++){
        g[e[i][0]].push_back({e[i][1], i});
        g[e[i][1]].push_back({e[i][0], i});
    }
 
    int odd = -1;
 
    for(int i=0; i<=n; i++){
        if(g[i].size()&1) odd = i;
        else if(odd < 0 && g[i].size()) odd = i;
    }
 
    if(odd < 0) return {};
 
    vector<bool> visited(e.size(), 0);
    stack<int> loop; loop.push(odd);
    vector<int> path;
 
    while(!loop.empty()){
        while(1){
            auto &i = g[loop.top()];
            while(!i.empty() && visited[i.back()[1]]) i.pop_back();
            if(!i.empty()){
                visited[i.back()[1]] = 1;
                loop.push(i.back()[0]);
            }
            else break;
        }
        while(!loop.empty() && g[loop.top()].empty()){
            path.push_back(loop.top());
            loop.pop();
        }
    }
 
    if(path.size() != e.size() + 1) return {};
 
    return {path.rbegin(), path.rend()};
}

