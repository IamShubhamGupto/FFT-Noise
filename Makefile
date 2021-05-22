CC=gcc
EXE=fft.out
FLAGS=-O3 -lm -g 
OUTPUT_PATH = bin
SRC_PATH = src

$(EXE): $(SRC_PATH)/main.c $(SRC_PATH)/fft.h
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(SRC_PATH)/main.c $(FLAGS) -o $(OUTPUT_PATH)/$(EXE)

clean: 
	rm -f -r bin/

cleanimg:
	rm -f bin/*.png