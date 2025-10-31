# Valorant Colorbot

A color-based aimbot and triggerbot for Valorant, implemented in **C++** with the **Windows API** and **OpenCV** for screen capture and analysis. Mouse control is offloaded to an **Arduino Leonardo** (emulating an HID device) for hardware-level input.

---

## ⚠️ Disclaimer
This project is for research and educational purposes only.  
Using Aim-assist tools in online games violates terms of service and may result in bans.

⚠️⚠️**You will have to change your Leonardo’s HID and PID to match your mouse’s.** This is a critical step for the hardware emulation to function as intended.⚠️⚠️

---

## Overview

This application captures a small portion of the screen, performs color-based filtering to identify enemy outlines, and calculates the necessary mouse movements to aim. These movements, along with click commands, are sent via serial communication to an Arduino Leonardo, which executes them as a hardware-level mouse.

The primary components are:
-   **Screen Capture**: A 250×250 pixel region is captured using `BitBlt` for high performance.
-   **Color Filtering**: The captured image is converted to the HSV color space. An `inRange` operation isolates the specific purple hue of enemy outlines.
-   **Target Detection**: The algorithm searches within a circular FOV for matching pixels and selects the topmost pixel as the target.
-   **Aiming Logic**: Calculates the relative delta between the target and the screen center, applying linear smoothing for more natural mouse motion.
-   **Triggerbot**: Automatically sends a click command when a valid target is within the FOV.
-   **HID Emulation**: An Arduino Leonardo receives serial commands and translates them into native USB HID mouse inputs.
-   **Serial Communication**: Handled via the [`SerialPort`](https://github.com/manashmandal/SerialPort) library.

---

## Features
-   Fast, region-based screen capture via `BitBlt`.
-   HSV-based color filtering for enemy outline detection.
-   Configurable smoothed mouse movement.
-   Integrated aimbot and triggerbot functionality.
-   Hardware-level mouse input via Arduino HID emulation.
-   Robust serial communication layer using the **SerialPort** library.

---

## Image Processing Example
The image on the left is the direct screen capture. The image on the right shows the result after applying the HSV color mask, isolating the target.

![Before and After Image Processing](Images/Color_Filtering_Example.png)

---

## Demonstration
![In Action](Images/Demo.gif)

---

## Technical Notes
-   The accuracy of the bot is highly dependent on the **HSV values** used for color filtering. These may need tuning.
-   The **FOV and smoothing** parameters directly control the bot's responsiveness and precision.
-   Using an Arduino with the SerialPort library provides a layer of abstraction, as the host PC is not directly manipulating mouse inputs, which can be a common detection vector.

---

## Installation & Usage

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/aditya0x77/Color-Based-Aimbot.git](https://github.com/aditya0x77/Color-Based-Aimbot.git)
    cd Color-Based-Aimbot
    ```

2.  **Spoof Arduino HID/PID:**
    -   You *must* modify your Arduino Leonardo's board definitions to spoof the HID (Human Interface Device) and PID (Product ID) to match your primary mouse.
    -   Follow a guide for this process, such as: [https://www.youtube.com/watch?v=krjCJBfBgr4&t=87s](https://www.youtube.com/watch?v=krjCJBfBgr4&t=87s)

3.  **Add SerialPort Library:**
    -   The C++ project requires the `SerialPort` library for communication.
    -   Add it to your project from: [https://github.com/manashmandal/SerialPort](https://github.com/manashmandal/SerialPort)

4.  **Upload Arduino Code:**
    -   Open the Arduino IDE.
    -   Upload the provided `.ino` sketch to your Arduino Leonardo.

5.  **Identify COM Port:**
    -   Check Windows Device Manager to find the COM port your Arduino Leonardo is connected to.

6.  **Compile and Run:**
    -   Open the `main.cpp` file in your C++ IDE or compile using g++.
    -   Run the compiled executable.
    -   Enter your Arduino's COM port when prompted.

7.  **Configuration (Optional):**
    -   Smoothing and FOV values can be adjusted directly in the source code.

---
## 🌃 End of the Line, Choomba  
Thanks for checking out this little project.  
BYE! BYE!

![goodbye gif](Images/Johnny.gif)
