#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <print>
#include <source_location>
#include <sstream>
#include <string_view>

#include "my_utils.hpp"
using namespace std;

#define PROFILE(body)                                                          \
    do {                                                                       \
        auto const& loc = std::source_location::current();                     \
        auto const start = std::chrono::high_resolution_clock::now();          \
        body();                                                                \
        auto const end = std::chrono::high_resolution_clock::now();            \
        auto const duration =                                                  \
            std::chrono::duration_cast<std::chrono::microseconds>(end -        \
                                                                  start);      \
        std::puts(std::format("Time taken in {0}:{1}: {2} us",                 \
                              loc.function_name(),                             \
                              loc.line(),                                      \
                              duration.count())                                \
                      .c_str());                                               \
    } while (0)

long long conv(const string &s)
{
    return stoll(s);
}

int main()
{
    vector<string> s;
    string line;
    while(getline(cin, line))
    {
        if(line.size())
            s.push_back(std::move(line));
    }
    int n = s.size();
    vector<long long> res(n);
    vector<vector<long long>> a(n);

    for(int i=0;i<n;i++)
    {
        vector<long long> t = std::move(split<long long>(s[i], conv));
        res[i] = t[0];
        t.erase(t.begin());
        a[i] = std::move(t);
    }

    std::function<long long(vector<long long>&, int, long long, long long, bool)> solve = 
    [&](vector<long long> &aa, int i, long long curr, long long target, bool hard) {
        if(curr == target) return target;
        if(i == static_cast<long long>(aa.size()) || curr > target) return 0LL;

        if(solve(aa, i + 1, curr * aa[i], target, hard)) return target;
        if(solve(aa, i + 1, curr + aa[i], target, hard)) return target;
        if(hard)
        {
            string s_curr = to_string(curr) + to_string(aa[i]);
            if(s_curr.size() > to_string(target).size()) return 0LL;
            if(solve(aa, i + 1, stoll(s_curr), target, hard)) return target;
        }
        return 0LL;
    };

    long long ans1 = 0, ans2 = 0;
    PROFILE([&]() {
    for(int i=0;i<n;i++)
        {
            ans1 += solve(a[i], 1, a[i][0], res[i], false);
        }
    });
    PROFILE([&]() {
        for(int i=0;i<n;i++)
        {
            ans2 += solve(a[i], 1, a[i][0], res[i], true);
            
            
        }
    });

    cout<<"PART 1: "<<ans1<<endl;
    cout<<"PART 2: "<<ans2<<endl; 
    return 0;
}