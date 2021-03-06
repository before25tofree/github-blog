#include "MutexLockGuard.h"

class Counter : noncopyable
{
public:
    Counter() : value_(0) {}
    int64_t value() const;
    int64_t getAndIncrease();
    friend void swap(Counter&,Counter&);
    Counter& operator= (const Counter& rhs);

private:
    int64_t value_;
    mutable MutexLock mutex_;
};

int64_t Counter::value() const
{
    MutexLockGuard lock(mutex_);
    return value_;
}

int64_t Counter::getAndIncrease()
{
    MutexLockGuard lock(mutex_);
    int64_t ret = value_++;
    return ret;
}
