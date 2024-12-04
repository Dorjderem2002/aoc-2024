#include <iostream>
#include <vector>
#include <map>

#include "my_utils.hpp"
using namespace std;

int count(const vector<string> &a, vector<string> &b, int y, int x)
{
    int res = 0;
    int n = a.size(), m = a[y].size();
    const int dir[][2] = {{1, 1}, {1, 0}, {0, 1}, {-1, -1}, {-1, 0}, {0, -1}, {-1, 1}, {1, -1}};

    for(auto d : dir)
    {
        string s;
        for(int i=0;i<4;++i)
        {
            int ny = y + d[0] * i;
            int nx = x + d[1] * i;
            if(ny > n || nx > m)
                continue;
            s += a[ny][nx];
        }
        if(s == "XMAS")
        {
            for(int i=0;i<4;++i)
            {
                int ny = y + d[0] * i;
                int nx = x + d[1] * i;
                b[ny][nx] = a[ny][nx];
            }
            res++;
        }
    }
    return res;
}

int main()
{
    vector<string> a;
    string line;
    while(cin>>line)
    {
        a.push_back(std::move(line));
    }
    int n = a.size(), ans = 0;
    vector<string> res(n);
    for (int i = 0; i < n; ++i)
    {
        int m = a[i].size();
        res[i] = string(m, '.');
        for(int j=0;j<m;j++)
        {
            int t = count(a, res, i, j);
            ans += t;
        }
    }
    for(auto &s : res) cout<<s<<endl;
    cout<<ans<<endl;
    return 0;
}