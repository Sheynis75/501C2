#include "httpClient.h"

/* reference: code snippet from https://docs.microsoft.com/en-us/windows/win32/api/winhttp/nf-winhttp-winhttpreaddata */
/* Collaborated with Alex, Carlos & Akshey */
using namespace std;

wstring HTTP::makeHttpRequest(wstring fqdn, int port, wstring uri, bool useTLS){
    LPCWSTR agent = L"agent1337";
    LPWSTR buffer;
    wstring result;

    // this is mainly from code snippet provided from reference above
    HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;
    BOOL bResults = false;
    DWORD dwSize = 0, dwDownloaded = 0;
    LPSTR pszOutBuffer;

    hSession = WinHttpOpen( agent, WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if(hSession){
        hConnect = WinHttpConnect( hSession, fqdn.data(), port, 0);
    }
    if(hConnect){
        DWORD tls = 0;
        if(useTLS){
            tls = WINHTTP_FLAG_SECURE;
        }
        hRequest = WinHttpOpenRequest( hConnect, L"GET", uri.data(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, tls);
    }
    if(hRequest){
        if(useTLS){
            //disable certificate verification 
            DWORD secure_protocols{ SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | 
            SECURITY_FLAG_IGNORE_CERT_CN_INVALID | SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE };
            if(!WinHttpSetOption( hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &secure_protocols, 4)){
                wcout << GetLastError() << endl;
            }
        }
        bResults = WinHttpSendRequest( hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA,0,0,0);
    }
    if (bResults){
        bResults = WinHttpReceiveResponse( hRequest, NULL);
    }

    // Keep checking for data until there is nothing left.
    if (bResults){
        do {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable( hRequest, &dwSize)) {
                printf( "Error %u in WinHttpQueryDataAvailable.\n",
                        GetLastError());
                break;
            }
            // No more available data.
            if (!dwSize) break;

            // Allocate space for the buffer.
            // Not the most efficient to dynamically allocate memory every round, but converting to wchar_t is easier this way
            pszOutBuffer = new char[dwSize+1];
            buffer = new wchar_t[dwSize+1];
            if (!pszOutBuffer || !buffer){
                printf("Out of memory\n");
                break;
            }
            
            // Read the Data.
            ZeroMemory(pszOutBuffer, dwSize+1);
            if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, 
                                  dwSize, &dwDownloaded)){                                  
                printf( "Error %u in WinHttpReadData.\n", GetLastError());
            }else{
                // converting char to wchar_t
                mbstowcs(buffer, pszOutBuffer, dwSize+1);
                result += buffer;
            }
        
            // Free the memory allocated to the buffer.
            delete [] pszOutBuffer;
            delete [] buffer;

            // This condition should never be reached since WinHttpQueryDataAvailable
            // reported that there are bits to read.
            if (!dwDownloaded)
                break;
                
        } while (dwSize > 0);
    }

    // close all open handles
    if(hSession){
        WinHttpCloseHandle(hSession);
    }
    if(hConnect){
        WinHttpCloseHandle(hConnect);
    }
    if(hRequest){
        WinHttpCloseHandle(hRequest);
    }

    return result;
}
