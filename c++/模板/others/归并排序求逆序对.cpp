auto merge = [&](int l, int mid, int r) {
    vector tmp(0, 0);
    int L = l, R = mid + 1;
    while (L <= mid && R <= r) {
        if (a[L] < a[R]) tmp.push_back(a[L++]);
        else {
            tmp.push_back(a[R++]);
            ans += mid - L + 1;
        }
    }
    while (L <= mid) tmp.push_back(a[L++]);
    while (R <= r) tmp.push_back(a[R++]);
    for (int i = 0; i < tmp.size(); i++) a[i + l] = tmp[i];
};

auto ms = [&](auto&& self, int l, int r) -> void {
    if (l == r) return;
    int mid = (l + r) >> 1;
    self(self, l, mid); self(self, mid + 1, r);
    merge(l, mid, r);
};
