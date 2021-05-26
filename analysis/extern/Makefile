CC=gcc
EXE=extern
FLAGS=-O3 -lm
OUTPUT_PATH = bin
SRC_PATH = src

$(EXE): $(SRC_PATH)/main.c
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(SRC_PATH)/main.c $(FLAGS) -o $(OUTPUT_PATH)/$(EXE)

clean: 
	rm -f -r bin/ output/ analysis/*.csv analysis/*.png