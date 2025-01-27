#include <windows.h>
#include <stdio.h>

void printFileInfo(const char *filePath);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Kullanim: %s <dosya yolu>\n", argv[0]);
        return 1;
    }

    printFileInfo(argv[1]);
    return 0;
}

void printFileInfo(const char *filePath)
{
    HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Dosya yolu yanlis.\n");
        return;
    }

    BY_HANDLE_FILE_INFORMATION fileInfo;
    if (!GetFileInformationByHandle(hFile, &fileInfo)) {
        printf("Dosya bilgisi alýnamadi\n");
        CloseHandle(hFile);
        return;
    }

    SYSTEMTIME creationTime, lastAccessTime, lastWriteTime;
    FileTimeToSystemTime(&fileInfo.ftCreationTime, &creationTime);
    FileTimeToSystemTime(&fileInfo.ftLastAccessTime, &lastAccessTime);
    FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &lastWriteTime);

    printf("Dosya: %s\n", filePath);
    printf("Dosya Boyutu: %d bayt\n", fileInfo.nFileSizeLow);
    printf("Oluþturulma Zamani: %02d/%02d/%04d %02d:%02d:%02d\n", creationTime.wDay, creationTime.wMonth, creationTime.wYear, creationTime.wHour, creationTime.wMinute, creationTime.wSecond);
    printf("Son Eriþim Zamani: %02d/%02d/%04d %02d:%02d:%02d\n", lastAccessTime.wDay, lastAccessTime.wMonth, lastAccessTime.wYear, lastAccessTime.wHour, lastAccessTime.wMinute, lastAccessTime.wSecond);
    printf("Deðistirilme Zamani: %02d/%02d/%04d %02d:%02d:%02d\n", lastWriteTime.wDay, lastWriteTime.wMonth, lastWriteTime.wYear, lastWriteTime.wHour, lastWriteTime.wMinute, lastWriteTime.wSecond);

    CloseHandle(hFile);
}

