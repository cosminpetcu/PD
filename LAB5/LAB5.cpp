#include <iostream>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <initguid.h>

#pragma comment(lib, "setupapi.lib")

void list_usb_devices() {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Eroare la obținerea listei de dispozitive." << std::endl;
        return;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    std::cout << "Dispozitive USB conectate:" << std::endl;
    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        char deviceName[256];
        char friendlyName[256];
        DWORD size;

        if (SetupDiGetDeviceInstanceIdA(deviceInfoSet, &deviceInfoData, deviceName, sizeof(deviceName), NULL)) {
            if (strncmp(deviceName, "USB\\", 4) == 0) {
                std::cout << "Dispozitiv USB " << i + 1 << ": " << deviceName;

                if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)friendlyName, sizeof(friendlyName), &size) ||
                    SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)friendlyName, sizeof(friendlyName), &size)) {
                    std::cout << " (" << friendlyName << ")";
                }

                std::cout << std::endl;
            }
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

int main() {
    list_usb_devices();
    system("pause"); // Pentru Windows, astfel încât fereastra să nu se închidă instant
    return 0;
}