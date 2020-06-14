#pragma once

#include "Thread.h"

//----------------------------------------------------------
// Calls the callback after a certain time 
// (-10% ... infinite because of non preemptive scheduling)
//----------------------------------------------------------
class Timer : public Thread
{
public:
  Timer(int32_t a_interval = 1000);

  void setInterval(int32_t a_interval);
  void setSingleShot(bool a_bSingleShot);
  void start();
  void stop();
  bool isActive() const;

protected:
  void exec();
  bool isReady() const;

private:
  bool m_bIsSingleShot = false;
  bool m_bConsumed = true;
};
