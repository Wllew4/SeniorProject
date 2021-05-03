#include "program/Program.h"

void Program::execute(char* main){
  mainFile.load(main);
  mainFile.execute();
}

std::vector<Primitive*>* Program::GetBuffer(){
	return &PrimitivesBuffer;
}