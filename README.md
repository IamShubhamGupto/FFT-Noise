<br />
<p align="center">

  <h1 align="center">FFT-Noise</h1>
  
<p align="center">
    <img src="./Assets/ifft_24.png" alt="FFT-Noise Sample" width="200px" height="200px">
</p>

  <p align="center">
    2D Fractal Noise using Fast Fourier Transforms.
    <br />
    <a href="https://github.com/IamShubhamGupto/FFT-Noise/blob/main/docs/ifft_24.png">View Demo</a>
    ·
    <a href="https://github.com/IamShubhamGupto/FFT-Noise/issues/new">Report Bug</a>
  </p>
</p>

# What is this?

FFT-Noise is an implementation of a method of producing Fractal Noise using Fast Fourier Transforms based on a method found in an [HRUMC Presentation](https://web.williams.edu/Mathematics/sjmiller/public_html/hudson/Dickerson_Terrain.pdf) by **Krista Bird**, **Thomas Dickerson**, and **Jessica George**<sup>1</sup>.

It takes in an array of random points as input (possibly from an image) and returns FFT-Noise generated from it. The Noise looks something like this:

<p align="center">
    <img src="./Assets/ifft_24.png" alt="FFT-Noise Sample">
</p>

This noise can be used in procedural texture and terrain generation.

# Usage

### Build 

Compile C files into binary.

```bash
$ make
```

### Run 

Generate FFT-Noise

```bash
$ bin/fftNoise <roughness> [<image>]
```

| Param | Required | Discription
|-------|---------|-------------|
| roughness | `true` | A floating point number. Ideal range [2,5] |
| image | `false` | Input image path. Must be square PNG with dimention being a power of 2 |

### Clean 

Delete transient files.

```bash
$ make clean
```

# Credits

**Special thanks to [Faraz Shaikh](https://github.com/FarazzShaikh) for introducing me to noise generation and terrain building 🤯**

| Refrence | Source | 
|----------|--------|
| <sup>1</sup>Techniques for Fractal Terrain Generation | [Krista Bird, et al.](https://web.williams.edu/Mathematics/sjmiller/public_html/hudson/Dickerson_Terrain.pdf) | 
| 2D FFT Function | [Karim Naaji](https://github.com/karimnaaji/fft) | 
| Generating noise with different power spectra laws | [Paul Bourke](http://paulbourke.net/fractals/noise/) |
| Fractal Landscapes via FFT | [RISC](https://www3.risc.jku.at/education/courses/ws2016/cas/landscape.html) | 
| Image filtering in the frequency domain | [Václav Hlaváč](http://people.ciirc.cvut.cz/~hlavac/TeachPresEn/11ImageProc/13FourierFiltrationEn.pdf) | 
| Image Enhancement in the Frequency Domain | [cs.tut.fi](http://www.cs.tut.fi/~moncef/SGN-3016-DIP/Chap04.pdf) | 
| Moving into the Frequency Domain | [Cardiff University](http://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/09_CM0268_Frequence_Space.pdf) | 


# Benchmarks

*Coming Soon!*