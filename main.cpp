#include "stdafx.h"
#include "main.h"
#include "ciphers/caesar/caesar_modified.h"
#include "ciphers/ctc/ctc.h"
#include "ciphers/vigenere/vigenere.h"

void printStartMessageTitle();									// print the title 'Encrypt machine'
void parseArguments(const std::vector<std::string>& vec);		// take all the arguments and turn them into options
inline bool exists_test (const std::string& name);				// check - does this file exist or not?
bool fileIsEmpty(std::ifstream& pFile);							// check - does file is empty or not?
bool checkQuietOptionForValidity();								// check - does all used options valid or not?
std::string getCipherMethodFromUser();							// if options aren't specified, we ask the user which cipher he wants to use
std::string getKeywordFromUser();								// if the cipher requires the key - we can ask the key from user using this func
std::string getMessageFromUser();								// if the user doesn't specified '-m' or '-i' option, we should ask the message from user
void printHelpMessage();										// help message

int main(int argc, char** argv)
{
	std::vector<std::string> arguments;
	for (int i = 1; i < argc; ++i)
	{
		arguments.push_back(argv[i]);
	}
	
	try
	{
		parseArguments(arguments);
	}
	catch(const std::string& ex)
	{
		std::cout << ex << '\n';
		return 0;
	}

	if (CommandLineArguments::bHelp)
	{
		printHelpMessage();
		return 0;
	}

	if(!checkQuietOptionForValidity())
	{
		std::cout << CColors::RED + "The '-q' option requires more paramaters to work! It is also possible that you entered one of the values incorrectly. Please double-check your input!\n" + CColors::WHITE;
		return 0;
	}

	if (!CommandLineArguments::bQuiet)
	{
		printStartMessageTitle();
	}

	// if nothing is specified, we ask the user which cipher he wants to use
	if (CommandLineArguments::cipherMethod.length() == 0)
	{
		CommandLineArguments::cipherMethod = getCipherMethodFromUser();
	}

	// we should write to the CommandLineArguments::keyword out keyword, if user specified '-ki' option
	if (CommandLineArguments::keywordInputFilePath.length() != 0)
	{
		// we are sure that the file is not empty, because we have already checked it, so we can do an integrity check on the file and then read data from it
		std::stringstream tmpStringStream;

		// open the filestream
		std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		try
		{
			file.open(CommandLineArguments::keywordInputFilePath);
		}
		catch (const std::ifstream::failure& ex)
		{
			// checking for opening files
			std::cerr << "Error while opening the keyword-input file!\n";
            std::cerr << "Error code: " << ex.what() << '\n';
			return -1;
		}

		tmpStringStream << file.rdbuf();
		CommandLineArguments::keyword = tmpStringStream.str();
		file.close();
	} 
	
	// if the cipher method is caesar's cipher, we call the caesar's modified cipher, but with the keyword - 3, even if the keyword was specified in the arguments
	if ( !strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[0].c_str()))
	{
		CommandLineArguments::keyword = std::to_string(3);
	}
	// if the '-b' option enabled and we use caesar-modified cipher, we don't need key
	else if (CommandLineArguments::bBrute && !strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[2].c_str()))
	{
		CommandLineArguments::keyword = "";
	}
	// also if user specified the keyword in the arguments (or specified the path to the key), we don't need ask the key
	else if (CommandLineArguments::keyword.length() == 0 && CommandLineArguments::keywordInputFilePath.length() == 0)
	{
		CommandLineArguments::keyword = getKeywordFromUser();
	}

	std::string messageToTheFunction;


	// if user doesn't specified message or input file, we should ask the user which message he wants to encrypt\decrypt
	if( CommandLineArguments::message.length() == 0 && CommandLineArguments::inputFilePath.length() == 0)
	{
		messageToTheFunction = getMessageFromUser();
	}
	// if user used '-m' option, we should use this message
	else if (CommandLineArguments::message.length() != 0)
	{
		messageToTheFunction = CommandLineArguments::message;
	}
	// if user used '-i' option, we should use message from the file
	else
	{
		// we are sure that the file is not empty, because we have already checked it, so we can do an integrity check on the file and then read data from it
		std::stringstream tmpStringStream;

		// open the filestream
		std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		try
		{
			file.open(CommandLineArguments::inputFilePath);
		}
		catch (const std::ifstream::failure& ex)
		{
			// checking for opening files
			std::cerr << "Error while opening the input file!\n";
            std::cerr << "Error code: " << ex.what() << '\n';
			return -1;
		}

		tmpStringStream << file.rdbuf();
		messageToTheFunction = tmpStringStream.str();

		file.close();
	}

	// call the func, which encrypt\decrypt smth
	// we pass in this func such args like:
		// CommandLineArguments::bDecrypt
		// data (message) (CommandLineArguments::message (or the string from the file CommandLineArguments::inputFilePath (so firstly we need to get the data from the file)))
		// CommandLineArguments::keyword
	// and return the decrypted/encrypted string 
	// after this manipulation we print the string in the terminal or put it in the output file

	std::string (*cipherFunction)(const bool&, const std::string&, const std::string&);


	if ( !strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[0].c_str()))
	{
		cipherFunction = caesar_modified;
	}
	else if (!strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[1].c_str()))
	{
		cipherFunction = ctc;
	}
	else if (!strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[2].c_str()))
	{
		if (CommandLineArguments::bBrute)
		{
			cipherFunction = bruteforceCaesarModified;
		}
		else
		{
			cipherFunction = caesar_modified;
		}
	}
	else if (!strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[3].c_str()))
	{
		// cipherFunction = hill;
	}
	else if (!strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[4].c_str()))
	{
		cipherFunction = vigenere;
	}

	std::string returnedString;
	try
	{
		returnedString = cipherFunction(CommandLineArguments::bDecrypt, messageToTheFunction, CommandLineArguments::keyword);
	}
	catch(const std::string& ex)
	{
		std::cout << CColors::RED + ex + CColors::WHITE << '\n';
		return 0;
	}

	// if user used '-o' option, we should write returnedString to this file
	if (CommandLineArguments::outputFilePath.length() != 0)
	{
		std::ofstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			file.open(CommandLineArguments::outputFilePath, std::ios::out | std::ios::trunc);
		}
		catch(const std::ifstream::failure& ex)
		{
			// checking for opening files
			std::cerr << "Error while opening the input file!\n";
            std::cerr << "Error code: " << ex.what() << '\n';
			return -1;
		}

		file << returnedString;
		file.close();

		std::cout << CColors::GREEN << "The ";
		if (CommandLineArguments::bDecrypt)
		{
			std::cout << "decrypted ";
		}
		else
		{
			std::cout << "encrypted ";
		}
		std::cout << "data was successfully read and written to the file " << CommandLineArguments::outputFilePath << '\n' << CColors::WHITE;
	}
	else
	{
		if (!CommandLineArguments::bQuiet)
		{
			std::cout << CColors::GREEN << "The ";
			if (CommandLineArguments::bDecrypt || (!strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[2].c_str()) && CommandLineArguments::bBrute))
			{
				std::cout << "decrypted ";
			}
			else
			{
				std::cout << "encrypted ";
			}
			std::cout << "data was successfully read. " << CColors::WHITE;
			if (CommandLineArguments::bDecrypt || (!strcmp(CommandLineArguments::cipherMethod.c_str(), namesOfTheCiphersWhichAreAllowed[2].c_str()) && CommandLineArguments::bBrute))
			{
				std::cout << "Decrypted ";
			}
			else
			{
				std::cout << "Encrypted ";
			}
			std::cout << "data:\n";
		}

		std::cout << returnedString << '\n';
	}

	return 0;
}

