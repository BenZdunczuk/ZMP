#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

#include "parser.hh"
#include "pluginManager.hh"
#include "libInterface.hh"

using namespace std;
using namespace xercesc;

#define LINE_SIZE 255

// #define STR(x) #x
// #define IF_CMD_THEN_READ(CmdName)                       \
//     if (Keyword == STR(CmdName))                        \
//     {                                                   \
//         if (!ReadCmd##CmdName(IStrm, CmdLst))           \
//             return false;                               \
//         continue;                                       \
//     }

// bool Parser::ReadCmdsList(std::istream &IStrm, std::list<std::string> &CmdLst)
// {
//     std::string Keyword;
//     while (IStrm >> Keyword)
//     {
//         IF_CMD_THEN_READ(Move)
//         IF_CMD_THEN_READ(Rotate)
//         IF_CMD_THEN_READ(Set)
//         IF_CMD_THEN_READ(Pause)
//         return false;
//     }
//     return true;
// }

// bool Parser::ReadCmdMove(std::istream &IStrm, std::list<std::string> &CmdLst){
//     if(manager.plugins.find("Move")->second->getCMD()->ReadParams(IStrm)){
//         manager.plugins.find("Move")->second->getCMD()->PrintParams();
//         return true;
//     }
//     return false;
// }

// bool Parser::ReadCmdRotate(std::istream &IStrm, std::list<std::string> &CmdLst){
//     if(manager.plugins.find("Rotate")->second->getCMD()->ReadParams(IStrm)){
//         manager.plugins.find("Rotate")->second->getCMD()->PrintParams();
//         return true;
//     }
//     return false;
// }

// bool Parser::ReadCmdSet(std::istream &IStrm, std::list<std::string> &CmdLst){
//     if(manager.plugins.find("Set")->second->getCMD()->ReadParams(IStrm)){
//         manager.plugins.find("Set")->second->getCMD()->PrintParams();
//         return true;
//     }
//     return false;
// }

// bool Parser::ReadCmdPause(std::istream &IStrm, std::list<std::string> &CmdLst){
//     if(manager.plugins.find("Pause")->second->getCMD()->ReadParams(IStrm)){
//         manager.plugins.find("Pause")->second->getCMD()->PrintParams();
//         return true;
//     }
//     return false;
// }

bool Parser::ReadCmd(std::istream &IStrm)
{
    std::string Keyword;
    while (IStrm >> Keyword)
    {
        std::shared_ptr<LibInterface> libHandler = manager.findPlugin(Keyword);
        if (libHandler != nullptr)
        {   
            manager.activePlugin = libHandler->getCMD();
            if (manager.activePlugin->ReadParams(IStrm))
            {
                manager.activePlugin->PrintSyntax();
                manager.activePlugin->PrintCmd();
            }
        }
        else
            return false;
    }
    return true;
}

std::string Parser::preprocessFile(const std::string &filename)
{
    std::string output_file = filename + ".tmp";

    std::string cmd = "cpp -P " + filename + " -o " + output_file;
    system(cmd.c_str());

    return output_file;
}

/*!
 * Czyta z pliku xml opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool Parser::ReadXMLFile(const char *sFileName, Configuration &rConfig)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException &toCatch)
    {
        char *message = XMLString::transcode(toCatch.getMessage());
        cerr << "Error during initialization! :\n";
        cerr << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    SAX2XMLReader *pParser = XMLReaderFactory::createXMLReader();

    pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    pParser->setFeature(XMLUni::fgXercesDynamic, false);
    pParser->setFeature(XMLUni::fgXercesSchema, true);
    pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

    pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

    DefaultHandler *pHandler = new XMLInterp4Config(rConfig);
    pParser->setContentHandler(pHandler);
    pParser->setErrorHandler(pHandler);

    try
    {

        if (!pParser->loadGrammar("config/config.xsd",
                                  xercesc::Grammar::SchemaGrammarType, true))
        {
            cerr << "!!! Plik grammar/actions.xsd, '" << endl
                 << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
                 << endl;
            return false;
        }
        pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);
        pParser->parse(sFileName);
    }
    catch (const XMLException &Exception)
    {
        char *sMessage = XMLString::transcode(Exception.getMessage());
        cerr << "Informacja o wyjatku: \n"
             << "   " << sMessage << "\n";
        XMLString::release(&sMessage);
        return false;
    }
    catch (const SAXParseException &Exception)
    {
        char *sMessage = XMLString::transcode(Exception.getMessage());
        char *sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

        cerr << "Blad! " << endl
             << "    Plik:  " << sSystemId << endl
             << "   Linia: " << Exception.getLineNumber() << endl
             << " Kolumna: " << Exception.getColumnNumber() << endl
             << " Informacja: " << sMessage
             << endl;

        XMLString::release(&sMessage);
        XMLString::release(&sSystemId);
        return false;
    }
    catch (...)
    {
        cout << "Zgloszony zostal nieoczekiwany wyjatek!\n";
        return false;
    }

    delete pParser;
    delete pHandler;
    return true;
}