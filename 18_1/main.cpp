#include <iostream>
#include <cmath>
#include <sstream>

struct Node {
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    ~Node() {
         if (left) {
             delete left;
         }
         if (right) {
             delete right;
         }
    }
};

Node* readTree(std::istream& is, Node* parent = nullptr)
{
    Node* node = new Node;
    node->parent = parent;
    char c = is.peek();
    if (c >= '0' && c <= '9') {
        is >> node->val;
        return node;
    }
    is.ignore(1); // '['
    node->left = readTree(is, node);
    is.ignore(1); // ','
    node->right = readTree(is, node);
    is.ignore(1); // ']'
    return node;
}

Node* merge(Node* l, Node* r)
{
    Node* root = new Node;
    root->left = l;
    l->parent = root;
    root->right = r;
    r->parent = root;
    return root;
}

void split(Node* node)
{
    node->left = new Node;
    node->left->parent = node;
    node->right = new Node;
    node->right->parent = node;
    node->left->val = node->val / 2;
    node->right->val = std::ceil(node->val / 2.0);
}

bool isRightChild(Node* node)
{
    return node->parent->right == node;
}

bool isLeftChild(Node* node)
{
    return !isRightChild(node);
}

void explode(Node* node)
{
    Node* tmp = node;
    while (tmp->parent && isRightChild(tmp)) { tmp = tmp->parent; }
    if (tmp->parent) {
        tmp = tmp->parent->right;
        while (tmp->left) { tmp = tmp->left; }
        tmp->val += node->right->val;
    }
    tmp = node;
    while (tmp->parent && isLeftChild(tmp)) { tmp = tmp->parent; }
    if (tmp->parent) {
        tmp = tmp->parent->left;
        while (tmp->right) { tmp = tmp->right; }
        tmp->val += node->left->val;
    }
    delete node->left;
    node->left = nullptr;
    delete node->right;
    node->right = nullptr;
    node->val = 0;
}

bool trySplit(Node* node)
{
    if (!node) {
        return false;
    }
    if (!node->left && !node->right && node->val >= 10) {
        split(node);
        return true;
    }
    return trySplit(node->left) ||
           trySplit(node->right);
}

bool tryExplode(Node* node, int depth = 0)
{
    if (!node) {
        return false;
    }
    if (depth == 4 && node->left && node->right) {
        explode(node);
        return true;
    }
    return tryExplode(node->left, depth + 1) ||
           tryExplode(node->right, depth + 1);
}

int evaluate(Node* node)
{
    if (!node->left && !node->right) {
        return node->val;
    }
    return 3 * evaluate(node->left) + 2 * evaluate(node->right);
}

void printTree(Node* node)
{
    if (!node) {
        return;
    }
    if (!node->left && !node->right) {
        std::cout << node->val;
        return;
    }
    std::cout << '[';
    printTree(node->left);
    std::cout << ',';
    printTree(node->right);
    std::cout << ']';
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    Node* resultTree = readTree(ss);
    while (std::getline(std::cin, line)) {
        ss = std::stringstream(line);
        Node* rightTree = readTree(ss);
        Node* merged = merge(resultTree, rightTree);
        while (tryExplode(merged) || trySplit(merged)) {}
        resultTree = merged;
    }
    std::cout << evaluate(resultTree) << std::endl;
    delete resultTree;
}
