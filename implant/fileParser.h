#include <windows.h>
#include <wincrypt.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <bcrypt.h>
#include <stdio.h>
#include <fstream>

using namespace std;

void parseObjectFromJson(string inputPath, string objectValue, LPWSTR output, DWORD* size);
int copyContentToFile(string inputPath, string outputPath);
int deleteFile(const char* filePath);