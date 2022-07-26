#pragma once

namespace PlatformGeneral
{
	inline void ProcessorPause()
	{
#if defined(__X86_X64__)
		_mm_pause();
#elif defined(__ARM__)
	# if !defined(__clang__) 
		__yield(); // MSVC 
	# else 
		__builtin_arm_yield();
	# endif 
#else
	#error Unsupported Architecture
#endif
	}
}