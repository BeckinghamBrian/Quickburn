// #include <SD.h>
#include <SPI.h>
#include <string>
#include <iostream>
#include <stdbool.h> // Allows use of booleans
#include <State.h>
#include "HX711.h"

#define SCK 27
#define DT 26

HX711 scale;

// put function declarations here:
void dataToBuffer1();
void dataToBuffer2();
void startHighSpeed();
void stopHighSpeed();
void readLoadCell();
void readData();
void writeData(int, float (*)[11]);

// Create an IntervalTimer object 
IntervalTimer myTimer, loadCell;

const int ledPin = LED_BUILTIN;  // the pin with a LED

const float sampleRate = 4500; // Hz

const float TIME_STEP = 1 / sampleRate;

const float highSpeed = 1000000 / sampleRate; // convert from Hz to microseconds
//const float highSpeed = 210; //4761.9 hz
const float lowSpeed = 10000;

#define BUFFER_SIZE 50  // Number of entries in each buffer
#define ENTRY_SIZE 11   // Number of float values per entry

// Define two buffers as 2D arrays of floats
float buffer1[BUFFER_SIZE][ENTRY_SIZE] = {{0.0}};
float buffer2[BUFFER_SIZE][ENTRY_SIZE] = {{0.0}};

// Define loadcell variable
long loadcell = 0;

// state machine byte
int newState = 0;

// Define index variables for each buffer
int buffer1_index = 0;
int buffer2_index = 0;

// buffer write flag
bool writeToBuffer1 = true;
// flags from writing data from a buffer to SD (serialout for now)
bool saveFromBuffer1 = false;
bool saveFromBuffer2 = false;

// Initialize all the pins we could want to use (only reading 9)
float pin1 = A9;    
float pin2 = A8; 
float pin3 = A7; 
float pin4 = A6; 
float pin5 = A5; 
float pin6 = A4; 
float pin7 = A3; 
float pin8 = A2; 
float pin9 = A1; 
float pin10 = A0; 
float pin11 = A17; 
float pin12 = A16; 
float pin13 = A15; 
float pin14 = A14; 
float pin15 = A11; 
float pin16 = A10; 

// Valve pin numbers
int NIV = 28;
int fuelVent = 29;
int oxVent = 30;
int MFV = 31;
int MOV = 32;
int RELAY_1 = 11;
int RELAY_2 = 12;

// SD card variable initializations
// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// Teensy audio board: pin 10
// Teensy 3.5 & 3.6 & 4.1 on-board: BUILTIN_SDCARD
// Wiz820+SD board: pin 4
// Teensy 2.0: pin 0
// Teensy++ 2.0: pin 20
const int chipSelect = BUILTIN_SDCARD;
// file name minus the file number
std::string baseFile = "dataFile";
// std::string opject we are using to build our filename
// I don't like how hard this was for me to figure out hopefully it's not super slow
std::string fileString;
// initialized filename variable, const is okay because it should only change on power cycles
const char* fileName;
// filename numbers will start at 1 and count up
int fileNum = 1;

std::string baseLog = "log";
std::string logString;
const char* logName;

void setup() {

  // LED for blinking while writing to SD
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // pin mode initializations
  pinMode(NIV, OUTPUT);
  pinMode(fuelVent, OUTPUT);
  pinMode(oxVent, OUTPUT);
  pinMode(MFV, OUTPUT);
  pinMode(MOV, OUTPUT);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);

  // set all pins low (closed) on power up
  digitalWrite(NIV, LOW);
  digitalWrite(fuelVent, LOW);
  digitalWrite(oxVent, LOW);
  digitalWrite(MFV, LOW);
  digitalWrite(MOV, LOW);
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);

  // start serial, i used 115200 because it was big, can always change this
  // baud rates must match on both ends of comms
  Serial.begin(115200);
  scale.begin(DT, SCK);

  // unsure if this is necessary but it works
  analogReadResolution(12);

  // attempt to initialize SD card
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  // unsure if this would resolve by plugging in a card 
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (!SD.begin(chipSelect)) {
      Serial.println("No SD card, insert a card and restart or go fuck yourself");
      delay(1000);
    }
  }
  // announce that we have a card and got past the blockage
  Serial.println("card initialized.");

  // tmp changes the int fileNum to a string to be concatenated
  std::string tmp = std::to_string(fileNum);

  // concatenate our first guess at a free filename into std::string object
  fileString = baseFile + tmp + ".txt";

  // check if the filename exists, iterate up until it does not
  while (SD.exists(fileString.c_str())){
    //iterate fileNum and retry the string
    fileNum = fileNum + 1;
    tmp = std::to_string(fileNum);
    fileString = baseFile + tmp + ".txt";
    logString = baseLog + tmp + ".log";
  }
  // give the filename to fileName in a const char* type so it can be used with the SD library
  fileName = fileString.c_str();
  logName = logString.c_str();
  // print our new filename so we can check it out
  Serial.println("new filename");
  Serial.println(fileName);

  // start the sampling rate object, this will interrupt (hopefully) all functions to maintain sample rate
  myTimer.begin(readData, lowSpeed);  // (program, delay in microseconds)
  // loadCell.begin(readLoadCell, 10000); // read loadcell every 100Hz
}

