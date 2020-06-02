#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <atomic>

namespace RenLib {
//自旋锁
class SpinMutex {
    std::atomic<bool> flag = ATOMIC_VAR_INIT(false);
public:
    SpinMutex() = default;
    SpinMutex(const SpinMutex&) = delete;
    SpinMutex& operator= (const SpinMutex&) = delete;
    void lock() {
        bool expected = false;
        while(!flag.compare_exchange_strong(expected, true))
            expected = false;
    }
    void unlock() {
        flag.store(false);
    }
};

class AutoSpinLock
{
public:
    AutoSpinLock(SpinMutex& s)
    {
        s_ = &s;
        s_->lock();
    }
    ~AutoSpinLock()
    {
        s_->unlock();
    }
private:
    SpinMutex* s_;
};
}

#endif // SPINLOCK_HPP
