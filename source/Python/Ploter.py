from ast import Lambda
from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt
import numpy as np
from tkinter import *

from .PlotOpt import PlotOpt  
from .ResultsReader import ResultsReader
from .Config import Config
from .Globals import *
from matplotlib import colors, rcParams
from matplotlib.ticker import FormatStrFormatter

class Ploter:

    reader:ResultsReader
    config:Config
    pltOpt:PlotOpt

    def __init__(self,config:Config , reader:ResultsReader):

        self.config = config
        self.reader = reader
        self.pltOpt = PlotOpt()
              
    def plotPolar(self):


        for i in range(len(self.config.filter.orbitList)): 

            orbit = self.config.filter.orbitList[i]
            n= orbit[0]
            k= orbit[1]
            lim = getlimits(n)
            if (i > 0 and  n!= self.config.filter.orbitList[i-1][0]) or i==0 :

                plt.figure()
                plt.xlabel(self.pltOpt.X_LABEL,fontdict=self.pltOpt.labelFont)
                plt.ylabel(self.pltOpt.Y_LABEL,fontdict=self.pltOpt.labelFont)
                plt.title(getPlotTitle(n),fontdict=self.pltOpt.titleFont)
                plt.xticks(fontsize=self.pltOpt.TICKS_FONT_SIZE)
                plt.yticks(fontsize=self.pltOpt.TICKS_FONT_SIZE)
                # plt.ylim(lim)

            # results = [Phi , Roh]
            results = self.reader.getResults(n,k,0)
            # results = [x , y]
            results = polarToCartzaian(results)

            lineType = getLineType(k)
            # exg k = 1
            #plt.plot(   X          ,          Y     , "-"   , label = "k = 1" )
            plt.plot(results[0]/self.pltOpt.unit,results[1]/self.pltOpt.unit,lineType,label = ('k = '+(str)(k)),linewidth = self.pltOpt.LINE_WIDTH-2)
            
            # uncomment to show plot legend
            if self.pltOpt.legendMode:
                plt.legend(frameon=True, loc='lower center', ncol=3)
            
            # plt.savefig("./plots/fig_%s_N_%d_2D.eps"%(self.config.timeStamp,n))

        # drow Center point
        plt.plot(0,0,'ko')

        plt.show()

    def plotDeltaPhi(self):

        sortedOrbitList = sorted(self.config.filter.orbitList,key=lambda x:x[1])

        for i in range(len(sortedOrbitList)): 

            orbit = sortedOrbitList[i]
            n= orbit[0]
            k= orbit[1]
            reletive = True
            if self.config.type == 1:
                reletive = False
            
            analical_val = calc_accrute_deltaPHi(k,reletive=reletive)
            # analical_val = 0
            
            if (i > 0 and  n!= sortedOrbitList[i-1][0]) or i==0:

                plt.figure()
                plt.ylabel(self.pltOpt.deltaPsi_Y_LABEL,fontdict=self.pltOpt.labelFont)
                plt.xlabel(self.pltOpt.deltaPsi_X_LABEL,fontdict=self.pltOpt.labelFont)
                plt.xticks(range(0,11),fontsize=self.pltOpt.TICKS_FONT_SIZE) 
                plt.yticks(fontsize=self.pltOpt.TICKS_FONT_SIZE)
                
                if self.pltOpt.digitsMode:

                    plt.gca().yaxis.set_major_formatter(FormatStrFormatter(self.pltOpt.y_digitsFormat))
                    plt.gca().xaxis.set_major_formatter(FormatStrFormatter(self.pltOpt.x_digitsFormat))
            
            results = np.unique(self.reader.getResults(n,k,0,reletive=True))
            analitcal = []

            for j in range(len(results)):
                analitcal.append(analical_val*j)
            
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :
                lineType = getLineType(k)
                plt.plot(analitcal,lineType,label = ('accurate K = '+(str)(k)),linewidth = self.pltOpt.LINE_WIDTH)
            
            marker = getMarkerType(k)

            plt.plot(results,marker,label = ('simulated N='+(str)(n)+' K = '+str(k)),markersize = self.pltOpt.MARKER_SIZE)
        
        plt.show()
        

    
    def plotDeltaPhiSpherical(self):

        
        sortedOrbitList = sorted(self.config.filter.orbitList,key=lambda x:x[1])
        for i in range(len(self.config.filter.orbitList)): 

            orbit = sortedOrbitList[i]

            n= orbit[0]
            k= orbit[1]
            m= orbit[2]
            reletive = True
            if self.config.type == 3:
                reletive = False
            
            analical_val = calc_accrute_deltaPHi(k,reletive=reletive)

            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :

                plt.figure()
                plt.ylabel(self.pltOpt.deltaPsi_Y_LABEL,fontdict=self.pltOpt.labelFont)
                plt.xlabel(self.pltOpt.deltaPsi_X_LABEL,fontdict=self.pltOpt.labelFont)
                plt.yticks(fontsize=self.pltOpt.TICKS_FONT_SIZE)
                
                if self.pltOpt.digitsMode:
                    plt.gca().yaxis.set_major_formatter(FormatStrFormatter(self.pltOpt.x_digitsFormat))
                    plt.gca().xaxis.set_major_formatter(FormatStrFormatter(self.pltOpt.y_digitsFormat))
            
            results = np.unique(self.reader.getResults(n,k,m,reletive=True))
            plt.xticks(range(0,len(results)+1),fontsize=self.pltOpt.TICKS_FONT_SIZE) 

            analitcal = []
            for j in range(len(results)):
                analitcal.append(analical_val*j)
            
            plt.plot(results,label = ('simulated N='+(str)(n)+' k='+str(k) + ' m='+str(m)),linewidth = self.pltOpt.LINE_WIDTH)
            
            if (i > 0 and  k!= sortedOrbitList[i-1][1]) or i==0 :

                plt.plot(analitcal,'.',label = ('accurate K = '+(str)(k)))

            plt.legend(frameon=True, loc='lower center', ncol=3)
        
        plt.show()
        
    def sphericalPlot(self):


        for i in range(len(self.config.filter.orbitList)): 
            
            orbit = self.config.filter.orbitList[i]
            n= orbit[0]
            k= orbit[1]
            m= orbit[2]

            if (i > 0 and  n!=self.config.filter.orbitList[i-1][0]) or i==0 :

                fig = plt.figure()
                ax = fig.add_subplot(projection = '3d')
         
                ax.set_xlabel(self.pltOpt.X_LABEL,fontdict = self.pltOpt.labelFont)
                ax.set_ylabel(self.pltOpt.Y_LABEL,fontdict = self.pltOpt.labelFont)
                ax.set_zlabel(self.pltOpt.Z_LABEL,fontdict = self.pltOpt.labelFont)

                lim = getlimits(orbit[0])
                
                ax.set_xlim(lim)
                ax.set_ylim(lim)
                ax.set_zlim(lim)
                
                ax.xaxis.set_tick_params(labelsize = self.pltOpt.TICKS_FONT_SIZE)
                ax.yaxis.set_tick_params(labelsize = self.pltOpt.TICKS_FONT_SIZE)
                ax.zaxis.set_tick_params(labelsize = self.pltOpt.TICKS_FONT_SIZE)

            results = self.reader.getResults(n,k,m)
            convertedResults = convertToSpherical(results) 
            ax.plot(-convertedResults[0]/self.pltOpt.unit,-convertedResults[1]/self.pltOpt.unit,-convertedResults[2]/self.pltOpt.unit,getLineType(k),label = ('k = %d m = %d')%(k,m),linewidth = self.pltOpt.LINE_WIDTH)
            
            if self.pltOpt.legendMode:

                plt.legend(frameon=True, loc='lower center', ncol=3)

            # plt.savefig("fig_%s_N_%d_3D.svg"%(self.config.timeStamp,n))

        plt.show()

