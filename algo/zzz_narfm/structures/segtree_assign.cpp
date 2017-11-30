struct node {
    long long fill, sum;
    int flag;
};

const int hfsize, treesize = hfsize << 1;

node tree[treesize];

void push(int i) {
    if (i >= hfsize - 1 || !tree[i].flag)
        return;
    int left = i * 2 + 1, right = left + 1;
    tree[left].flag = tree[right].flag = 1;
    tree[left].fill = tree[right].fill = tree[i].fill;
    tree[left].sum = tree[right].sum = tree[i].sum / 2;
    tree[i].flag = 0;
}

void change(
    int i, int l, int r, int tl, int tr, long long val) {
    if (r < tl || l > tr)
        return;
    if (l >= tl && r <= tr) {
        tree[i].flag = 1;
        tree[i].fill = val;
        tree[i].sum = val * (r - l + 1);
        return;
    }
    push(i);
    int m = (l + r) / 2, left = i * 2 + 1, right = left + 1;
    change(left, l, m, tl, tr, val);
    change(right, m + 1, r, tl, tr, val);
    tree[i].sum = tree[left].sum + tree[right].sum;
}
long long get(int i, int l, int r, int tl, int tr) {
    if (r < tl || l > tr)
        return 0;
    if (l >= tl && r <= tr)
        return tree[i].sum;
    push(i);
    int m = (l + r) / 2, left = i * 2 + 1, right = left + 1;
    return get(left, l, m, tl, tr)
        + get(right, m + 1, r, tl, tr);
}
