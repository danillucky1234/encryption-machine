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
    std::string newMessage = message;
    newMessage += ' '; // we add a space at the end of the message so that we can finish our iteration on the message 
    for (int i = 0; i < static_cast<int>(newMessage.length()); ++i)
    {
        letter = "";
        j = 0;

        while (newMessage[i + j] != ' ')
        {
            letter += newMessage[i + j];
            ++j;
        }
        if (j != 0)
        {
            i = i + j;

            decryptedMessage += decodedMorseCode.find(letter)->second;
        }
        else
        {
            if (newMessage[i + 1] == ' ' && newMessage[i + 2] == ' ')
            {
                decryptedMessage += ' ';
            }
            i += 2;
        }
    }
    return decryptedMessage;
}