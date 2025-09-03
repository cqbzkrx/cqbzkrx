template <class T>
constexpr ostream & operator << (ostream &out, const pair <T, T> &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

template <class T>
constexpr ostream & operator << (ostream &out, const vector <T> &a) {
    for (auto &v : a) out << v << " ";
    return out;
}
