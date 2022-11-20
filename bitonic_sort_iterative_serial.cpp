#include <iostream>
#include <vector>
#include <chrono>

enum Direction
{
    ASCENDING,
    DESCENDING
};

void compare_and_swap_asc(std::vector<int> &v, const int i, const int j)
{
    if (v[i] > v[j])
    {
        const int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

void compare_and_swap_desc(std::vector<int> &v, const int i, const int j)
{
    if (v[i] < v[j])
    {
        const int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

void compare_and_swap(std::vector<int> &v, const int i, const int j, const Direction dir)
{
    if (dir == ASCENDING)
    {
        compare_and_swap_asc(v, i, j);
    }
    else if (dir == DESCENDING)
    {
        compare_and_swap_desc(v, i, j);
    }
    else
    {
        std::cerr << "Invalid direction" << std::endl;
        exit(1);
    }
}

void bitonic_sort_kernel(std::vector<int> &v, const int p, const int q, const Direction dir)
{
    const int dist = 1 << (p - q);

    for (int i = 0; i < (int)v.size(); ++i) {
        const bool ascending = ((i >> p) & 2) == 0;

        if ((i & dist) == 0 && (v[i] > v[i | dist]) == ascending) {
            std::swap(v[i], v[i | dist]);
        }
    }
}

void bitonic_sort(std::vector<int> &v, const Direction dir)
{
    // padding
    int logN = 0;
    while ((1 << logN) < (int)v.size())
    {
        logN++;
    }
    const int N = 1 << logN;
    v.resize(N, 0);

    // bitonic sort
    for (int i = 0; i < logN; ++i) {
        for (int j = 0; j <= i; ++j) {
            bitonic_sort_kernel(v, i, j, dir);
        }
    }

}

void print_vector(const std::vector<int> &v)
{
    for (int i = 0; i < (int)v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> v(N);
    for (int i = 0; i < N; ++i)
        std::cin >> v[i];

    std::cout << "Input: ";
    print_vector(v);
    std::cout << std::endl;

    // execution
    const auto start = std::chrono::system_clock::now();
    bitonic_sort(v, ASCENDING);
    const auto end = std::chrono::system_clock::now();
    const double duration_ms = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);

    std::cout << "Output: ";
    print_vector(v);
    std::cout << std::endl;

    std::cout << "===Result===" << std::endl;
    for (int i = 0; i < N - 1; ++i)
    {
        if (v[i] > v[i + 1])
        {
            std::cout << "Failed" << std::endl;
            return 1;
        }
    }
    std::cout << "Success" << std::endl;

    std::cout << "===Performance===" << std::endl;
    std::cout << "Time: " << duration_ms << " [ms]" << std::endl;
}