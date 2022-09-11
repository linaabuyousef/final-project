from source.Python.Simlation import Simulation


def main():
    
    simulation  = Simulation("config.ini","filter.ini")
    simulation.start()

if __name__ == "__main__":
    main()