void printStartMessageTitle()
{

 std::cout << CColors::BLUE + 
 			  "    ______                             _    \n";
 std::cout << "   |  ____|                           | |   \n";
 std::cout << "   | |__   _ __   ___ _ __ _   _ _ __ | |_  \n";
 std::cout << "   |  __| | '_ \\ / __| '__| | | | '_ \\| __| \n";
 std::cout << "   | |____| | | | (__| |  | |_| | |_) | |_  \n";
 std::cout << "   |______|_| |_|\\___|_|   \\__, | .__/ \\__| \n";
 std::cout << "                            __/ | |         \n";
 std::cout << "                         _ |___/|_|         \n";
 std::cout << "                        | |   (_)           \n";
 std::cout << "    _ __ ___   __ _  ___| |__  _ _ __   ___ \n";
 std::cout << "   | '_ ` _ \\ / _` |/ __| '_ \\| | '_ \\ / _ \\ \n";
 std::cout << "   | | | | | | (_| | (__| | | | | | | |  __/ \n";
 std::cout << "   |_| |_| |_|\\__,_|\\___|_| |_|_|_| |_|\\___|\n";
 std::cout << "                                            \n" + CColors::WHITE;
                                          
}

std::string getCipherMethodFromUser()
{
	int cipherNumber;
	std::string tmpStr;
	while(true)
	{
		// These choices must be in the same order as the strings in the namesOfTheCiphersWhichAllowed vector
		std::cout << CColors::BLUE + "What cipher will we use:\n";
		std::cout << CColors::GREEN + "\t[0] " + CColors::BLUE + "Caesar\'s\n" + CColors::WHITE;
		std::cout << CColors::GREEN + "\t[1] " + CColors::BLUE + "Column Transposition\n" + CColors::WHITE;
		std::cout << CColors::GREEN + "\t[2] " + CColors::BLUE + "Caesar\'s modified\n" + CColors::WHITE;
		std::cout << CColors::GREEN + "\t[3] " + CColors::BLUE + "Hill\'s\n" + CColors::WHITE;
		std::cout << CColors::GREEN + "\t[4] " + CColors::BLUE + "Vigenere\n\n" + CColors::WHITE;
		
		std::cout << "Enter the option:\n" + CColors::RED + "\t[>] " + CColors::WHITE;
		std::cin >> tmpStr;
		std::cin.ignore(1, '\n');
		try
		{
			cipherNumber = std::stoi(tmpStr);
		}
		catch(const std::invalid_argument& ia)
		{
			cipherNumber = -1;
		}

		if (cipherNumber < 0 || cipherNumber > static_cast<int>(namesOfTheCiphersWhichAreAllowed.size()))
		{
			std::cout << CColors::RED + "Incorrect input! Try again\n" + CColors::WHITE;
		}
		else
		{
			break;
		}
	}
	std::cout << '\n';
	return namesOfTheCiphersWhichAreAllowed[cipherNumber];
}

