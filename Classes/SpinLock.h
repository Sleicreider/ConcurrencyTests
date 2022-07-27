#pragma once

#include <atomic>

// acquire & release should be sufficient and cannot dead lock
// https://preshing.com/20170612/can-reordering-of-release-acquire-operations-introduce-deadlock/

class SpinLock
{
	SpinLock(const SpinLock&) = delete;
	SpinLock operator=(const SpinLock&) = delete;

public:
	SpinLock() = default;

	void Lock()
	{
		while (true)
		{
			if (!bFlag.test_and_set(std::memory_order_acquire))
			{
				break;
			}
			
			// intel suggestion to not starve other threads & reduce power consumption
			while (bFlag.test(std::memory_order_relaxed))
			{
				PlatformGeneral::ProcessorPause();
			}
		}
	}

	//void TryLock();
	void Unlock()
	{
		bFlag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag bFlag = ATOMIC_FLAG_INIT;
};
