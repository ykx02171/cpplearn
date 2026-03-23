//
// Created by secon on 2024/12/28.
//

#ifndef INC_27_DEQUE_DEQUE_H
#define INC_27_DEQUE_DEQUE_H
#include <iostream>

template<typename T>
class Deque {
private:
    T* buffer;
    std::size_t capacity;
    std::size_t count;
    std::size_t front_idx;
    std::size_t back_idx;
public:
    Deque(size_t initial_capacity = 10):capacity(initial_capacity),count(0),front_idx(0),back_idx(0){
        buffer = new T[capacity]();
    }

    ~Deque(){
        delete[] buffer;
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }

    void resize(size_t new_capacity){
        T * new_buffer = new T[new_capacity]();
        for(size_t i = 0;  i < count ; ++i){
            new_buffer[i] = buffer[(front_idx + i) % capacity];
        }

        delete[] buffer;
        buffer = new_buffer;
        front_idx = 0;
        back_idx = count;
        capacity = new_capacity;
    }

    void push_front(const T& value){
        if(count == capacity){
            resize(capacity*2);
        }

       front_idx =  (front_idx == 0) ? capacity -1 : front_idx-1;
       buffer[front_idx] = value;
        ++count ;
    }

    void push_back(const T& value){
        if(count == capacity){
            resize(capacity * 2);
        }

        buffer[back_idx] = value;
        back_idx = (back_idx + 1)% capacity;
        count ++;
    }

    void pop_front(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }

        front_idx = (front_idx +1)% capacity;
        --count;
    }

    void pop_back(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        back_idx = back_idx == 0 ? capacity -1 : back_idx -1;
        --count;
    }

    T& back(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }

        size_t last_idx = back_idx == 0 ? capacity-1: back_idx -1;
        return buffer[last_idx];
    }

    const T& back() const{
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }

        size_t last_idx = back_idx == 0 ? capacity-1: back_idx -1;
        return buffer[last_idx];
    }

    T& front(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }

        return buffer[front_idx];
    }

    const T& front() const{
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }

        return buffer[front_idx];
    }

    class Iterator{
    private:
        Deque<T> * deque_ptr;
        size_t pos;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Deque<T> * deque, size_t position):deque_ptr(deque),pos(position){}

        reference operator*() const{
            size_t real_idx = (deque_ptr->front_idx + pos) % (deque_ptr->capacity);
            return deque_ptr->buffer[real_idx];
        }

        pointer operator -> () const{
            size_t real_idx = (deque_ptr->front_idx + pos) % (deque_ptr->capacity);
            return &(deque_ptr->buffer[real_idx]);
        }

        Iterator& operator++(){
            ++pos;
            return * this;
        }

        Iterator operator++(int){
            Iterator tmp = *this;
            ++pos;
            return tmp;
        }

        Iterator& operator--(){
            --pos;
            return * this;
        }

        Iterator operator--(int){
            Iterator tmp = *this;
            --pos;
            return tmp;
        }

        bool operator == (const Iterator& other) const {
            return (deque_ptr == other.deque_ptr) && (pos == other.pos);
        }

        bool operator != (const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin(){
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this,count);
    }
};


#endif //INC_27_DEQUE_DEQUE_H