std::string getKeywordFromUser()
{
	std::string keyword;
	std::cout << CColors::GREEN + "[+] " + CColors::BLUE + "Enter the keyword (it could be a phrase or the number (if the cipher method is caesar\'s-modified)): \n" + CColors::WHITE;
	std::cout << CColors::RED + "\t[>] " + CColors::WHITE;
	std::getline(std::cin, keyword);
	std::cout << '\n';
	return keyword;
}

std::string getMessageFromUser()
{
	std::string message;
	std::cout << CColors::GREEN + "[+] " + CColors::BLUE + "Enter the message (it could be a phrase): \n" + CColors::WHITE;
	std::cout << CColors::RED + "\t[>] " + CColors::WHITE;
	std::getline(std::cin, message);
	std::cout << '\n';
	return message;
}

void parseArguments(const std::vector<std::string>& vec)
{
	// std::vector<std::string> returnedVector;
	for(int i = 0; i < static_cast<int>(vec.size()); ++i)
	{
		if( !strcmp(vec[i].c_str(), "-d") || !strcmp(vec[i].c_str(), "--decrypt") )
		{
			CommandLineArguments::bDecrypt = true;
		}
		else if ( !strcmp(vec[i].c_str(), "-h") || !strcmp(vec[i].c_str(), "--help") )
		{
			CommandLineArguments::bHelp = true;
			break;
		}
		else if( !strcmp(vec[i].c_str(), "-q") || !strcmp(vec[i].c_str(), "--quiet") )
		{
			CommandLineArguments::bQuiet = true;
		}
		else if ( !strcmp(vec[i].c_str(), "-b") || !strcmp(vec[i].c_str(), "--bruteforce"))
		{
			CommandLineArguments::bBrute = true;
		}
		else if( !strcmp(vec[i].c_str(), "-i") || !strcmp(vec[i].c_str(), "--input") )
		{	
			std::string possibleException;
			try
			{
				// check file does it exists
				if (exists_test(vec.at(i + 1)))
				{
					std::ifstream file;
					file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
					try
					{
						file.open(vec[i + 1]);
					}
					catch(const std::ifstream::failure& ex)
					{
            			std::cerr << "Error code: " << ex.what() << '\n';
						possibleException = static_cast<std::string>("Error while opening the input file!\n");
						throw possibleException; // we throw std::string
					}
					// check file is it empty
					if(!fileIsEmpty(file))
					{
						CommandLineArguments::inputFilePath = vec[i + 1];
					}
					else
					{
						possibleException = static_cast<std::string>("The input file is empty!");
						throw possibleException; // we throw std::string
					}
					file.close();
				}
				else
				{
					possibleException =  static_cast<std::string>("The input file doesn't exist!\n");
					throw possibleException; // we throw std::string
				}
			}
			catch(const std::string& ex) // and if we catch this string, 
			{								// we take it out of this function and send it to the main function,
				throw ex;						// where another try-catch is waiting for it
			}
			catch(const std::out_of_range& ex)
			{
				std::cout << "Maybe you wrote the input file path in the wrong order, please recheck again. Use \"./encryption-machine -h\" to get detailed iformation!\n";
				std::cout << "Out of range error: " << ex.what() << '\n';
				throw static_cast<std::string>("Incorrect usage of the -i option");
			}
		}
		else if ( !strcmp(vec[i].c_str(), "-ki") || !strcmp(vec[i].c_str(), "--keyword-input") )
		{
			std::string possibleException;
			try
			{
				// check file does it exists
				if (exists_test(vec.at(i + 1)))
				{
					std::ifstream file;
					file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
					try
					{
						file.open(vec[i + 1]);
					}
					catch(const std::ifstream::failure& ex)
					{
            			std::cerr << "Error code: " << ex.what() << '\n';
						possibleException = static_cast<std::string>("Error while opening the keyword-input file!\n");
						throw possibleException; // we throw std::string
					}
					// check file is it empty
					if(!fileIsEmpty(file))
					{
						CommandLineArguments::keywordInputFilePath = vec[i + 1];
					}
					else
					{
						possibleException = static_cast<std::string>("The keyword-input file is empty!");
						throw possibleException; // we throw std::string
					}
					file.close();
				}
				else
				{
					possibleException =  static_cast<std::string>("The keyword-input file doesn't exist!\n");
					throw possibleException; // we throw std::string
				}
			}
			catch(const std::string& ex) // and if we catch this string, 
			{								// we take it out of this function and send it to the main function,
				throw ex;						// where another try-catch is waiting for it
			}
			catch(const std::out_of_range& ex)
			{
				std::cout << "Maybe you wrote the keyword-input file path in the wrong order, please recheck again. Use \"./encryption-machine -h\" to get detailed iformation!\n";
				std::cout << "Out of range error: " << ex.what() << '\n';
				throw static_cast<std::string>("Incorrect usage of the -ki option");
			}
		}
		else if ( !strcmp(vec[i].c_str(), "-o") || !strcmp(vec[i].c_str(), "--output") )
		{
			std::string possibleException;
			try
			{
				std::ofstream file;
				file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					file.open(vec[i + 1], std::ios::out | std::ios::trunc);
				}
				catch(const std::ifstream::failure& ex)
				{
            		std::cerr << "Error code: " << ex.what() << '\n';
					possibleException = static_cast<std::string>("Error while opening the output file! Maybe we don\'t have permissions to create\\write the smth in the inputed folder\n");
					throw possibleException; // we throw std::string
				}
				
				CommandLineArguments::outputFilePath = vec.at(i + 1);
				file.close();
			}
			catch(const std::string& ex)
			{
				throw ex;
			}
			catch(const std::out_of_range& ex)
			{
				std::cout << "Maybe you wrote the output file path in the wrong order, please recheck again. Use \"./encryption-machine -h\" to get detailed iformation!\n";
				std::cout << "Out of range error: " << ex.what() << '\n';
				throw static_cast<std::string>("Incorrect usage of the -o option");
			}
		}
		else if( !strcmp(vec[i].c_str(), "-c") || !strcmp(vec[i].c_str(), "--cipher") )
		{
			// namesOfTheCiphersWhichAreAllowed vector was written in the file main.h
			for (const auto& it : namesOfTheCiphersWhichAreAllowed)
			{
				try
				{
					if ( !strcmp(vec.at(i + 1).c_str(), it.c_str()))
					{
						CommandLineArguments::cipherMethod = vec[i + 1];
					}
				}
				catch(const std::out_of_range& ex)
				{
					std::cout << "Maybe you wrote the cipher name (method) in the wrong order, please recheck again. Use \"./encryption-machine -h\" to get detailed iformation!\n";
					std::cout << "Out of range error: " << ex.what() << '\n';
					throw static_cast<std::string>("Incorrect usage of the -c option");
				}
			}
		}
		else if ( !strcmp(vec[i].c_str(), "-m") || !strcmp(vec[i].c_str(), "--message") )
		{
			try
			{
				CommandLineArguments::message = vec.at(i + 1);
			}
			catch(const std::out_of_range& ex)
			{
				std::cout << "Maybe you wrote the message in the wrong order, please recheck again. Use \"./encryption-machine -h\" to get detailed iformation!\n";
				std::cout << "Out of range error: " << ex.what() << '\n';
				throw static_cast<std::string>("Incorrect usage of the -m option");
			}
		}
		else if ( !strcmp(vec[i].c_str(), "-k") || !strcmp(vec[i].c_str(), "--keyword") )
		{
			try
			{
				CommandLineArguments::keyword = vec.at(i + 1);
			}
			catch(const std::out_of_range& ex)
			{
				std::cout << "Maybe you wrote the keyword in the wrong order, please recheck again. Use \"./encryption-machine -h\" to get detailed iformation!\n";
				std::cout << "Out of range error: " << ex.what() << '\n';
				throw static_cast<std::string>("Incorrect usage of the -k option");
			}
		}
	}
}

