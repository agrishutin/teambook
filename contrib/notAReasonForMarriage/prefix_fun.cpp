vector<int> pFunc(string s)
{
	int n = s.size();
	vector<int> ret(n);
	ret[0] = 0;
	for (int i = 1; i < n; ++i)
	{
		int t = ret[i-1];
		while (t && s[t] != s[i])
			t = ret[t-1];
		if (s[t] == s[i])
			t++;
		ret[i] = t;
	}
	return ret;
}
