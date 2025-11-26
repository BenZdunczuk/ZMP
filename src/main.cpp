#include <filesystem>

#include "interpreter.hh"

// #define PLUGIN_NAME__move "./plugin/libInterp4Move.so"
// #define PLUGIN_NAME__rotate "./plugin/libInterp4Rotate.so"
// #define PLUGIN_NAME__set "./plugin/libInterp4Set.so"
// #define PLUGIN_NAME__pause "./plugin/libInterp4Pause.so"

using namespace std;

int main(int argc, char **argv)
{
    interpreter Intpr;
    if (argc < 3)
    {
        cout << "Error: Missing input file/files!\n";
        cout << "Usage: ./cmds_intepreter [config_file_path] [commands_file_path]\n";
        return 1;
    }

    for (int i = 1; i <= 2; i++)
    {
        if (!std::filesystem::exists(argv[i]))
        {
            cout << "Error: File " << argv[i] << " not found!\n";
            return 1;
        }
    }

    if (Intpr.interprete(argv[1], argv[2]))
    {
        return 1;
    }

    return 0;
}
