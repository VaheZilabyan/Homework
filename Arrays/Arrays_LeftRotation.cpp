vector<int> rotLeft(vector<int> a, int d) {
    vector<int> res;
    for(int i = d; i < a.size(); ++i) {
        res.push_back(a[i]);
    }
    for(int i = 0; i < d; ++i) {
        res.push_back(a[i]);
    }
    return res;
}