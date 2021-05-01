#include "program/Program.h"

Program::Program(char* main){
	ObjectBufferBuffer.push_back(new ObjectBuffer);
  mainFile.load(main);
  mainFile.execute();
}

int Program::AppendBuffer(){
	ObjectBufferBuffer.push_back(new ObjectBufferBuffer);
	return ObjectBufferBuffer.back;
}

void Program::RemoveBuffer(int index){
	ObjectBufferBuffer.erase(index);
}