#pragma once
#include "noncopyable.h"
//#include "CurrentThread.h"
#include <assert.h>
#include <pthread.h>

class MutexLock : noncopyable
{
public:
    MutexLock()
    : holder_(0)
    { pthread_mutex_init(&mutex_, NULL); }

    ~MutexLock()
    {
        assert(holder_ == 0);
        pthread_mutex_destroy(&mutex_);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
        //holder_ = CurrentThread::tid();
    }

    void unlock()
    {
        holder_ = 0;
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};

class MutexLockGuard : noncopyable
{
public:
    explicit MutexLockGuard(MutexLock& mutex)
    : mutex_(mutex)
    { mutex_.lock(); }

    ~MutexLockGuard()
    { mutex_.unlock(); }
private:
    MutexLock& mutex_;
};