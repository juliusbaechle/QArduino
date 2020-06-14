#include "Thread.h"
#include "Scheduler.h"
#include "Arduino.h"

Thread::Thread(uint16_t a_interval)
  : m_interval(a_interval) 
{
  m_interval = a_interval > 10 ? a_interval : 10;
  m_lastMillis = 0;

  Scheduler::registerThread(this);
}

Thread::~Thread() {
  Scheduler::removeThread(this);
}

int32_t Thread::getTimeToDeadline() const { 
  return (m_lastMillis - millis()) + m_interval;
}

void Thread::exec() { 
  SglTimeout.emit();
  m_lastMillis = millis();
}

bool Thread::isReady() const {
  return true;
}