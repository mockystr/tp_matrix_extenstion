#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<int>> m = {{1, 2, 3}, {12, 2}};

    for (const std::vector<int> &v : m)
    {
        for (int x : v)
            std::cout << x << ' ';
        std::cout << std::endl;
    }
}