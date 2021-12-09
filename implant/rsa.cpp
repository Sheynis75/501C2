#include "rsa.h"
#include <string>
#include <vector>

struct MyRSAPublicBlob {
    BCRYPT_RSAKEY_BLOB blob;
    BYTE exponent[6];
    BYTE modulus[256];
    MyRSAPublicBlob(BYTE* mod, BYTE* exp)
    {
        blob.BitLength = 256 * 8;
        blob.Magic = BCRYPT_RSAPUBLIC_MAGIC;
        blob.cbModulus = 256;
        blob.cbPublicExp = 6;
        for (size_t i = 0; i < 256; ++i) //copy BigEndian
            modulus[i] = mod[255 - i];
        for (size_t i = 0; i < 6; ++i) //copy BigEndian
            exponent[i] = exp[5 - i];
    }
    MyRSAPublicBlob() { ; }
};

RSA:: ~RSA(){
    Cleanup();
}

//https://stackoverflow.com/questions/58419870/how-to-use-bcrypt-for-rsa-asymmetric-encryption
// Freebie: initialize AES class
RSA::RSA( BYTE* key, DWORD key_size){
    hAlg = 0;
    hKey = NULL;
    //pretty print for key
    for(size_t i = 0; i < key_size; i++){
        printf("%d ", (int)key[i]);
    }
    printf("\n%d\n", key_size);

    // create a handle to an RSA provider
    // https://docs.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptopenalgorithmprovider
    nStatus = ::BCryptOpenAlgorithmProvider(
        &hAlg, 
        BCRYPT_RSA_ALGORITHM, 
        NULL, 
        0);
    if (! NT_SUCCESS(nStatus))
    {
        wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", nStatus);
        Cleanup();
        return;
    }
    if (!hAlg){
        wprintf(L"Invalid handle!\n");
    }

    BCRYPT_RSAKEY_BLOB myBlob;
    myBlob.Magic = BCRYPT_RSAPUBLIC_MAGIC;
    myBlob.BitLength = 2048;
    myBlob.cbPublicExp = 256;

    nStatus = BCryptImportKeyPair(hAlg,
        NULL,
        BCRYPT_RSAPUBLIC_BLOB,
        &hKey,
        key,
        128,
        BCRYPT_NO_KEY_VALIDATION);
    if (!NT_SUCCESS(nStatus)) {
        printf("Failed to import Private key..status : %08x\n", nStatus);
        Cleanup();
    } 

    nStatus = ::BCryptFinalizeKeyPair(
        hKey,
        0
    );
    //https://docs.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptimportkeypair
    //imports the public key from key blob
    /*
    nStatus = ::BCryptImportKeyPair(hAlg,
        NULL,
        BCRYPT_RSAPUBLIC_BLOB,
        &hKey,
        key,
        key_size,
        BCRYPT_NO_KEY_VALIDATION);
    if (!NT_SUCCESS(nStatus)) {
        printf("Failed to import public key..status : %08x\n", nStatus);
        Cleanup();
    }
    */
}

/*
https://docs.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptencrypt
*/
void RSA::Encrypt(BYTE* data, size_t dataLen){
    // check if we have valid handles before continuing, initalization should've initialzed them
    if(!hKey){
        return;
    }
    ULONG EncryptedBufferSize = 0;
    nStatus = ::BCryptEncrypt(hKey,
        data,
        dataLen,
        NULL,
        NULL,
        0,
        NULL,
        0,
        &EncryptedBufferSize,
        0
    );
    if (!NT_SUCCESS(nStatus)) {
        printf("Failed to get required size of buffer..status : %08x\n", status);
        Cleanup();
    }

    UCHAR *encryptedBuffer = (PUCHAR)::HeapAlloc(GetProcessHeap(), 0, EncryptedBufferSize);
    if (encryptedBuffer == NULL) {
        printf("failed to allocate memory for blindedFEKBuffer\n");
        Cleanup();
    }
    nStatus = BCryptEncrypt(hKey,
        data,
        dataLen,
        NULL,
        NULL,
        0,
        encryptedBuffer,
        EncryptedBufferSize,
        &EncryptedBufferSize,
        0
    );
    if (!NT_SUCCESS(nStatus)) {
        printf("Failed encrypt data..status : %08x\n", status);
        Cleanup();
    }
    ciphertext = encryptedBuffer;
    ptBufferSize = EncryptedBufferSize;
}

void RSA::Cleanup(){
    if(hAlg){
        ::BCryptCloseAlgorithmProvider(hAlg,0);
        hAlg = NULL;
    }
    if(hKey){
        ::BCryptDestroyKey(hKey);
        hKey = NULL;
    }
    if(ciphertext){
        ::HeapFree(GetProcessHeap(), 0, (LPVOID)ciphertext);
        ciphertext = NULL;
    }
}
