#pragma warning(disable:4996)

#include <string>

#include "debug/Log.h"
#include "debug/Debug.h"
#include "program/File.h"

#include "execution/Exec.h"


void File::load(char* file){
    FILE* f = fopen(file, "rb");

    if(f){
        fseek(f, 0, SEEK_END);
        int bufsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        m_file = new char[bufsize + 1];
        m_file[bufsize] = '\0';

        int readsize = fread(m_file, sizeof(char), bufsize + 1, f);
        if(bufsize != readsize){
            free(m_file);
            //Log::Error(3,"Could not allocate memory for file ", file, "\n");
            exit(1);
        }
        fclose(f);
        if(options[0]){
            //Log::Print(5,"DEBUG Print source file: ", file, "\n", m_file, "\n\n");
        }
    } else {
        //Log::Error(3,"Could not find file ", file, "\n");
        exit(1);
    }
}

void File::execute(){
	exe.Init(m_file);
}