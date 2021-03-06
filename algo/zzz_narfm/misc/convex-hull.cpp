typedef long long coord;
struct point {
    coord x, y;
    point() {}
    point(coord x, coord y)
        : x(x)
        , y(y) {}
    point(point a, point b)
        : x(b.x - a.x)
        , y(b.y - a.y) {}
};
inline coord operator*(point a, point b) {
    return a.x * b.x + a.y * b.y;
}
inline coord operator%(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
inline coord operator==(point a, point b) {
    // Warning: consider using epsilon!
    return a.x == b.x && a.y == b.y;
}

inline bool as_pair(const point& a, const point& b) {
    // Warning: consider using epsilon!
    return (a.x == b.x ? a.y < b.y : a.x < b.x);
}

vector<point> hull(vector<point> p) {
    sort(p.begin(), p.end(), as_pair);
    p.erase(unique(p.begin(), p.end()), p.end());
    sort(p.begin() + 1, p.end(), [corner=p[0]](point a, point b) {
        auto cross = point(corner, a) % point(corner, b);
        // Warning: consider using epsilon!
        return cross > 0 || (
            cross == 0 && point(a, corner) * point(a, b) < 0
        );
    });

    // Iff non strictly convex
    auto rit = p.rbegin();
    while (rit != p.rend()
        && 0 == Point(p[0], p.back()) % Point(p[0], *rit)
    ) {
        ++rit;
    }
    reverse(p.rbegin(), rit);

    vector<point> ret;
    int sz = 0;
    for (size_t i = 0; i < p.size(); ++i) {
        // Warning: consider using epsilon!
        while (sz > 1
            && point(ret[sz - 2], ret[sz - 1])
                    % point(ret[sz - 1], p[i])
                <= 0) { // < 0 <-> non-strict convex
            ret.pop_back();
            --sz;
        }
        ret.push_back(p[i]);
        ++sz;
    }

    return ret;
}
