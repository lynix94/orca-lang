/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  porting.cpp - porting layer

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <errno.h>

#include "porting.h"

#ifdef WINDOWS
#else
#include <unistd.h>
#endif


using namespace std;

// WINDOWS dl/*{{{*/
#ifdef WINDOWS
DLHANDLE dlopen(const char* name, int mode)
{
	return LoadLibraryA(name);
}

void* dlsym(DLHANDLE handle, const char* name)
{
	return GetProcAddress(handle, name);
}

char* dlerror()
{
	return "dl open error";
}
#endif
/*}}}*/

#ifdef WINDOWS
string dl_get_filename(const string& mod_name)/*{{{*/
{
	return string("orca_") + mod_name + ".dll";
}
/*}}}*/
#else 
string dl_get_filename(const string& mod_name)/*{{{*/
{
	return string("liborca_") + mod_name + ".so";
}
/*}}}*/
#endif

// mutex
// WINDOWS mutex /*{{{*/
#ifdef WINDOWS
int pthread_mutex_init(pthread_mutex_t* mutex, void* vp)
{
	*mutex = CreateMutex(NULL, false, NULL);
	return 0;
}

int pthread_mutex_destroy(pthread_mutex_t* mutex)
{
	CloseHandle(*mutex);
	*mutex = NULL;
	return 0;
}

int pthread_mutex_lock(pthread_mutex_t* mutex)
{
	WaitForSingleObject(*mutex, INFINITE);
	return 0;
}

int pthread_mutex_trylock(pthread_mutex_t* mutex)
{
	int ret = WaitForSingleObject(*mutex, 0);
	return ret == WAIT_OBJCT_0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	ReleaseMutex(*mutex);
	return 0;
}
#endif
/*}}}*/

// cond
// WINDOWS cond/*{{{*/
#ifdef WINDOWS
void pthread_cond_init(pthread_cond_t* cond, void* vp)
{
	*cond = CreateEvent(NULL, false, false, NULL);
	ResetEvent(*cond);
}

void pthread_cond_destroy(pthread_cond_t* cond)
{
	CloseHandle(*cond);
}

void pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex)
{
	pthread_cond_timedwait(cond, mutex, NULL);
}

int pthread_cond_timedwait(pthread_cond_t* cond, 
							pthread_mutex_t* mutex,
							struct timespec* timeout)
{
	int msec = -1;

	if (timeout != NULL) {
		struct timeval now, to;
		gettimeofday(&now, NULL);

		to.tv_sec = timeout->tv_sec;
		to.tv_usec = timeout->tv_nsec / 1000;

		msec = (to.tv_sec - now.tv_sec) * 1000;
		msec += (to.tv_usec - now.tv_usec) / 1000;

		if (msec < 0) msec = 0;
	}

	int ret = SignalObjectAndWait(*mutex, *cond, msec, false);
	pthread_mutex_lock(mutex);

	return (ret == WAIT_TIMEOUT)?-1:0;
}

void pthread_cond_signal(pthread_cond_t* cond)
{
	SetEvent(*cond);
}
#endif
/*}}}*/

// semaphore
// WINDOWS semaphore/*{{{*/
#ifdef WINDOWS
sem_t semget(int key, int max, int opt)
{
	char buff[32];
	sprintf(buff, "sem_%d", key);
	sem_t ret =  CreateSemaphoreA(NULL, 0, max, buff);

	return ret;
}

// just for delete
void semctl(sem_t sem, int i, int j, int k)
{
	CloseHandle(sem);
}
#endif
/*}}}*/

#ifdef WINDOWS
void sem_inc(sem_t sem)/*{{{*/
{
	ReleaseSemaphore(sem, 1, NULL);
}
/*}}}*/

void sem_dec(sem_t sem)/*{{{*/
{
	WaitForSingleObject(sem, INFINITE);
}
/*}}}*/
#else

static struct sembuf sembuf_inc = { 0, 1, SEM_UNDO };
static struct sembuf sembuf_dec = { 0, -1, SEM_UNDO };

void sem_inc(sem_t sem)/*{{{*/
{
	semop(sem, &sembuf_inc, 1);
}
/*}}}*/

void sem_dec(sem_t sem)/*{{{*/
{
	semop(sem, &sembuf_dec, 1);
}
/*}}}*/
#endif


// shmem
// WINDOWS share memory/*{{{*/
#ifdef WINDOWS
shm_t shmget(int key, int size, int v)
{
	char buff[32];
	sprintf(buff, "shm_%d", key);
	return CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, buff);

}

// fix size 
void* shmat(shm_t id, void* v, int size)
{
	return MapViewOfFile(id, FILE_MAP_ALL_ACCESS, 0, 0, size);
}
#endif
/*}}}*/

#ifdef WINDOWS
void shm_rm(shm_t id, void* ptr)/*{{{*/
{
	UnmapViewOfFile(ptr);
	CloseHandle(id);
}/*}}}*/
#else
void shm_rm(shm_t id, void* ptr)/*{{{*/
{
	shmctl(id, IPC_RMID, NULL);
}/*}}}*/
#endif


