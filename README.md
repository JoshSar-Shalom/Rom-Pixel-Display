# Rom-Pixel-Display
Using [Sebastian Lague's Digital Logic Sim](https://github.com/SebLague/Digital-Logic-Sim) and a compiler I programed in C, I'm able to display a 16x16 pixel pattern on his program with binary machine instructions.

The open canvas of the simulator allowed me to freely experiment and test with any set up I wanted to work with after watching the explanatory videos that the developer has been posting on his youtube channel.
<br>
<br>
The main focus of this project was the display screen and the ROM chip (labeled in blue as "ROM 256x16").
<br>

<p float="left">
  <img src="image/Display_Assembly.png" width="600"/>
</p>
Everything to the left of the ROM chip, although visually complex, is a binary counter that allows for the ROM chip to increment each instruction by 1 line. The multiplexer labeled, "8 Bit 2-to-1 Multi" allows me to troubleshoot/reset the counter anytime I turn off its set input to zero, allowing for the integer 0 to be continuously inputted in the loop, effectively halting the ROM chip from executing its program.

# Modularity example
This is an example of how the chips are built from pre existing chips. This cycle of modularity repeats until it reaches the lowest level of logic gate in the software(NAND)
<br>
<p float="left">
  <img src="image/8BitRegister.png" width="240"/>
  <img src="image/4Bit.png" width="240"/>
  <img src="image/1Bit.png" width="240"/>
  <img src="image/DLatch.png" width="240"/>
</p>

# ROM
The developer of the simulator provided a built-in 256 Bit ROM chip in his latest update as of May 2025. This chip is what inspired me to make this project and allows binary input that can output to any chip as needed
<br>
After manual testing, I found that the pixel display addresses run left to right, bottom to top, so the binary code 
<br>
<p float="left">
  <img src="image/ROM.png" width="600"/>
  <img src="image/Display.png" width="400"/>
</p>

Without a compiler, the ROM wouldn't be able to perform more complex pattern and operations.

# Custom Compiler
So the bulk of the project was utlizing the SDL2 library with C to create an interface of a 16x16 pixel grid so I could display the image in the simulator


<br>
<img src="image/Compiler.png" width="550">

