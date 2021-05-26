CC=gcc
EXE=fftNoise
FLAGS=-O3 -lm -Wall
OUTPUT_PATH = bin
SRC_PATH = src
INC_PATH = include

PNG_LIB = $(INC_PATH)/libattopng/libattopng.c

$(EXE): $(SRC_PATH)/main.c $(INC_PATH)/fft.h
	@mkdir -p $(OUTPUT_PATH)
	@mkdir -p output
	$(CC) $(SRC_PATH)/main.c $(PNG_LIB) $(FLAGS) -o $(OUTPUT_PATH)/$(EXE)

clean: 
	rm -f -r bin/ output/ analysis/*.csv analysis/*.png