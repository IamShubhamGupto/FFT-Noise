# FFT-Noise
Utilizing 2D Fast Fourier Transforms on 2D vectors/ images to generate 1/f Noise.

## How to Compile & Run
<details>
  <summary><b> Linux & Mac </b> </summary>
  
  ```shell
  git clone https://github.com/IamShubhamGupto/FFT-Noise.git
  cd FFT-Noise
  make 
  ./bin/fft.out beta [path]
  ```  

  <b>EXAMPLE </b>
  
  ```shell
  make 
  ./bin/fft.out 1.7 
  ```

   ```shell
  make 
  ./bin/fft.out 1.7 samples/noise3.png
  ```
  
  Guide:
  
  ```
Usage: ./bin/fft.out beta [path]

beta - roughness factor

path - optional - path to a square input image, dimensions are a power of 2.
  ```
  #### Clean Up
  In order to clean the bin directory, run ```make clean```.

  In order to remove only the generated images, run ``` make cleanimg```.
</details> 

## Results

