#pragma warning(disable:4996)

#include "debug/Callback.h"
#include "debug/Log.h"
#include "program/File.h"

File::File(PrimitiveBuffer& _program)
    : m_exe(_program), m_file("") {}

File::~File()
{
    free(m_file);
}

void File::Load(char* _file)
{
    FILE* file = fopen(_file, "rb");

    if (file) {
        fseek(file, 0, SEEK_END);
        int bufferSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        m_file = new char[bufferSize + 1];
        m_file[bufferSize] = '\0';

        size_t readSize = fread(m_file, sizeof(char), bufferSize + 1, file);
        if (bufferSize != readSize) {
            free(m_file);
            Debug::Log::Crash(111) << "Could not allocate memory for file " << m_file << '\n';
            exit(111);
        }
        fclose(file);
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