#include <windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "SerialPort.hpp"

using namespace std;
using namespace cv;

Scalar colorlow = Scalar(140, 110, 150);
Scalar colorhigh = Scalar(150, 195, 255);

string comPort = "COM3";
SerialPort arduino(comPort.c_str());

static void mousemove(int x, int y)
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.mi.dx = x;
    input.mi.dy = y;
    SendInput(1, &input, sizeof(INPUT));
}

static void shoot()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main()
{
    if (!arduino.isConnected())
    {
        std::cerr << "Arduino not connected." << std::endl;
        return 1;
    }

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

    bool exitLoop = false;
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

            int centerX = 250 / 2;
            int centerY = 250 / 2;

            for (int y = 0; y < 250; y++)
            {
                for (int x = 0; x < 250; x++)
                {
                    if (mask.at<uchar>(y, x) != 0)
                    {
                        int relx = x + 835 - 960;
                        int rely = y + 3 + 415 - 540;

                        if (relx > 0)
                            relx += 2;
                        else
                            relx -= 2;

                        mousemove(relx, rely);
                        shoot();
                        Sleep(10); // Adjust the sleep time
                        break;
                    }
                }
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
