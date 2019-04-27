#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int>> m;
    m.clear();

    long n = 123123;
    m = {{int(n), int(n), 3},
         {12, 2}};
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
            cout << m[i][j];
        cout << endl;
    }

    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
            m[i][j] += 5;
    }

    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
            cout << m[i][j];
        cout << endl;
    }

}
