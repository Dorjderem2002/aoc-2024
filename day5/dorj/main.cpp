#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <charconv>

#include "my_utils.hpp"
using namespace std;

int conv(const string &str)
{
    int result;
    std::from_chars(str.data(), str.data() + str.size(), result);
    return result;
}

unordered_map<int,vector<int>> pre_process(const vector<int> &v, unordered_map<int,vector<int>> &mp)
{
    set<int> st;
    for(int item : v)
    {
        st.insert(item);
    }

    unordered_map<int,vector<int>> graph;
    for(int item : v)
    {
        vector<int> stay;
        for(int i : mp[item])
        {
            if(st.find(i) != st.end())
            {
                stay.push_back(i);
            }
        }
        graph[item] = std::move(stay);
    }

    return graph;
}

int main()
{
    string line;
    vector<pair<int,int>> order;
    vector<vector<int>> arr;
    unordered_map<int,vector<int>> mp;
    mp.reserve(1000);
    while(cin>>line)
    {
        if(line.size() == 5 && line[2] == '|')
        {
            string_view a(line.c_str(), 2);
            string_view b(line.c_str()+3, 2);
            // hopefully no allocations
            int res_a = 0, res_b = 0;
            std::from_chars(a.data(), a.data() + a.size(), res_a);
            std::from_chars(b.data(), b.data() + b.size(), res_b);
            order.emplace_back(res_a, res_b);
            mp[res_a].push_back(res_b);
        }
        else if(line.size() > 0)
        {
            vector<int> a = split<int>(line, conv, ',');
            arr.push_back(std::move(a));
        }
    }

    int ans1 = 0, ans2 = 0;

    for(auto &v : arr)
    {
        int m = v.size();
        int mid = v[m / 2];
        bool ok = true;

        auto graph = std::move(pre_process(v, mp));

        // problem 1
        unordered_map<int,int> completed;

        for (int i = m - 1; i >= 0; --i)
        {
            for(int parent : graph[v[i]])
            {
                if(completed.find(parent) == completed.end())
                {
                    // one of the parent hasn't completed
                    ok = false;
                    break;
                }
            }
            if(!ok) break;
            completed[v[i]] = 1;
        }

        if(ok)
        {
            ans1 += mid;
            continue;
        }

        // problem 2
        completed.clear();
        vector<int> res;

        std::function<void(int)> dfs = [&](int node) {
            completed[node] = 1;
            for(int parent : graph[node])
            {
                if(completed.find(parent) == completed.end())
                    dfs(parent);
            }
            res.push_back(node);
        };
        for(int i : v)
        {
            if(completed.find(i) == completed.end())
                dfs(i);
        }
        ans2 += res[m / 2];
    }

    cout<<"PART 1: "<<ans1<<endl;
    cout<<"PART 2: "<<ans2<<endl;
    return 0;
}










