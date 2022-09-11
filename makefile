CC = gcc
EXE = electronSimulation
CFLAGS = -mhard-float -O3 
MAIN_PY = main.py

ifeq ($(OS),Windows_NT)
RUN_P = python $(MAIN_PY)
else
RUN_P = python3 $(MAIN_PY)
endif

SOURCE_P = source/C/

config_path = $(SOURCE_P)config/
util_path = $(SOURCE_P)utility/
polar_path = $(SOURCE_P)Polar/
spherical_path = $(SOURCE_P)Spherical/
spin_path = $(SOURCE_P)Spin/

calculations_wildCard = calculations/*.c

calculations_files = $(polar_path)$(calculations_wildCard) $(spherical_path)$(calculations_wildCard) $(spin_path)$(calculations_wildCard)
simulation_files = $(polar_path)*.c $(spherical_path)*.c $(spin_path)*.c
util_files = $(util_path)*.c 
config_files = $(config_path)*.c
main_file = $(SOURCE_P)main.c

source_files = $(util_files) $(config_files) $(calculations_files) $(simulation_files) $(main_file)



defult: 
	$(CC) $(CFLAGS) $(source_files) -lm -o $(EXE)
run:
	./$(EXE)
plot:
	$(RUN_P)
val: 
	valgrind  --leak-check=full --show-leak-kinds=all ./$(EXE)
	