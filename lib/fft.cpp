struct FFT{

    int B = 0;

    long double pi = 3.141592653589793238462643383279502884L;
    vector<vector<complex<long double> > > w;
    vector<int> invbit;

    FFT(int B_ = 0){
        enlarge(B_);
    }

    void enlarge(int B_){
        B = max(B, B_);
        while((int)w.size() <= B){
            int z = 1<<w.size(), b = w.size();
            w.resize(w.size()+1);
            w[b].resize(z);

            for(int i=0; i<z; i++) w[b][i] = polar(1.0L, pi*i/z);
            
            invbit.resize(z, 0);
            for(int i=0; i<z/2; i++){
                invbit[i] <<= 1;
                invbit[i+z/2] = invbit[i]|1;
            }
        }
    }

    void fft(vector<complex<long double> > &v, bool inv = 0){
        
        int n = v.size();
        int b = 0;
        while(1<<b < n) b++;
        n = 1<<b;
        v.resize(n, {0, 0});

        enlarge(b);

        int shift = B-b;
        for(int i=0; i<n; i++){
            if(i < invbit[i]>>shift) swap(v[i], v[invbit[i]>>shift]);
        }

        for(int r=0; r<b; r++){
            int rd = 1<<r;
            for(int i=0; i<n; i+=2*rd){
                for(int j=i; j<i+rd; j++){
                    auto tmp = w[r][j-i]*v[j+rd];
                    v[j+rd] = v[j]-tmp;
                    v[j] = v[j]+tmp;
                }
            }
        }

        if(inv){
            reverse(v.begin()+1, v.end());
            for(int i=0; i<n; i++) v[i] /= (long double)n;
        }
    }

    template<typename T> vector<T> conv(vector<T> &a, vector<T> &b, int cz=0){
        if(cz == 0) cz = a.size()+b.size();

        vector<complex<long double> > c(cz);
        int za = a.size(), zb = b.size();
        int mx = max(za, zb);
        for(int i=0; i<mx; i++){
            if(i < za) c[i] = {(long double)a[i], 0};
            if(i < zb) c[i] = {c[i].real(), (long double)b[i]};
        }
        fft(c);
        cz = c.size();
        for(int i=0; 2*i<=cz; i++){
            int j = (cz-i)%cz;
            c[i] = -(c[i]-conj(c[j]))*(c[i]+conj(c[j]))*complex<long double>(0, 1.0/4);
            c[j] = conj(c[i]);
        }

        fft(c, 1);
        vector<T> ct(c.size(), (T)0);
        for(int i=0; i<cz; i++) ct[i] = round(c[i].real());
        return ct;
    }
};

