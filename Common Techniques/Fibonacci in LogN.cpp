vector<vector<long long>> identityMatrix({
    {1, 0}, 
    {0, 1}
});
vector<vector<long long>> result({
    {0, 0},
    {0, 0}
});
void multiply(vector<vector<long long>> a, vector<vector<long long>> b){
    for(auto &i : result){
        for(auto &j : i){
            j = 0;
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                result[i][k] += a[i][j] * b[j][k];
                result[i][k] %= MOD;
            }
        }
    }
}
void matrixExpo(vector<vector<long long>> matrix, long long n){
    if(n == 0){
        result = identityMatrix;
        return;
    }
    matrixExpo(matrix, n / 2);
    multiply(result, result);
    if(n & 1){
        multiply(result, matrix);
    }
}
long long nthFibonacciNumber(long long n){ // n <= 1e18, F0 = 0, F1 = 1, F2 = 1
    if(n <= 1)
        return n;
    vector<vector<long long>> baseMatrix({
        {1, 1},
        {1, 0}
    });
    multiply(baseMatrix, identityMatrix);
    matrixExpo(baseMatrix, n - 1);
    return result[0][0];
}