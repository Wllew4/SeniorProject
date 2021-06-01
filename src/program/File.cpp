//#pragma warning(disable:4996)
#include "program/File.h"
#include "debug/Log.h"
#include "debug/Callback.h"

File::~File()
{
    free(m_file);
}

void File::Load(char* file)
{
    FILE* f = fopen(file, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        int bufsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        m_file = new char[bufsize + 1];
        m_file[bufsize] = '\0';

        int readsize = fread(m_file, sizeof(char), bufsize + 1, f);
        if (bufsize != readsize) {
            free(m_file);
            Debug::Log::Crash(111) << "Could not allocate memory for file " << m_file << '\n';
            exit(111);
        }
        fclose(f);
        Debug::Callback::LoadFile(m_file);
    }
    else {
        Debug::Log::Crash(112) << "Could not locate file " << m_file << '\n';
        exit(112);
    }
}

void File::Execute()
{
	m_exe.Init(m_file);
}