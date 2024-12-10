# -*- coding: utf-8 -*-
"""
Created on Sun Aug  4 10:39:54 2024

@author: brian
"""

import serial
from time import sleep
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk
import numpy as np

teensy = serial.Serial(port='COM3', baudrate=115200, timeout=0)

FILE = open("test.txt", "w")



# commandtosend = [0,1,0,0,0]
# # commandtosend = 0
# commandtosend = bytes([0])
# print(commandtosend)
# teensy.write(commandtosend)
print('hi')

i = 0

sleep(5)

def read():

    data = teensy.readline().decode("ascii")
    return   data


def main():
    global i
    state=0
    print(state)
    commandtosend = bytes([state])
    print(commandtosend)
    teensy.write(commandtosend)
    while (i<340):
        

    
        
        value = read()
    
        FILE.write(value)
        # print(value)
        i = i + 1
        if (i % 10 == 0):
            # print(value)
            state = state + 1
            if (i>330):
                state=0
            print(state)
            commandtosend = bytes([state])
            print(commandtosend)
            teensy.write(commandtosend)
        sleep(.01)
        # print(teensy.read())
            
        # if ((i%1)==0):
            # a=float(value.split(' ')[5])
            # print((value.split(' ')))
            # print(value)
            # print(commandtosend)
            # teensy.write(commandtosend)

            
        # sleep(.5)
        # if (i==1):
        #     commandtosend = [1,0,0,0,0]
        #     teensy.write(commandtosend)
        # if (i==2):
        #     commandtosend = [1,1,0,0,0]
        #     teensy.write(commandtosend)
        # if (i==3):
        #     commandtosend = [1,1,1,0,0]
        #     teensy.write(commandtosend)
        # if (i==4):
        #     commandtosend = [1,1,1,1,0]
        #     teensy.write(commandtosend)
        # if (i==5):
        #     commandtosend = [1,1,1,1,1]
        #     teensy.write(commandtosend)
        # if (i==6):
        #     commandtosend = [0,1,1,1,1]
        #     teensy.write(commandtosend)
        # if (i==7):
        #     commandtosend = [0,0,1,1,1]
        #     teensy.write(commandtosend)
        # if (i==8):
        #     commandtosend = [0,0,0,1,1]
        #     teensy.write(commandtosend)
        # if (i==9):
        #     commandtosend = [0,0,0,0,1]
        #     teensy.write(commandtosend)
        # if (i==10):
        #     commandtosend = [0,0,0,0,0]
        #     teensy.write(commandtosend)
        


main()

FILE.close()
teensy.close()