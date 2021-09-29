template<typename T, typename L> struct lazyseg{

    int N = 1;
    vector<T> seg;
    vector<L> lazy;
    vector<bool> flag;

    int ql, qr;
    L val;
    
    T iadd(int l, int r, int k){
        push(k, l, r);
        if(qr < l || ql > r) return seg[k];
        if(ql <= l && qr >= r) return drop(k, l, r);
        int m = (l+r)/2;
        seg[k] = join(iadd(l, m, 2*k), iadd(m+1, r, 2*k+1));
        return seg[k];
    }

    
    T iqer(int l, int r, int k){
        push(k, l, r);
        if(qr < l || ql > r) return nil;
        if(ql <= l && qr >= r) return seg[k];
        int m = (l+r)/2;
        return join(iqer(l, m, 2*k), iqer(m+1, r, 2*k+1));
    }

    lazyseg(int n){
        while(N < n) N *= 2;
        seg.resize(2*N, nil);
        lazy.resize(2*N, lazynil);
        flag.resize(2*N, 0);
    }

    lazyseg(vector<T> &v, int offset=0){
        int n = v.size();
        while(N < n+offset) N *= 2;
        seg.resize(2*N, nil);
        lazy.resize(2*N, lazynil);
        flag.resize(2*N, 0);
        for(int i=0; i<n; i++) seg[N+i+offset] = v[i];
        for(int i=N-1; i; i--) seg[i] = join(seg[2*i], seg[2*i+1]);
    }
    
    // push down logic.
    void push(int k, int l, int r){
        if(flag[k]){
            seg[k] = lazymerge(seg[k], lazy[k], l, r);
            if(k < N){
                lazy[2*k] = lazyjoin(lazy[2*k], lazy[k]);
                lazy[2*k+1] = lazyjoin(lazy[2*k+1], lazy[k]);
                flag[2*k] = flag[2*k+1] = 1;
            }
            flag[k] = 0;
            lazy[k] = lazynil;
        }
    }
    
    // set lazy value to cell.
    T drop(int k, int l, int r){
        flag[k] = 1;
        lazy[k] = lazyjoin(lazy[k], val);
        return lazymerge(seg[k], lazy[k], l, r);
    }
    
    // default query return value and default lazy value.
    const T nil = 0;
    const L lazynil = 0;
  
    // qer query join.
    T join(T a, T b){
        return a+b;
    }
    
    // join b to a
    L lazyjoin(L a, L b){
        return a+b;
    }

    // merge lazy to segtree
    T lazymerge(T a, L b, int l, int r){
        return a+b*(r-l+1);
    }

    // query operations. closed segments.
    T qer(int l, int r){
        ql = l; qr = r;
        return iqer(0, N-1, 1);
    }
    
    void add(int l, int r, T o){
        ql = l; qr = r;
        val = o;
        iadd(0, N-1, 1);
    }
};

