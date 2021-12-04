#include <windows.h>
#include <string>
#include <iostream>
#include <winhttp.h>

class HTTP{
    public:
        std::wstring makeHttpRequest(std::wstring fqdn, int port, std::wstring uri, bool useTLS);
};

