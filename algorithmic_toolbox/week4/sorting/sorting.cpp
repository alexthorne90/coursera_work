#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

using std::vector;
using std::swap;

typedef struct part3 {
    int part_l;
    int part_r;
} part3;

int partition2(vector<int> &a, int l, int r) {
    int x = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    int m = partition2(a, l, r);

    randomized_quick_sort(a, l, m - 1);
    randomized_quick_sort(a, m + 1, r);
}

part3 partition3(vector<int> &a, int l, int r)
{
    int x = a[l];
    int j = l;
    part3 partition;
    partition.part_l = l;
    partition.part_r = l;
    //for (int i = l + 1; i <= r; i++) {
    //    if (a[i] <= x) {
    //        j++;
    //        swap(a[i], a[j]);
    //    }
    //}
    //std::cout << "\nInitial Array:  ";
    for (int i = l; i < r; i ++)
    {
        //std::cout << a[i] << " ";
    }
    //std::cout << "\n";
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < x) {
            partition.part_l ++;
            partition.part_r ++;
            //std::cout << "A[" << i << " < " << x;
            for (int i2 = i; i2 > partition.part_l; i2 --)
                swap(a[i2], a[i2 - 1]);
        }
        else if (a[i] == x)
        {
            partition.part_r ++;
            swap(a[i], a[partition.part_r]);
        }
    }
    swap(a[l], a[partition.part_l]);
    //std::cout << "Final Array:  ";
    //for (int i = l; i <= r; i ++)
    //{
    //    std::cout << a[i] << " ";
    //}
    //std::cout << "\n\n";
    return partition;
}

void randomized_quicksort3(vector<int> &a, int l, int r)
{
    //std::cout << "New quicksort call\n";
    if (l >= r) {
        //std::cout << "L >= r, finished \n";
        return;
    }

    int k = l + rand() % (r - l + 1);
    //std::cout << "\nK = " << k << "\n";
    //int k = l;
    swap(a[l], a[k]);
    //std::cout << "\nPartition3 from " << l << " to " << r << " on array: ";
    //for (int i = l; i <= r; i ++)
    //    std::cout << a[i] << " ";
    //std::cout << "\n";
    part3 m = partition3(a, l, r);

    //std::cout << "Recursive call with l = " << l << " and r = " << (m.part_l - 1);
    randomized_quicksort3(a, l, m.part_l - 1);
    //std::cout << "Recursive call with l = " << (m.part_r + 1) << " and r = " << r;
    randomized_quicksort3(a, m.part_r + 1, r);
}

void test_sorting(void)
{
    while (1)
    {
        int n = rand() % (5);
        vector<int> arr_slow(n);
        vector<int> arr_fast(n);
        std::cout << "\n" << n << "\n";
        for (int i = 0; i < n; i ++)
        {
            int x = rand() % 10;
            arr_slow[i] = x;
            arr_fast[i] = x;
            std::cout << x << " ";
        }

        randomized_quick_sort(arr_slow, 0, arr_slow.size() - 1);
        randomized_quicksort3(arr_fast, 0, arr_fast.size() - 1);

        std::cout << "\nSlow:  ";
        for (int i = 0; i < n; i ++)
        {
            std::cout << arr_slow[i] << " ";
        }
        std::cout << "\nFast:  ";
        for (int i = 0; i < n; i ++)
        {
            std::cout << arr_fast[i] << " ";
        }

        for (int i = 0; i < n; i ++)
        {
            assert(arr_slow[i] == arr_fast[i]);
        }
    }
}

int main() {
    //test_sorting();
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quicksort3(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
