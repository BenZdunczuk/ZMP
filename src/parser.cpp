#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <thread>

#include "xmlinterp.hh"
#include "parser.hh"
#include "libInterface.hh"

using namespace std;
using namespace xercesc;

void paralellCommand(AbstractInterp4Command *cmd, AbstractScene &scene, ComChannel &channel)
{
    cmd->ExecCmd(scene,channel);
    // std::cout << "tred\n";
}

bool Parser::ReadAndExecCmd(std::istream &IStrm, pluginManager manager, Scene &scene, ComChannel &channel)
{
    // bool parallel = false;
    std::list<std::thread> threadList;
    std::string Keyword;

    while (IStrm >> Keyword)
    {
        if (Keyword == "Begin_Parallel_Actions")
        {
            // cout << "begin_parallel\n";
            while (Keyword != "End_Parallel_Actions")
            {

                IStrm >> Keyword;
                // cout << Keyword << "\n";
                std::shared_ptr<LibInterface> libHandler = manager.findPlugin(Keyword);
                if (libHandler != nullptr)
                {
                    manager.setActivePlugin(libHandler->getCMD());
                    if (manager.getActivePlugin()->ReadParams(IStrm))
                    {
                        manager.getActivePlugin()->PrintSyntax();
                        manager.getActivePlugin()->PrintCmd();
                        std::thread task(paralellCommand, manager.getActivePlugin(), std::ref(scene), std::ref(channel));
                        threadList.push_back(std::move(task));
                    }
                }else{break;}
            }
            if (Keyword == "End_Parallel_Actions")
            {
                for (std::thread &thread : threadList)
                {
                    thread.join();
                }
                // cout << "end\n";

                threadList.clear();
                // parallel = false;
                continue;
                // cout << "++++++++end\n";

            }

            // parallel = true;
            continue;
        }

        std::shared_ptr<LibInterface> libHandler = manager.findPlugin(Keyword);
        if (libHandler != nullptr)
        {
            manager.setActivePlugin(libHandler->getCMD());
            if (manager.getActivePlugin()->ReadParams(IStrm))
            {
                manager.getActivePlugin()->PrintSyntax();
                manager.getActivePlugin()->PrintCmd();
                manager.getActivePlugin()->ExecCmd(scene,channel);
                // std::cout << "singl\n";
            }
        }
        else
            return false;
    }
    return true;
}

std::string Parser::preprocessFile(const std::string &cmdsFileName)
{
    std::string outputFile = cmdsFileName + ".tmp";
    std::string cmd = "cpp -P " + cmdsFileName + " -o " + outputFile;
    system(cmd.c_str());

    return outputFile;
}

bool Parser::ReadXMLFile(const std::string xmlFileName, Configuration &Config)
{
    const char *fileName = xmlFileName.c_str();
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

    DefaultHandler *pHandler = new XMLInterp4Config(Config);
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
        pParser->parse(fileName);
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