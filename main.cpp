#include <windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "SerialPort.hpp"


using namespace std;
using namespace cv;

Scalar colorlow = Scalar(140, 110, 150);
Scalar colorhigh = Scalar(150, 195, 255);

int main()
{
    string comPort;

    cout << "Enter the COM port (e.g., COM9): ";
    cin >> comPort;

    SerialPort arduino(comPort.c_str());

    if (!arduino.isConnected())
    {
        std::cerr << "Arduino not connected." << std::endl;
        return 1;
    }
    double smoothing = 200;
    int fov = 100;

    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, 250, 250);
    HGDIOBJ hOldBitmap = SelectObject(hMemoryDC, hBitmap);

    Mat screen(250, 250, CV_8UC4);
    Mat hsvImage;
    Mat mask;

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 250;
    bmi.bmiHeader.biHeight = -250;  // Negative height to ensure correct top-down order
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    //namedWindow("Detected Point", WINDOW_NORMAL);
    bool exitLoop = false;
    int prevTopmostX = -1;
    int prevTopmostY = -1;
    while (!exitLoop)
    {
        if (GetAsyncKeyState(VK_NUMPAD5))
        {
            exitLoop = true;
        }

        if (GetAsyncKeyState(VK_XBUTTON2))
        {
            BitBlt(hMemoryDC, 0, 0, 250, 250, hScreenDC, 835, 415, SRCCOPY);
            GetDIBits(hMemoryDC, hBitmap, 0, 250, screen.data, &bmi, DIB_RGB_COLORS);

            cvtColor(screen, hsvImage, COLOR_BGR2HSV);

            inRange(hsvImage, colorlow, colorhigh, mask);


            int topmostX = -1;
            int topmostY = -1;
            int relx = 0;
            int rely = 0;
            bool foundpixel = false;


            int centerX = 250 / 2;
            int centerY = 250 / 2;
            int circleRadius = fov;

            for (int y = 0; y < 250; y++)
            {
                for (int x = 0; x < 250; x++)
                {
                    int distanceX = x - centerX;
                    int distanceY = y - centerY;
                    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                    if (distance <= circleRadius && mask.at<uchar>(y, x) != 0)
                    {
                        topmostX = x;
                        topmostY = y;
                        foundpixel = true;
                        break;
                    }
                }

                if (topmostX != -1)
                    break; 
            }

            relx = topmostX + 835 - 960;
            rely = topmostY + 3 + 415 - 540;

            if (relx > 0)
            {
                relx += 2;
            }
            else
            {
                relx -= 2;
            }

            if (foundpixel)
            {
                double maxOffset = smoothing;
                double proportionalX = static_cast<double>(relx) / 250.0 * maxOffset;
                double proportionalY = static_cast<double>(rely) / 250.0 * maxOffset;

                char buffer[3];
                buffer[0] = static_cast<char>(proportionalX);
                buffer[1] = static_cast<char>(proportionalY);
                buffer[2] = static_cast<char>(0);
                arduino.writeSerialPort(buffer, sizeof(buffer));
                
                char buffer2[3];
                buffer2[0] = static_cast<char>(0);
                buffer2[1] = static_cast<char>(0);
                buffer2[2] = static_cast<char>(1);
                arduino.writeSerialPort(buffer2, sizeof(buffer2));

                Sleep(50);
            }
        }
    }

    arduino.closeSerial();
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    DeleteObject(hBitmap);

    return 0;
}
