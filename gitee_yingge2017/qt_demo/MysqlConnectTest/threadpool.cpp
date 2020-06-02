#include "threadpool.h"

using namespace std;

RenLib::ThreadPool::ThreadPool()
    : max_(40)
    , is_stop_(false)
{
}

RenLib::ThreadPool::~ThreadPool()
{
    lock_guard<mutex> lock(mutex_entrys_);
    is_stop_ = true;
    for (auto entry : entrys_)
    {
        delete entry;
        entry = nullptr;
    }
    entrys_.clear();
}

RenLib::ThreadPool * RenLib::ThreadPool::Instance()
{
    static ThreadPool* instance = nullptr;
    if (instance == nullptr)
        instance = new	ThreadPool();
    return instance;
}

void RenLib::ThreadPool::SetMaxThreads(uint32_t max)
{
    max_ = max;
}

bool RenLib::ThreadPool::ThreadCall(ThreadCallback cb, void * user_data)
{
    RenLib::CThreadEntry* entry = GetThreadEntry();
    if (entry == nullptr)
        return false;
    return entry->Run(cb, user_data);
}

RenLib::CThreadEntry* RenLib::ThreadPool::GetThreadEntry()
{
    lock_guard<mutex> lock(mutex_entrys_);
    auto entry_count = static_cast<uint32_t>(entrys_.size());
    if(entry_count < max_)
    {
        auto entry = new CThreadEntry();
        entrys_.push_back(entry);
        return entry;
    }

    for (CThreadEntry* entry : entrys_)
    {
        if (entry != nullptr && !entry->IsRunning_())
            return entry;
    }

    return nullptr;
}

RenLib::CThreadEntry::CThreadEntry()
    : cb_(nullptr)
    , user_data_(nullptr)
    , is_running_(false)
    , is_delete_(false)
{
}



bool RenLib::CThreadEntry::Run(ThreadCallback& cb, void* user_data)
{
    if (is_running_)
        return false;
    is_running_ = true;
    cb_ = cb;
    user_data_ = user_data;

    auto thread_work = [&](void*) {
        if (cb_ != nullptr)
            cb_(user_data_);
        cb_ = nullptr;
        user_data_ = nullptr;
        is_running_ = false;
    };
    thread_ = thread(thread_work, nullptr);
    return true;
}
