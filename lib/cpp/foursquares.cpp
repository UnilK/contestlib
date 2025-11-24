typedef array<double, 4> Quat;

Quat operator*(const Quat& lhs, const Quat& rhs){
    return {
        lhs[0]*rhs[0]-lhs[1]*rhs[1]-lhs[2]*rhs[2]-lhs[3]*rhs[3],
        lhs[0]*rhs[1]+lhs[1]*rhs[0]+lhs[2]*rhs[3]-lhs[3]*rhs[2],
        lhs[0]*rhs[2]-lhs[1]*rhs[3]+lhs[2]*rhs[0]+lhs[3]*rhs[1],
        lhs[0]*rhs[3]+lhs[1]*rhs[2]-lhs[2]*rhs[1]+lhs[3]*rhs[0]
    };
}

Quat operator/(const Quat& lhs, const double& rhs){
    Quat r = lhs;
    for(double &i : r) i /= rhs;
    return r;
}

Quat operator-(const Quat& lhs, const Quat& rhs){
    Quat r = lhs;
    for(int i=0; i<4; i++) r[i] -= rhs[i];
    return r;
}

Quat conj(const Quat& q){
    Quat r = q;
    for(int i=1; i<4; i++) r[i] = -r[i];
    return r;
}

double norm(const Quat& q){
    double sum = 0;
    for(double i : q) sum += i*i;
    return sum;
}

Quat operator/(const Quat& lhs, const Quat& rhs){
    return (lhs*conj(rhs))/norm(rhs);
}

Quat toH(const Quat& a){
    Quat best = a;
    double mind = 123;
    for(int i=0; i<(1<<4); i++){
        Quat b = a;
        for(int j=0; j<4; j++){
            if((i>>j)&1){
                b[j] = floor(b[j]);
            } else {
                b[j] = ceil(b[j]);
            }
        }
        double d = norm(a-b);
        if(d < mind){
            mind = d;
            best = b;
        }
    }
    
    Quat b = a;
    for(int j=0; j<4; j++) b[j] = floor(b[j]) + 0.5;
    double d = norm(a-b);
    if(d < mind){
        mind = d;
        best = b;
    }

    return best;
}

Quat gcd(Quat a, Quat b){
    while(norm(b) != 0){
        a = a - toH(a/b)*b;
        swap(a, b);
    }
    return a;
}

array<int, 4> four_squares(int n){

    vector<int> p;
    int nn = n;
    for(int i=2; i*i<=nn; i++){
        if(nn%i == 0){
            p.push_back(i);
            while(nn%i == 0) nn /= i;
        }
    }
    if(nn != 1) p.push_back(nn);

    nn = n;
    Quat ans = {1, 0, 0, 0};
    for(int x : p){
        
        double a = 0, b = 0;
        vector<int> sum(x, -1);
        for(long long i=0; i<x; i++){
            if(sum[i*i%x] != -1){
                a = sum[i*i%x];
                b = i;
                break;
            }
            sum[x-1-i*i%x] = i;
        }

        Quat suba = gcd({(double)x, 0, 0, 0}, {1, a, b, 0});
        while(nn%x == 0){
            ans = suba*ans;
            nn /= x;
        }
    }
    
    if(norm(ans) != n){
        return {0, 0, 0, 0};
    }


    if((int)(2*ans[0])%2 == 1){
        
        vector<Quat> units;
        
        for(int i=0; i<4; i++){
            Quat u{0, 0, 0, 0};
            u[i] = 1;
            units.push_back(u);
            u[i] = -1;
            units.push_back(u);
        }
        
        for(int i=0; i<(1<<4); i++){
            Quat u = {0.5, 0.5, 0.5, 0.5};
            for(int j=0; j<4; j++){
                if((i>>j)&1) u[j] = -0.5;
            }
            units.push_back(u);
        }

        for(Quat u : units){
            if((int)(2*(u*ans)[0])%2 == 0){
                ans = u*ans;
                break;
            }
        }
    }

    for(double &i : ans) i = abs(i);
    sort(ans.rbegin(), ans.rend());

    return {(int)ans[0], (int)ans[1], (int)ans[2], (int)ans[3]};
}
