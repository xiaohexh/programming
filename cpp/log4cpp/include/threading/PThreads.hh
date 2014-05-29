#ifndef _LOG4CPP_THREADING_PTHREADS_HH
#define _LOG4CPP_THREADING_PTHREADS_HH

#include "Portability.hh"
#include <pthread.h>
#include <assert.h>
#include <string>

namespace log4cpp
{
	namespace threading
	{
		std::string getThreadId();

		/*
		 * definition of mutex
		 */
		class Mutex
		{
		public:
			inline Mutex()
			{
				::pthread_mutex_init(&m_mutex, NULL);
			}

			inline ~Mutex()
			{
				::pthread_mutex_destroy(&m_mutex);
			}

			inline void lock()
			{
				::pthread_mutex_lock(&m_mutex);
			}

			inline void unlock()
			{
				::pthread_mutex_unlock(&m_mutex);
			}

		private:
			pthread_mutex_t m_mutex;

			Mutex(const Mutex&);   // Remove
			Mutex& operator=(const Mutex&);   // Remove
		};

		/*
		 * definition of scopedlock
		 */
		class ScopedLock
		{
		public:
			inline ScopedLock(Mutex& mutex)
				: m_mutex(mutex)
			{
				m_mutex.lock();
			}

			inline ~ScopedLock()
			{
				m_mutex.unlock();
			}
		private:
			Mutex& m_mutex;
		};

		/**
		 * definition of ThreadLocalDataHolder
		 */
		template <typename T>
		class ThreadLocalDataHolder
		{
		public:

			typedef T data_type;

			inline ThreadLocalDataHolder()
			{
				::pthread_key_create(&m_key, freeHolder);
			}

			inline static void freeHolder(void* p)
			{
				assert(p != NULL);
				delete reinterpret_cast<T *>(p);
			}

			inline ~ThreadLocalDataHolder()
			{
				T* data = get();
				if (data != NULL)
				{
					delete data;
				}
				::pthread_key_delete(m_key);
			}

			inline T* get()
			{
				return reinterpret_cast<T *>(::pthread_getspecific(m_key));
			}

			inline T* operator->() const {return get();}
			inline T& operator*() const {return *get();}

			inline T* release()
			{
				T* result = get();
				::pthread_setspecific(m_key, NULL);

				return result;
			}

			inline void reset(T* p = NULL)
			{
				T* data = get();
				if (data != NULL)
				{
					delete data;
				}
				
				::pthread_setspecific(m_key, p);
			}

		private:
			pthread_key_t m_key;
		};
	}
}

#endif // _LOG4CPP_THREADING_PTHREADS_HH
