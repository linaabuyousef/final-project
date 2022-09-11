
from .Config import Config
from .Ploter import Ploter
from .ResultsReader import ResultsReader
from .UI import UI
from tkinter import *
from .Globals import*

class Simulation:
    
    config:Config
    reader:ResultsReader
    ploter:Ploter
    ui:UI

    def __init__(self,configPath:str,filterPath:str):

        self.config = Config(configPath,filterPath)
        self.reader =  ResultsReader(self.config)
        self.ploter = Ploter(self.config,self.reader)
        self.ui = UI(self.config,self.reader,self.ploter)

    def start(self):
        self.ui.root.mainloop()
