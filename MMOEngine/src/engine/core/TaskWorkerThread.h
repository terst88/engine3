/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef TASKWORKERTHREAD_H_
#define TASKWORKERTHREAD_H_

#include "engine/service/ServiceThread.h"

#include "TaskStatistics.h"

namespace engine {
  namespace core {

	class TaskManager;
	class TaskQueue;

	class TaskWorkerThread : public ServiceThread {
		Mutex blockMutex;
		TaskQueue* queue;
		int cpu;

		bool blockDuringSave;

#ifdef COLLECT_TASKSTATISTICS
		HashTable<const char*, TaskStatistics> tasksStatistics;
		ReadWriteLock tasksStatsGuard;
#endif

	public:
		TaskWorkerThread(const String& s, TaskQueue* queue, int cpu, bool blockDuringSave);

		virtual ~TaskWorkerThread();

		void start();

		//void pushToRetryQueue(Task* task);

		virtual void run();

		void stop();

#ifdef COLLECT_TASKSTATISTICS
		HashTable<const char*, TaskStatistics> getTasksStatistics();

		void clearTaskStatistics();
#endif

		inline Mutex* getBlockMutex() {
			return &blockMutex;
		}

		inline bool doBlockWorkerDuringSave() const {
			return blockDuringSave;
		}
	};

  } // namespace service
} // namespace engine

using namespace engine::core;

#endif /* TASKWORKERTHREAD_H_ */
