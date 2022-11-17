mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

double rnd(){
    return uniform_real_distribution<double>(0, 1)(rng32);
}
int rnd(int a, int b){
    return uniform_int_distribution<int>(a, b)(rng32);
}

