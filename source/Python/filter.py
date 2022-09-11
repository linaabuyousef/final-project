import os
from .Globals import *

class Filter:
    
    orbitList = []

    def __init__(self,filterPath:str,sperical:bool):

        filterFile = open(filterPath,"r")
        
        filterLines = filterFile.readlines()
        orbit = [-1,-1,-1]

        for i in range(len(filterLines)):

            currLine = filterLines[i]
            #parse all N Segments    
            if 'N' in currLine:
                orbit[0] =(int)(currLine[currLine.find("N")+1])
                
                if "{}" in currLine:
                
                    if sperical:
                
                        for j in range(1,orbit[0]+1):
                            orbit[1] = j

                            for k in range(j+1):
                                orbit[2] = k
                                self.orbitList.append(orbit.copy())
                    else:
                        for j in range(1,orbit[0]+1):
                            orbit[1] = j
                            self.orbitList.append(orbit.copy())

            #parse all K segments
            elif 'K' in currLine:
                orbit[1] =(int)(currLine[currLine.find("K")+1])
                
                if not sperical:
                    self.orbitList.append(orbit.copy())
                
                elif "{}" in currLine  and sperical:
                
                    for j in range(orbit[1]+1):
                        orbit[2] = j
                        self.orbitList.append(orbit.copy())

            if sperical:
                #parse all Msegments 
                if 'M' in currLine:    
                    orbit[2] =(int)(currLine[currLine.find("M")+1])
                    self.orbitList.append(orbit.copy())
                
    def changeTimeStamp(self,timeStamp:str):
        
        
        self.orbitList = []
        # get all folders in timestamp folder
        nFileList = sorted(os.listdir(RESULT_P+timeStamp))
        # remove unwanted file fom list
        if("meta.txt" in nFileList):
            nFileList.remove("meta.txt")
        
        kLists = []
        #get all folders or files that contain K in the name
        for nDir in nFileList:
            kLists.append(sorted(os.listdir(RESULT_P+timeStamp+"/"+nDir)))
        #if thay are not txt file then create list for the m files
        if(".txt" not in kLists[0][0]):
            mLists = []
            for i in range(len(nFileList)):
                for j in range(len(kLists[i])):
                    mLists.append(sorted(os.listdir(RESULT_P+timeStamp+"/"+nFileList[i] +"/"+kLists[i][j])))


            m_index = 0
            # fill the orbits in the orbit list
            for n_index in range(len(nFileList)):
                n =(int)(nFileList[n_index][-1:])
                
                for k_index in range(len(kLists[n_index])):
                
                    k = (int)(kLists[n_index][k_index][-1:])

                    for j in range (len(mLists[m_index])):
                        mFile = mLists[m_index][j]
                        m = mFile[mFile.find(".")-1:]
                        m = (int)(m[0:1])
                        self.orbitList.append([n,k,m])

                    m_index+=1
        else:
            # 2D only n and k are relavent m = -1
            for n_index in range(len(nFileList)):
                n =(int)(nFileList[n_index][-1:])

                for k_index in range(len(kLists[n_index])):
                    k = kLists[n_index][k_index]
                    k = k[k.find(".")-1:]
                    k = (int)(k[0:1])
                    self.orbitList.append([n,k,-1])
    
    def __str__(self):

        string = "[n,k,m]\n"
        
        for i in range(len(self.orbitList)):
            n = self.orbitList[i][0]
            if i > 0 and self.orbitList[i-1][0] != n:
                string+="  " 
            string += str(self.orbitList[i])
        
        return string