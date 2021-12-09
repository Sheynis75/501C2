#include <windows.h>
#include <wincrypt.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;
void decode(wstring encrypted_key, BYTE *pbArray, DWORD* bArraySize);