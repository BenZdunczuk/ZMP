#include "PPFunc.hh"
#include <sstream>
#include <iostream>


bool preprocesFile(const char* fileName, std::istringstream &stream){

    std::string cmd= "cpp -P ";
    char line[LINE_SIZE];
    std::ostringstream tmp;

    cmd+= fileName;
    FILE* pProc = popen(cmd.c_str(), "r");

    if (!pProc) return false;

    while (fgets(line, LINE_SIZE, pProc))
    {
        tmp << line;
    }
    stream.str(tmp.str());

    return pclose(pProc)==0;
}
