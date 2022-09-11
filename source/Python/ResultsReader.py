from distutils.command.config import config
from pickle import TRUE
import numpy as np
from source.Python.Config import Config
import os
from .Globals import*

class ResultsReader:

    config:Config

    def __init__(self,config:Config):
        self.config = config

    def getResults(self,n:int,k:int,m:int,reletive=False):

        if(self.config.spherical):
            resultFile = open(self.config.resultFormat%(n,k,m),"r")
        else:
            resultFile = open(self.config.resultFormat%(n,k),"r")

        resultLines = resultFile.readlines()
        
        resultsArr = []
        phi_arr = []
        roh_arr = []
        th_arr = []
        delphi_arr = []
        
        for i in range(len(resultLines)):
            
            currLine = resultLines[i]
            
            if reletive:
                dt_index = currLine.find("deltaPhi= ")+10
                dt_val = currLine[dt_index:]
                delphi = (float)(dt_val[:dt_val.find("\t")])
                delphi_arr.append(delphi)
                continue

            r_index = currLine.find("r= ")+3
            r_val = currLine[r_index:]
            r = (float)(r_val[:r_val.find("\t")])
            roh_arr.append(r)

            phi_index = currLine.find("phi= ")+5
            phi_val = currLine[phi_index:]
            phi = (float)(phi_val[:phi_val.find("\t")])
            phi_arr.append(phi)
            
            if self.config.spherical:
                th_index = currLine.find("theta= ")+7
                th_val = currLine[th_index:]
                th = (float)(th_val[:th_val.find("\t")])
                th_arr.append(th)
            
        if reletive:
            return np.vstack((delphi_arr))

        if self.config.spherical:
            resultsArr = np.vstack((phi_arr,th_arr,roh_arr))
        else:
            resultsArr = np.vstack((phi_arr,roh_arr))

        return resultsArr 
    