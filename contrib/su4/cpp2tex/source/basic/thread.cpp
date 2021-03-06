/*
 * This file [basic/thread.cpp] is part of the “libtamias” library
 * Copyright (c) 2007-2009 Oleg Davydov, Yury Petrov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Our contacts:
 *   mailto: burunduk3@gmail.com (Oleg Davydov)
 *   mailto: jpsbur@gmail.com (Yury Petrov)
 */

#include "../../include/basic/thread.h"

using tamias::Thread;
using tamias::FunctionThread;

namespace tamias
{
  void* threadRun( void* object );
}

void* tamias::threadRun( void* object )
{
  return ((Thread*)object)->run();
}

void* Thread::run()
{
  return NULL;
}

Thread::Thread()
{
}

Thread::Thread( const Thread &thread ) : threadHandle(thread.threadHandle)
{
}

Thread::~Thread()
{
}

Thread& Thread::operator = ( const Thread &thread )
{
  threadHandle = thread.threadHandle;
  return *this;
}

void Thread::create()
{
  ::pthread_create(&threadHandle, NULL, threadRun, this);
}

void Thread::cancel()
{
  ::pthread_cancel(threadHandle);
}

void Thread::sleep( const Time &time )
{
  struct timespec req;
  req.tv_sec = time.seconds();
  req.tv_nsec = time.nanoSeconds();
  ::nanosleep(&req, NULL);
}

void* FunctionThread::run()
{
  threadFunction();
  return NULL;
}

FunctionThread::FunctionThread( Function function ) : Thread(), threadFunction(function)
{
}

FunctionThread::FunctionThread( const FunctionThread &thread) : Thread(thread), threadFunction(thread.threadFunction)
{
}

FunctionThread::~FunctionThread()
{
}

FunctionThread& FunctionThread::operator = ( const FunctionThread &thread )
{
  Thread::operator = (thread);
  threadFunction = thread.threadFunction;
  return *this;
}

