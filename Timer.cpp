#include "Timer.h"
#include "Arduino.h"

Timer::Timer(int32_t a_interval)
  : Thread(a_interval)
{}

void Timer::setInterval(int32_t a_interval)
{
  m_interval = a_interval;
}

void Timer::setSingleShot(bool a_bSingleShot)
{
  m_bIsSingleShot = a_bSingleShot;
}

void Timer::start()
{
  m_bConsumed = false;
  m_lastMillis = millis();
}

void Timer::stop()
{
  m_bConsumed = true;
}

void Timer::exec()
{
  if (m_bIsSingleShot) m_bConsumed = true;   
  SglTimeout.emit();
  m_lastMillis += m_interval;
}

bool Timer::isReady() const
{
  return !m_bConsumed && (getTimeToDeadline() <= 0);
}

bool Timer::isActive() const
{
  return !m_bConsumed;
}