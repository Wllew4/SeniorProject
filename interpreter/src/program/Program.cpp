#include "program/Program.h"

void Program::execute(char* main){
  mainFile.load(main);
  mainFile.execute();
}

PrimitiveBuffer* Program::GetBuffer(){
	return &objbuffer;
}