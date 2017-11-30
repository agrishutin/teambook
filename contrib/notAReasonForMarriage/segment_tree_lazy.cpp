#define left morkva
#define right svekolka
long long sum[treesize];
int left[treesize], right[treesize];
int tsz = 0;
void change(int &t, int l, int r, int at, long long value)
{
    if (l > at || r < at)
        return;
    if (t == -1)
        t = tsz++;
    if (l == r)
        return void(sum[t] = value);
    int m = (l+r)/2;
    change(left[t], l, m, at, value);
    change(right[t], m+1, r, at, value);
    sum[t] = 0;
    if (left[t] != -1)
        sum[t] += sum[left[t]];
    if (right[t] != -1)
        sum[t] += sum[right[t]];
}
long long get(int t, int l, int r, int tl, int tr)
{
    if (l > tr || r < tl || t == -1)
        return 0;
    if (l >= tl && r <= tr)
        return sum[t];
    int m = (l+r)/2;
    return get(left[t], l, m, tl, tr) + get(right[t], m+1, r, tl, tr);
}
