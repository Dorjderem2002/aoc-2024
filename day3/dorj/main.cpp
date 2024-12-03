#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include "my_utils.hpp"
using namespace std;

map<string, int> mp;

pair<int,int> valid(const string &s)
{
    std::regex pattern(R"(^mul\((\d{1,3}),(\d{1,3})\)$)");
    std::smatch match;
    if (std::regex_match(s, match, pattern)) {
        string a = match[1].str();
        string b = match[2].str();
        if(a.size() < 1 || a.size() > 3 || b.size() < 1 || b.size() > 3)
            return {-1, -1};
        if(a[0] == '0' || b[0] == '0')
            return {-1,-1};
        return {stoi(a), stoi(b)};
    }
    return {-1,-1};
}

int process_str(const string &s)
{
    int res = 0, n = s.size();
    for (int i = 0; i < n; ++i)
    {
        if(s.substr(i, 4) == "mul(")
        {
            for(int j=6;j<13;j++)
            {
                auto r = valid(s.substr(i, j));
                if(r.first != -1)
                {
                    res += r.first * r.second;
                    break;
                }
            }
        }
    }

    return res;
}

int main()
{
    vector<string> a;
    string s;
    while(cin>>s)
    {
        a.push_back(std::move(s));
    }
    int ans = 0;
    for(auto &i : a)
    {
        ans += process_str(i);
    }
    cout<<ans<<endl;
    return 0;
}