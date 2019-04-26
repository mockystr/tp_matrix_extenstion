#include <iostream>
#include <vector>

using namespace std;

int main()
{
    long n = 123123;
    vector<vector<int>> m = {{int(n), int(n), 3},
                             {12, 2}};
    // vector<vector<int>> m;
    // if (m.empty()) {
    // m.pop_back();
    // cout << "empty\n";
    // }


    for (const std::vector<int> &v : m)
    {
        for (int x : v)
            std::cout << x << ' ';
        std::cout << std::endl;
    }
}