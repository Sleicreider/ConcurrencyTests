#pragma once

#include <atomic>

class SpinLock
{
public:
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