/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  porting.h - porting layer

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_PORTING
#define _DEF_PORTING

#ifdef WIN32
#ifdef LIBORCA_EXPORTS
#define LIBORCA_API __declspec(dllexport)
#else
#define LIBORCA_API __declspec(dllimport)
#endif
#else
#define LIBORCA_API
#endif

#include <string>
#include <stdio.h>

#if defined(WIN32) || defined(_WIN64)
#define WINDOWS
#endif

#ifdef WINDOWS
#include <winsock2.h>
#include <wininet.h>
#include <process.h>
#else
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>


#define SOCKET int
#define SOCKADDR_IN sockaddr_in
#define INVALID_SOCKET -1
#define SOCKADDR sockaddr
#define SOCKET_ERROR -1
#endif



/********************************************************************/
// pipe
/********************************************************************/

#ifdef WINDOWS
#define popen _popen
#define pclose _pclose
#define snprintf _snprintf
#endif




/********************************************************************/
// dl
/********************************************************************/

std::string dl_get_filename(const std::string& mod_name);

#ifdef WINDOWS
#define RTLD_NOW 1
#define DLHANDLE HINSTANCE
DLHANDLE dlopen(const char* name, int mode);
void* dlsym(DLHANDLE handle, const char* name);
char* dlerror();
#else
#define DLHANDLE void*
#endif



/********************************************************************/
// ipc
/********************************************************************/

#ifdef WINDOWS

struct timespec {
	long tv_sec;
	long tv_nsec;
};

typedef HANDLE pthread_mutex_t;
LIBORCA_API void pthread_mutex_init(pthread_mutex_t* mutex, void* vp);
LIBORCA_API void pthread_mutex_destroy(pthread_mutex_t* mutex);
LIBORCA_API void pthread_mutex_lock(pthread_mutex_t* mutex);
LIBORCA_API void pthread_mutex_unlock(pthread_mutex_t* mutex);

typedef HANDLE pthread_cond_t;
LIBORCA_API void pthread_cond_init(pthread_cond_t* cond, void* vp);
LIBORCA_API void pthread_cond_destroy(pthread_cond_t* cond);
LIBORCA_API void pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);
LIBORCA_API int pthread_cond_timedwait(pthread_cond_t* cond, 
							pthread_mutex_t* mutex,
							struct timespec* timeout);
LIBORCA_API void pthread_cond_signal(pthread_cond_t* cond);

typedef HANDLE sem_t;
typedef HANDLE shm_t;

sem_t semget(int key, int max, int opt);
void semctl(sem_t sem, int i, int j, int k);

#ifndef ETIMEDOUT
#define ETIMEDOUT (-10)
#endif

#define IPC_CREAT 1
#define IPC_RMID 0

#else

typedef int sem_t;
typedef int shm_t;

#endif

void sem_inc(sem_t sem);
void sem_dec(sem_t sem);


/********************************************************************/
// socket
/********************************************************************/

#ifdef WINDOWS
typedef int socklen_t;
#endif

void port_closesocket(SOCKET sock);



/********************************************************************/
// Thread
/********************************************************************/

#ifdef WINDOWS
typedef unsigned int (__stdcall *thread_fp)(void*);
#define THREAD_RET unsigned int __stdcall

typedef HANDLE pthread_t;
int pthread_create(pthread_t* id, void* vp, thread_fp fp, void* arg);
LIBORCA_API void pthread_join(pthread_t id, void** status);

typedef DWORD pthread_key_t;

#define pthread_setspecific(a, b)	TlsSetValue(a, b)
#define pthread_getspecific(a)		TlsGetValue(a)
#define pthread_key_delete(a)		TlsFree(a)

int pthread_key_create(pthread_key_t* key, void* dummy);



#else
#define THREAD_RET void*
typedef void* (*thread_fp)(void* vp);
#endif



/********************************************************************/
// platform independent util
/********************************************************************/

LIBORCA_API void port_msleep(int msec);
LIBORCA_API void port_nsleep(long long nsec);
LIBORCA_API int port_cpu_num();
LIBORCA_API long long port_memory();
LIBORCA_API long long port_free();
LIBORCA_API std::string port_os();

#ifdef WINDOWS
struct timezone
{
  int  tz_minuteswest;
  int  tz_dsttime;
};

LIBORCA_API int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif



/********************************************************************/
// C++ porting layer
/********************************************************************/

class LIBORCA_API portMutex
{
public:
	portMutex();
	~portMutex();
	void lock();
	void unlock();
	pthread_mutex_t* handle();

private:
	pthread_mutex_t m_mutex;
};


class LIBORCA_API portCond
{
public:
	portCond();
	~portCond();
	bool wait(long long nsec = -1); // true : signaled, false : timeout
	bool wait(portMutex* mutex, long long nsec = -1); // true : signaled, false : timeout
	void signal();

private:
	pthread_cond_t m_cond;
	pthread_mutex_t m_cond_mutex;
};

class LIBORCA_API portFile
{
public:
	portFile() : fp(NULL) {}
	~portFile();

	bool open(const std::string& name);
	bool create(const std::string& name);
	void close();
	bool open_force(const std::string& name);

	std::string reads();
	void writes(const std::string& str);
	char* read();
	size_t read(char* buff, int size, int count);
	size_t write(char* buff, int size, int count);
	size_t size();

private:
	FILE* fp;
};


#endif /* _DEF_PORTING */



