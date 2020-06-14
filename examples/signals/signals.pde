// Created by Julius Bächle

#include "QArduino.h"

void print() {
  Serial.println("print");
}

void printNumber(int number) {
  Serial.println(number);
}

// Printer will be used, to show how to connect of member functions
class Printer {
public:
  void print() {
    Serial.println("Printer");
  }

  void printText(char* text) {
    Serial.println(text);
  }
};

// Declare Signals
Signal<int> SglPrintNumber;
Signal<> SglPrint;
Signal<char*> SglPrintText;

Printer printer;

void setup() {
  Serial.begin(9600);

  // Non member functions are connected by the function pointer only
  SglPrintNumber.connect(printNumber);

  // member functions are object-bound, so you have to pass the object pointer
  // to pass a member function, you have to use the SLOT(...) macro, in which you pass the parameter types
  SglPrint.connect(&printer, SLOT() Printer::print);
  SglPrintText.connect(&printer, SLOT(char*) Printer::printText);

  // you can connect more than one slot, and even mix member and non member functions
  SglPrint.connect(print);
}

void loop() {
  static int i = 0;

  // To call the connected functions you call emit and pass the parameters
  SglPrintNumber.emit(i++);
  SglPrint.emit();
  SglPrintText.emit("QArduino");

  Serial.println();
  delay(1000);
}
