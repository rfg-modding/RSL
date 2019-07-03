#pragma once
#include "KeenNamespace.h"

namespace keen
{
	/* 3337 */
	struct Array_WorkerThreadContext
	{
		keen::WorkerThreadContext *m_pData;
		unsigned int m_size;
	};

	/* 3340 */
	struct SizedArray_TaskQueueContext
	{
		keen::TaskQueueContext *m_pData;
		unsigned int m_size;
		unsigned int m_capacity;
	};

	/* 3341 */
	struct Semaphore
	{
		void *m_semaphoreHandle;
		int m_value;
	};

	/* 3336 */
	struct WorkerThreadContext
	{
		keen::Thread thread;
		unsigned int threadIndex;
		keen::TaskSystem *pTaskSystem;
	};

	/* 3345 */
	struct Array_TaskPointer
	{
		keen::Task **m_pData;
		unsigned int m_size;
	};

	/* 3346 */
	struct Queue_TaskPointer
	{
		unsigned int m_size;
		unsigned int m_bottom;
		unsigned int m_top;
		keen::Array_TaskPointer m_data;
	};

	/* 3338 */
	struct TaskQueue
	{
		keen::TaskSystem *pTaskSystem;
		unsigned int clientThreadId;
		char *pCopyBuffer;
		unsigned int copyBufferSlotIndex;
		keen::Queue_TaskPointer queue;
		keen::Mutex queueMutex;
		unsigned int pendingTaskCount;
		unsigned int inProgressTaskCount;
		keen::Event taskCompleteEvent;
		unsigned int maxTaskSize;
	};

	/* 3339 */
	struct TaskQueueContext
	{
		keen::TaskQueue *pQueue;
		unsigned int priority;
	};

	/* 3344 */
	struct TaskHeader
	{
		void(__cdecl *pTaskFunction)(keen::TaskContext*);
	};

	/* 3342 */
	struct Task
	{
		keen::TaskHeader header;
	};

	/* 3343 */
	const struct TaskContext
	{
		keen::Task *pTask;
		const unsigned int threadIndex;
	};

	/* 3335 */
	struct TaskSystem
	{
		unsigned int clientThreadId;
		keen::Array_WorkerThreadContext workerThreadContexts;
		keen::SizedArray_TaskQueueContext taskQueueContexts;
		keen::Mutex queueArrayMutex;
		keen::Semaphore wakeUpSemaphore;
	};
};