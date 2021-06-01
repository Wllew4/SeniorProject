/*      Janelle Interpreter
 *      Created by William Janelle
 *      Bedford High School Senior Project
 * 
 *      TO-DO:
 *          - PEMDAS
 *          - Rendering
 */

#pragma warning(disable:4996)
#include <string>

#include "debug/Debug.h"
#include "program/Program.h"

Program program;

int main(int argc, char** argv)
{
    Debug::parseArgs(argc, argv);
    Debug::Timer t ("Program Execution Time", options[3]);
    program.execute(argv[1]);
    return 0;
}