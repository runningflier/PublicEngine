/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef TIMEDTASKQUEUE_H_
#define TIMEDTASKQUEUE_H_

#include "system/lang.h"

#include "../log/Logger.h"

#include "Task.h"

namespace engine {
  namespace core {

	class TaskScheduler;

	class TimedTaskQueue : public PriorityQueue, public Condition, public Logger {
		TaskScheduler* taskScheduler;

		Mutex* condMutex;

		bool blocked;

		bool waitingForTask;
		bool changePlan;

	public:
		TimedTaskQueue();

		~TimedTaskQueue();

		bool add(Task* e, uint64 delay);
		bool add(Task* e, Time& time);

		bool add(Task* e, bool doLock = true);

		bool addAll(PriorityQueue& queue, bool doLock = true);

		Task* get();

		bool remove(Task* e, bool doLock = true);

		void flush();

		void repair();

		void printQueue();

		// setters and getters
		inline void setTaskScheduler(TaskScheduler* scheduler) {
			taskScheduler = scheduler;
		}

		inline void setMutexName(const String& s) {
			condMutex->setLockName(s);
		}
	};

  } // namespace core
} // namespace engine

using namespace engine::core;

#endif /* TIMEDTASKQUEUE_H_ */
