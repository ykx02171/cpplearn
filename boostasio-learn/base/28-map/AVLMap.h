//
// Created by secon on 2025/1/11.
//

#ifndef INC_28_MAP_AVLMAP_H
#define INC_28_MAP_AVLMAP_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

template<typename KeyType, typename ValueType>
struct AVLNode{
    KeyType key;
    ValueType value;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(const KeyType& k, const ValueType& val):key(k),value(val),height(1),left(nullptr),right(nullptr){}
};

template<typename KeyType, typename ValueType>
class AVLMap {
public:
    AVLMap():root(nullptr){}

    AVLNode<KeyType, ValueType> * GetRoot() const{
        return root;
    }

    void put(const KeyType& key, const ValueType& value){
        root = insertNode(root, key, value);
    }

    ValueType * get(const KeyType& key){
        return searchNode(root, key);
    }

    void remove(const KeyType& key){
        root = deleteNode(root, key);
    }

    std::vector<std::pair<KeyType, ValueType>> inorderTraversal() const{
        std::vector<std::pair<KeyType, ValueType>> result;
        inorderHelper(root, result);
        return result;
    }

    ~AVLMap(){
        std::function<void(AVLNode<KeyType, ValueType>*)> destroy = [&](AVLNode<KeyType, ValueType> * node){
          if(node != nullptr){
              destroy(node->left);
              destroy(node->right);
              delete node;
          }
       };
        destroy(root);
    }
private:
    void inorderHelper(AVLNode<KeyType, ValueType> * node,
                       std::vector<std::pair<KeyType, ValueType>>& result) const{
        if(node == nullptr) return;
        inorderHelper(node->left,result);
        result.emplace_back(node->key, node->value);
        inorderHelper(node->right,result);
    }

    int getHeight(AVLNode<KeyType, ValueType> * node){
        if(node == nullptr) return 0;
        return node->height;
    }

    int getBalance(AVLNode<KeyType, ValueType> * node){
        if(node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    AVLNode<KeyType, ValueType> *rightRotate(AVLNode<KeyType, ValueType> * y){
        auto * x = y->left;
        auto * T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left),getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode<KeyType, ValueType> * leftRotate(AVLNode<KeyType, ValueType> * x){
        auto * y = x->right;
        auto * T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode<KeyType, ValueType> * insertNode(AVLNode<KeyType, ValueType> * node,
                                             const KeyType& key, const ValueType& value){
        if(node == nullptr){
            return new AVLNode<KeyType, ValueType>(key, value);
        }

        if(key < node->key){
            node->left =  insertNode(node->left, key, value);
        }else if(key > node->key){
            node->right =  insertNode(node->right, key, value);
        }else{
            node->value = value;
            return node;
        }

        node->height = 1+ std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        if(balance > 1 &&  key < node->left->key){
            return rightRotate(node);
        }

        if(balance < -1 && key > node->right->key){
            return leftRotate(node);
        }

        if(balance < -1 && key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        if(balance > 1 && key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        return node;
    }

    AVLNode<KeyType, ValueType> * deleteNode(AVLNode<KeyType, ValueType> * root, const KeyType& key){
        if(root == nullptr) return root;
        if(key < root->key){
            root->left = deleteNode(root->left, key);
        }else if(key > root->key){
            root->right = deleteNode(root->right,key);
        }else{
            if((root->left == nullptr) || (root->right == nullptr)){
                auto * temp = root->left ? root->left:root->right;
                if(temp == nullptr){
                    temp = root;
                    root = nullptr;
                }else{
                    *root = *temp;
                }

                delete temp;
            }else{
                auto * temp = getMinValueNode(root->right);
                root->key = temp->key;
                root->value = temp ->value;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if(root == nullptr) return root;
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        // 4. 根据平衡因子进行旋转

        // 左左情况
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // 左右情况
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // 右右情况
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // 右左情况
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    AVLNode<KeyType, ValueType> * getMinValueNode(AVLNode<KeyType, ValueType> * node){
        auto * current = node;
        while(current->left != nullptr){
            current = current->left;
        }
        return current;
    }

    ValueType* searchNode(AVLNode<KeyType, ValueType> * node, const KeyType& key){
        if(node == nullptr) return nullptr;
        if(key == node->key){
            return &(node->value);
        }else if(key < node ->key){
            return searchNode(node->left, key);
        }else{
            return searchNode(node->right,key);
        }
    }

    AVLNode<KeyType, ValueType> * root;
};


#endif //INC_28_MAP_AVLMAP_H
