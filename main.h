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

const std::vector<std::string> namesOfTheCiphersWhichAreAllowed = {"caesar", "ctc", "caesar-modified", "hill"};

const std::vector<char> englishAlphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const std::vector<char> englishAlphabetUpperLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 

const std::vector<char> punctuation = {' ', '`', '\'', '\"', '~', ',', '.', '/', '\\', '-', '=', '+', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_',
                                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// we create a vector which contains all alphabets what we have, because in this way we can iterate by alphabets
const std::vector<std::vector<char>> AllAlphabets = {englishAlphabet, englishAlphabetUpperLetters};

#endif