inline bool exists_test (const std::string& name)
{
	struct stat buffer;
	return (stat (name.c_str(), &buffer) == 0); 
}

bool fileIsEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

bool checkQuietOptionForValidity()
{
	// Options '-i' and '-o' we checked in the func parseArguments() when use lstat() or stat() functions, so they need not be checked
	// Options '-m' and '-k' aren't needed in checked, because the message or the key can be everything  

	// Option '-q' is required three another options: '-m'/-i' and '-c'
	if(CommandLineArguments::bQuiet)
	{
		// if '-m' and '-i' aren't specified
		if( CommandLineArguments::message.length() == 0 && CommandLineArguments::inputFilePath.length() == 0 )
		{
			return false;
		}

		// check for option '-c'
		if( CommandLineArguments::cipherMethod.length() == 0 )
		{
			return false;
		}
	}

	return true;
}

void printHelpMessage()
{

	std::cout << "Usage: ./encryption-machine [-option] [value] ...\n\n";

	std::cout << "Possible options:\n";
	std::cout << CColors::BLUE + "\t-h, --help\t\t\t\t\t\tShow this help message and exit\n" + CColors::WHITE;
	std::cout << "\t-m \"some text\", --message \"some text\"\t\t\tMessage which will be encrypted\n";
	std::cout << CColors::BLUE + "\t-c \"name of the cipher\", --cipher \"name of the cipher\"\tCipher name (method)\n" + CColors::WHITE;
	std::cout << "\t-b, --bruteforce\t\t\t\t\tUse brute force for crack caesar-modified cipher (key doesn\'t required)\n"; 
	std::cout << CColors::BLUE + "\t-k \"some text\", --keyword \"some text\"\t\t\tKeyword that is required for some ciphers\n" + CColors::WHITE;
	std::cout << "\t-ki <path/to/the/file>, --keyword-input <path/to/the/file>\tPath to the file, which will used as a keyword\n";
	std::cout << CColors::BLUE + "\t-i <path/to/the/file>, --input <path/to/the/file>\tPath to the file which will be encrypted/decrypted\n" + CColors::WHITE;
	std::cout << "\t-o <path/to/the/file>, --output <path/to/the/file>\tPath to the output file where the encrypted/decrypted message will be saved\n";
	std::cout << CColors::BLUE + "\t-q, --quiet\t\t\t\t\t\tThe qiet output. " + CColors::RED + "Important note: this option requires these parameters:\n" + CColors::WHITE;
	std::cout << CColors::BLUE + "\t\t\t\t\t\t\t\tIf you want to encrypt the message/file without any output\n";
	std::cout << "\t\t\t\t\t\t\t\t\t1) -m(--message) or -i(--input)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t2) -c(--cipher)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t3) -k(--keyword)\n";
	std::cout << CColors::BLUE + "\t\t\t\t\t\t\t\tIf you want to decrypt the message/file without any output\n" + CColors::WHITE;
	std::cout << "\t\t\t\t\t\t\t\t\t1) -d(--decrypt)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t2) -m(--message) or -i(--input)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t3) -c(--cipher)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t4) -k(--keyword)\n";
	std::cout << CColors::RED + "\t\t\t\t\t\t\t\t\tNote:" + CColors::BLUE + "\tIf you using the caesar-modified cipher with \'-b\' option, you don\'t need to use the \'-k\' option\n\n" + CColors::WHITE;
	

	std::cout << CColors::RED + "All ciphers which you can use:\n" + CColors::WHITE;
	std::cout << "\t- caesar\n";
	std::cout << "\t- ctc\n";
	std::cout << "\t- caesar-modified\n";
	std::cout << "\t- hill\n";
	std::cout << "\t- vigenere\n\n";

	std::cout << CColors::BLUE + "Note:\t If you use a caesar-modified cipher, use a number instead of the key to set the shift. For example:\n" + CColors::WHITE;
	std::cout << "./encryption-machine -c caesar-modified -k 5 -o encryptedMessage.txt -i inputCaesarCipher.txt\n";
	std::cout << CColors::BLUE + "If you write a word or phrase in the keyword instead of a number, a shift will be used with the size of the number of characters in the string\n" + CColors::WHITE;
	std::cout << CColors::BLUE + "If you want to decrypt a cipher message, but you don\'t know the shift (key), you can use bruteforce (check option -b). BruteForce works only with caesar-modified cipher\n\n" + CColors::WHITE;
	
	std::cout << CColors::BLUE + "Note 2:\t All cipher names are written in small letters\n\n" + CColors::WHITE;

	std::cout << CColors::BLUE + "Note 3:\t ctc stands for column transposition cipher\n\n" + CColors::WHITE;

	std::cout << '\n';

	std::cout << CColors::RED + 
				 "###################\n";
	std::cout << "#  Usage Examples #\n";
	std::cout << "###################\n\n" + CColors::WHITE;

	std::cout << "$ ./encryption-machine\n";
	std::cout << "$ ./encryption-machine -c caesar -m \"Message which will be encrypted\" -o encryptedMessage.txt\n";
	std::cout << "$ ./encryption-machine -i ~/Desktop/fileToDecrypt.txt -d -o decryptedMessage.txt\n";
	std::cout << "$ ./encryption-machine -ki ~/Desktop/keyword.txt -c vigenere -o output.txt -m \"This message will be encrypted using Vigenere cipher!\"\n";
	std::cout << "$ ./encryption-machine -c caesar-modified -b -d -i input.txt\n";
	std::cout << "$ ./encryption-machine -c ctc -k \"This is a keyword\" -m \"Linus Torvalds is a genius\" -q\n";
}

