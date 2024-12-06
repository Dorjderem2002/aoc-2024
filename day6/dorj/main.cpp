#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "my_utils.hpp"
using namespace std;


int main()
{
    vector<string> a;
    a.reserve(1000);
    string line;
    while(cin>>line)
    {
        a.push_back(std::move(line));
    }
    int n = a.size(), m = a[0].size();
    int y=-1, x=-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(a[i][j] == '^')
            {
                y = i;
                x = j;
                break;
            }
        }
        if(y+x>=0) break;
    }
    int ans1 = 0, ans2 = 0;
    vector<vector<vector<int>>> path(n, vector<vector<int>>(m, vector<int>(4, 0)));
    vector<pair<int,pair<int,int>>> visited;
    visited.reserve(100000);
    std::function<int(int, int, int)> dfs = [&](int y, int x, int d){
        if(path[y][x][d])
            return -1;
        path[y][x][d] = 1;
        visited.push_back({y, {x, d}});
        const int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
        int ny = y + dir[d][0];
        int nx = x + dir[d][1];
        if(ny < 0 || nx < 0 || ny >= n || nx >= m)
            return 1;
        if(a[ny][nx] == '#')
        {
            d = (d + 1) % 4;
            ny = y;
            nx = x;
        }
        return dfs(ny, nx, d);
    };
    auto start = std::chrono::system_clock::now();
    dfs(y, x, 0);
    for(int i=0;i<n;i++) 
    {
        for(int j=0;j<m;j++) 
        {
            ans1 += min(1, path[i][j][0] + path[i][j][1] + path[i][j][2] + path[i][j][3]);
        }
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    cout<<"PART 1: "<<ans1<<" - took: "<<elapsed.count()<<"ms"<<endl;
    auto path_clear = [&]() {
        for(auto &[i, p] : visited)
        {
            int j = p.first;
            int k = p.second;
            path[i][j][k] = 0;
        }
        visited.clear();
    };
    start = std::chrono::system_clock::now();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if(a[i][j] == '.')
            {
                a[i][j] = '#';
                path_clear();
                int pos = dfs(y, x, 0);
                if(pos == -1) ans2++;
                a[i][j] = '.';
            }
        }
    }
    end = std::chrono::system_clock::now();
    elapsed = end - start;
    cout<<"PART 2: "<<ans2<<" - took: "<<elapsed.count()<<"ms"<<endl;

    return 0;
}