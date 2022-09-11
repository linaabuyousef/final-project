class PlotOpt:

    digitsModelse:bool
    legendModelse:bool
    x_digitsFormat:str
    y_digitsFormat:str
    deltaPsi_Y_LABEL:str
    deltaPsi_X_LABEL:str
    X_LABEL:str
    Y_LABEL:str
    Z_LABEL:str
    labelFont:dict
    titleFont:dict
    LINE_WIDTH:int
    TICKS_FONT_SIZE:int
    MARKER_SIZE:int
    unit:float
    def __init__(self):

        self.digitsMode = False
        self.legendMode = False
        self.x_digitsFormat = '%.1f'
        self.y_digitsFormat = '%.1f'
        self.deltaPsi_Y_LABEL = "$\Delta\psi$"
        self.deltaPsi_X_LABEL = "revolution number"
        self.X_LABEL = "X($\AA$)"
        self.Y_LABEL = "Y($\AA$)"
        self.Z_LABEL = "Z($\AA$)"
        self.labelFont = {
            'color':  'black',
            'weight': 'normal',
            'size': 30,
            }
        self.titleFont = {
            'color':  'black',
            'weight': 'normal',
            'size': 18,
            }
        self.LINE_WIDTH = 5
        self.TICKS_FONT_SIZE = 20
        self.MARKER_SIZE = 10
        self.unit = 1e-8