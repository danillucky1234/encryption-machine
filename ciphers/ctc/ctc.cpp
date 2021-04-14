#include "ctc.h"

std::string ctc(const bool& bDecrypt, const std::string& message, const std::string& keyword)
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

    std::string returnedString;

    std::map<int, int> keyMap = getPermutationOrder(keyword);

    if(bDecrypt)
    {
        // decrypt
        returnedString = decrypt_ctc(message, keyword, keyMap);
    }
    else
    {
        // encrypt
        returnedString = encrypt_ctc(message, keyword, keyMap);
    }

    return returnedString;
}

std::string encrypt_ctc(const std::string& message, const std::string& keyword, const std::map<int, int>& keyMap)
{
    std::string encryptedString;

    // get number of columns in matrix
    int col = keyword.length();

    // calculate the maximum row of the matrix 
    int row = message.length() / col;

    if(message.length() % col)
    {
        ++row;
    }

    char matrix[row][col];

    for (int i = 0, k = 0; i < row; ++i)
    {
        for (int j =0; j < col; /* */)
        {
            if (message[k] == '\0')
            {
                // adding the '_' symbol
                matrix[i][j] = '_';
                ++j;
            }

            if(isalpha(message[k]) || message[k] == ' ' || isTheSymbolPunctuation(message[k]))
            {
                // we add to our matrix only spaces and characters from the alphabet (letters)
                matrix[i][j] = message[k];
                ++j;
            }

            ++k;
        }
    }

    int j;
    for (const auto& it : keyMap)
    {
        j = it.second;

        // getting the encrypted text from the matrix column using permutated key
        for (int i = 0; i < row; ++i)
        {
            if (isalpha(matrix[i][j]) || matrix[i][j] == ' ' || matrix[i][j] == '_' || isTheSymbolPunctuation(matrix[i][j]))
            {
                encryptedString += matrix[i][j];
            }
        }
    }


    return encryptedString;
}

std::map<int, int> getPermutationOrder(const std::string& keyword)
{
    std::map<int, int> keyMap;

    // add an order of permutations to the map
    for (int i = 0; i < static_cast<int>(keyword.length()); ++i)
    {
        keyMap[keyword[i]] = i;
    }

    return keyMap;
}

bool isTheSymbolPunctuation(const char& c)
{
    for (const auto& it : punctuation)
    {
        if (it == c)
        {
            return true;
        }
    }
    return false;
}

std::string decrypt_ctc(const std::string& message, const std::string& keyword, std::map<int, int> keyMap)
{
    // calculate row and column for the cipher matrix
    int col = keyword.length();

    int row = message.length() / col;

    char cipherMat [row][col];

    // add the characther to the column to the matrix
    for (int j = 0, k = 0; j < col; ++j)
    {
        for (int i = 0; i < row; ++i)
        {
            cipherMat[i][j] = message[k++];
        }
    }

    // update order of keys for decryption
    int index = 0;
    for (auto it = keyMap.begin(); it != keyMap.end(); ++it)
    {
        it->second = index++;
    }
    
    // arrange the column of the matrix according to the order of permutations by adding to the new matrix
    char decCipher[row][col];

    // std::map<int, int>::iterator ii = keyMap.begin();
    int k = 0;
    for (int l = 0, j; keyword[l] != '\0'; ++k)
    {
        j = keyMap[keyword[l++]];
        for (int i = 0; i < row; ++i)
        {
            decCipher[i][k] = cipherMat[i][j];
        }
    }

    // get message using matrix
    std::string decryptedString;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (decCipher[i][j] != '_')
            {
                decryptedString += decCipher[i][j];
            }
        }
    }

    return decryptedString;
}