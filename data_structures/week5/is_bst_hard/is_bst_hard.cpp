#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void FillInOrderTraversalVector(int node, vector<Node> *result,
        const vector<Node> &tree)
{
    if (tree[node].left != -1)
    {
        FillInOrderTraversalVector(tree[node].left, result, tree);
    }
    result->push_back(tree[node]);
    if (tree[node].right != -1)
    {
        FillInOrderTraversalVector(tree[node].right, result, tree);
    }
}

bool CheckIfNodeInSubtree(int node, Node expected_node,
        const vector<Node> &tree)
{
    if (tree[node].key == expected_node.key &&
            tree[node].left == expected_node.left &&
            tree[node].right == expected_node.right)
    {
        return true;
    }
    if (tree[node].left != -1)
    {
        CheckIfNodeInSubtree(tree[node].left, expected_node, tree);
    }
    if (tree[node].right != -1)
    {
        CheckIfNodeInSubtree(tree[node].right, expected_node, tree);
    }
    return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    // Implement correct algorithm here
    if (tree.size() == 0)
        return true;
    vector<Node> result;
    FillInOrderTraversalVector(0, &result, tree);
    for (int i = 0; i < result.size() - 1; i ++)
    {
        if (result[i].key > result[i+1].key)
        {
            return false;
        }
        if (result[i].key == result[i+1].key)
        {
            if (result[i].right == -1)
            {
                return false;
            }
            if (!CheckIfNodeInSubtree(result[i].right, result[i+1], tree))
            {
                return false;
            }
        }
    }
    return true;
}

int main_with_large_stack_space() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }

    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif

    return main_with_large_stack_space();
}
