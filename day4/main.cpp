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
                break;
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

int cross_count(const vector<string> &a, int y, int x)
{
    string s1 = {a[y][x], a[y+1][x+1], a[y+2][x+2]};
    string s2 = {a[y+2][x], a[y+1][x+1], a[y][x+2]};

    if((s1 == "MAS" || s1 == "SAM") && (s2 == "MAS" || s2 == "SAM"))
        return 1;
    return 0;
}

int main()
{
    vector<string> a;
    string line;
    while(cin>>line)
    {
        a.push_back(std::move(line));
    }
    int n = a.size(), ans1 = 0, ans2 = 0;
    vector<string> res(n);
    for (int i = 0; i < n - 2; ++i)
    {
        int m = a[i].size();
        res[i] = string(m, '.');
        for(int j=0;j<m - 2;j++)
        {
            int t = count(a, res, i, j);
            ans1 += t;
            ans2 += cross_count(a, i, j);
        }
    }
    // for(auto &s : res) cout<<s<<endl;
    cout<<"PART 1: "<<ans1<<endl;
    cout<<"PART 2: "<<ans2<<endl;
    return 0;
}