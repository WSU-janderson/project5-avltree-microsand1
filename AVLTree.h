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

        AVLNode(const KeyType& key, const ValueType& value) : key(key), value(value), height(0), left(nullptr), right(nullptr){}

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;



    };

public:
    //done
    bool contains(const std::string& key) const;

    //done
    optional<size_t> get(const std::string& key) const;

    //
    vector<size_t> findRange( const std::string& lowKey,const std::string& highKey) const;

    //done
    size_t& operator[](const std::string& key);

    //done
    vector<std::string> keys() const;

    //done
    size_t size() const;

    //done
    size_t getHeight() const;

    //done
    AVLTree(const AVLTree& other);

    //done
    void operator=(const AVLTree& other);

    //done
    ~AVLTree();

    //done
    void destroyTree(AVLNode *node);

    //done
    friend std::ostream& operator<<(ostream& os, const AVLTree & avlTree);

    //done
    AVLTree();

    //done
    bool insert(const std::string& key, size_t value);

    //done
    bool remove(const KeyType &key);

    private:
    AVLNode* root;

    //done
    bool insertHelper(AVLNode *& current,  const std::string& key, size_t value);

    //done
    static void printInOrder(std::ostream& os, AVLNode * current);

    //done
    size_t sizeHelper(AVLNode *node) const;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

    //done
    void updateHeight(AVLNode *node);

    //done
    size_t getNodeHeight(AVLNode *node) const;

    //done
    AVLNode* dupeHelper(AVLNode* node);

    //done
    bool containsHelper(AVLNode* node, const std::string& key) const;

    //done
    optional<size_t> getHelper(AVLNode* node, const std::string& key) const;

    //done
    size_t& operatorHelper(AVLNode*& node, const std::string& key);

    //done
    void keysHelper(AVLNode* node, std::vector<std::string>& out) const;

    //done
    void findRangeHelper(AVLNode* node, const std::string& lowKey,const std::string& highKey, std::vector<size_t> &out) const;

};

#endif //AVLTREE_H
