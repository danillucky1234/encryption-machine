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

    std::vector<std::pair<int, int>> keyMap = getPermutationOrder(keyword);

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

std::string encrypt_ctc(const std::string& message, const std::string& keyword, const std::vector<std::pair<int, int>>& keyMap)
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
        for (int j = 0; j < col; ++j)
        {
            matrix[i][j] = message[k];
            
            if (message[k] == '\0') 
            {
                for (int k = i; k < row; ++k)
                {
                    for (int l = j; l < col; ++l)
                    {
                        matrix[k][l] = '_';
                    }
                }
                break;                
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
            encryptedString += matrix[i][j];
        }
    }
    return encryptedString;
}

std::vector<std::pair<int, int>> getPermutationOrder(const std::string& keyword)
{
    std::vector<std::pair<int, int>> keyMap;

    for (int i = 0; i < static_cast<int>(keyword.length()); ++i)
    {
        keyMap.push_back(std::make_pair(keyword[i], i));    
    }

    // sort our vector
    std::sort(keyMap.begin(), keyMap.end());

    return keyMap;
}

std::string decrypt_ctc(const std::string& message, const std::string& keyword, const std::vector<std::pair<int, int>>& keyMap)
{
    // calculate row and column for the cipher matrix
    int row = keyword.length();

    int col = message.length() / row;

    char cipherMat [row][col];

    // add the character to the column to the matrix
    for (int i = 0, k = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            cipherMat[i][j] = message[k++];
        }
    }

    std::string decryptedString;

    char decryptedMatrix[row][col];

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            decryptedMatrix[keyMap[i].second][j] = cipherMat[i][j];
        }
    }

    for (int j = 0; j < col; ++j)
    {
        for (int i = 0; i < row; ++i)
        {
            if (decryptedMatrix[i][j] != '_')
            {
                decryptedString += decryptedMatrix[i][j];
            }
        }
    }

    return decryptedString;
}