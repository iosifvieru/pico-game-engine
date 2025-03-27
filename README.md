# 2D Game Engine for Embedded Systems

This project focuses on developing a 2D Game engine for low-cost embedded systems. It is part of my bachelor's degree paper.
My implementation is based on RP2040 microcontroller found on boards like Raspberry Pi Pico and Marble Pico.

## Usage

### 1. Prerequisites
Before using the engine, make sure you have the following installed:

- Raspberry Pi Pico SDK
- CMake
- ARM GCC Toolchain
- Ninja
- VS Code Raspberry Pi Pico Extension (optional)

### 2. Cloning the Repository

    git clone https://github.com/iosifvieru/pico-game-engine.git
    cd pico-game-engine

### 3. Building the project
Before building the project:
- Hold the BOOTSEL button on the Pico.
- Plug it into your computer via USB.

Run the following script to build the project:
    
    ./build-pico.sh

If for some reason you don't have permission try using:

    sudo ./build-pico.sh

This script will:
- Initialize CMake.
- Build the project using the Pico SDK.
- Generate a .uf2 file for flashing.
- Flash the .uf2 file to your Pico.
- Restart the pico and start running the new code.

You can alternatively use the VS Code Raspberry Pi Pico Extension to do all this with just a click.

## Hardware setup
### **Marble Pico**
Marble Pico is a development board based on RP2040 produced by Raspberry Pi. It is fully compatible with Raspberry Pi Pico (the board has the same pinout as pico) but it has some upgrades such as:
- USB type C (Pico has micro USB)
- microSD Card adaptor
- 8 MB of QSPI Flash (as opposed to 2MB on Pi Pico)
- I2C 3v3 connector

**General pin functions**:
- VBUS - the input voltage on the board from the USB cable. This pin can be used to power the board from a 5V DC external source.
- VSYS - if the board is powered by USB, this pin can be used as a power source for other modules. 200mA - peak current consumption.
- 3V3 - a 3.3V power source generated by the onboard voltage regulator.
- GND - ground pin
- ADC_VREF: reference voltage for ADC conversion.
- GPIO Pins: 25 pins for input and output. Note that GPIO15 has a "special function during board reset" on Marble Pico.

Pinout schematic can be found [here](https://github.com/GroundStudio/GroundStudio_Marble_Pico/blob/main/Documentation/REV0.0.3/RLJDMV_GS%20REV0.0.3%20GroundStudio%20Marble%20Pico%20Pinout%20REV%201.1.pdf).
Official Marble Pico repo: [here](https://github.com/GroundStudio/GroundStudio_Marble_Pico).


### **RP2040**
RP2040 is a 32-bit dual ARM Cortex-M0+ microcontroller produced by Raspberry Pi Ltd.
This project is written in C++ but the microcontroller can also be programmed in MicroPython, Assembly, Rust, Go.

- Key features:
    - Dual ARM Cortex-M0+ cores 133Mhz.
    - 264 KB SRAM 
    - 30 GPIO Pins
    - Two UART controllers
    - Two SPI controllers
    - 16 PWM Channels.

The RP2040 Datasheet can be found [here](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf).

### **ST7735**
ST7735 is a TFT LCD Display that I have used in my implementation. It supports 18, 16 and 12 bit colors and features 128x128 resolution.

- Key features:
    - TFT LCD display type.
    - 128x128 pixel resolution (there are also 128x160 pixel resolution variants)
    - 18, 16 or 12-bit color depth. My implementation uses 16-bit color depth.
    - SPI communication.
    - it operates at 3.3V but it can also be used at 5V.

The ST7735 Datasheet can be found [here](https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf).

### Pin Connections

| Marble Pico / Raspberry Pi Pico | Display (ST7735) |
|------------------|------------------|
| 3.3V             | VCC              |
| GND              | GND              |
| GPIO18             | SCK              |
| GPIO19             | MOSI             |
| GPIO20             | DC               |
| GPIO21             | RESET            |
| GPIO17             | CS               |

Buttons can be connected at any GPIO pin then configure them in software.

## Software documentation

### 1. Rendering

![Rendering logic](./Documentation/render-logic.png)

The rendering logic is separated in two main components:
1. **Canvas** - handles the drawing operation.
1. **Display** - the display driver provides a *flush* method to transfer the buffer to the screen.

These two interfaces are then incapsulated in a RenderSystem.

You can then write your own driver by implementing the _Display_ interface. In this project the ST7735 class does exactly that. I consider this version a great approach because it provides a layer of abstraction between the actual hardware and the software implementation.

Example of *flush* implementation:

    void ST7735::flush(const uint16_t* buffer){
        static uint8_t bf[ST7735_WIDTH * ST7735_HEIGHT * 2];
        uint8_t *bf_ptr = bf;

        /* populating the bf with the pixel data in the correct order. */
        for (int i = 0; i < ST7735_HEIGHT * ST7735_WIDTH; i++) {
            *bf_ptr++ = buffer[i] >> 8;
            *bf_ptr++ = buffer[i];
        }

        this->set_cs(0);
        this->set_dc(1);

        /* sending all of the data once. */
        spi_write_blocking(spi0, bf, sizeof(bf));

        this->set_cs(1);
    }

To optimize rendering and avoid flickering a double buffered canvas is used. All the drawing operations are made in a back buffer and only the front buffer is rendered to the screen. On the next frame these two are swapped.

Example of drawing a pixel to canvas:

    void BufferedCanvas::set_pixel(uint16_t x, uint16_t y, uint16_t color) {
        if(x >= width || x <= 0){
            return;
        }
        if(y >= height || y <= 0){
            return;
        }

        this->back_buffer[y * width + x] = color;
    }