// The main program will print the data to serial monitor
void loop() {

  if (saveFromBuffer1) {
    writeData(1, buffer1);
  }

  if (saveFromBuffer2) {
    writeData(2, buffer2);
  }
  // Serial.println(Serial.available());
  if (Serial.available() > 0) {
    // Serial.println("input available");

    newState = Serial.read();
    // newState = newState - 49;
    // Serial.println(Serial.read());
    Serial.println(newState);
    switch (newState)
    {
    case 90:
      startHighSpeed();
      break;

    case 91:
      stopHighSpeed();
      break;
    
    default:
      stateMachine(&NIV, &fuelVent, &oxVent, &MFV, &MOV, newState, logName);
      break;
    }
    
  }
}

// put function definitions here:
void dataToBuffer1() {
  // read data into buffer1
  buffer1[buffer1_index][0] = micros();
  buffer1[buffer1_index][1] = analogRead(pin1);
  buffer1[buffer1_index][2] = analogRead(pin2);
  buffer1[buffer1_index][3] = analogRead(pin3);
  buffer1[buffer1_index][4] = analogRead(pin4);
  buffer1[buffer1_index][5] = analogRead(pin5);
  buffer1[buffer1_index][6] = analogRead(pin6);
  buffer1[buffer1_index][7] = analogRead(pin7);
  buffer1[buffer1_index][8] = analogRead(pin15);
  buffer1[buffer1_index][9] = analogRead(pin16);
  // buffer1[buffer1_index][10] = loadcell;
  buffer1[buffer1_index][10] = 0.0;
  buffer1_index++;
}

void dataToBuffer2() {

  // read data into buffer2
  buffer2[buffer2_index][0] = micros();
  buffer2[buffer2_index][1] = analogRead(pin1);
  buffer2[buffer2_index][2] = analogRead(pin2);
  buffer2[buffer2_index][3] = analogRead(pin3);
  buffer2[buffer2_index][4] = analogRead(pin4);
  buffer2[buffer2_index][5] = analogRead(pin5);
  buffer2[buffer2_index][6] = analogRead(pin6);
  buffer2[buffer2_index][7] = analogRead(pin7);
  buffer2[buffer2_index][8] = analogRead(pin8);
  buffer2[buffer2_index][9] = analogRead(pin9);
  // buffer2[buffer2_index][10] = loadcell;
  buffer2[buffer2_index][10] = 0.0;
  buffer2_index++;
}

void startHighSpeed(){
  myTimer.update(highSpeed);
}

void stopHighSpeed(){
  myTimer.update(lowSpeed);
}

void readLoadCell(){
  loadcell =  scale.get_units(10);
}

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void readData() {

  // Check if buffer 1 is full
  if (buffer1_index >= BUFFER_SIZE) {
    buffer1_index = 0;  // Reset index for buffer 1
    writeToBuffer1 = false; // when buffer1 is full flag will trip to write to buffer2 as buffer1 is saved
    saveFromBuffer1 = true; // flag tripped to begin saving from buffer1 to SD
    // xTaskNotifyGive(writeToTerminalFunction);  // Signal writeToTerminalTask to write to term
  }

  // Check if buffer 2 is full
  if (buffer2_index >= BUFFER_SIZE) {
    buffer2_index = 0;  // Reset index for buffer 2
    writeToBuffer1 = true; // when buffer2 is full flag will trip to write to buffer1 as buffer2 is saved
    saveFromBuffer2 = true; // flag tripped to begin saving from buffer2 to SD
    // xTaskNotifyGive(writeToTerminalFunction);  // Signal writeToTerminalTask to write to term
  }

  if (writeToBuffer1) {
    dataToBuffer1();
  }
  else {
    dataToBuffer2();
  }
}

void writeData(int buffer_select, float buffer[BUFFER_SIZE][ENTRY_SIZE]) {

  digitalWrite(LED_BUILTIN, HIGH);
  File dataFile = SD.open(fileName, FILE_WRITE);

  int i,j;
  
  // Serial.println("Printing buffer:");
  for (i=0;i<BUFFER_SIZE;i++) {
    for (j=0;j<ENTRY_SIZE;j++) {
      Serial.print(buffer[i][j]);
      Serial.print(" ");
      if (dataFile){
        // Serial.println("SD write");
        dataFile.print(buffer[i][j]);
        dataFile.print(" ");
      }
      buffer[i][j] = 0; // Clear buffer after writing
    }
    Serial.println(" ");
    if (dataFile){
      dataFile.println(" ");
    }
  }
  dataFile.flush();
  dataFile.close();
  Serial.flush();
  digitalWrite(LED_BUILTIN, LOW);

  if (buffer_select == 1) {
    saveFromBuffer1 = false; // flag tripped to cancel saving from buffer1 to SD
  }

  if (buffer_select == 2) {
    saveFromBuffer2 = false; // flag tripped to cancel saving from buffer1 to SD
  }

  // Clear buffer after writing
  // memset(buffer, 0, sizeof([BUFFER_SIZE][ENTRY_SIZE]));
}
