#include "morse.h"

std::string morse(const bool& bDecrypt, const std::string& message, const std::string& keyword)
{
    std::string returnedString;
    if (bDecrypt)
    {
        // decrypt
        returnedString = decrypt_morse(message);
    }
    else
    {
        // encrypt
        returnedString = encrypt_morse(message);
    }

    return returnedString;
}

std::string encrypt_morse (const std::string& message)
{
    std::string encryptedMessage;
    for (int i = 0; i < static_cast<int>(message.length()); ++i)
    {
        encryptedMessage += morseCode.find(message[i])->second;
        encryptedMessage += ' ';
    }
    return encryptedMessage;
}

std::string decrypt_morse (const std::string& message)
{
    std::string decryptedMessage;
    std::string letter;
    int j;

    for (int i = 0; i < static_cast<int>(message.length()); ++i)
    {
        letter = "";
        j = 0;

        while (message[i + j] != ' ')
        {
            letter += message[i + j];
            ++j;
        }
        if (j != 0)
        {
            i = i + j;

            decryptedMessage += decodedMorseCode.find(letter)->second;
        }
        else
        {
            if (message[i + 1] == ' ' && message[i + 2] == ' ')
            {
                decryptedMessage += ' ';
            }
            i += 2;
        }
    }
    return decryptedMessage;
}