const int hfsize;
struct node {
    int value;
    node *l, *r;
    node()
        : l(0)
        , r(0) {}
    node(int value)
        : value(value)
        , l(0)
        , r(0) {}
    node(int value, node* l, node* r)
        : value(value)
        , l(l)
        , r(r) {}
};
node* setValue(node* v, int l, int r, int at, int value) {
    if (l > at || r < at)
        return v;
    if (l == r)
        return new node(value);
    int m = (l + r) / 2;
    node* left = setValue(v ? v->l : 0, l, m, at, value);
    node* right = setValue(v ? v->r : 0, m + 1, r, at, value);
    return new node(
        (left ? left->value : 0) + (right ? right->value : 0),
        left, right);
}
int getsum(node* v, int l, int r, int tl, int tr) {
    if (l > tr || r < tl || !v)
        return 0;
    if (l >= tl && r <= tr)
        return v->value;
    int m = (l + r) / 2;
    return getsum(v->l, l, m, tl, tr)
        + getsum(v->r, m + 1, r, tl, tr);
}
