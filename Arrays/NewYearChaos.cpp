void minimumBribes(vector<int> q) {
    int sz = q.size();
    int p1 = 1;
    int p2 = 2;
    int p3 = 3;
    int ans = 0;
    for(int i = 0; i < sz; ++i) {
        if (q[i] == p1) {
            p1 = p2;
            p2 = p3;
            ++p3;
        } else if (q[i] == p2) {
            ++ans;
            p2 = p3;
            ++p3;
        } else if (q[i] == p3) {
            ans += 2;
            ++p3;
        } else {
            cout << "Too chaotic" << endl;
            return;
        }
    }
    cout << ans << endl;
}