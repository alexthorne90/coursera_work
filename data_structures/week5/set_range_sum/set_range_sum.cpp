#include <cstdio>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    int key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
        : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex* find(Vertex*& root, int key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x) {
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x) {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

void RemoveLargestKeyAsRoot(void)
{
    if (root->left != NULL)
    {
        root->left->parent = NULL;
        root = root->left;
    }
    else
    {
        root = NULL;
    }
}

void erase(int x) {
    // Implement erase yourself
    if (root == NULL)
    {
        return;
    }

    if (find(root, x + 1) == NULL)      //splay next(x)
    {                                   //if NULL, this is removing biggest key
        if (root->key == x)
        {
            RemoveLargestKeyAsRoot();
        }
    }
    else
    {
        find(root, x);
        if (root->key != x)
        {
            return;
        }
        Vertex *l = root->left;
        Vertex *r = root->right;
        r->left = l;
        if (l != NULL)
        {
            l->parent = r;
        }
        root = r;
        r->parent = NULL;
    }
}

bool find(int x) {
    // Implement find yourself
    Vertex *v = find(root, x);
    if (v != NULL)
        return (v->key == x);
    else
        return false;
}

long long sum(int from, int to) {
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    // Complete the implementation of sum
    ans = middle->sum;
    printf("Left tree = %d  Middle = %d  Right = %d\n",
            left == NULL ? 0 : left->sum,
            middle == NULL ? 0 : middle->sum,
            right == NULL ? 0 : right->sum);
    //Vertex *merged_L_M = merge(left, middle);
    //Vertex *merged_M_R = merge(merged_L_M, right);
    left = merge(left, middle);
    root = merge(left, right);
    //root = merged_M_R;
    printf("Root sum after remerge = ",
            root == NULL ? 0 : root->sum);

    return ans;
}

const int MODULO = 1000000001;

int main(){
    int n;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
            case '+' : {
                           int x;
                           scanf("%d", &x);
                           insert((x + last_sum_result) % MODULO);
                       } break;
            case '-' : {
                           int x;
                           scanf("%d", &x);
                           erase((x + last_sum_result) % MODULO);
                       } break;
            case '?' : {
                           int x;
                           scanf("%d", &x);
                           printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
                       } break;
            case 's' : {
                           int l, r;
                           scanf("%d %d", &l, &r);
                           long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
                           printf("%lld\n", res);
                           last_sum_result = int(res % MODULO);
                       }
        }
    }
    return 0;
}
