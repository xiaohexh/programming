#ifndef _LOG4CPP_PORTABLILITYIMPL_HH
#define _LOG4CPP_PORTABLILITYIMPL_HH

#ifdef LOG4CPP_CSTDLIB_NOT_IN_STD
#include <cstdlib>
namespace std
{
	static inline char* getenv(const char* name){return ::getenv(name);};
	static inline int atoi(const char* nptr){return ::atoi(nptr);};
	static inline unsigned long int 
		strtoul(const char* nptr, char **endptr, int base){
			return ::strtol(nptr, endptr, base);
		};
	static inline void abort(void){::abort();};
}
#endif // LOG4CPP_CSTDLIB_NOT_IN_STD

#ifdef LOG4CPP_CSTRING_NOT_IN_STD
#include <cstring>
namespace std
{
	static inline void * memmove(void* dest, const void* src, size_t n){
		return ::memmove(dest, src, n);
	}
}
#endif // LOG4CPP_CSTRING_NOT_IN_STD

#ifdef LOG4CPP_CMATH_NOT_IN_STD
namespace std
{
	static inline int abs(int i){return ::abs(i);}
}
#endif // LOG4CPP_CMATH_NOT_IN_STD

namespace log4cpp
{
	template <typename T>
	const T& min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	const T& max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}
}

#endif // _LOG4CPP_PORTABLILITYIMPL_HH
