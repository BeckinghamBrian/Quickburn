#include <iostream>
#include "State.h"


void stateMachine(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, int state_int, const char* logName) {
    File logFile = SD.open(logName, FILE_WRITE);
    logFile.println("stateMachine");
    logFile.println(state_int);

    switch (state_int)
    {
    case 79:
        close_all(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of close_all");
        logFile.close();
        break;
    
    case 39:
        safe(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of safe");
        logFile.close();
        break;
    
    case 78:
        press(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of press");
        logFile.close();
        break;
    
    case 19:
        fire(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of fire");
        logFile.close();
        break;
    
    case 77:
        open_all(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of open_all");
        logFile.close();
        break;
    
    case 38:
        vent_fuel(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of vent_fuel");
        logFile.close();
        break;
    
    case 76:
        vent_ox(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of vent_ox");
        logFile.close();
        break;
    
    case 9:
        main_fuel(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of main_fuel");
        logFile.close();
        break;
    
    case 75:
        main_ox(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of main_ox");
        logFile.close();
        break;
    
    case 37:
        valve1(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve1");
        logFile.close();
        break;
    
    case 74:
        valve2(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve2");
        logFile.close();
        break;
    
    case 18:
        valve3(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve3");
        logFile.close();
        break;
    
    case 73:
        valve4(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve4");
        logFile.close();
        break;
    
    case 36:
        valve5(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve5");
        logFile.close();
        break;
    
    case 72:
        valve6(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve6");
        logFile.close();
        break;
    
    case 4:
        valve7(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve7");
        logFile.close();
        break;
    
    case 71:
        valve8(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve8");
        logFile.close();
        break;
    
    case 35:
        valve9(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve9");
        logFile.close();
        break;
    
    case 70:
        valve10(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve10");
        logFile.close();
        break;
    
    case 17:
        valve11(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve11");
        logFile.close();
        break;
    
    case 69:
        valve12(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve12");
        logFile.close();
        break;
    
    case 34:
        valve13(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve13");
        logFile.close();
        break;
    
    case 68:
        valve14(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve14");
        logFile.close();
        break;
    
    case 8:
        valve15(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve15");
        logFile.close();
        break;
    
    case 67:
        valve16(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve16");
        logFile.close();
        break;
    
    case 33:
        valve17(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve17");
        logFile.close();
        break;
    
    case 95:
        valve18(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve18");
        logFile.close();
        break;
    
    case 47:
        valve19(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve19");
        logFile.close();
        break;
    
    case 94:
        valve20(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve20");
        logFile.close();
        break;
    
    case 23:
        valve21(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve21");
        logFile.close();
        break;
    
    case 93:
        valve22(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve22");
        logFile.close();
        break;
    
    case 46:
        valve23(NIV, fuelVent, oxVent, MFV, MOV, logFile);
        // Serial.println(state_int);
        logFile.println("out of valve23");
        logFile.close();
        break;
    
    default:
        // Serial.println("Defaulting out");
        // Serial.println(state_int);
        break;
    }
}

void close_all(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("close_all");
    // Serial.println("close_all");
    
}

void safe(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("safe");
    // Serial.println("safe");
    
}

void press(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("press");
    // Serial.println("press");
    
}

void fire(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("fire");
    // Serial.println("fire");

}

void open_all(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("open_all");
    // Serial.println("open_all");
    
}

void vent_fuel(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("vent_fuel");
    // Serial.println("vent_fuel");
    
}

void vent_ox(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("vent_ox");
    // Serial.println("vent_ox");
    
}

void main_fuel(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("main_fuel");
    // Serial.println("main_fuel");
    
}

void main_ox(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("main_ox");
    // Serial.println("main_ox");

}

void valve1(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("valve1");
    // Serial.println("valve1");

}

void valve2(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("valve2");
    // Serial.println("valve2");

}

void valve3(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, LOW);
    logFile.println("valve3");
    // Serial.println("valve3");

}

void valve4(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve4");
    // Serial.println("valve4");

}

void valve5(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve5");
    // Serial.println("valve5");

}

void valve6(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve6");
    // Serial.println("valve6");

}

void valve7(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve7");
    // Serial.println("valve7");

}

void valve8(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve8");
    // Serial.println("valve8");

}

void valve9(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve9");
    // Serial.println("valve9");

}

void valve10(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve10");
    // Serial.println("valve10");

}

void valve11(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve11");
    // Serial.println("valve11");

}

void valve12(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve12");
    // Serial.println("valve12");

}

void valve13(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve13");
    // Serial.println("valve13");

}

void valve14(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve14");
    // Serial.println("valve14");

}

void valve15(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve15");
    // Serial.println("valve15");
    
}

void valve16(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve16");
    // Serial.println("valve16");

}

void valve17(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve17");
    // Serial.println("valve17");

}

void valve18(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, LOW);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve18");
    // Serial.println("valve18");

}

void valve19(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve19");
    // Serial.println("valve19");

}

void valve20(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve20");
    // Serial.println("valve20");

}

void valve21(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, LOW);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve21");
    // Serial.println("valve21");

}

void valve22(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, HIGH);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, HIGH);
    digitalWrite(*MOV, LOW);
    logFile.println("valve22");
    // Serial.println("valve22");

}

void valve23(int* NIV, int* fuelVent, int* oxVent, int* MFV, int* MOV, File logFile){
    digitalWrite(*NIV, LOW);
    digitalWrite(*fuelVent, HIGH);
    digitalWrite(*oxVent, HIGH);
    digitalWrite(*MFV, LOW);
    digitalWrite(*MOV, HIGH);
    logFile.println("valve23");
    // Serial.println("valve23");

}