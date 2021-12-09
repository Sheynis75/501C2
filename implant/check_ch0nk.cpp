#include <filesystem>
#include <iostream>
#include <windows.h>
#include <string>
#include <winhttp.h>



int wmain(int argc,  wchar_t* argv[]){
    bool check = std::filesystem::exists("C:\\malware\\ch0nky.txt");
    if(check == true){
        printf("ch0nk found");
    }
    else{
        printf("ch0nk not found");
    }
    return 0;
    
}