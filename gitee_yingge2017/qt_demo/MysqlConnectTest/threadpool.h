#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <functional>

namespace RenLib
{
    //typedef void(*ThreadCallback)(void*);
    typedef std::function<void(void*)> ThreadCallback;

    class CThreadEntry
    {
    public:
        CThreadEntry();
        bool Run(ThreadCallback& cb, void* user_data);
        bool IsRunning_() { return is_running_; }
    private:
        std::thread thread_;
        ThreadCallback cb_;
        void* user_data_;
        bool is_running_;
        bool is_delete_;
    };

    class ThreadPool
    {
    public:
        ThreadPool();
        ~ThreadPool();

        static ThreadPool* Instance();

        void SetMaxThreads(uint32_t max);

        bool ThreadCall(ThreadCallback cb, void* user_data);

    private:
        std::mutex mutex_entrys_;
        std::vector<CThreadEntry*> entrys_;
        uint32_t max_;
        bool is_stop_;

        CThreadEntry* GetThreadEntry();
    };
}

