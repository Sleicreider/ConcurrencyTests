#pragma once

template <typename Lockable>
class LockGuard
{
	LockGuard(const LockGuard&) = delete;
	LockGuard operator=(const LockGuard&) = delete;

public:
	LockGuard(Lockable& InLock)
		:Lock(InLock)
	{
		Lock.Lock();
	}

	~LockGuard()
	{
		Lock.Unlock();
	}


private:
	Lockable& Lock;
};