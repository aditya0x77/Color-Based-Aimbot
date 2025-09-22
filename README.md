# Valorant Colorbot 🎮

Color-based aimbot + triggerbot for Valorant.  
Implemented in **C++ (Windows API, OpenCV)** for capture and detection, with an **Arduino Leonardo** handling HID mouse emulation.

---

## ⚠️ Disclaimer
This project is for research and educational purposes only.  
Using Aim-assist tools in online games violates terms of service and may result in bans.

⚠️⚠️You will have to change your Leonardo’s HID and PID to match your mouse’s.⚠️⚠️

---

## 🔍 Overview
- **Screen Capture**: 250×250 pixel region via `BitBlt`.  
- **Color Filtering**: Conversion to HSV + `inRange` to isolate enemy outline color (purple).  
- **Target Detection**: Search within a circular FOV; pick the topmost matching pixel.  
- **Aiming**: Calculate relative delta to screen center; apply linear smoothing for natural motion.  
- **Triggering**: Automatic click when a valid target is inside FOV.  
- **Arduino HID**: Serial communication with Arduino (Leonardo) for hardware-level mouse input.  
- **Serial Com**: Communication handled through the [`SerialPort`](https://github.com/manashmandal/SerialPort) library.  

---

## ✨ Features
- Fast region-based capture  
- HSV outline detection  
- Smoothed mouse movement  
- Aimbot + triggerbot functionality  
- Hardware-level input via Arduino HID  
- Serial communication layer using **SerialPort** lib 

---

## 🖼️ Image Processing Example
![Before and After Image Processing](Images/Color_Filtering_Example.png)

---

## 🎥 In Action
![In Action](Images/Demo.gif)

---

## 📝 Notes
- 🎯 HSV values define detection accuracy  
- 🎛️ FOV and smoothing determine responsiveness and precision  
- ⚡ Arduino + SerialPort lib provide HID-level control with minimal detection surface  

---
## Installation & Usage 🚀

```bash
# Clone the repository
git clone https://github.com/aditya0x77/Color-Based-Aimbot.git
cd Color-Based-Aimbot

# Spoof the HID and PID of your Arduino to match your mouse
# Follow this guide: https://www.youtube.com/watch?v=krjCJBfBgr4&t=87s

# Add the SerialPort library to your project
# GitHub: https://github.com/manashmandal/SerialPort

# Open Arduino IDE and upload the Arduino code to your Arduino Leonardo

# Check the COM port to which the Leonardo is connected

# Run the main.cpp (compile and execute in your C++ IDE or using g++)
# Enter your COM port when prompted

# Optional: change smoothing and FOV directly in the code if desired
```
## 🌃 End of the Line, Choomba  
Thanks for checking out this little project.  
BYE! BYE!

![goodbye gif](Images/Johnny.gif)
