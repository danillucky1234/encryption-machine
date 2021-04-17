#include "vigenere.h"

std::string vigenere(const bool& bDecrypt, const std::string& message, const std::string& keyword)
{
    int cheker;
    // check converting string to int
    try
    {
        // if successful convert - keyword is a number, so we should throw an error
        cheker = std::stoi(keyword);
        throw static_cast<std::string>("This cipher requires an string keyword!\n");
    }
    catch(const std::invalid_argument& ia)
    {
        // in case of an error we are sure that our keyword is string, so we can continue
    }

    std::string keyStream;
    if (keyword.length() != message.length())
    {
        if (keyword.length() < message.length())
        {
            keyStream = keyword;
            for(int i = keyword.length(); i < static_cast<int>(message.length()); ++i)
            {
                keyStream += keyword[i % keyword.length()];
            }
        }
        // if the message is shorter than the key, then the Vigenere cipher is essentially the one-time pad, which is unbreakable for a random key
        else
        {
            keyStream = keyword;
        }
    }
    else
    {
        keyStream = keyword;
    }

    std::string returnedString;
    if (bDecrypt)
    {
        // decrypt
        returnedString = decrypt_vigenere(message, keyStream);
    }
    else
    {
        // encrypt
        returnedString = encrypt_vigenere(message, keyStream);
    }

    return returnedString;
}

std::string encrypt_vigenere(const std::string& message, const std::string& keyword)
{
    std::string encryptedString;
    int sumOfTheMessageLetterAndTheKeywordLetter = 0;
    int numberOfMessageLetter = 0;
    int numberOfKeywordLetter = 0;

    for (int i = 0; i < static_cast<int>(message.length()); ++i)
    {
        numberOfMessageLetter = getTheCharacterNumber(message[i]);

        numberOfKeywordLetter = getTheCharacterNumber(keyword[i]);
        
        sumOfTheMessageLetterAndTheKeywordLetter = numberOfMessageLetter + numberOfKeywordLetter;
        
        sumOfTheMessageLetterAndTheKeywordLetter %= allSymbols.size();
        
        encryptedString += allSymbols[sumOfTheMessageLetterAndTheKeywordLetter];
        
    }

    return encryptedString;
}

int getTheCharacterNumber(const char& symbol)
{
    for (int i = 0; i < static_cast<int>(allSymbols.size()); ++i)
    {
        if (allSymbols[i] == symbol)
        {
            return i;
        }
    }

    return -1;
}

std::string decrypt_vigenere(const std::string& message, const std::string& keyword)
{
    std::string decryptedString;
    int sumOfTheMessageLetterAndTheKeywordLetter = 0;
    int numberOfMessageLetter = 0;
    int numberOfKeywordLetter = 0;

    for (int i = 0; i < static_cast<int>(message.length()); ++i)
    {
        numberOfMessageLetter = getTheCharacterNumber(message[i]);

        numberOfKeywordLetter = getTheCharacterNumber(keyword[i]);
        
        sumOfTheMessageLetterAndTheKeywordLetter = numberOfMessageLetter - numberOfKeywordLetter;
        
        if (sumOfTheMessageLetterAndTheKeywordLetter < 0)
        {
            sumOfTheMessageLetterAndTheKeywordLetter += allSymbols.size();
        }

        sumOfTheMessageLetterAndTheKeywordLetter %= allSymbols.size();
        
        decryptedString += allSymbols[sumOfTheMessageLetterAndTheKeywordLetter];
    }

    return decryptedString;
}