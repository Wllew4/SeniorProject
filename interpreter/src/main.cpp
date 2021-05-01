/*      Janelle Interpreter
 *      Created by William Janelle
 *      Bedford High School Senior Project
 * 
 *      TO-DO:
 *          - PEMDAS
 *          - Rendering
 */


#include <string>

#include "util/Debug.h"
#include "program/Program.h"

int main(int argc, char** argv){
    setbuf(stdout, NULL);
    
    parseArgs(argc, argv);

    Program program (argv[1]);
}