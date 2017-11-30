const int triesize, alph;
struct node {
    int p, pch;
    int link, term, upterm;
    int next[alph], go[alph];
};
node t[triesize];
int tsz = 0;

int mkNode(int p, int pch) {
    t[tsz].p = p;
    t[tsz].pch = pch;
    t[tsz].link = t[tsz].upterm = -1;
    memset(t[tsz].next, -1, sizeof t[tsz].next);
    memset(t[tsz].go, -1, sizeof t[tsz].go);
    t[tsz].term = 0;
    return tsz++;
}

void addWord(string s) {
    int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int c = s[i] - '0';
        if (t[v].next[c] == -1)
            t[v].next[c] = mkNode(v, c);
        v = t[v].next[c];
    }
    t[v].term = 1;
}

int q[triesize];
void bfs() {
    int ql = 0, qr = 0;
    q[qr++] = 0;
    t[0].link = 0;
    t[0].upterm = 0;
    for (int i = 0; i < alph; ++i)
        t[0].go[i] = max(t[0].next[i], 0);
    while (ql < qr) {
        int v = q[ql++];
        for (int i = 0; i < alph; ++i) {
            int u = t[v].next[i];
            if (u == -1)
                continue;
            t[u].link = (v ? t[t[v].link].go[i] : 0);
            t[u].upterm
                = (t[t[u].link].upterm || t[u].term ? 1 : 0);
            for (int j = 0; j < alph; ++j)
                t[u].go[j]
                    = (t[u].next[j] == -1 ? t[t[u].link].go[j]
                                          : t[u].next[j]);
            q[qr++] = u;
        }
    }
}
