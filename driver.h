#include <cstdint>
#include <Windows.h>
#include <iostream>

#include <cstdint>
#include <Windows.h>
#include <iostream>

class MouseController {
public:
    enum class Button {
        None = 0,
        LeftButtonDown = 1,
        LeftButtonUp = 2,
        RightButtonDown = 4,
        RightButtonUp = 8,
        MiddleButtonDown = 16,
        MiddleButtonUp = 32,
        XButton1Down = 64,
        XButton1Up = 128,
        XButton2Down = 256,
        XButton2Up = 512,
        MouseWheel = 1024,
        MouseHorizontalWheel = 2048
    };

    MouseController() {
        hDriver = CreateFileA("\\\\.\\Oykyo", GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
            OPEN_EXISTING, 0, nullptr);
        if (hDriver == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to open driver.\n";
        }
    }

    ~MouseController() {
        if (hDriver != INVALID_HANDLE_VALUE) {
            CloseHandle(hDriver);
        }
    }

    bool MoveMouse(int x, int y) {
        return SendMouseEvent(x, y, Button::None);
    }

    bool Click(Button button) {
        return SendMouseEvent(0, 0, button);
    }

private:
    HANDLE hDriver;

    struct MouseRequest {
        int x;
        int y;
        USHORT buttonFlags;
    };

    bool SendMouseEvent(int x, int y, Button button) {
        if (hDriver == INVALID_HANDLE_VALUE) {
            return false;
        }

        MouseRequest request{ x, y, static_cast<USHORT>(button) };
        return DeviceIoControl(hDriver, CTL_CODE(34U, 73142U, 0U, 0U),
            &request, sizeof(request), nullptr, 0, nullptr, nullptr);
    }
};
