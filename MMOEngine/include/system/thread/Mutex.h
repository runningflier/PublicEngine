/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MUTEX_H_
#define MUTEX_H_

#include "Lockable.h"

namespace sys {
  namespace thread {

	class ReadWriteLock;

	class Mutex : public Lockable {
		pthread_mutex_t mutex;
		pthread_mutexattr_t attr;
		bool recursiveMutex;

	public:
		Mutex() : Lockable() {
			pthread_mutex_init(&mutex, NULL);
			recursiveMutex = false;
		}
		
		Mutex(bool recursive) : Lockable() {
		        if (recursive) {
        		        pthread_mutexattr_init(&attr);

                		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
                		
                		pthread_mutex_init(&mutex, &attr);
                		
                		recursiveMutex = true;
                        } else {
                                pthread_mutex_init(&mutex, NULL);
                                recursiveMutex = false;
                        }
                        
		}

		Mutex(const String& s) : Lockable(s) {
			pthread_mutex_init(&mutex, NULL);
			
			recursiveMutex = false;
		}

		Mutex(const Mutex& m) : Lockable() {
			pthread_mutex_init(&mutex, NULL);
			
			recursiveMutex = false;
		}

		virtual ~Mutex() {
			pthread_mutex_destroy(&mutex);
			
			if (recursiveMutex)
				pthread_mutexattr_destroy(&attr);
		}

		void lock(bool doLock = true);
		void lock(Mutex* m);
		void lock(Lockable* lockable);

		bool tryLock();
		bool tryLock(uint64 time);

		void unlock(bool doLock = true);

		friend class Condition;
		friend class ReadWriteLock;
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;

#endif /*MUTEX_H_*/
