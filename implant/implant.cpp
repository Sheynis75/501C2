#include <cstdlib>
#include <fstream>
#include <iostream>
#include "httpClient.h"
 
/* List of basic powershell commands: https://devblogs.microsoft.com/scripting/table-of-basic-powershell-commands/ */
int wmain()
{
    HTTP *client = new HTTP();
    int port = 5000, tls = 0;
    client->additionalHeader = L"ch0nk:lol";
    client->header_size = 9;
    std::wcout << client->makeHttpRequest(L"localhost", port, L"/", tls) << std::endl;
    
    std::system("powershell ipconfig >C:\\Users\\User\\test.txt");
    std::cout << std::ifstream("C:\\Users\\User\\test.txt").rdbuf();
    std::remove("C:\\Users\\User\\test.txt");

    delete client;
    return 0;
}
