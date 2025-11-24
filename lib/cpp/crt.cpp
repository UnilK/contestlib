long long crt(int a, int b, int x, int y){
    // a*c + b*d = gcd(a, b), assume gcd(a, b) = 1
    auto [c, d] = exeu(a, b);
    // return x + a * c * (y - x);
    return x + ((long long)c*(y-x)%b + b)%b*a;
}
