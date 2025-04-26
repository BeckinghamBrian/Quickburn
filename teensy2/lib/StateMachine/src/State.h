#ifndef STATE_H
#define STATE_H
#include <Arduino.h>
#include <SD.h>

// rs serial define (i think this is rs485)
#define HWSERIAL Serial1

void stateMachine(int*, int*, int*, int*, int*, int, const char*);
void close_all(int*, int*, int*, int*, int*, File);
void safe(int*, int*, int*, int*, int*, File);
void press(int*, int*, int*, int*, int*, File);
void fire(int*, int*, int*, int*, int*, File);
void open_all(int*, int*, int*, int*, int*, File);
void vent_fuel(int*, int*, int*, int*, int*, File);
void vent_ox(int*, int*, int*, int*, int*, File);
void main_fuel(int*, int*, int*, int*, int*, File);
void main_ox(int*, int*, int*, int*, int*, File);
void valve1(int*, int*, int*, int*, int*, File);
void valve2(int*, int*, int*, int*, int*, File);
void valve3(int*, int*, int*, int*, int*, File);
void valve4(int*, int*, int*, int*, int*, File);
void valve5(int*, int*, int*, int*, int*, File);
void valve6(int*, int*, int*, int*, int*, File);
void valve7(int*, int*, int*, int*, int*, File);
void valve8(int*, int*, int*, int*, int*, File);
void valve9(int*, int*, int*, int*, int*, File);
void valve10(int*, int*, int*, int*, int*, File);
void valve11(int*, int*, int*, int*, int*, File);
void valve12(int*, int*, int*, int*, int*, File);
void valve13(int*, int*, int*, int*, int*, File);
void valve14(int*, int*, int*, int*, int*, File);
void valve15(int*, int*, int*, int*, int*, File);
void valve16(int*, int*, int*, int*, int*, File);
void valve17(int*, int*, int*, int*, int*, File);
void valve18(int*, int*, int*, int*, int*, File);
void valve19(int*, int*, int*, int*, int*, File);
void valve20(int*, int*, int*, int*, int*, File);
void valve21(int*, int*, int*, int*, int*, File);
void valve22(int*, int*, int*, int*, int*, File);
void valve23(int*, int*, int*, int*, int*, File);


#endif /* STATE_H */