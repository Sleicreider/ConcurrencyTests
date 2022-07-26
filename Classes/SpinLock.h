#pragma once

#include <atomic>

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