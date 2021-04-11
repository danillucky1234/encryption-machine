#include "stdafx.h"

void printStartMessageTitle();
int printAndGetPossibleEncryptOptions();
bool printAndGetInfoAboutWhatWeShouldEncryptMessageOrFile();
std::string printAndGetKeyword();
void chooseWhatToEncrypt(int cypherCode, bool messageOrFile);
void printHelpMessage();

int main(int argc, char** argv)
{
	
	// if input will be like these:
	// ./Encryption-machine -i
	// ./Ecnryption-machine --input
	// we'll write error message
	if (argc == 2 && (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--input") == 0) )
	{
		std::cout << CColors::RED + "Incorrect usage!" + CColors::WHITE + '\n';
		std::cout << CColors::BLUE + "Use \"./Encrypte-machine --help\" for detail information\n" + CColors::WHITE;
	}
	else
	{
		// ./Encrypt-machine
		if(argc == 1)
		{
			printStartMessageTitle();
			int cypherCode = printAndGetPossibleEncryptOptions();
			
			// printAndGetInfoAboutWhatWeShouldEncryptMessageOrFile returned:
			// 0 - Message
			// 1 - File
			bool isUsedFile = printAndGetInfoAboutWhatWeShouldEncryptMessageOrFile();
			std::string keyword = printAndGetKeyword();

			chooseWhatToEncrypt(cypherCode, isUsedFile);
		
		} 	// ./Encrypt-machine --help || ./Encrupt-machine -h 
		else if(argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
		{
			printHelpMessage();
			return 0;
		}
		
		if (argc == 2 && (strcmp(argv[1], "--rsa") == 0 || strcmp(argv[1], "--RSA") == 0))
		{
			// we will encrypt message which were taken from terminal
			std::cout << CColors::GREEN + "Enter the message that will be encrypted:\n" + CColors::WHITE;
			std::string inputMessageStr;
			std::getline(std::cin, inputMessageStr);
			
		}
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

int printAndGetPossibleEncryptOptions()
{
	int cryptargument;
	while(true)
	{
		std::cout << CColors::GREEN + "[0] " + CColors::BLUE + "Disjunction\n" + CColors::WHITE;
		std::cout << CColors::GREEN + "[1] " + CColors::BLUE + "RSA\n" + CColors::WHITE;
		
		std::cout << "Enter the option:\n" + CColors::RED + "\t[>] " + CColors::WHITE;
		std::cin >> cryptargument;
		if (cryptargument < 0 || cryptargument > 1)
		{
			std::cout << CColors::RED + "Incorrect input! Try again\n" + CColors::WHITE;
		}
		else
		{
			break;
		}
	}
	std::cout << '\n';
	return cryptargument;
}

bool printAndGetInfoAboutWhatWeShouldEncryptMessageOrFile()
{
	std::string cryptMessage;
	std::cout << CColors::GREEN + "[0] " + CColors::BLUE + "To encrypt the message (default)\n" + CColors::WHITE;
	std::cout << CColors::GREEN + "[1] " + CColors::BLUE + "To encrypt the file\n" + CColors::WHITE;
	
	std::cout << "Enter the option:\n" + CColors::RED + "\t[>] " + CColors::WHITE;
	std::cin.ignore();
	std::getline(std::cin, cryptMessage);
	
	if ((atoi(cryptMessage.c_str()) != 0) && (atoi(cryptMessage.c_str()) != 1))
	{
		std::cout << "The default option to encrypt the message was selected!\n";
		return 0;
	}
	std::cout << '\n';
	return atoi(cryptMessage.c_str());
}

std::string printAndGetKeyword()
{
	std::string keyword;
	std::cout << CColors::GREEN + "[+] " + CColors::BLUE + "Enter the keyword (it could be a phrase): \n" + CColors::WHITE;
	std::cout << CColors::RED + "\t[>] " + CColors::WHITE;
	std::getline(std::cin, keyword);

	return keyword;
}

void chooseWhatToEncrypt(int cypherCode, bool messageOrFile)
{
	std::string enteredInformation;
	// True - File
	if(messageOrFile)
	{
		std::cout << CColors::GREEN + "[+] " + CColors::BLUE + "Enter the path to the file:\n";
		std::cout << CColors::RED + "\t[>] ";
		std::string path;
		std::cin >> path;
		
		// Open the file
		std::ifstream inputFile;
		inputFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		std::stringstream ss;
		try
		{
			inputFile.open(path);
			
			// ss << inputFile;

			// close the file
			inputFile.close();
		}
		catch(const std::exception& ex)
		{
			std::cout << CColors::RED + "Incorrectly entered file path. Error code:\n" + CColors::WHITE + ex.what();
			return;
		}
			
	}
	else
	{
		std::cout << CColors::GREEN + "[+] " + CColors::BLUE + "Enter the message:\n";
		std::cout << CColors::RED + "\t[>] ";
		std::string enteredInformation;
		std::getline(std::cin, 	enteredInformation);
	}
	switch(cypherCode)
	{
		case 0:
		break;


	}


}

// void printHelpMessage()
// {
//
// 	std::cout << "Usage: ./Encrypt-machine [possible args]\n\n";
//
// 	std::cout << "Optional arguments:\n";
// 	std::cout << "\t-h, --help\t\t\t\t\t\t" + CColors::BLUE + "Show this help message and exit\n" + CColors::WHITE;
// 	std::cout << "\t-m \"some text\", --message\"some text\"\t\t\t" + CColors::BLUE + "Message which will be encrypted\n" + CColors::WHITE;
// 	std::cout << "\t-c \"name of the cipher\", --cipher \"name of the cipher\"\t" + CColors::BLUE + "Cipher name (method)\n" + CColors::WHITE;
// 	std::cout << "\t-k \"some text\", --keyword \"some text\"\t\t\t" + CColors::BLUE + "Keyword that is required for some ciphers\n" + CColors::WHITE;
// 	std::cout << "\t-i <path/to/the/file>, --input <path/to/the/file>\t" + CColors::BLUE + "Path to the file which will be encrypted/decrypted\n" + CColors::WHITE;
// 	std::cout << "\t-o <path/to/the/file>, --output <path/to/the/file>\t" + CColors::BLUE + "Path to the output file where the encrypted/decrypted message will be saved\n" + CColors::WHITE;
// 	std::cout << "\t-q, --quiet\t\t\t\t\t\t" + CColors::BLUE + "The qiet output. " + CColors::RED + "Important note: this option requires these parameters:\n";
// 	std::cout << CColors::BLUE + "\t\t\t\t\t\t\t\tIf you want to encrypt the message/file without any output\n" + CColors::WHITE;
// 	std::cout << "\t\t\t\t\t\t\t\t\t1) -m(--message) or -i(--input)\n";
// 	std::cout << "\t\t\t\t\t\t\t\t\t2) -c(--cipher). If this cipher has a keyword, then you need one more parameter -k(--keyword)\n";
// 	std::cout << CColors::BLUE + "\t\t\t\t\t\t\t\tIf you want to decrypt the message / file without any output\n" + CColors::WHITE;
// 	std::cout << "\t\t\t\t\t\t\t\t\t1) -d(--decrypt)\n";
// 	std::cout << "\t\t\t\t\t\t\t\t\t2) -m(--message) or -i(--input)\n";
// 	std::cout << "\t\t\t\t\t\t\t\t\t3) -c(--cipher). If the cipher has a key, then you need one more parameter -k(--keyword)\n";
//	
//
// 	std::cout << CColors::BLUE + "Note:\t If you use a cipher like the modified Caesar cipher, use a number instead of the key to set the shift. For example:\n" + CColors::WHITE;
// 	std::cout << "./encryption-machine -c caesar-modified -k 5 -o encryptedMessage.txt -i inputCaesarCipher.txt\n";
//	
// 	std::cout << CColors::BLUE + "Note 2:\t All cipher names are written in small letters" + CColors::WHITE;
//
// 	std::cout << CColors::BLUE + "All ciphers which you can use:\n" + CColors::WHITE;
// 	std::cout << "\t- caesar\n";
// 	std::cout << "\t- caesar-modified\n";
// 	std::cout << "\t- rsa\n";
// 	std::cout << "\t- hill\n";
//
// 	std::cout << '\n';
//
// 	std::cout << CColors::RED + 
// 				 "###################\n";
// 	std::cout << "#  Usage Examples #\n";
// 	std::cout << "###################\n\n" + CColors::WHITE;
//
// 	std::cout << "$ ./encryption-machine\n";
// 	std::cout << "$ ./encryption-machine -c caesar -m \"Message which will be encrypted\" -o encryptedMessage.txt\n";
// 	std::cout << "$ ./encryption-machine -i ~/Desktop/fileToDecrypt.txt -d -o decryptedMessage.txt\n";
// }

void printHelpMessage()
{

	std::cout << "Usage: ./Encrypt-machine [possible args]\n\n";

	std::cout << "Optional arguments:\n";
	std::cout << CColors::BLUE + "\t-h, --help\t\t\t\t\t\tShow this help message and exit\n" + CColors::WHITE;
	std::cout << "\t-m \"some text\", --message\"some text\"\t\t\tMessage which will be encrypted\n";
	std::cout << CColors::BLUE + "\t-c \"name of the cipher\", --cipher \"name of the cipher\"\tCipher name (method)\n" + CColors::WHITE;
	std::cout << "\t-k \"some text\", --keyword \"some text\"\t\t\tKeyword that is required for some ciphers\n";
	std::cout << CColors::BLUE + "\t-i <path/to/the/file>, --input <path/to/the/file>\tPath to the file which will be encrypted/decrypted\n" + CColors::WHITE;
	std::cout << "\t-o <path/to/the/file>, --output <path/to/the/file>\tPath to the output file where the encrypted/decrypted message will be saved\n";
	std::cout << CColors::BLUE + "\t-q, --quiet\t\t\t\t\t\tThe qiet output. " + CColors::RED + "Important note: this option requires these parameters:\n";
	std::cout << CColors::BLUE + "\t\t\t\t\t\t\t\tIf you want to encrypt the message/file without any output\n" + CColors::WHITE;
	std::cout << "\t\t\t\t\t\t\t\t\t1) -m(--message) or -i(--input)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t2) -c(--cipher). If this cipher has a keyword, then you need one more parameter -k(--keyword)\n";
	std::cout << CColors::BLUE + "\t\t\t\t\t\t\t\tIf you want to decrypt the message / file without any output\n" + CColors::WHITE;
	std::cout << "\t\t\t\t\t\t\t\t\t1) -d(--decrypt)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t2) -m(--message) or -i(--input)\n";
	std::cout << "\t\t\t\t\t\t\t\t\t3) -c(--cipher). If the cipher has a key, then you need one more parameter -k(--keyword)\n";
	

	std::cout << CColors::BLUE + "Note:\t If you use a cipher like the modified Caesar cipher, use a number instead of the key to set the shift. For example:\n" + CColors::WHITE;
	std::cout << "./encryption-machine -c caesar-modified -k 5 -o encryptedMessage.txt -i inputCaesarCipher.txt\n";
	
	std::cout << CColors::BLUE + "Note 2:\t All cipher names are written in small letters" + CColors::WHITE;

	std::cout << CColors::BLUE + "All ciphers which you can use:\n" + CColors::WHITE;
	std::cout << "\t- caesar\n";
	std::cout << "\t- caesar-modified\n";
	std::cout << "\t- rsa\n";
	std::cout << "\t- hill\n";

	std::cout << '\n';

	std::cout << CColors::RED + 
				 "###################\n";
	std::cout << "#  Usage Examples #\n";
	std::cout << "###################\n\n" + CColors::WHITE;

	std::cout << "$ ./encryption-machine\n";
	std::cout << "$ ./encryption-machine -c caesar -m \"Message which will be encrypted\" -o encryptedMessage.txt\n";
	std::cout << "$ ./encryption-machine -i ~/Desktop/fileToDecrypt.txt -d -o decryptedMessage.txt\n";
}

