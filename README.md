# Valorant Colorbot 🎮

Color-based aimbot + triggerbot for Valorant.  
Implemented in **C++ (OpenCV, Windows API)** for capture and detection, with an **Arduino Leonardo** handling HID mouse emulation.

---

## ⚠️ Disclaimer
This project is for research and educational purposes only.  
Using automation or aim-assist tools in online games violates terms of service and may result in bans.

---

## 🔍 Overview
- **Screen Capture**: 250×250 pixel region via `BitBlt`.  
- **Color Filtering**: Conversion to HSV + `inRange` to isolate enemy outline color (purple).  
- **Target Detection**: Search within a circular FOV; pick the topmost matching pixel.  
- **Aiming**: Calculate relative delta to screen center; apply linear smoothing for natural motion.  
- **Triggering**: Automatic click when a valid target is inside FOV.  
- **Arduino HID**: Serial communication to Arduino, which performs the mouse input at hardware level.

---

## ✨ Features
- Fast region-based capture  
- HSV outline detection  
- Smoothed mouse movement  
- Aimbot + triggerbot functionality  
- Hardware-level input via Arduino HID  

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
- ⚡ Arduino integration provides HID-level control rather than software injection  

---

## 🌃 End of the Line, Choomba
May your tracking stay sharp.  

![goodbye gif](Images/Johnny.gif)
