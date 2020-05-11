#ifndef COUNTWORDS_MULTI_THREAD_QUEUE_H
#define COUNTWORDS_MULTI_THREAD_QUEUE_H

#include <iostream>
#include <map>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class MultiThreadQueue {
private:
    size_t max_length;
    mutable std::mutex m;
    std::condition_variable cv_in, cv_out;
    std::queue<T> main_queue;
public:

    unsigned int iter = 0;

    MultiThreadQueue (size_t length) {
        this->max_length = length;
    }

    void push (T element) {
//        std::cout << "Current Queue size:" << main_queue.size() << std::endl;
        std::unique_lock<std::mutex> lk(m);
        while (main_queue.size() >= max_length) {
            cv_in.wait(lk);
        }

        main_queue.push(element);
        ++iter;

        lk.unlock();
        cv_out.notify_one();
    }

    T pop (void) {
//        std::cout << "here" <<std::endl;
        std::unique_lock<std::mutex> lk(m);
        while (main_queue.empty())
        {
            cv_out.wait(lk);
        }
        auto item = main_queue.front();
        main_queue.pop();
        lk.unlock();

        cv_in.notify_one();
        return item;
    }

    void pop (T item) {
        std::unique_lock<std::mutex> lk(m);
        while (main_queue.empty())
        {
            cv_out.wait(lk);
        }
        item = main_queue.front();
        main_queue.pop();
        lk.unlock();

        cv_in.notify_one();
    }

    bool empty(){
//        std::cout << "here" <<std::endl;
//        std::cout << main_queue.size() << std::endl;
        return main_queue.size() == 0;
    }


};


#endif //COUNTWORDS_MULTI_THREAD_QUEUE_H
