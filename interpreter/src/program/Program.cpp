#include "program/Program.h"

Program::Program(char* main){
  mainFile.load(main);
  mainFile.execute();
}