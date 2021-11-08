template<typename T, typename L, template<typename, typename> typename O> struct lazyseg{

    using X = O<T, L>;
    int N = 1;
    vector<T> seg;
    vector<L> lazy;
    vector<bool> flag; 
    int ql, qr;
    L val;

    lazyseg(int n=1, vector<T> v={}, int offset=0){ init(n, v, offset); }
    void init(int n=1, vector<T> v={}, int offset=0){
        n = max(n, (int)v.size());
        while(N < n+offset) N *= 2;
        seg.resize(2*N, (T)X::inil);
        lazy.resize(2*N, (L)X::lnil);
        flag.resize(2*N, 0);
        for(int i=0; i<(int)v.size(); i++) seg[N+i+offset] = v[i];
        for(int i=N-1; i; i--) seg[i] = X::segjoin(seg[2*i], seg[2*i+1]);
    }

    void push(int k, int d){
        if(flag[k]){
            seg[k] = X::lazymerge(seg[k], lazy[k], d);
            if(k < N){
                X::lazyjoin(lazy[2*k], lazy[k]);
                X::lazyjoin(lazy[2*k+1], lazy[k]);
                flag[2*k] = flag[2*k+1] = 1;
            }
            flag[k] = 0;
            lazy[k] = X::lnil;
        }
    }

    T iadd(int l, int r, int k){
        push(k, r-l);
        if(qr <= l || ql >= r) return seg[k];
        if(ql <= l && qr >= r){
            flag[k] = 1;
            X::lazyjoin(lazy[k], val);
            return X::lazymerge(seg[k], lazy[k], r-l);
        }
        int m = (l+r)/2;
        seg[k] = X::segjoin(iadd(l, m, 2*k), iadd(m, r, 2*k+1));
        return seg[k];
    }
    
    T isum(int l, int r, int k){
        push(k, r-l);
        if(qr <= l || ql >= r) return X::qnil;
        if(ql <= l && qr >= r) return seg[k];
        int m = (l+r)/2;
        return X::segjoin(isum(l, m, 2*k), isum(m, r, 2*k+1));
    }
    
    T sum(int l, int r){
        if(l > r) return X::qnil;
        ql = l; qr = r+1;
        return isum(0, N, 1);
    }
    
    void add(int l, int r, L o){
        if(l > r) return;
        ql = l; qr = r+1; val = o;
        iadd(0, N, 1);
    }
};

template<typename T, typename L> struct lsegsum {
    static constexpr T inil = 0;
    static constexpr T qnil = 0;
    static constexpr L lnil = 0;
    static T segjoin(T a, T b){ return a+b; }
    static void lazyjoin(L &a, L b){ a+=b; }
    static T lazymerge(T a, L b, int d){ return a+b*d; }
};

