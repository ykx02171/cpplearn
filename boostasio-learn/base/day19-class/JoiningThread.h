//
// Created by secon on 2024/11/13.
//

#ifndef DAY19_CLASS_JOININGTHREAD_H
#define DAY19_CLASS_JOININGTHREAD_H

#include <thread>
class JoiningThread {
public:
    JoiningThread() :_i(0){}
    JoiningThread(int i) : _i{i} {}
    JoiningThread(const JoiningThread & other): _i(other._i){}
    int GetIndex() const { return _i; }
private:
    std::thread _t;
    int _i;
};


#endif //DAY19_CLASS_JOININGTHREAD_H
