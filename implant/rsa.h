#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)
#define STATUS_MISMATCHTAG(Status)  ((NTSTATUS)(Status) == (NTSTATUS)0xC000A002)
#define RSA_256_KEY_SIZE    256
#define RSA_BLOCK_SIZE        16

class RSA{
//https://www.cryptosys.net/pki/manpki/pki_aesgcmauthencryption.html
    BOOL status = FALSE;
    NTSTATUS nStatus;

    BCRYPT_ALG_HANDLE hAlg;
    BCRYPT_KEY_HANDLE hKey;
   
    void Cleanup();

    public:
        void Encrypt(BYTE *data, size_t dataLen);
         RSA(BYTE *key, DWORD key_size); // initialize with key 
         ~RSA();
        DWORD keysize = 0;
        BCRYPT_RSAKEY_BLOB keyBlob;;
        BYTE* ciphertext = NULL; // pointer to ciphertext
        DWORD ptBufferSize = 0; // pointer to plaintext size
};