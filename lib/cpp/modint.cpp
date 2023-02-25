template<int MOD> struct Mint{
    
    int i;

    Mint(long long j=0) : i(j<0 ? j%MOD+MOD : j%MOD) {}
    
    int inv() const {
        int v0 = MOD, v1 = i, r0 = 0, r1 = 1;
        while(v1){
            int d = v0/v1;
            r0 -= d*r1; v0 -= d*v1;
            swap(v0, v1); swap(r0, r1);
        }
        return r0 < 0 ? r0+MOD : r0; 
    }

    Mint &operator+=(const Mint &j){
        i += j.i;
        if(i >= MOD) i -= MOD;
        return *this;
    }
    Mint &operator-=(const Mint &j){
        i -= j.i;
        if(i < 0) i += MOD;
        return *this;
    }
    Mint &operator*=(const Mint &j){
        i = (long long)i*j.i%MOD;
        return *this;
    }
    Mint &operator/=(const Mint &j){
        i = (long long)i*j.inv()%MOD;
        return *this;
    }
    
    explicit operator int() const { return i; }
    explicit operator size_t() const { return i; }
    explicit operator long long() const { return i; }
    friend Mint operator+(Mint a, const Mint &b){ return a += b; }
    friend Mint operator-(Mint a, const Mint &b){ return a -= b; }
    friend Mint operator*(Mint a, const Mint &b){ return a *= b; }
    friend Mint operator/(Mint a, const Mint &b){ return a /= b; }
    friend bool operator==(const Mint &a, const Mint &b){ return a.i == b.i; }
    friend bool operator!=(const Mint &a, const Mint &b){ return a.i != b.i; }
    friend ostream &operator<<(ostream &s, const Mint &j){ return s << j.i; }
    friend istream &operator>>(istream &s, Mint &j){ return s >> j.i; }
};

const int P = 998244353;
using mint = Mint<P>;

