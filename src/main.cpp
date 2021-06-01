/*      Janelle Interpreter
 *      Created by William Janelle
 */

#include "program/Program.h"
#include "debug/Debug.h"

Program program;

int main(int argc, char** argv)
{
    Debug::Init(argc, argv);

    program.Execute(argv[1]);
    return 0;
}