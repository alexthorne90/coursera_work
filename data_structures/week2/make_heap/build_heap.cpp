#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
    private:
        vector<int> data_;
        vector< pair<int, int> > swaps_;

        void WriteResponse() const {
            cout << swaps_.size() << "\n";
            for (int i = 0; i < swaps_.size(); ++i) {
                cout << swaps_[i].first << " " << swaps_[i].second << "\n";
            }
        }

        void ReadData() {
            int n;
            cin >> n;
            data_.resize(n);
            for(int i = 0; i < n; ++i)
                cin >> data_[i];
        }

        void SiftDown(int parent_index)
        {
            bool sift_needed = true;

            while (sift_needed)
            {
                int left_child_index = 2 * parent_index + 1;
                int right_child_index = 2 * parent_index + 2;
                int min_index = parent_index;
                sift_needed = false;
                if ((left_child_index < data_.size()) &&
                        (data_[left_child_index] < data_[min_index]))
                {
                    min_index = left_child_index;
                }
                if ((right_child_index < data_.size()) &&
                        (data_[right_child_index] < data_[min_index]))
                {
                    min_index = right_child_index;
                }
                if (min_index != parent_index)
                {
                    swap(data_[parent_index], data_[min_index]);
                    swaps_.push_back(make_pair(parent_index, min_index));
                    sift_needed = true;
                    parent_index = min_index;
                }
            }
        }

        void GenerateSwaps() {
            swaps_.clear();
            // The following naive implementation just sorts
            // the given sequence using selection sort algorithm
            // and saves the resulting sequence of swaps.
            // This turns the given array into a heap,
            // but in the worst case gives a quadratic number of swaps.
            //
            // TODO: replace by a more efficient implementation
            //for (int i = 0; i < data_.size(); ++i)
            //    for (int j = i + 1; j < data_.size(); ++j) {
            //        if (data_[i] > data_[j]) {
            //            swap(data_[i], data_[j]);
            //            swaps_.push_back(make_pair(i, j));
            //        }
            //    }
            for (int i = std::floor(data_.size() / 2) - 1; i >= 0; i --)
            {
                SiftDown(i);
            }
        }

    public:
        void Solve() {
            ReadData();
            GenerateSwaps();
            WriteResponse();
        }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
