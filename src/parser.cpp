#include "parser.hh"

#define LINE_SIZE 255

#define STR(x) #x
#define IF_CMD_THEN_READ(CmdName)                       \
    if (Keyword == STR(CmdName))                        \
    {                                                   \
        if (!ReadCmd##CmdName(IStrm, CmdLst))           \
            return false;                               \
        continue;                                       \
    }

bool Parser::ReadCmdsList(std::istream &IStrm, std::list<std::string> &CmdLst)
{
    std::string Keyword;
    while (IStrm >> Keyword)
    {
        IF_CMD_THEN_READ(Move)
        // IF_CMD_THEN_READ(Turn)
        IF_CMD_THEN_READ(Rotate)
        return false;
    }
    return true;
}

bool Parser::ReadCmdMove(std::istream &IStrm, std::list<std::string> &CmdLst){

    return true;
}
bool Parser::ReadCmdRotate(std::istream &IStrm, std::list<std::string> &CmdLst){
    return true;
}
// bool ReadCmdTurn(std::istream &IStrm, std::list<std::string> &CmdLst);

// bool Parser::preprocessFile(const char *fileName, std::istringstream &stream)
// {
//     std::string cmd = "cpp -P ";
//     char line[LINE_SIZE];
//     std::ostringstream tmp;

//     cmd += fileName;
//     FILE *pProc = popen(cmd.c_str(), "r");

//     if (!pProc) return false;

//     while (fgets(line, LINE_SIZE, pProc))
//     {
//         tmp << line;
//     }
//     stream.str(tmp.str());

//     return pclose(pProc) == 0;
// }

// bool Parser::preprocessFile(const char *fileName, std::istringstream &stream){
//     std::string cmd = "cpp -P ";
//     // char line[LINE_SIZE];
//     std::ostringstream tmp;

//     cmd += fileName;
//     FILE *pProc = popen(cmd.c_str(), "r");

//     if (!pProc) return false;

//     std::string str;
//     pProc >> str;

// }