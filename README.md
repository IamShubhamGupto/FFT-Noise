# FFT-Noise
Utilizing 2D Fast Fourier Transforms on 2D vectors/ images to generate 1/f Noise.

## How to Compile & Run
<details>
  <summary><b> Linux & Mac </b> </summary>
  
  ```shell
  git clone https://github.com/IamShubhamGupto/FFT-Noise.git
  cd FFT-Noise
  make 
  ./bin/fft.out ./bin/fft.out mode path-to-input-image beta
  ```  

  <b>EXAMPLE </b>
  
  ```shell
  make 
  ./bin/fft.out 2 "samples/download.png" 1.70 
  ```
  
  Guide:
  
  ```
Usage: ./bin/fft.out mode path-to-input-image beta
mode:

        1 - Direct Fourier Transform

        2 - Inverse Fourier Transform

beta - roughness factor
  ```
  #### Clean Up
  In order to clean the bin directory, run ```make clean```.

  In order to remove only the generated images, run ``` make cleanimg```.
</details> 

## Results

