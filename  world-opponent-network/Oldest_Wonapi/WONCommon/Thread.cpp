#define __WON_MASTER_CPP__
#include "Thread.h"

using namespace WONAPI;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ThreadBase::ThreadBase() 
{
	mStopped = true;
	mRunning = false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ThreadBase::~ThreadBase() 
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ThreadBase::Start() 
{
	if(!mRunning)
	{
		mStopped = false; 
		mRunning = true;
		StartHook();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ThreadBase::Stop(bool waitForStop) 
{ 
	if(!mStopped)
	{
		mStopped = true; 
		Signal(); 
		if(waitForStop)
			WaitForStop();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ThreadBase::Signal() 
{ 
	mSignalEvent.Set(); 
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool ThreadBase::InThisThread() 
{ 
	if(!mRunning)
		return false;
	else
		return InThisThreadHook();
}
	

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void ThreadBase::WaitForStop() 
{
	if(mRunning && !InThisThread())
		WaitForStopHook();
}
