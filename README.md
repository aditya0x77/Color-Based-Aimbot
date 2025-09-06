# Valorant Colorbot 🎮

This project implements a color-based aimbot and triggerbot for Valorant using C++ with OpenCV for screen grabbing and color filtering, paired with an Arduino for mouse control. The bot captures a portion of the screen, filters for enemy outline colors (purple in Valorant), and sends mouse movement or click commands to an Arduino, which emulates mouse input to aim or shoot.

**⚠️ Disclaimer**: This project is for educational purposes only. Using aimbots or similar tools in online games like Valorant violates terms of service and can result in bans. Use responsibly and at your own risk.

## Features ✨

- **Screen Grab**: Captures a 250x250 pixel region of the screen using BitBlt for efficient screen capture.
- **Color Filtering**: Uses OpenCV to convert screen captures to HSV color space and filter for enemy outline colors (purple).
- **Aimbot**: Detects the topmost pixel of the filtered color within a specified field of view (FOV) and moves the mouse to aim at it, with linear smoothing for human-like movement.
- **Triggerbot**: Sends a mouse click command when a target is detected within the FOV.
- **Arduino Integration**: Communicates with an Arduino via serial port to emulate mouse movements and clicks, bypassing some anti-cheat detection.
- **Configurable Parameters**:
  - Adjustable FOV for aimbot and triggerbot.
  - Smoothing factor to control mouse movement speed.
  - Customizable HSV color range for filtering enemy outlines.

## Image Processing Example 🖼️

![Before and After Image Processing](Images/Color_Filtering_Example.png)

## Requirements ⚙️

### Hardware
- Arduino board (e.g., Arduino Leonardo or Micro) with mouse emulation support.
- PC running Windows.
- USB cable to connect the Arduino to the PC.

### Software
- **C++ Environment**:
  - Visual Studio or another C++ compiler.
  - OpenCV library (`opencv2`).
  - Windows SDK for screen capture (`windows.h`).
- **Arduino**:
  - Arduino IDE or PlatformIO.
  - `Mouse` library for Arduino.
- **Dependencies**:
  - Install OpenCV for C++ (e.g., via vcpkg or manual setup).
  - Ensure the Arduino is flashed with the provided firmware.
  - You will have to change the HID and PID of your Arduino; there are plenty of tutorials on YouTube.
  - SerialCom library by this guy "@mamashmandal" https://github.com/manashmandal/SerialPort

## Installation 🛠️
   ###Make sure you got the SerialPort library installed correctly
1. **Compile C++ Code**:
   - Clone this repository: `git clone https://github.com/yourusername/valorant-colorbot.git`.
   - Open the project in your IDE (e.g., Visual Studio).
   - Ensure `windows.h` and `opencv2/opencv.hpp` are accessible.
   - Build and run the C++ program.

2. **Arduino Setup**:
   - Open the Arduino sketch (`arduino.ino`) in the Arduino IDE.
   - Connect your Arduino board via USB.
   - Upload the sketch to the Arduino.
   - Ensure the baud rate matches between the C++ code and Arduino (default: 9600).

3. **Configure COM Port**:
   - Identify your Arduino’s COM port (e.g., COM9) in Device Manager (Windows).
   - Run the C++ program and input the COM port when prompted.

## Usage 🎯

1. **Launch the Game**:
   - Start Valorant and ensure it’s running in a compatible resolution (screen capture is centered at 835, 415).
   - Make sure raw input buffer is turned off, enemy color is set to purple, and the game is running in borderless windowed mode.

2. **Run the Program**:
   - Execute the compiled C++ program.

3. **Controls**:
   - Press **XButton2** (mouse side button) to activate the aimbot/triggerbot.
   - Press **Numpad 5** to exit the program.
   - Modify `fov` (default: 100 pixels) and `smoothing` (default: 200) for desired aimbot behavior.

## How It Works 🔍

1. **Screen Capture**:
   - Uses `BitBlt` to capture a 250x250 pixel region centered at (835, 415).
   - Converts the capture to an OpenCV `Mat` for processing.

2. **Color Filtering**:
   - Converts the captured image to HSV color space.
   - Applies `inRange` to filter pixels within the specified HSV range (purple outlines).
   - Non-matching pixels are ignored, creating a mask.

3. **Target Detection**:
   - Scans the masked image within the FOV (circle of radius `fov` pixels) to find the topmost pixel.
   - Calculates relative coordinates (`relx`, `rely`) from the screen center (960, 540).
   - Applies smoothing to mouse movements for human-like aiming.

4. **Arduino Communication**:
   - Sends proportional movement values (`proportionalX`, `proportionalY`) and a command byte to the Arduino.
   - The Arduino moves the mouse or clicks based on the command.

## In Action 🎥

![In Action](Images/Demo.gif)

## Notes 📝

- **Anti-Cheat Risks**:
  - Using an Arduino for mouse control may reduce detection risk, but Valorant’s anti-cheat (Vanguard) is aggressive. Use at your own risk.
  - Avoid rapid or unnatural mouse movements by tuning the `smoothing` parameter.

- **Troubleshooting**:
  - Ensure the Arduino is on the correct COM port.
  - Verify HSV values match Valorant’s enemy outlines.
  - Check screen resolution and adjust capture coordinates (835, 415) if needed.
- **Ethics**:
  - Use this project ethically and understand the risks of using it in competitive games. ⚠️
