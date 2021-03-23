#include <string>

#include "util/Log.h"
#include "util/Debug.h"
#include "util/File.h"

char* File::readFile(char* file){
    FILE* f = fopen(file, "rb");

    if(f){
        fseek(f, 0, SEEK_END);
        int bufsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char* buffer = new char[bufsize + 1];
        buffer[bufsize] = '\0';

        int readsize = fread(buffer, sizeof(char), bufsize, f);
        if(bufsize != readsize){
            free(buffer);
            Log::Error(3,"Could not allocate memory for file ", file, "\n");
            exit(1);
        }
        fclose(f);
        if(options[0]){
            Log::Print(5,"DEBUG Print source file: ", file, "\n", buffer, "\n\n");
        }

        return buffer;
    } else {
        Log::Error(3,"Could not find file ", file, "\n");
        exit(1);
    }
}