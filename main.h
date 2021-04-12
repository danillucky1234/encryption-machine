#ifndef MAIN_H
#define MAIN_H 

// namespace with the custom colors, which will be used for colorful output
namespace CColors
{
    const std::string RED	= "\033[31m"; 
    const std::string GREEN	= "\033[32m"; 
    const std::string BLUE	= "\033[36m"; 
    const std::string WHITE	= "\033[0m";  
}

namespace CommandLineArguments
{
    // string vars
    static std::string inputFilePath   = "";
    static std::string outputFilePath  = "";
    static std::string keyword         = "";
    static std::string cipherMethod    = "";
    static std::string message         = "";

    // bool vars
    static bool bDecrypt               = false;    // if no '-d' parameter is specified, we will encrypt the file
    static bool bQuiet                 = false;    // originally we will print some messages
    static bool bHelp                  = false;    // should we print the help message or not
}

const std::vector<std::string> namesOfTheCiphersWhichAreAllowed = {"caesar", "rsa", "caesar-modified", "hill"};

#endif