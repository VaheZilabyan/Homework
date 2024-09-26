int hourglassSum(vector<vector<int>> arr) {
    int sumMatrix[16]{0};
    int k = 0;
    int jf = 0;
    int jl = 2;
    int il = 2;
    for (int i = 0; i <= 3; ++i) {
        while (jl <= 5) {
            for (int j = jf; j <= jl; ++j) {
                sumMatrix[k] += arr[i][j];
            }
            sumMatrix[k] += arr[i + 1][jl - 1];
            for (int j = jf; j <= jl; ++j) {
                sumMatrix[k] += arr[il][j];
            }
            ++jf;
            ++jl;
            ++k;
        }
        ++il;
        jf = 0;
        jl = 2;
    }
    
    int maxSum = sumMatrix[0];
    for (int i = 1; i < 16; ++i) {
        if (sumMatrix[i] > maxSum) {
            maxSum = sumMatrix[i];
        }   
    }
    return maxSum;
}