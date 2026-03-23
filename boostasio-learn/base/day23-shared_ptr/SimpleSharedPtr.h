//
// Created by secon on 2024/12/8.
//

#ifndef DAY23_SHARED_PTR_SIMPLESHAREDPTR_H
#define DAY23_SHARED_PTR_SIMPLESHAREDPTR_H
#include <mutex>
#include <atomic>

struct ControlBlock{
    std::atomic<int> ref_count ;
    ControlBlock() : ref_count(1) {}
};

template <typename T>
class SimpleSharedPtr {
private:
    T *ptr;
    ControlBlock * control;
    void release(){
        if(control){
            -- control->ref_count;
            if(control->ref_count == 0){
                delete ptr;
                ptr = nullptr;
                delete control;
                control = nullptr;
            }
        }
    }

public:
    SimpleSharedPtr():ptr(nullptr),control(nullptr){}
    explicit  SimpleSharedPtr(T *p) : ptr(p){
        if(p){
            control = new ControlBlock();
        }else{
            control = nullptr;
        }
    }

    ~SimpleSharedPtr(){
        if(ptr){
            release();
        }
    }

    // SimpleSharedPtr s2(s1) ;
    SimpleSharedPtr(const SimpleSharedPtr &s) : ptr(s.ptr), control(s.control){
        if(control){
            ++ control->ref_count;
        }
    }

    //  SimpleSharedPtr s2(new student()); s2 = s1;
    SimpleSharedPtr & operator=(const SimpleSharedPtr &s){
        if(this != &s){
            release();
            ptr = s.ptr;
            control = s.control;
            if(control){
                ++ control->ref_count;
            }
        }
        return *this;
    }
    // SimpleSharedPtr s2(std::move(s1));
    SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr(other.ptr), control(other.control){
        other.ptr = nullptr;
        other.control = nullptr;
    }

    // SimpleSharedPtr s2; s2 = std::move(s1);
    SimpleSharedPtr & operator=(SimpleSharedPtr &&other) noexcept{
        if(this != &other){
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
        }
        return *this;
    }

    // SimpleSharedPtr s2(new student());    s2->name = "tom";  s2.ptr->name = "tom";

    T*  operator->() const {
        return ptr;
    }

    //  SimpleSharedPtr s2(new student());  (*s2).name = "tom"; (*s2.ptr).name = "tom";
    T& operator *() const {
        return *ptr;
    }

    // Student* raw_s2 =  s2.get()
    T* get() const{
        return ptr;
    }

    int use_count() const{
        return control ? control->ref_count.load() : 0;
    }

    // s2.reset(new Student());
    // s2.reset();
    void reset(T* p =nullptr){
        release();
        ptr = p;
        if(p){
            control = new ControlBlock();
        }else{
            control = nullptr;
        }
    }
};


#endif //DAY23_SHARED_PTR_SIMPLESHAREDPTR_H
