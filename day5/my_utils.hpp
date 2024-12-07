#pragma once

#include <functional>
#include <cstring>

using namespace std;

template<typename T>
vector<T> split(const string &s, const std::function<T(string)> &convert, const char del)
{
    vector<T> res;
    int n = s.size();
    string val;
    for (int i = 0; i < n; ++i)
    {
        if(s[i] == del)
        {
            if(val.size() > 0) res.push_back(convert(val));
            val = "";
            continue;
        }
        val += s[i];
    }
    if(val.size()) res.push_back(convert(val));
    return res;
}