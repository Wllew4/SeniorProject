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
#include <chrono>

#include "debug/Debug.h"
#include "program/Program.h"

Program program;

int main(int argc, char** argv){
    setbuf(stdout, NULL);
    parseArgs(argc, argv);
    program.execute(argv[1]);
    DebugEnd();
    return 0;
}