template<typename T> struct lazyseg{

    int N = 1;
    vector<T> seg, lazy;
    vector<bool> flag;

    // default lazy value.
    const int nil = 0;
   
    // qer query join.
    T join(T a, T b){
        return a+b;
    }
    
    // add query join.
    T lazyjoin(T a, T b){
        return a+b;
    }

    // set lazy value to cell.
    T drop(int k){
        flag[k] = 1;
        lazy[k] = lazyjoin(lazy[k], val);
        return lazyjoin(seg[k], lazy[k]);
    }

    // lazy values resolving logic.
    void push(int k){
        if(flag[k]){
            seg[k] = lazyjoin(seg[k], lazy[k]);
            if(k < N){
                lazy[2*k] = lazyjoin(lazy[2*k], lazy[k]);
                lazy[2*k+1] = lazyjoin(lazy[2*k+1], lazy[k]);
                flag[2*k] = flag[2*k+1] = 1;
            }
            flag[k] = 0;
            lazy[k] = nil;
        }
    }

    int ql, qr;
    T val;

    T iadd(int l, int r, int k){
        push(k);
        if(qr < l || ql > r) return seg[k];
        if(ql <= l && qr >= r) return drop(k);
        int m = (l+r)/2;
        seg[k] = join(iadd(l, m, 2*k), iadd(m+1, r, 2*k+1));
        return seg[k];
    }

    
    T iqer(int l, int r, int k){
        push(k);
        if(qr < l || ql > r) return nil;
        if(ql <= l && qr >= r) return seg[k];
        int m = (l+r)/2;
        return join(iqer(l, m, 2*k), iqer(m+1, r, 2*k+1));
    }

    void add(int l, int r, T o){
        ql = l; qr = r; val = o;
        iadd(0, N-1, 1);
    }

    T qer(int l, int r){
        ql = l; qr = r;
        return iqer(0, N-1, 1);
    }

    lazyseg(int n){
        while(N < n) N *= 2;
        seg.resize(2*N, nil);
        lazy.resize(2*N, nil);
        flag.resize(2*N, 0);
    }

    lazyseg(vector<T> &v, int offset=0){
        int n = v.size();
        while(N < n+offset) N *= 2;
        seg.resize(2*N, nil);
        lazy.resize(2*N, nil);
        flag.resize(2*N, 0);
        for(int i=0; i<n; i++) seg[N+i+offset] = v[i];
        for(int i=N-1; i; i--) seg[i] = join(seg[2*i], seg[2*i+1]);
    }

};
