/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef TRANSACTIONALTASKMANAGER_H_
#define TRANSACTIONALTASKMANAGER_H_

#include "engine/util/Command.h"

#include "engine/core/TaskQueue.h"

#include "engine/core/TaskManager.h"

#include "engine/stm/task/LocalTaskManager.h"

namespace engine {
  namespace stm {

  	class TransactionalTaskManager : public TaskManager, public Command {
  		TaskManagerImpl* taskManager;

  		ThreadLocal<LocalTaskManager*>  localTaskManager;

  	  public:
  		static const int WORKER_THREADS = 2;
  		static const int SCHEDULER_THREADS = 5;

  		void initialize();

  		void start();

  		void shutdown();

  		void executeTask(Task* task);

#ifdef WITH_STM
  		void retryTaskInSerial(Task* task);

  		Thread* getSerialWorker();
#endif

  		void scheduleTask(Task* task, uint64 delay);
  		void scheduleTask(Task* task, Time& time);

  		void rescheduleTask(Task* task, uint64 delay);
  		void rescheduleTask(Task* task, Time& time);

  		Vector<Locker*>* blockTaskManager();
  		void unblockTaskManager(Vector<Locker*>* lockers);

  		bool cancelTask(Task* task);

  		Task* getTask();

  		inline TaskManagerImpl* getTaskManagerImpl() {
  			return taskManager;
  		}

  		bool isTaskScheduled(Task* task);

  		bool getNextExecutionTime(Task* task, Time& nextExecutionTime);

  		void flushTasks();

  		String getInfo(bool print);

  		int getScheduledTaskSize();

  		int getExecutingTaskSize();

  		void execute();

  		void undo();

  	  protected:
  		LocalTaskManager* getLocalTaskManager();

  	  };

  } // namespace stm
} // namespace engine

using namespace engine::stm;

#endif /* TASKMANAGER_H_ */
