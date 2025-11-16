/*
micah sanders-johnson
november 15 2025
Avl tree
*/

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;

        size_t getHeightHelper(AVLNode* current) const;


    };

public:




    private:
    AVLNode* root;

    bool insertHelper(AVLNode *&current,  const std::string& key, size_t value);

    bool insert(const std::string& key, size_t value);

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

    bool contains(const std::string& key) const;

    optional<size_t> get(const std::string& key) const;

    size_t& operator[](const std::string& key);

    vector<std::string> keys() const;

    size_t size() const;

    size_t getHeight() const;

    AVLTree(const AVLTree& other);

    void operator=(const AVLTree& other);

    ~AVLTree();

    friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);
};

#endif //AVLTREE_H