// TCP
#ifdef WINDOWS
class WinsockInit/*{{{*/
{
public:
	WinsockInit() {
		WSADATA wsaData;
		if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			printf("WSAStartup() error!");
			exit(0);
		}
	}

	~WinsockInit() {
		WSACleanup();
	}

	static WinsockInit sOnly;
};
/*}}}*/

WinsockInit WinsockInit::sOnly;
#endif

void port_closesocket(SOCKET handle)/*{{{*/
{
#ifdef WINDOWS
	closesocket(handle);
#else
	close(handle);
#endif
}
/*}}}*/

// Thread
#ifdef WINDOWS
int pthread_create(pthread_t* id, void* vp, thread_fp fp, void* arg)/*{{{*/
{
	unsigned int win_tid;
	*id = (HANDLE)_beginthreadex(NULL, 0, fp, arg, 0, &win_tid);
	if (*id == NULL) {
		return -1;
	}

	return 0;
}
/*}}}*/

void pthread_join(pthread_t id, void** status) /*{{{*/
{
	WaitForSingleObject(id, INFINITE);
}
/*}}}*/

int pthread_key_create(pthread_key_t* key, void* dummy)/*{{{*/
{
	*key = TlsAlloc();
	return 0;
}
/*}}}*/
#endif

// common utils
void port_msleep(int msec)/*{{{*/
{
#ifdef WINDOWS
	Sleep(msec);
#else
	struct timeval tv;
	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000);
	select(0, NULL, NULL, NULL, &tv);
#endif
}
/*}}}*/

void port_nsleep(long long nsec)
{
#ifdef WINDOWS
	HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
	if (timer == NULL) {
		return;
	}

	LARGE_INTEGER li;
	li.QuadPart = -ns;
	if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
		CloseHandle(timer);
		return;
	}

	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
#else
	struct timespec wait;
	wait.tv_sec = nsec / (1000*1000*1000);
	wait.tv_nsec = nsec % (1000*1000*1000);
	nanosleep(&wait, NULL);
#endif
}


// WINDOWS gettimeosday/*{{{*/
#ifdef WINDOWS

/**************************************************************
 *
 * windows porting function for gettimeofday
 * this code comes from  
 * 
 * http://suacommunity.com/dictionary/gettimeofday-entry.php
 *
 **************************************************************/

#include <time.h>

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

// Definition of a gettimeofday function
int gettimeofday(struct timeval *tv, struct timezone *tz)/*{{{*/
{
// Define a structure to receive the current Windows filetime
  FILETIME ft;
 
// Initialize the present time to 0 and the timezone to UTC
  unsigned __int64 tmpres = 0;
  static int tzflag = 0;
 
  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
 
// The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
// intervals since Jan 1, 1601 in a structure. Copy the high bits to 
// the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
// Convert to microseconds by dividing by 10
    tmpres /= 10;
 
// The Unix epoch starts on Jan 1 1970.  Need to subtract the difference 
// in seconds from Jan 1 1601.
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
 
// Finally change microseconds to seconds and place in the seconds value. 
// The modulus picks up the microseconds.
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }
 
  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }
  
// Adjust for the timezone west of Greenwich
      tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }
 
  return 0;
}
/*}}}*/
#endif
/*}}}*/

// system info
int port_cpu_num()/*{{{*/
{
#ifdef WINDOWS
	SYSTEM_INFO a;
	GetSystemInfo( &a);
	return a.dwNumberOfProcessors;
#else
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}
/*}}}*/

long long port_memory()/*{{{*/
{
#ifdef WINDOWS
	MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys;
#else
	return (long long)sysconf(_SC_PHYS_PAGES) * (long long)sysconf(_SC_PAGE_SIZE);
#endif
}
/*}}}*/

long long port_free()/*{{{*/
{
#ifdef WINDOWS
	MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullAvailPhys;
#else
	return (long long)sysconf(_SC_AVPHYS_PAGES) * (long long)sysconf(_SC_PAGE_SIZE);
#endif
}
/*}}}*/

string port_os()/*{{{*/
{
#ifdef WINDOWS
	struct win_os_name 
	{
		const char* name;
		int major;
		int minor;
	};

	win_os_name names[] = {
		{ "Windows 7 (6.1)", 6, 1 },
		{ "Windows Server Longhorn / Windows Vista (6.0)", 6, 0 },
		{ "Windows Server 2003 (5.2)", 5, 2 },
		{ "Windows XP (5.1)", 5, 1},
		{ "Windows 2000 (5.0)", 5, 0},
		{ "Windows Me (4.90)", 4, 90},
		{ "Windows 98 (4.10)", 4, 10},
		{ "Windows NT 4.0 / Windows 95 (4.0)", 4, 0},
	};

	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);

	for (int i=0; i<sizeof(names); i++) {
		if (names[i].major == ver.dwMajorVersion &&
			names[i].minor == ver.dwMinorVersion)
		{
			return names[i].name;
		}
	}

	char buff[256];
	sprintf(buff, "Windows (%d.%d)\n", 
			ver.dwMajorVersion, ver.dwMinorVersion);

	return buff;
