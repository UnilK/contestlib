array<int, 2> exeu(int a, int b){
    int v0 = b, v1 = a, a0 = 0, a1 = 1, b0 = 1, b1 = 0;
    while(v1){
        int d = v0/v1;
        a0 -= d*a1; b0 -= d*b1; v0 -= d*v1;
        swap(v0, v1); swap(a0, a1); swap(b0, b1);
    }
    return {a0, b0};
}

