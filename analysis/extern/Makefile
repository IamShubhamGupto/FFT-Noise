CC=gcc
EXE=extern
FLAGS=-O3 -lm -Wall
OUTPUT_PATH = bin
SRC_PATH = src

$(EXE): $(SRC_PATH)/main.c
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(SRC_PATH)/main.c $(FLAGS) -o $(OUTPUT_PATH)/$(EXE)
