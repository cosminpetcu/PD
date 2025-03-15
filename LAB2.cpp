#include <Windows.h>
#include <winreg.h>
#include <stdio.h>

int main() {
    HKEY hKey, hSubKey;
    DWORD i = 0;
    DWORD retCode;
    char achKey[255];
    DWORD cbName;
    char lpData[32767];
    DWORD dwDataSize;
    DWORD dwType;
    const char* keyPath = "SYSTEM\\CurrentControlSet\\Services";

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        printf("Eroare la deschiderea cheii HKLM\\%s\n", keyPath);
        return 1;
    }


    i = 0;
    while (1) {
        cbName = 255;
        retCode = RegEnumKeyExA(hKey, i, achKey, &cbName, NULL, NULL, NULL, NULL);

        if (retCode != ERROR_SUCCESS) {
            break;
        }


        if (RegOpenKeyExA(hKey, achKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {

            dwDataSize;
            if (RegQueryValueExA(hSubKey, "ImagePath", NULL, &dwType, (LPBYTE)lpData, &dwDataSize) == ERROR_SUCCESS) {
                printf("%s: %s\n", achKey, lpData);
            }

            RegCloseKey(hSubKey);
        }

        i++;
    }


    RegCloseKey(hKey);

    return 0;
}