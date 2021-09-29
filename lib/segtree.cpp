template<typename T> struct segtree{

    int N = 1;
    vector<T> seg;

    segtree(int n){
        while(N < n) N *= 2;
        seg.resize(2*N, nil);
    }

    segtree(vector<T> &v, int offset=0){
        int n = v.size();
        while(N < n+offset) N *= 2;
        seg.resize(2*N, nil);
        for(int i=0; i<n; i++) seg[N+i+offset] = v[i];
        for(int i=N-1; i; i--) seg[i] = join(seg[2*i], seg[2*i+1]);
    }

    // default value
    const T nil = 0;
    
    // join subtrees and query
    T join(T a, T b){
        return a+b;
    }

    // queries
    T qer(int l, int r){
        l += N; r += N;
        T s = nil;
        while(l<=r){
            if(l&1) s = join(s, seg[l++]);
            if(~r&1) s = join(s, seg[r--]);
            l /= 2; r /= 2;
        }
        return s;
    }
    
    void add(int i, T o){
        i += N;
        seg[i] += o;
        for(i /= 2; i; i /= 2) seg[i] = join(seg[2*i], seg[2*i+1]);
    }
};

