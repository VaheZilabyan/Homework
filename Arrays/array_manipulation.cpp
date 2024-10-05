long arrayManipulation(int n, vector<vector<int>> queries) {
    vector<long> arr(n);
    int row = queries.size();
    int j = 0;
    for (int i = 0; i < row; ++i) {
        int a = queries[i][0];
        int b = queries[i][1];
        int k = queries[i][2];
        arr[a-1] += k;
        if (b < n) {
            arr[b] -= k;
        }
    }

    long curr = 0;
    long max_num = 0;
    for (int i = 0; i < n; ++i) {
        curr += arr[i];
        max_num = max(curr, max_num);
    }
    return max_num;
}