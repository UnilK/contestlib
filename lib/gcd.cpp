int gcd(int a, int b){
    while(b){ a = a%b; swap(a, b); }
    return a;
}

