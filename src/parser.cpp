#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

#include "parser.hh"

using namespace xercesc;

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

bool Parser::ReadFile(const char* sFileName, Configuration &rConfig){
    try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            std::cerr << "Error during initialization! :\n";
            std::cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
        std::cerr << "!!! Plik grammar/actions.xsd, '" << std::endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << std::endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            std::cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            std::cerr << "Blad! " << std::endl
                 << "    Plik:  " << sSystemId << std::endl
                 << "   Linia: " << Exception.getLineNumber() << std::endl
                 << " Kolumna: " << Exception.getColumnNumber() << std::endl
                 << " Informacja: " << sMessage 
                 << std::endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}