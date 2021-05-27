CC=gcc
EXE=fftNoise
FLAGS=-O3 -lm
OUTPUT_PATH = bin
SRC_PATH = src
INC_PATH = include

PNG_LIB = $(INC_PATH)/libattopng/libattopng.c
PNG_LIB2 = $(INC_PATH)/upng/upng.c

$(EXE): $(SRC_PATH)/main.c $(INC_PATH)/fft.h
	@mkdir -p $(OUTPUT_PATH)
	@mkdir -p output
	$(CC) $(SRC_PATH)/main.c $(PNG_LIB) $(PNG_LIB2) $(FLAGS) -o $(OUTPUT_PATH)/$(EXE)

clean: 
	rm -f -r \
		bin/ \
		analysis/extern/bin/ \
		output/ \
		analysis/*.csv \
		analysis/plots/