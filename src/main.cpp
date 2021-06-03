/*      Janelle Interpreter
 *      Created by William Janelle
 * 
 *      TO-DO:
 *          - Name standardization
 *          - Build argv processing into Program class, only activate Debug Singleton when necessary
 *          - Change debug options from bool array to bit array
 *          - Change method of getting line of error
 *          - Exception handling
 *          - Require parenthesis for control flow boolean
 *          - Boolean primitive type
 *          - Boolean expression evaluation
 *          - More comparison operators
 */

#include "program/Program.h"
#include "debug/Debug.h"

int main(int argc, char** argv)
{
    Debug::Init(argc, argv);

    Program program;
    program.Execute(argv[1]);
    return 0;
}