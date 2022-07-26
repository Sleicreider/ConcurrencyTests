#pragma once

namespace PlatformGeneral
{
	inline void ProcessorPause()
	{
#if defined(__X86_x64__)
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

//
//
//	static FORCEINLINE void Yield()
//	{
//#if PLATFORM_CPU_X86_FAMILY 
//		_mm_pause();
//#elif PLATFORM_CPU_ARM_FAMILY 
//# if !defined(__clang__) 
//		__yield(); // MSVC 
//# else 
//		__builtin_arm_yield();
//# endif 
//#else 
//# error Unsupported architecture! 
//#endif 
//	}
}