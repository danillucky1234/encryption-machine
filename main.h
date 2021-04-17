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
    std::string inputFilePath   		= "";
    std::string outputFilePath  		= "";
    std::string keyword         		= "";
	std::string keywordInputFilePath 	= "";
    std::string cipherMethod    		= "";
    std::string message         		= "";

    // bool vars
    bool bDecrypt				= false;    // if no '-d' parameter is specified, we will encrypt the file
    bool bQuiet  				= false;    // originally we will print some messages
    bool bHelp   				= false;    // should we print the help message or not
    bool bBrute  				= false;    // bruteforce for caesar-modified cipher
}

const std::vector<std::string> namesOfTheCiphersWhichAreAllowed = {"caesar", "ctc", "caesar-modified", "hill", "vigenere"};

#endif