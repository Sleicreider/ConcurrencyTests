#include <iostream>

#include "PlatformGeneral.h"
#include "SpinLock.h"

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
				Lock.Lock();

				++value;
				step++;

				if (value >= 100000)
				{
					break;
				}

				Lock.Unlock();
			}

		});


	std::thread f2([&value, &step2, &Lock]
		{

			while (true)
			{
				Lock.Lock();

				++value;
				step2++;

				if (value >= 100000)
				{
					break;
				}

				Lock.Unlock();
			}

		});

	//PlatformGeneral::ProcessorPause();

	f1.join();
	f2.join();

	return 0;
}