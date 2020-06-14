#include <Arduino.h>
#include "Scheduler.h"
#include "Thread.h";

#define MAXIMUM_INT_64 0x7FFFFFFFFFFFFFFF

Vector<Thread*> Scheduler::m_threads(5);
bool Scheduler::m_showLoad = false;

void Scheduler::exec() {
  while (true) {
    int64_t minDeadline = MAXIMUM_INT_64;
    Thread* nextThread = nullptr;
    
    for (Thread* thread : m_threads) {
      if (!thread->isReady())
        continue;      

      int64_t deadline = thread->getTimeToDeadline();

      if (deadline < minDeadline) {
        nextThread = thread;
        minDeadline = deadline;
      }
    }

    if (nextThread != nullptr)
      nextThread->exec();

    if(m_showLoad)
      monitorLoad(nextThread == nullptr);
  }
}

void Scheduler::registerThread(Thread* thread) {
  m_threads << thread;
}

void Scheduler::removeThread(Thread* thread) {
  m_threads.removeAll(thread);
}



void Scheduler::monitorLoad(bool cycleWasIdle) {
  static uint32_t lastCycle = 0;
  static uint32_t msIdle = 0;
  static uint32_t msWork = 0;
  
  if (cycleWasIdle)
    msIdle += (millis() - lastCycle);
  else
    msWork += (millis() - lastCycle);

  if (msWork + msIdle > 1000) {
    uint8_t percentCPU = (100 * msWork) / (msWork + msIdle);
    msIdle = 0;
    msWork = 0;
  
    printLoad(percentCPU);
  }

  lastCycle = millis();
}

void Scheduler::printLoad(uint8_t loadCPU) {
  static uint8_t ramUpdateCounter = 4;

  if (ramUpdateCounter == 4) {
    uint8_t loadRAM = 100 * (8192.0 - (float)availableMemory()) / 8192;

    Serial.print("CPU: ");
    Serial.print(loadCPU);
    Serial.print("%, RAM: ");
    Serial.print(loadRAM);
    Serial.println("%");
    ramUpdateCounter = 0;
  }
  else {
    Serial.print("CPU: ");
    Serial.print(loadCPU);
    Serial.println("%");
    ramUpdateCounter++;
  }
}

int Scheduler::availableMemory() {
  // Scanning RAM takes 82 ms (Mega, 82% load)

  int size = 8192;
  byte* buf;
  while ((buf = (byte*)malloc(--size)) == NULL);
  free(buf);
  return size;
}