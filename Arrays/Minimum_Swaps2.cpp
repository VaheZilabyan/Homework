int minimumSwaps(vector<int> arr) {
    int sz = arr.size();
    int result = 0;
    bool t;
    for (int i = 0; i < sz - 1; ++i) {
        int min = arr[i];
        int swap_index = i;
        t = true;
        for (int j = i + 1; j < sz; ++j) {
            if (arr[j] < min) {
                min = arr[j];
                swap_index = j;
                if (t == true) {
                    ++result;
                    t = false;
                }
            }
        }
        std::swap(arr[i], arr[swap_index]);
    }
    return result;
}