#else
	char buff[1024];
	FILE* fp = fopen("/proc/version", "r");
	int len = fread(buff, 1, 1024, fp);
	buff[len] = 0;
	fclose(fp);

	return buff;
#endif
}
/*}}}*/

// portMutex
portMutex::portMutex() /*{{{*/
{
	pthread_mutex_init(&m_mutex, NULL);
}
/*}}}*/

portMutex::~portMutex() /*{{{*/
{
	pthread_mutex_destroy(&m_mutex);
}
/*}}}*/

void portMutex::lock()/*{{{*/
{
	pthread_mutex_lock(&m_mutex);
}
/*}}}*/

bool portMutex::trylock()/*{{{*/
{
	return pthread_mutex_trylock(&m_mutex) == 0;
}
/*}}}*/

void portMutex::unlock()/*{{{*/
{
	pthread_mutex_unlock(&m_mutex);
}
/*}}}*/

pthread_mutex_t* portMutex::handle()/*{{{*/
{
	return &m_mutex;
}
/*}}}*/

// portCond
portCond::portCond() /*{{{*/
{
	pthread_cond_init(&m_cond, NULL);
	pthread_mutex_init(&m_cond_mutex, NULL);
}
/*}}}*/

portCond::~portCond() /*{{{*/
{
	pthread_cond_destroy(&m_cond);
	pthread_mutex_destroy(&m_cond_mutex);
}
/*}}}*/

bool portCond::wait(long long nsec) // true : signaled, false : timeout/*{{{*/
{ 
	if (nsec < 0) {
		pthread_mutex_lock(&m_cond_mutex);
		pthread_cond_wait(&m_cond, &m_cond_mutex);
	}
	else {
		struct timespec to;
		struct timeval now;
		gettimeofday(&now, NULL);

		long long to_ts = now.tv_sec * (1000*1000*1000) + now.tv_usec * 1000 + nsec;
		to.tv_sec = to_ts / (1000*1000*1000);
		to.tv_nsec = to_ts % (1000*1000*1000);

		pthread_mutex_lock(&m_cond_mutex);
		int ret = pthread_cond_timedwait(&m_cond, &m_cond_mutex, &to);
		if (ret == ETIMEDOUT) {
			return false;
		}

		if (ret == EINVAL) {
			return false;
		}
	}

	return true;
}
/*}}}*/

bool portCond::wait(portMutex* mutex, long long nsec) // true : signaled, false : timeout/*{{{*/
{ 
	if (nsec < 0) {
		pthread_cond_wait(&m_cond, mutex->handle());
	}
	else {
		struct timespec to;
		struct timeval now;
		gettimeofday(&now, NULL);

		long long to_ts = now.tv_sec * (1000*1000*1000) + now.tv_usec * 1000 + nsec;
		to.tv_sec = to_ts / (1000*1000*1000);
		to.tv_nsec = to_ts % (1000*1000*1000);
		
		int ret = pthread_cond_timedwait(&m_cond, mutex->handle(), &to);
		if (ret == ETIMEDOUT) {
			return false;
		}

		if (ret == EINVAL) {
			return false;
		}
	}

	return true;
}
/*}}}*/

void portCond::signal() /*{{{*/
{
	pthread_cond_signal(&m_cond);
}
/*}}}*/

// portFile
portFile::~portFile() /*{{{*/
{
	if (fp) fclose(fp);
	fp = NULL;
}
/*}}}*/

bool portFile::open(const std::string& name) /*{{{*/
{
	if (fp) close();
	fp = fopen(name.c_str(), "r+");
	return fp ? true : false;
}
/*}}}*/

bool portFile::create(const std::string& name) /*{{{*/
{
	if (fp) close();
	fp = fopen(name.c_str(), "w+");
	return fp ? true : false;
}
/*}}}*/

void portFile::close()/*{{{*/
{
	fclose(fp);
	fp = NULL;
}
/*}}}*/

bool portFile::open_force(const std::string& name) /*{{{*/
{
	if (open(name) == false)
		return create(name);

	return true;
}
/*}}}*/

std::string portFile::reads()/*{{{*/
{
	fseek(fp, 0, SEEK_END);

	std::string out;
	size_t s = size();
	char buff[1024];

	do {
		int ret = read(buff, 1, sizeof(buff));
		out += buff;
		if (ret < sizeof(buff)) break;
	} while(true);

	return out;
}
/*}}}*/

void portFile::writes(const std::string& str)/*{{{*/
{
	write((char*)str.c_str(), 1, str.size());
}
/*}}}*/

char* portFile::read()/*{{{*/
{
	fseek(fp, 0, SEEK_SET);

	size_t s = size();
	char* buff = new char[s];

	read(buff, 1, s);

	return buff;
}
/*}}}*/

size_t portFile::read(char* buff, int size, int count)/*{{{*/
{
	return fread(buff, size, count, fp);
}
/*}}}*/

size_t portFile::write(char* buff, int size, int count)/*{{{*/
{
	return fwrite(buff, size, count, fp);
}
/*}}}*/

size_t portFile::size()/*{{{*/
{
	size_t cp = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size_t ret = ftell(fp);
	fseek(fp, cp, SEEK_SET);

	return ret;
}
	/*}}}*/

