#include "base64.h"

void decode(wstring encrypted_key, BYTE* pbArray, DWORD* bArraySize){
    DWORD arraySize = encrypted_key.size();
    LPCWSTR stringPointer = encrypted_key.c_str();
    DWORD decodeLength;

    // we will return the converted array size to bArraySize
    if(pbArray == NULL){
        if(!CryptStringToBinaryW(stringPointer, arraySize, CRYPT_STRING_BASE64, NULL, &decodeLength, NULL, NULL)){
            wprintf(L"*** Error with cryptStringToBinaryW with error code: %x", GetLastError());
        }
        *bArraySize = decodeLength;
    }

    decodeLength = *bArraySize;
    if(!CryptStringToBinaryW(stringPointer, arraySize, CRYPT_STRING_BASE64, pbArray, &decodeLength, NULL, NULL)){
        wprintf(L"*** Error with cryptStringToBinaryW with error code: %x", GetLastError());
    }
}
