//===========================================================//
// Name: threadtools.h
// Purpose: Threading stuff
// Date: 8/11/2019
//===========================================================// 
#pragma once

#include "platform.h"

#ifdef _WIN32
#include <Windows.h>
#elif defined(_LINUX)
#include <pthread.h>
#include <semaphore.h>
#endif

/* Simple thread proc */
typedef int(*ThreadProc_t)(void* param);

extern "C"
{

#ifdef _LINUX
typedef pthread_mutex_t mutex_t;
typedef pthread_t thread_t;
#elif defined(_WIN32)
#error implement for windows
#endif

//===========================================================//
// Mutex C library
//===========================================================//
void mutex_lock(mutex_t* mutex);

void mutex_init(mutex_t* mutex);

void mutex_trylock(mutex_t* mutex);

void mutex_unlock(mutex_t* mutex);

void mutex_destroy(mutex_t* mutex);

//===========================================================//
// Thread procs
//===========================================================//
void thread_init(thread_t* thread, ThreadProc_t proc);

void thread_destroy(thread_t* thread);

void thread_kill(thread_t* thread);

int thread_getreturn(thread_t* thread);

}


#ifdef __cplusplus



/*
Simple thread class
*/
class CThread
{
private:
	bool m_bRunning = false;
	bool m_bExited = false;
	int m_nReturn = 1;
#ifdef _WIN32

#elif defined(_LINUX)
	pthread_t m_thread;
	pthread_attr_t m_threadattr;
	pthread_mutex_t m_mutex;
	/* private data */
	void* m_pData;
#endif
public:
	/* Types */
public:
	CThread(ThreadProc_t proc);

	~CThread();
public:
	//-----------------------------------------------------//
	// Start execution of the thread proc in a new thread
	// with the specified parameter
	//-----------------------------------------------------//
	void Start(void* param);

	//-----------------------------------------------------//
	// Immediately stops the thread and kills it
	//-----------------------------------------------------//
	void Kill();

	//-----------------------------------------------------//
	// Suspends the thread until resumed
	//-----------------------------------------------------//
	void Suspend();

	//-----------------------------------------------------//
	// Resumes the execution of the thread
	//-----------------------------------------------------//
	void Resume();

	//-----------------------------------------------------//
	// Returns if the thread is running
	//-----------------------------------------------------//
	bool IsRunning() const;

	//-----------------------------------------------------//
	// Returns if the thread is paused
	//-----------------------------------------------------//
	bool IsPaused() const;

	//-----------------------------------------------------//
	// Returns if the thread proc has exited yet
	//-----------------------------------------------------//
	bool IsComplete() const;

	//-----------------------------------------------------//
	// If the thread is running still, returns -1, else,
	// returns the return code of thread proc
	//-----------------------------------------------------//
	int GetReturnCode() const;
};

//-----------------------------------------------------//
// Status of a mutex
//-----------------------------------------------------//
enum class EMutexStatus
{
	OK = 0,
	TimedOut,
};

/*
Mutex that doesnt rely on the OS mutex things
*/
class CFastMutex
{
private:

public:
	CFastMutex();

	~CFastMutex();

public:
	//-----------------------------------------------------//
	// Lock the mutex, blocks until locked
	//-----------------------------------------------------//
	int Lock();

	//-----------------------------------------------------//
	// Try to lock mutex, does not block
	//-----------------------------------------------------//
	int TryLock();

	//-----------------------------------------------------//
	// Unlock the mutex
	//-----------------------------------------------------//
	void Unlock();

	//-----------------------------------------------------//
	// Destroy the mutex
	//-----------------------------------------------------//
	void Destroy();
};

/*
Simple mutex class
*/
class CMutex
{
public:
	CMutex();

	~CMutex();
public:
	//-----------------------------------------------------//
	// Lock the mutex, blocks until locked
	//-----------------------------------------------------//
	int Lock();

	//-----------------------------------------------------//
	// Try to lock mutex, does not block
	//-----------------------------------------------------//
	int TryLock();

	//-----------------------------------------------------//
	// Unlock the mutex
	//-----------------------------------------------------//
	void Unlock();

	//-----------------------------------------------------//
	// Destroy the mutex
	//-----------------------------------------------------//
	void Destroy();
};

/*
Mutex that multiple threads can lock
*/
class CSharedMutex
{
public:
	//-----------------------------------------------------//
	// Create a new shared mutex with x max owning threads
	//-----------------------------------------------------//
	CSharedMutex(int nMaxThreads = 1);

	~CSharedMutex();
public:
	//-----------------------------------------------------//
	// Lock the mutex, blocks until locked
	//-----------------------------------------------------//
	int Lock();

	//-----------------------------------------------------//
	// Try to lock mutex, does not block
	//-----------------------------------------------------//
	int TryLock();

	//-----------------------------------------------------//
	// Unlock the mutex
	//-----------------------------------------------------//
	void Unlock();

	//-----------------------------------------------------//
	// Destroy the mutex
	//-----------------------------------------------------//
	void Destroy();
};

/*
Simple semaphore
*/
class CSemaphore
{
private:

public:
};

#endif //__cplusplus