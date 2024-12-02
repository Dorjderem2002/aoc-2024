#include <iostream>
#include <vector>
#include <map>

#include "my_utils.hpp"
using namespace std;

int conv(const string &s)
{
    return std::stoi(s);
}

int main()
{
    vector<vector<int>> a;
    string line;
    while(getline(cin, line))
    {
        vector<int> t = split<int>(line, conv);
        a.push_back(std::move(t));
    }
    int n = a.size();
    int ans = 0;
    for (auto &v : a)
    {
        for(int i=0;i<(int)v.size();++i)
        {
            vector<int> t = v;
            t.erase(t.begin() + i);
            vector<int> b = t, c = t;
            sort(b.begin(), b.end());
            sort(c.begin(), c.end());
            reverse(c.begin(), c.end());
            bool ok = true;
            if(t != b && t != c)
            {
                ok = false;
            }
            int m = t.size();
            for(int j=1;j<m;++j)
            {
                int diff = abs(t[j] - t[j-1]);
                if(diff < 1 || diff > 3)
                {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                ans++;
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}