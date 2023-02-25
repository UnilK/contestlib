mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
int rnd(){ return rng32()>>1; }
 
template<typename T>
struct treap {
 
    struct node {
        int l = 0, r = 0, z, w;
        T v;
        node() : z(0), w(rnd()) {}
        node(T val) : z(1), w(rnd()), v(val) {}
    };
 
    vector<node> nd;
 
    treap(){ nd.resize(1); }
 
    int create(T val){
        nd.emplace_back(val);
        return nd.size()-1;
    }
 
    int create(const vector<T> &v){
        if(v.empty()) return 0;
        int root = create(v[0]);
        for(unsigned i=1; i<v.size(); i++) root = mrg(root, create(v[i]));
        return root;
    }
 
    void drop(int c){}
    
    void push(int c){}
    
    void update(int c){
        nd[c].z = nd[nd[c].r].z + nd[nd[c].l].z + 1;
    }

    node &operator[](int c){ return nd[c]; }
 
    int mrg(int l, int r){
        if(!l) return r;
        if(!r) return l;
        push(l); push(r);
        int c;
        if(nd[l].w > nd[r].w){
            nd[l].r = mrg(nd[l].r, r);
            c = l;
        } else {
            nd[r].l = mrg(l, nd[r].l);
            c = r;
        }
        update(c);
        return c;
    }
 
    // split to [0, k] [k+1, n[
    void cut(int c, int &l, int &r, int k){
 
        if(!c){ l = 0; r = 0; return; }
        push(c);
        if(k >= nd[nd[c].l].z){
            l = c;
            cut(nd[c].r, nd[l].r, r, k-nd[nd[c].l].z-1);
            update(l);
        } else {
            r = c;
            cut(nd[c].l, l, nd[r].l, k);
            update(r);
        }
    }
 
    array<int, 2> cut(int c, int k){
        int l = 0, r = 0;
        cut(c, l, r, k);
        return {l, r};
    }
 
    void tour(int c, vector<T> &v){
        if(!c) return;
        push(c);
        tour(nd[c].l, v);
        v.push_back(nd[c].v);
        tour(nd[c].r, v);
    }
 
    vector<T> vec(int i){
        vector<T> v;
        tour(i, v);
        return v;
    }
 
    // [0, ql-1] [ql, qr] [qr+1, n[
    array<int, 3> pick(int root, int ql, int qr){
        auto [x, r] = cut(root, qr);
        auto [l, m] = cut(x, ql-1);
        return {l, m, r};
    }
 
    int glue(int l, int m, int r){
        return mrg(mrg(l, m), r);
    }
};

