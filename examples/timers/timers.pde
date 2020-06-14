// Created by Julius Bächle

#include <Timer.h>
#include <Scheduler.h>

void print1() {
  Serial.println("1");
}

void print2() {
  Serial.println("2");
}

Timer timer1(1000);
Timer timer2;


void setup() {
  Serial.begin(9600);
  
  timer1.SglTimeout.connect(print1);
  timer1.start();
  timer1.setSingleShot(true);

  timer2.setInterval(2000);
  timer2.setSingleShot(false);
  timer2.SglTimeout.connect(print2);
  timer2.start();
}

void loop() {
  Scheduler::exec();
}
