#include <windows.h>
#include <cstdio>
#include <cmath>

int binarySearch(int *arr, int low, int high, int x);

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
case WM_CREATE:
{
    // Input label
    CreateWindowEx(0,
                   "STATIC",
                   "Enter a positive number:",
                   WS_VISIBLE | WS_CHILD,
                   10, 10, 150, 20,
                   hwnd,
                   NULL,
                   GetModuleHandle(NULL),
                   NULL);

    // Input box
    CreateWindowEx(0,
                   "EDIT",
                   "",
                   WS_VISIBLE | WS_CHILD | WS_BORDER,
                   170, 10, 100, 20,
                   hwnd,
                   (HMENU)1,
                   GetModuleHandle(NULL),
                   NULL);

    // Calculate button
    CreateWindowEx(0,
                   "BUTTON",
                   "Calculate",
                   WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                   280, 10, 80, 20,
                   hwnd,
                   (HMENU)2,
                   GetModuleHandle(NULL),
                   NULL);

    // Result display label
    CreateWindowEx(0,
                   "STATIC",
                   "Result:",
                   WS_VISIBLE | WS_CHILD,
                   10, 40, 50, 20,
                   hwnd,
                   NULL,
                   GetModuleHandle(NULL),
                   NULL);

    // Result display
    CreateWindowEx(0,
                   "STATIC",
                   "",
                   WS_VISIBLE | WS_CHILD | SS_CENTER,
                   70, 40, 250, 30,
                   hwnd,
                   (HMENU)3,
                   GetModuleHandle(NULL),
                   NULL);
}
break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 2:
        {
            char buffer[256];
            GetWindowText(GetDlgItem(hwnd, 1), buffer, sizeof(buffer));
            int x = atoi(buffer);

            if (x < 0)
            {
                MessageBox(hwnd, "Only positive numbers are allowed", "Error", MB_OK | MB_ICONERROR);
            }
            else
            {
                int low = 0;
                int high = x;
                int arr[x + 1];
                for (int i = 0; i <= x; ++i)
                {
                    arr[i] = i;
                }
                int result = binarySearch(arr, low, high, x);
                if (result == -1)
                {
                    SetWindowText(GetDlgItem(hwnd, 3), "No square root found");
                }
                else
                {
                    char resultStr[256];
                    sprintf(resultStr, "Square root: %d", result);
                    SetWindowText(GetDlgItem(hwnd, 3), resultStr);
                }
            }
        }
        break;
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int main()
{
    WNDCLASSEX wc;
    HWND hwnd;

    MSG Msg;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          g_szClassName,
                          "Square Root Calculator",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, 400, 150,
                          NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

int binarySearch(int *arr, int low, int high, int x)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if ((arr[mid] * arr[mid]) == x)
        {
            return mid;
        }
        if ((arr[mid] * arr[mid]) > x)
        {
            high = mid - 1;
        }
        else if ((arr[mid] * arr[mid]) < x)
        {
            low = mid + 1;
        }
    }
    return -1;
}
