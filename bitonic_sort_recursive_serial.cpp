#include <iostream>
#include <vector>
#include <chrono>


enum Direction { ASCENDING, DESCENDING };


void compare_and_swap_asc(std::vector<int> &v, const int i, const int j) {
    if (v[i] > v[j]) {
        const int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

void compare_and_swap_desc(std::vector<int> &v, const int i, const int j) {
    if (v[i] < v[j]) {
        const int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }
}

void compare_and_swap(std::vector<int> &v, const int i, const int j, const Direction dir) {
    if (dir == ASCENDING) {
        compare_and_swap_asc(v, i, j);
    } else if (dir == DESCENDING) {
        compare_and_swap_desc(v, i, j);
    } else {
        std::cerr << "Invalid direction" << std::endl;
        exit(1);
    }
}

void bitonic_merge_rec(std::vector<int> &v, const int low, const int high, const Direction dir) {
    if (high - low <= 1) {
        // leaf of recursion
        return;
    }
    const int mid = (high + low) / 2;
    const int offset = high - mid;
    for (int i = low; i < mid; ++i) {
        compare_and_swap(v, i, i + offset, dir);
    }
    bitonic_merge_rec(v, low, mid, dir);
    bitonic_merge_rec(v, mid, high, dir);
}

void bitonic_sort_rec(std::vector<int> &v, const int low, const int high, const Direction dir) {
    if (high - low <= 1) {
        return;
    }
    const int mid = (high + low) / 2;
    bitonic_sort_rec(v, low, mid, ASCENDING);
    bitonic_sort_rec(v, mid, high, DESCENDING);

    bitonic_merge_rec(v, low, high, dir);
}

void bitonic_sort(std::vector<int> &v, const Direction dir) {
    bitonic_sort_rec(v, 0, (int)v.size(), dir);
}

void print_vector(const std::vector<int> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int N;
    std::cin >> N;
    std::vector<int> v(N);
    for (int i = 0; i < N; ++i) std::cin >> v[i];

    std::cout << "Input: ";
    print_vector(v);
    std::cout << std::endl;

    // execution
    const auto start = std::chrono::system_clock::now();
    bitonic_sort(v, ASCENDING);
    const auto end= std::chrono::system_clock::now();
    const double duration_ms = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);

    std::cout << "Output: ";
    print_vector(v);
    std::cout << std::endl;

    std::cout << "===Result===" << std::endl;
    for (int i = 0; i < N - 1; ++i) {
        if (v[i] > v[i + 1]) {
            std::cout << "Failed" << std::endl;
            return 1;
        }
    }
    std::cout << "Success" << std::endl;

    std::cout << "===Performance===" << std::endl;
    std::cout << "Time: " << duration_ms << " [ms]" << std::endl;
}