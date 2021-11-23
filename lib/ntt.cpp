template<int MOD, int U> struct NTT {

    int B = 0;
    vector<vector<int> > w;
    vector<int> invbit;

    NTT(int B_) : B(B_), w(B_), invbit(1<<B_, 0) {
        
        w[B-1].resize(1<<(B-1));
        w[B-1][0] = 1;
        int u = pwr(U, (MOD-1)>>B);
        for(int i=1; i<(1<<(B-1)); i++) w[B-1][i] = (long long)w[B-1][i-1]*u%MOD;
        if(B>1) invbit[1] = 1;

        for(int b=B-2; b>=0; b--){
            int n = 1<<b, nn = 1<<(B-b-1);
            w[b].resize(n);
            for(int i=0; i<nn; i++){
                invbit[i] <<= 1;
                invbit[i+nn] = invbit[i]|1;
            }
            for(int i=0; i<n; i++) w[b][i] = w[b+1][2*i];
        }
    }

    int pwr(int a, int b){
        int p = 1;
        for(;b; b/=2){
            if(b&1) p = (long long)p*a%MOD;
            a = (long long)a*a%MOD;
        }
        return p;
    }
    
    int div(int x){
        int v0 = MOD, v1 = x, r0 = 0, r1 = 1;
        while(v1){
            int d = v0/v1;
            r0 -= d*r1; v0 -= d*v1;
            swap(v0, v1); swap(r0, r1);
        }
        return r0 < 0 ? r0+MOD : r0; 
    }

    void ntt(vector<int > &v, bool inv = 0){
        
        int n = v.size();
        int b = 0;
        while(1<<b < n) b++;
        
        n = 1<<b;
        v.resize(n, 0);

        int shift = B-b;
        for(int i=0; i<n; i++){
            if(i < invbit[i]>>shift) swap(v[i], v[invbit[i]>>shift]);
        }

        for(int r=0; r<b; r++){
            int rd = 1<<r;
            for(int i=0; i<n; i+=2*rd){
                for(int j=i; j<i+rd; j++){
                    long long tmp = (long long)w[r][j-i]*v[j+rd];
                    v[j+rd] = (v[j]-tmp)%MOD;
                    v[j] = (v[j]+tmp)%MOD;
                }
            }
        }

        for(int i=0; i<n; i++) if(v[i] < 0) v[i] += MOD;
        
        if(inv){
            int invn = div(n);
            reverse(v.begin()+1, v.end());
            for(int i=0; i<n; i++) v[i] = (long long)v[i]*invn%MOD;
        }
    }

    template<typename T> vector<T> conv(vector<T> &a, vector<T> &b, int n=0){
        
        if(n == 0) n = a.size()+b.size();

        vector<int> aa(n, 0), bb(n, 0);
        int za = a.size(), zb = b.size();
        for(int i=0; i<za; i++) aa[i] = a[i];
        for(int i=0; i<zb; i++) bb[i] = b[i];

        ntt(aa);
        ntt(bb);

        n = aa.size();
        for(int i=0; i<n; i++) aa[i] = (long long)aa[i]*bb[i]%MOD;

        ntt(aa, 1);
        
        vector<T> c(n, (T)0);
        for(int i=0; i<n; i++) c[i] = aa[i];

        return c;
    }
};

