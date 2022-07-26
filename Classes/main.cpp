#include <iostream>

#include "PlatformGeneral.h"
#include "SpinLock.h"
#include "LockGuard.h"

#include <thread>

#include <atomic>

int main()
{
	std::cout << "Hello World" << std::endl;
	
	int value = 0;
	int step = 0;
	int step2 = 0;
	SpinLock Lock;

	std::thread f1([&value, &step, &Lock]
		{
			
			while (true)
			{
				LockGuard<SpinLock> ScopedLock(Lock);
				++value;
				step++;

				if (value >= 100000)
				{
					break;
				}
			}

		});

	std::thread f2([&value, &step2, &Lock]
		{

			while (true)
			{
				LockGuard<SpinLock> ScopedLock(Lock);
				++value;
				step2++;

				if (value >= 100000)
				{
					break;
				}
			}

		});

	//PlatformGeneral::ProcessorPause();

	f1.join();
	f2.join();

	return 0;
}