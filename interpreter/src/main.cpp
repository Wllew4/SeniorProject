/*      Janelle Interpreter
 *      Created by William Janelle
 *      Bedford High School Senior Project
 * 
 *      TO-DO:
 *          - Recursion
 *          - PEMDAS
 *          - Rendering
 */


#include <string>

#include "util/Log.h"
#include "util/Debug.h"
#include "parser/Parser.h"

int main(int argc, char** argv){
    setbuf(stdout, NULL);
    
    parseArgs(argc, argv);

    Parser::parse(argv[1]);
}