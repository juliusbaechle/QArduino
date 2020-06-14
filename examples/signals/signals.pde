// Created by Julius Bächle

#include "QArduino.h"

void printNumber(int number) {
  Serial.println(number);
}

// Printer will be used, to show how to connect member functions
class Printer {
public:
  void print() {
    Serial.println("Printer");
  }

  void printText(char* text) {
    Serial.println(text);
  }
};

// Declare Signals with the correct parameter types
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
}

void loop() {
  // To call the connected functions you have to call emit and pass the parameters
  SglPrint.emit();
  SglPrintNumber.emit(2);
  SglPrintText.emit("QArduino");

  delay(1000);
}
