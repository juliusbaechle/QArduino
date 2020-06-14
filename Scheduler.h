#pragma once

#include "Vector.h"
class Thread;

class Scheduler {
public:
  static void exec();
  static void registerThread(Thread* thread);
  static void removeThread(Thread* thread);

  static void showLoad(bool show) { m_showLoad = show; };

private:
  static void monitorLoad(bool cycleWasIdle);
  static void printLoad(uint8_t loadCPU);
  static int  availableMemory();

private:
  static Vector<Thread*> m_threads;
  static bool m_showLoad;
};