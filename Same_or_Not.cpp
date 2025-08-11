#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin >> n,m;
    stack<int> a;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        a.push(val);
    }

    queue<int> b;
    for (int i = 0; i < m; i++)
    {
        int val;
        cin >> val;
        b.push(val);
    }

    if (a.size() != b.size())
    {
        cout << "NO";
    }
    else
    {
        bool flag = true;
        while (!a.empty() && !b.empty())
        {
            if (a.top() != b.front())
            {
                flag = false;
                break;
            }
            a.pop();
            b.pop();
        }
        if (flag == true)
        {
            cout << "YES";
        }
        else
        {
            cout << "NO";
        }
    }

    return 0;
}