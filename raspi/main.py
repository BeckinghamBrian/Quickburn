# -*- coding: utf-8 -*-
"""
Created on Fri Jan  3 14:07:44 2025

@author: brian
"""
# import the base gui from gui.py
from gui import Ui_MainWindow

# import pyqt5 stuff and widgets
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from pyqtgraph import PlotWidget

# import image resource file
import stand_img_rc

# base imports needed for other stuff
import time
import traceback, sys
import serial
import numpy as np

teensy = serial.Serial(port='COM3', baudrate=115200, timeout=0)

FILE = open("test.txt", "w")

i = 0



class WorkerSignals(QObject):
    '''
    Defines the signals available from a running worker thread.

    Supported signals are:

    finished
        No data

    error
        tuple (exctype, value, traceback.format_exc() )

    result
        object data returned from processing, anything

    progress
        int indicating % progress

    '''
    # finished = pyqtSignal()
    error = pyqtSignal(tuple)
    # result = pyqtSignal(object)
    dataSig = pyqtSignal(object)


class Worker(QRunnable):
    '''
    Worker thread

    Inherits from QRunnable to handler worker thread setup, signals and wrap-up.

    :param callback: The function callback to run on this worker thread. Supplied args and
                     kwargs will be passed through to the runner.
    :type callback: function
    :param args: Arguments to pass to the callback function
    :param kwargs: Keywords to pass to the callback function

    '''

    def __init__(self, fn, *args, **kwargs):
        super().__init__()

        # Store constructor arguments (re-used for processing)
        self.fn = fn
        self.args = args
        self.kwargs = kwargs
        self.signals = WorkerSignals()

        # Add the callback to our kwargs
        self.kwargs['dataPacket'] = self.signals.dataSig

    @pyqtSlot()
    def run(self):
        '''
        Initialise the runner function with passed args, kwargs.
        '''

        # Retrieve args/kwargs here; and fire processing using them
        try:
            self.fn(*self.args, **self.kwargs)
        except serial.serialutil.PortNotOpenError:
            pass
        except ValueError as e:
            if e == "ValueError: I/O operation on closed file.":
                pass
        except:
            traceback.print_exc()
            exctype, value = sys.exc_info()[:2]
            self.signals.error.emit((exctype, value, traceback.format_exc()))
        else:
            # self.signals.result.emit(result)  # Return the result of the processing to be printed below by print_output
            print("hit the else statement")
        finally:
            # self.signals.finished.emit()  # Done <- this streams the output of thread_complete without passing data
            print("good exit")


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        
        self.setupUi(self)
        
        self.toggleNIV = '0'
        self.toggleOxVV = '0'
        self.toggleFuelVV = '0'
        self.toggleOxMPV = '0'
        self.toggleFuelMPV = '0'
        
        # plot lists
        self.plotTime = []
        self.N2_plot_data = []
        self.reg_plot_data = []
        self.ethTank_plot_data = []
        self.oxTank_plot_data = []
        self.ethMPV_press_plot_data = []
        self.oxMPV_press_plot_data = []
        self.pc_plot_data = []
        self.ethMPV_temp_plot_data = []
        self.oxMPV_temp_plot_data = []
        self.loadcell_plot_data = []

        self.commandtosend = bytes([0])
        self.newCommand = False
        
        # get primary state buttons wired up
        self.pressButton.clicked.connect(self.press)
        self.safeButton.clicked.connect(self.safe)
        self.closeAllButton.clicked.connect(self.closeAll)
        self.fireButton.clicked.connect(self.fire)
        self.openAllButton.clicked.connect(self.openAll)
        #self.pressButton.clicked.connect(lambda: self.press("pressButton"))
        
        # get the toggle buttons wired up
        self.toggleNIVButton.clicked.connect(lambda: self.toggle('toggleNIV'))
        self.toggleOxVVButton.clicked.connect(lambda: self.toggle('toggleOxVV'))
        self.toggleFuelVVButton.clicked.connect(lambda: self.toggle('toggleFuelVV'))
        self.toggleOxMPVButton.clicked.connect(lambda: self.toggle('toggleOxMPV'))
        self.toggleFuelMPVButton.clicked.connect(lambda: self.toggle('toggleFuelMPV'))
        
        # high speed on/off
        self.startHighSpeedButton.clicked.connect(self.startHighSpeed)
        self.stopHighSpeedButton.clicked.connect(self.stopHighSpeed)
        
        # the thread pool is threading within the pyqt5 gui
        self.threadpool = QThreadPool()
        print("Multithreading with maximum %d threads" % self.threadpool.maxThreadCount())
        
        #start data handling
        self.dataThreadStart()
        
        self.stateDict = {
            '00000' : 0,
            '01100' : 1,
            '10000' : 2,
            '10011' : 3,
            '11111' : 4,
            '00100' : 5,
            '01000' : 6,
            '00001' : 7,
            '00010' : 8,
            '10100' : 9,
            '11000' : 10,
            '11100' : 11,
            '00101' : 12,
            '00110' : 13,
            '00111' : 14,
            '01001' : 15,
            '01010' : 16,
            '01011' : 17,
            '01101' : 18,
            '01110' : 19,
            '01111' : 20,
            '10001' : 21,
            '10010' : 22,
            '00011' : 23,
            '10101' : 24,
            '10110' : 25,
            '10111' : 26,
            '11001' : 27,
            '11010' : 28,
            '11011' : 29,
            '11101' : 30,
            '11110' : 31
            }
        
    def closeAll(self):
        
        self.commandtosend = bytes([0])
        self.newCommand = True
        
        self.toggleNIV = '0'
        self.toggleOxVV = '0'
        self.toggleFuelVV = '0'
        self.toggleOxMPV = '0'
        self.toggleFuelMPV = '0'
        
        self.NIV_label.setText('CLOSED')
        self.NIV_label.setStyleSheet("background-color: black")
        self.ox_VV_label.setText('CLOSED')
        self.ox_VV_label.setStyleSheet("background-color: black")
        self.fuel_VV_label.setText('CLOSED')
        self.fuel_VV_label.setStyleSheet("background-color: black")
        self.LOX_MPV_label.setText('CLOSED')
        self.LOX_MPV_label.setStyleSheet("background-color: black")
        self.ETH_MPV_label.setText('CLOSED')
        self.ETH_MPV_label.setStyleSheet("background-color: black")
        
    def safe(self):
        
        self.commandtosend = bytes([1])
        self.newCommand = True
        
        self.toggleNIV = '0'
        self.toggleOxVV = '1'
        self.toggleFuelVV = '1'
        self.toggleOxMPV = '0'
        self.toggleFuelMPV = '0'
        
        self.NIV_label.setText('CLOSED')
        self.NIV_label.setStyleSheet("background-color: black")
        self.ox_VV_label.setText('OPEN')
        self.ox_VV_label.setStyleSheet("background-color: white")
        self.fuel_VV_label.setText('OPEN')
        self.fuel_VV_label.setStyleSheet("background-color: white")
        self.LOX_MPV_label.setText('CLOSED')
        self.LOX_MPV_label.setStyleSheet("background-color: black")
        self.ETH_MPV_label.setText('CLOSED')
        self.ETH_MPV_label.setStyleSheet("background-color: black")
        
    def press(self):
        
        self.commandtosend = bytes([2])
        self.newCommand = True
        
        self.toggleNIV = '1'
        self.toggleOxVV = '0'
        self.toggleFuelVV = '0'
        self.toggleOxMPV = '0'
        self.toggleFuelMPV = '0'
        
        self.NIV_label.setText('OPEN')
        self.NIV_label.setStyleSheet("background-color: white")
        self.ox_VV_label.setText('CLOSED')
        self.ox_VV_label.setStyleSheet("background-color: black")
        self.fuel_VV_label.setText('CLOSED')
        self.fuel_VV_label.setStyleSheet("background-color: black")
        self.LOX_MPV_label.setText('CLOSED')
        self.LOX_MPV_label.setStyleSheet("background-color: black")
        self.ETH_MPV_label.setText('CLOSED')
        self.ETH_MPV_label.setStyleSheet("background-color: black")
        
    def fire(self):
        
        self.commandtosend = bytes([3])
        self.newCommand = True
        
        self.toggleNIV = '1'
        self.toggleOxVV = '0'
        self.toggleFuelVV = '0'
        self.toggleOxMPV = '1'
        self.toggleFuelMPV = '1'
        
        self.NIV_label.setText('OPEN')
        self.NIV_label.setStyleSheet("background-color: white")
        self.ox_VV_label.setText('CLOSED')
        self.ox_VV_label.setStyleSheet("background-color: black")
        self.fuel_VV_label.setText('CLOSED')
        self.fuel_VV_label.setStyleSheet("background-color: black")
        self.LOX_MPV_label.setText('OPEN')
        self.LOX_MPV_label.setStyleSheet("background-color: white")
        self.ETH_MPV_label.setText('OPEN')
        self.ETH_MPV_label.setStyleSheet("background-color: white")
        
    def openAll(self):
        
        self.commandtosend = bytes([4])
        self.newCommand = True
        
        self.toggleNIV = '1'
        self.toggleOxVV = '1'
        self.toggleFuelVV = '1'
        self.toggleOxMPV = '1'
        self.toggleFuelMPV = '1'
        
        self.NIV_label.setText('OPEN')
        self.NIV_label.setStyleSheet("background-color: white")
        self.ox_VV_label.setText('OPEN')
        self.ox_VV_label.setStyleSheet("background-color: white")
        self.fuel_VV_label.setText('OPEN')
        self.fuel_VV_label.setStyleSheet("background-color: white")
        self.LOX_MPV_label.setText('OPEN')
        self.LOX_MPV_label.setStyleSheet("background-color: white")
        self.ETH_MPV_label.setText('OPEN')
        self.ETH_MPV_label.setStyleSheet("background-color: white")
        
    def toggle(self,btn):
        
        if btn == 'toggleNIV':
            if self.toggleNIV == '0':
                self.toggleNIV = '1'
                self.NIV_label.setText('OPEN')
                self.NIV_label.setStyleSheet("background-color: white")
            elif self.toggleNIV == '1':
                self.toggleNIV = '0'
                self.NIV_label.setText('CLOSED')
                self.NIV_label.setStyleSheet("background-color: black")
                    
        elif btn == 'toggleOxVV':
            if self.toggleOxVV == '0':
                self.toggleOxVV = '1'
                self.ox_VV_label.setText('OPEN')
                self.ox_VV_label.setStyleSheet("background-color: white")
            elif self.toggleOxVV == '1':
                self.toggleOxVV = '0'
                self.ox_VV_label.setText('CLOSED')
                self.ox_VV_label.setStyleSheet("background-color: black")
                    
        elif btn == 'toggleFuelVV':
            if self.toggleFuelVV == '0':
                self.toggleFuelVV = '1'
                self.fuel_VV_label.setText('OPEN')
                self.fuel_VV_label.setStyleSheet("background-color: white")
            elif self.toggleFuelVV == '1':
                self.toggleFuelVV = '0'
                self.fuel_VV_label.setText('CLOSED')
                self.fuel_VV_label.setStyleSheet("background-color: black")
                    
        elif btn == 'toggleOxMPV':
            if self.toggleOxMPV == '0':
                self.toggleOxMPV = '1'
                self.LOX_MPV_label.setText('OPEN')
                self.LOX_MPV_label.setStyleSheet("background-color: white")
            elif self.toggleOxMPV == '1':
                self.toggleOxMPV = '0'
                self.LOX_MPV_label.setText('CLOSED')
                self.LOX_MPV_label.setStyleSheet("background-color: black")
                    
        elif btn == 'toggleFuelMPV':
            if self.toggleFuelMPV == '0':
                self.toggleFuelMPV = '1'
                self.ETH_MPV_label.setText('OPEN')
                self.ETH_MPV_label.setStyleSheet("background-color: white")
            elif self.toggleFuelMPV == '1':
                self.toggleFuelMPV = '0'
                self.ETH_MPV_label.setText('CLOSED')
                self.ETH_MPV_label.setStyleSheet("background-color: black")
                
        else:
            print('somehow thru the btns')
            
        print(self.toggleNIV)
        print(self.toggleOxVV)
        print(self.toggleFuelVV)
        print(self.toggleOxMPV)
        print(self.toggleFuelMPV)
        temp = self.toggleNIV + self.toggleOxVV + self.toggleFuelVV + self.toggleOxMPV + self.toggleFuelMPV
                                         
        self.newCommand = True
        print(temp)
        print(self.stateDict[temp])
        print(bytes([self.stateDict[temp]]))
        self.commandtosend = bytes([self.stateDict[temp]])
        
    def startHighSpeed(self):
        
        self.newCommand = True
        self.commandtosend = bytes([90])

    def stopHighSpeed(self):
        
        self.newCommand = True
        self.commandtosend = bytes([91])
        
    def dataThreadStart(self):
        
        self.data_worker = Worker(self.dataHandling)
        self.data_worker.signals.dataSig.connect(self.displayData)
        self.threadpool.start(self.data_worker)
    
    def displayData(self, data):
        
        # print(data)
        try:
            self.N2_bottle_press_label.setText(data.split(' ')[1])
            self.Reg_Press_label.setText(data.split(' ')[2])
            self.ETH_Tank_label.setText(data.split(' ')[3])
            self.LOX_Tank_label.setText(data.split(' ')[4])
            self.ETH_MPV_Press_label.setText(data.split(' ')[5])
            self.LOX_MPV_Press_label.setText(data.split(' ')[6])
            self.PC_Press_label.setText(data.split(' ')[7])
            self.ETH_Temp_label.setText(data.split(' ')[8])
            self.LOX_Temp_label.setText(data.split(' ')[9])
            # self.loadcell_label.setText(data.split(' ')[10])
            
            self.plotTime.append(round((float(data.split(' ')[0]) / 1000000),1))
            self.N2_plot_data.append(float(data.split(' ')[1]))
            self.reg_plot_data.append(float(data.split(' ')[2]))
            self.ethTank_plot_data.append(float(data.split(' ')[3]))
            self.oxTank_plot_data.append(float(data.split(' ')[4]))
            self.ethMPV_press_plot_data.append(float(data.split(' ')[5]))
            self.oxMPV_press_plot_data.append(float(data.split(' ')[6]))
            self.pc_plot_data.append(float(data.split(' ')[7]))
            self.ethMPV_temp_plot_data.append(float(data.split(' ')[8]))
            self.oxMPV_temp_plot_data.append(float(data.split(' ')[9]))
            # self.loadcell_plot_data.append(float(data.split(' ')[10]))
        
            if len(self.plotTime) >= 50:
                self.plotTime.pop(0)
                self.N2_plot_data.pop(0)
                self.reg_plot_data.pop(0)
                self.ethTank_plot_data.pop(0)
                self.oxTank_plot_data.pop(0)
                self.ethMPV_press_plot_data.pop(0)
                self.oxMPV_press_plot_data.pop(0)
                self.pc_plot_data.pop(0)
                self.ethMPV_temp_plot_data.pop(0)
                self.oxMPV_temp_plot_data.pop(0)
                # self.loadcell_plot_data.pop(0)
                
            self.N2_Bottle_Press_Widget.plot(self.plotTime, self.N2_plot_data)
            self.N2_Bottle_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.N2_plot_data)+500), maxYRange = (max(self.N2_plot_data)+500))
            self.N2_Bottle_Press_Widget.getAxis('bottom').setLabel('Time', units='s')
            
            self.Reg_Press_Widget.plot(self.plotTime, self.reg_plot_data)
            self.Reg_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.reg_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.reg_plot_data)+500), maxYRange = (max(self.reg_plot_data)+500))
            
            self.ETH_Tank_Press_Widget.plot(self.plotTime, self.ethTank_plot_data)
            self.ETH_Tank_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.ethTank_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.ethTank_plot_data)+500), maxYRange = (max(self.ethTank_plot_data)+500))
            
            self.LOX_Tank_Press_Widget.plot(self.plotTime, self.oxTank_plot_data)
            self.LOX_Tank_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.oxTank_plot_data)+500), maxYRange = (max(self.oxTank_plot_data)+500))
            
            self.ETH_MPV_Press_Widget.plot(self.plotTime, self.ethMPV_press_plot_data)
            self.ETH_MPV_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.ethMPV_press_plot_data)+500), maxYRange = (max(self.ethMPV_press_plot_data)+500))
            
            self.LOX_MPV_Press_Widget.plot(self.plotTime, self.oxMPV_press_plot_data)
            self.LOX_MPV_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.oxMPV_press_plot_data)+500), maxYRange = (max(self.oxMPV_press_plot_data)+500))
            
            self.PC_Press_Widget.plot(self.plotTime, self.pc_plot_data)
            self.PC_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.pc_plot_data)+500), maxYRange = (max(self.pc_plot_data)+500))
            
            self.ETH_Temp_Widget.plot(self.plotTime, self.ethMPV_temp_plot_data)
            self.ETH_Temp_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.ethMPV_temp_plot_data)+500), maxYRange = (max(self.ethMPV_temp_plot_data)+500))
            
            self.LOX_Temp_Widget.plot(self.plotTime, self.oxMPV_temp_plot_data)
            self.LOX_Temp_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.oxMPV_temp_plot_data)+500), maxYRange = (max(self.oxMPV_temp_plot_data)+500))
            
            # self.N2_Bottle_Press_Widget.plot(self.plotTime, self.loadcell_plot_data)
            # self.N2_Bottle_Press_Widget.setLimits(xMin = self.plotTime[0], xMax = self.plotTime[-1], yMin = -100, yMax = (max(self.N2_plot_data)+400), minXRange = (self.plotTime[-1] - self.plotTime[0]), maxXRange = (self.plotTime[-1] - self.plotTime[0]), minYRange = (max(self.loadcell_plot_data)+500), maxYRange = (max(self.loadcell_plot_data)+500))
        
        except IndexError:
            pass
        
    def read(self):

        data = teensy.readline().decode("ascii")
        return   data
        
    def dataHandling(self, dataPacket):
        
        # starting state (close all)
        state=0
        print(state)
        print(self.commandtosend)
        teensy.write(self.commandtosend)
        counter = 0
        
        while (True):
            
            try:
                if (teensy.in_waiting > 0):
                    value = self.read()
                    FILE.write(value)
                    # print(value)
                    
                    if self.newCommand:
                        # print(self.commandtosend)
                        teensy.write(self.commandtosend)
                        self.newCommand = False
                        
                    if (counter % 100 == 0):
                        dataPacket.emit(value)
                        
                    counter = counter + 1
                    if counter >= 100:
                        counter = 0
            except serial.serialutil.SerialException:
                break
            
def cleanup():
    
    FILE.close()
    teensy.close()

QApplication.setAttribute(Qt.AA_EnableHighDpiScaling)
app = QApplication(sys.argv)
win = MainWindow()
win.showMaximized()
app.aboutToQuit.connect(cleanup)
sys.exit(app.exec_())
