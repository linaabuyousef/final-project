from distutils.command.config import config
import numpy as np
from .filter import Filter
from .Globals import*

class Config:
    
    revolutions:float
    iterationMode:bool
    deltaPsiMode:bool
    t_inrev:float
    itrations:int
    log_p:int
    filter:Filter
    type:int
    spherical:bool
    resultFormat:str
    timeStamp:str
    filePath:str
    fillterPath:str

    def __init__(self,configPath:str,filterpath:str = None):

        
        self.filePath = configPath
        self.fillterPath = filterpath
        self.filter = None
        self.readFromFile(configPath)

        if(filterpath != None):
        
            self.filter = Filter(filterpath,self.spherical)

    def writeToFile(self):
        
        configFile = open(self.filePath,"r")
        configLines = configFile.readlines()

        for i , currLine in enumerate(configLines):
            if "itrs" in  currLine:
                currLine = "itrs ="+(str)(self.itrations) +"\n"
            elif "logPerod" in currLine:
                currLine = "logPerod ="+(str)(self.log_p)+"\n"
            elif "Type" in currLine:
                currLine = "Type ="+(str)(self.type)+"\n"
            elif "revolutions" in currLine:
                currLine = "revolutions ="+(str)(self.revolutions)+"\n"
            elif "iterationMode" in currLine:
                currLine = "iterationMode ="+(str)(self.iterationMode) +"\n"
            elif "deltaPsiMode" in currLine:
                currLine = "deltaPsiMode ="+(str)(self.deltaPsiMode) +"\n"
            elif "t =" in currLine:
                currLine = "t =%E\n"%(self.t_inrev)

            configLines[i] = currLine

        configFile.close()
        configFile = open(self.filePath,"w")

        configFile.writelines(configLines)
        configFile.close()

    def readFromFile(self,filePath):
        
        metaFile = open(filePath,'r')
        configLines = metaFile.readlines()
        for i in range(len(configLines)):
            
            currLine = configLines[i]
            valueIndex = currLine.find('=')+1
            if "itrs" in  currLine:
                self.itrations = (int)(currLine[valueIndex:])
            elif "logPerod" in currLine:
                self.log_p = (int)(currLine[valueIndex:])
            elif "Type" in currLine:
                self.type = (int)(currLine[valueIndex:])
                if self.type > 2:
                    self.spherical = True
                else:
                    self.spherical =False
            elif "TimeStamp" in currLine:
                self.timeStamp = currLine[valueIndex:-1]
            elif "revolutions" in currLine:
                self.revolutions = (float)(currLine[valueIndex:])
            elif "iterationMode" in currLine:
                self.iterationMode = (bool)((int)(currLine[valueIndex:])) 
            elif "deltaPsiMode" in currLine:
                self.deltaPsiMode = (bool)((int)(currLine[valueIndex:])) 
            elif "t =" in currLine:
                self.t_inrev =  (float)(currLine[valueIndex:])
                 
       
        pathStr = RESULT_P+self.timeStamp+"/results_N%d/results_K%d"
        
        if self.spherical:
            pathStr+= "/results_M%d.txt"
        else:
            pathStr+= ".txt"

        self.resultFormat = pathStr
        if self.filter != None:

            self.filter.changeTimeStamp(self.timeStamp)

    def __str__(self) -> str:
        
        string ="Revolutions: "+(str)(self.revolutions)+"\n"
        string +="Iterirations: "+(str)(self.itrations)+"\n"
        string +="Iterirations mode:"+(str)(self.iterationMode)+"\n"
        string +="deltaPsi mode:"+(str)(self.deltaPsiMode)+"\n"
        string +="Time Step :"+(str)(self.t_inrev)+"\n"
        string +="Type :"+(str)(self.type)+"\n"
        string +="Log Period :"+(str)(self.log_p)+"\n"
        string +="Time Stamp :"+(str)(self.timeStamp)+"\n"
        
        return string
