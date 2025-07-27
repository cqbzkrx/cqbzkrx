template <class T>
constexpr vector <T> operator += (vector <T> &lhs, const vector <T> &rhs) {
    lhs.insert (lhs.end (), all(rhs));
    return lhs;
}

template <class T>
constexpr vector <T> operator + (vector <T> lhs, const vector <T> &rhs) {
    lhs += rhs;
    return lhs;
}
