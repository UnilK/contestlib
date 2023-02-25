template<typename T, typename L, template<typename, typename> typename O> struct segtree {

    using X = O<T, L>;
    int N = 1;
    vector<T> seg;

    segtree(int n=1, vector<T> v = {}, int offset=0){ init(n, v, offset); }
    void init(int n=1, vector<T> v = {}, int offset=0){
        n = max(n, (int)v.size());
        while(N < n+offset) N *= 2;
        seg.resize(2*N, (T)X::inil);
        for(int i=0; i<(int)v.size(); i++) seg[N+i+offset] = v[i];
        for(int i=N-1; i; i--) seg[i] = X::join(seg[2*i], seg[2*i+1]);
    }
    

    T sum(int l, int r){
        l += N; r += N;
        T s = X::qnil;
        while(l<=r){
            if(l&1) s = X::join(s, seg[l++]);
            if(~r&1) s = X::join(s, seg[r--]);
            l/=2; r/=2;
        }
        return s;
    }
    
    void add(int i, L o){
        i += N;
        X::drop(seg[i], o);
        for(i/=2; i; i/=2) seg[i] = X::join(seg[2*i], seg[2*i+1]);
    }
};

template<typename T, typename L> struct segsum {
    static constexpr T inil = 0;
    static constexpr T qnil = 0;
    static void drop(T &a, L b){ a += b; }
    static T join(T a, T b){ return a+b; }
};

