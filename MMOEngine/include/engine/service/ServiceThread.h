/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef SERVICETHREAD_H_
#define SERVICETHREAD_H_

#include "../../system/lang.h"

#include "../log/Logger.h"

#include "../core/TaskManager.h"

#include "ServiceException.h"

namespace engine {
  namespace service {
  	
	class ServiceThread : public Thread, public Mutex, public Logger, public Object {
	protected:
		TaskManager* taskManager;
		
		bool doRun, serviceReady;
	
	public:
		ServiceThread(const String& s);
		
		virtual ~ServiceThread();
		
		virtual void init();

		void start(bool waitForStartup = true);
	
		virtual void run();
		
		virtual void stop(bool doJoin = true);
		
		/*// scheduler methods
		inline void scheduleTask(Task* task, uint64 delay = 0) {
			taskManager->scheduleTask(task, delay);
		}

		inline void scheduleTask(Task* task, Time& time) {
			taskManager->scheduleTask(task, time);
		}*/

		// setters and getters
		inline void setRunning(bool val) {
			doRun = val;
		}
	
		inline bool isRunning() {
			return doRun;
		}
	
		inline void setReady(bool val) {
			serviceReady = val;
		}
	
		inline bool isReady() {
			return serviceReady;
		}
	};

  } // namespace service
} // namespace engine

using namespace engine::service;

#endif /*SERVICETHREAD_H_*/
