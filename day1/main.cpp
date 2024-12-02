#include <iostream>
#include <vector>
#include <map>

#include "my_utils.hpp"
using namespace std;

long long conv(string s)
{
    return std::stoll(s);
}

int main()
{
    vector<long long> a, b;
    string line;
    while(getline(cin, line))
    {
        vector<long long> t = split<long long>(line, conv);
        a.push_back(t[0]);
        b.push_back(t[1]);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    map<long long,long long> mp;
    for(long long i : b) mp[i]++;

    long long ans = 0;
    for(int i=0;i<(int)a.size();i++)
    {
        // ans += abs(a[i] - b[i]);
        ans += a[i] * mp[a[i]];
    }
    cout<<ans<<endl;
    return 0;
}