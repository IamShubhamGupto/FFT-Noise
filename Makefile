CC=gcc
EXE=fftNoise
FLAGS=-O3 -lm -g
OUTPUT_PATH = bin
SRC_PATH = src
INC_PATH = include

$(EXE): $(SRC_PATH)/main.c $(INC_PATH)/fft.h
	@mkdir -p $(OUTPUT_PATH)
	@mkdir -p output
	$(CC) $(SRC_PATH)/main.c $(FLAGS) -o $(OUTPUT_PATH)/$(EXE)

clean: 
	rm -f -r bin/ output/