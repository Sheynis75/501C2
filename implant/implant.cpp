#include <cstdlib>
#include <fstream>
#include <iostream>
#include "httpClient.h"
 
/* List of basic powershell commands: https://devblogs.microsoft.com/scripting/table-of-basic-powershell-commands/ */
int wmain()
{
    HTTP *client = new HTTP();
    int port = 0, tls = 0;
    std::wcout << client->makeHttpRequest(L"google.com", port, L"/", tls) << std::endl;
    
    std::system("powershell ipconfig >C:\\Users\\User\\test.txt");
    std::cout << std::ifstream("C:\\Users\\User\\test.txt").rdbuf();
    std::remove("C:\\Users\\User\\test.txt");

    delete client;
    return 0;
}
