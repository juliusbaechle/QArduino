#pragma once

#include "Signal.h"

//----------------------------------------
// Minimal Interval 25ms
//----------------------------------------
class Thread {
  friend class Scheduler;

public:
  Thread(uint16_t a_interval);
  ~Thread();
  
public:
  Signal<> SglTimeout;

protected:
  virtual void exec();
  int32_t getTimeToDeadline() const;
  virtual bool isReady() const;

protected:
  uint16_t m_interval = 0;
  uint32_t m_lastMillis = 0;
};