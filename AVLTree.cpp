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

AVLTree::AVLTree() : root(nullptr) {

}

AVLTree::AVLTree(const AVLTree& other) {
    root = dupeHelper(other.root);
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

bool AVLTree::insert(const std::string& key, size_t value) {
    return insertHelper(root, key, value);
}

bool AVLTree::insertHelper(AVLNode *& current, const std::string& key, size_t value) {
    if (!root) {
        root = new AVLNode(key, value);
        root->height = 0;
        return true;
    }


    if (!current) {
        current = new AVLNode(key, value);
        return true;
    }

    updateHeight(current);

    if (key<current->key) {
        return insertHelper(current->left, key, value);
    } else if (key>current->key){
        return insertHelper(current->right, key, value);
    } else {
        return false;
    }

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

size_t AVLTree::getHeight() const {
    if (!root) {
        return 0;
    }
    return root->getHeight();
}

size_t AVLTree::sizeHelper(AVLNode* node) const {
    if (!node) return 0;
    return 1 + sizeHelper(node->left) + sizeHelper(node->right);
}

size_t AVLTree::size() const {
    return sizeHelper(root);
}

void AVLTree::printInOrder(std::ostream& os, AVLNode * current) {
    if (!current) return;
    printInOrder(os, current->left);
    os << current->key << ": " << current->value << " ";
    printInOrder(os, current->right);
}

std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree) {
    os << "{ ";
    AVLTree::printInOrder(os, avlTree.root);
    os << "}";
    return os;
}
