//
// Created by secon on 2025/1/18.
//

#ifndef INC_29_UNORDERMAP_MYHASHMAP_H
#define INC_29_UNORDERMAP_MYHASHMAP_H
#include <iostream>
#include <utility>
#include <functional>
#include <list>
#include <vector>
#include <iterator>
#include <stdexcept>

template<typename Key, typename T >
struct HashNode{
    std::pair<Key,T> data;
    HashNode* next;
    HashNode(const Key& key, const T& value):data(std::make_pair(key, value)), next(nullptr){}
};

template<typename Key, typename T, typename Hash = std::hash<Key>>
class MyHashMap {
public:

    class Iterator;
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;

    MyHashMap(size_type initial_capacity = 16, double max_load_factor = 0.75):
    bucket_count_(initial_capacity), element_count_(0), max_load_factor_(max_load_factor),
    hash_func_(Hash()){
        buckets_.resize(bucket_count_);
    }
    ~MyHashMap(){
        clear();
    }

    void clear(){
        for(size_type i = 0; i < buckets_.size(); ++i){
            HashNode<Key, T>* current_node = buckets_[i];
            while(current_node != nullptr){
                HashNode<Key, T>* temp = current_node;
                current_node = current_node->next;
                delete temp;
            }
            buckets_[i] = nullptr;
        }
        element_count_ = 0;
    }

    MyHashMap(const MyHashMap& other) = delete;
    MyHashMap& operator=(const MyHashMap& other) = delete;

    void insert(const Key& key, const T& value){
        size_type hash_value = hash_func_(key);
        size_type index = hash_value % bucket_count_;

        auto * node = buckets_[index];

        while(node != nullptr){
            if(node->data.first == key){
                node->data.second = value;
                return;
            }
            node = node->next;
        }

        auto * new_node = new HashNode<Key, T>(key, value);
        new_node->next = buckets_[index];
        buckets_[index] = new_node;
        ++element_count_;
        auto load_factor = static_cast<double>(element_count_) / bucket_count_;
        if(load_factor > max_load_factor_){
            rehash();
        }
    }
    T* find(const Key& key){
        auto hash_value = hash_func_(key);
        auto index = hash_value % bucket_count_;
        auto * node = buckets_[index];
        while(node != nullptr){
            if(node->data.first == key){
                return &(node->data.second);
            }
            node = node->next;
        }

        return nullptr;
    }
    bool erase(const Key& key){
        auto hash_value = hash_func_(key);
        auto index = hash_value %  bucket_count_;

        auto * node = buckets_[index];
        HashNode<Key, T>* prev = nullptr;
        while(node != nullptr){
            if(node->data.first == key){
                if(prev == nullptr){
                    buckets_[index] = node->next;
                }else{
                    prev->next = node->next;
                }

                delete node;
                --element_count_;
                return true;
            }

            prev = node;
            node = node->next;
        }
        return false;
    }
    size_type size() const{
        return element_count_;
    }
    bool empty() const{
        return element_count_ == 0;
    }


    Iterator begin(){
        for(size_type i = 0; i <bucket_count_; ++i){
            if(buckets_[i] != nullptr){
                return Iterator(this, i, buckets_[i]);
            }
        }

        return end();
    }
    Iterator end(){
        return Iterator(this, bucket_count_, nullptr);
    }

    class Iterator{
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<Key, T>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        Iterator(MyHashMap* map, size_type bucket_index, HashNode<Key, T>* node):
        map_(map), bucket_index_(bucket_index), current_node_(node){

        }
        reference operator*() const{
            if(current_node_ == nullptr){
                throw std::out_of_range("Iterator out of range");
            }
            return static_cast<value_type &>(current_node_->data);
        }
        pointer operator->() const{
            if(current_node_ == nullptr){
                throw std::out_of_range("Iterator out of range");
            }
            return &(current_node_->data);
        }

        Iterator& operator++(){
            advance();
            return *this;
        }
        Iterator operator++(int){
            Iterator temp = *this;
            advance();
            return temp;
        }

        bool operator==(const Iterator& other) const{
            return map_ == other.map_ && bucket_index_ == other.bucket_index_
            && current_node_ == other.current_node_;
        }
        bool operator != (const Iterator& other) const{
            return !(*this == other);
        }
    private:
        MyHashMap* map_;
        size_type bucket_index_;
        HashNode<Key, T>* current_node_;
        void advance(){
            if(current_node_ != nullptr){
                current_node_ = current_node_->next;
            }
           while(current_node_ == nullptr){
               if(bucket_index_ +1  < map_->bucket_count_){
                   ++bucket_index_;
                   current_node_ = map_->buckets_[bucket_index_];
               }else if(bucket_index_ +1  == map_->bucket_count_){
                   ++bucket_index_;
                   break;
               }
           }
        }
    };

private:
    std::vector<HashNode<Key, T>*> buckets_;
    size_type bucket_count_;
    size_type element_count_;
    double max_load_factor_;
    Hash hash_func_;
    void rehash(){
        auto new_bucket_count = bucket_count_*2;
        std::vector<HashNode<Key,T>*> new_buckets(new_bucket_count,nullptr);
        for(size_type i = 0; i < buckets_.size(); ++i){
            auto * node = buckets_[i];
            while(node != nullptr){
                auto * next_node = node->next;
                auto new_index = hash_func_(node->data.first) % new_bucket_count;
                node->next = new_buckets[new_index];
                new_buckets[new_index] = node;
                node = next_node;
            }
        }

        buckets_ = std::move(new_buckets);
        bucket_count_ = new_bucket_count;
    }
};


#endif //INC_29_UNORDERMAP_MYHASHMAP_H
