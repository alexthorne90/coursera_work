#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
    public:
        int key;
        Node *parent;
        std::vector<Node *> children;

        Node() {
            this->parent = NULL;
        }

        void setParent(Node *theParent) {
            parent = theParent;
            parent->children.push_back(this);
        }
};


int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;

    std::vector<Node> nodes;
    std::vector<int> heights_array(n, 0);
    std::queue<Node*> traversal_queue;
    nodes.resize(n);
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
        {
            nodes[child_index].setParent(&nodes[parent_index]);
        }
        else
        {
            traversal_queue.push(&nodes[child_index]);
            heights_array[child_index] = 1;
        }
        nodes[child_index].key = child_index;
    }

    // Replace this code with a faster implementation
    int max_height = 0;
    while (!traversal_queue.empty())
    {
        Node *current_node = traversal_queue.front();
        traversal_queue.pop();
        if (current_node->children.size() >= 1)
        {
            for (int i = 0; i < current_node->children.size(); i ++)
            {
                traversal_queue.push(current_node->children[i]);
                heights_array[current_node->children[i]->key] =
                    (heights_array[current_node->key] + 1);
            }
        }
    }
    for (int i = 0; i < n; i ++)
    {
        if (heights_array[i] > max_height)
        {
            max_height = heights_array[i];
        }
    }

    std::cout << max_height << std::endl;
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
