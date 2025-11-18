/*
micah sanders-johnson
november 15 2025
HashTable
Make a HashTable using random probe
then write about the time complexity
*/

#include "AVLTree.h"
#include <algorithm>
#include <string>
#include <iostream>

size_t AVLTree::AVLNode::numChildren() const {
    size_t children = 0;
    if (right) {
        children++;
    }
    if (left) {
        children++;
    }
    return children;
}

bool AVLTree::AVLNode::isLeaf() const {
    return numChildren() == 0;
}

size_t AVLTree::AVLNode::getHeight() const {
    return height;
}

bool AVLTree::contains(const std::string& key) const {
    return containsHelper(root, key);
}

optional<size_t> AVLTree::get(const std::string& key) const {
    return getHelper(root, key);
}

size_t& AVLTree::operator[](const std::string& key) {
    return operatorHelper(root, key);
}

vector<std::string> AVLTree::keys() const {
    std::vector<std::string> result;
    keysHelper(root, result);
    return result;
}

size_t AVLTree::size() const {
    return sizeHelper(root);
}

size_t AVLTree::getHeight() const {
    if (!root) {
        return 0;
    }
    return root->getHeight();
}

AVLTree::AVLTree(const AVLTree& other) {
    root = dupeHelper(other.root);
}

void AVLTree::operator=(const AVLTree& other) {
    if (this == &other) {
        return;
    }
    destroyTree(root);
    root = dupeHelper(other.root);
}

AVLTree::~AVLTree() {
    destroyTree(root);
    root = nullptr;
}

void AVLTree::destroyTree(AVLNode* node) {
    if (!node) return;

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}

std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
    os << "{ ";
    AVLTree::printInOrder(os, avlTree.root);
    os << "}";
    return os;
}

AVLTree::AVLTree() : root(nullptr) {

}
bool AVLTree::insert(const std::string& key, size_t value) {
    if (!root) {
        root = new AVLNode(key, value);
        root->height = 0;
        return true;
    }

    return insertHelper(root, key, value);
}

bool AVLTree::remove(const KeyType &key) {
    if (!root) {
        return false;
    }

    if (key<root->key) {
        return remove(root->left, key);
    } else if (key>root->key){
        return remove(root->right, key);
    } else {
        return removeNode(root);
    }
}

bool AVLTree::insertHelper(AVLNode *& current, const std::string& key, size_t value) {
    if (!current) {
        current = new AVLNode(key, value);
        return true;
    }

    bool inserted = false;

    if (key<current->key) {
        inserted = insertHelper(current->left, key, value);
    } else if (key>current->key){
        inserted = insertHelper(current->right, key, value);
    } else {
        return false;
    }

    if (inserted) {
        updateHeight(current);
    }

    return inserted;
}

void AVLTree::printInOrder(std::ostream& os, AVLNode * current) {
    if (!current) return;
    printInOrder(os, current->left);
    os << current->key << ": " << current->value << " ";
    printInOrder(os, current->right);
}

size_t AVLTree::sizeHelper(AVLNode* node) const {
    if (!node) return 0;
    return 1 + sizeHelper(node->left) + sizeHelper(node->right);
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    if (!current) {
        return false;
    }

    if (key<current->key) {
        return remove(current->left, key);
    } else if (key>current->key){
        return remove(current->right, key);
    } else {
        return removeNode(current);
    }
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

void AVLTree::balanceNode(AVLNode *&node) {
}

void AVLTree::updateHeight(AVLNode* node) {
    node->height = 1 + std::max(getNodeHeight(node->left),getNodeHeight(node->right));
}

size_t AVLTree::getNodeHeight(AVLNode* node) const {
    if (node) {
        return node->height;
    } else {
        return 0;
    }

}

AVLTree::AVLNode* AVLTree::dupeHelper(AVLNode* node) {
    if (!node) {
        return nullptr;
    }

    AVLNode* newNode = new AVLNode(node->key, node->value);

    newNode->height = node->height;

    newNode->left = dupeHelper(node->left);
    newNode->right = dupeHelper(node->right);

    return newNode;

}

bool AVLTree::containsHelper(AVLNode* node, const std::string& key) const {
    if (!node) {
        return false;
    }

    if (key==node->key) {
        return true;
    } else if (key < node->key) {
        return containsHelper(node->left, key);
    } else {
        return containsHelper(node->right, key);
    }
}

optional<size_t> AVLTree::getHelper(AVLNode* node, const std::string& key) const {
    if (!node) {
        return nullopt;
    }

    if (key==node->key) {
        return node->value;
    } else if (key < node->key) {
        return getHelper(node->left, key);
    } else {
        return getHelper(node->right, key);
    }
}

vector<std::string> AVLTree::findRange(const std::string &lowKey, const std::string &highKey) const {
    std::vector<std::string> result;
    findRangeHelper(root, lowKey, highKey,result);
    return result;
}

void AVLTree::findRangeHelper(AVLNode* node, const std::string &lowKey, const std::string &highKey, std::vector<std::string> &out) const {
    if (!node) return;
    findRangeHelper(node->left, lowKey, highKey, out);
    if (node->key<=lowKey && node->key>=highKey) {
        out.push_back(node->key);
    }
    findRangeHelper(node->right, lowKey, highKey, out);
}



size_t& AVLTree::operatorHelper(AVLNode*& node, const std::string& key) {
    if (!node) {
        node = new AVLNode(key, 0);
        return node->value;
    }

    if (key == node->key) {
        return node->value;
    } else if (key < node->key) {
        return operatorHelper(node->left, key);
    } else {
        return operatorHelper(node->right, key);
    }
}

void AVLTree::keysHelper(AVLNode *node, std::vector<std::string> &out) const {
    if (!node) return;
    keysHelper(node->left, out);
    out.push_back(node->key);
    keysHelper(node->right, out);
}
