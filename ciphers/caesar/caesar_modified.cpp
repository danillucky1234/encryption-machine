#include "caesar_modified.h"

std::string caesar_modified(const bool& bDecrypt, const std::string& message, const std::string& keyword)
{
    int shift;
    // trying to convert string to int
    try
    {
        // if success, we get the keyword
        shift = std::stoi(keyword);
    }
    catch(const std::invalid_argument& ia)
    {
        // in case of an error we get the keyword by measuring the length of the argument string
        shift = keyword.length();
    }
    std::string returnedString;

    std::pair<int, int> p;

    // decrypt the message
    if (bDecrypt)
    {
        for (const auto& it : message)
        {
            p = is_in_alphabet(it);
            if (p.first != -1)
            {
                // if returned value isn't -1, then we found alphabet and number of letter in this alphabet
                // which means we only need to shift characters to the right
                if (p.second + shift >= static_cast<int>(AllAlphabets[p.first].size()))
                {
                    returnedString.push_back(AllAlphabets[p.first][(p.second + shift + AllAlphabets[p.first].size()) % AllAlphabets[p.first].size()]);
                }
                else
                {
                    returnedString.push_back(AllAlphabets[p.first][p.second + shift]);
                }
            }
            else
            {
                char letter = checkPunctuation(it);
                if (letter != -1)
                {
                    returnedString.push_back(letter);
                }
                else
                {
                    returnedString.push_back(' ');
                }
            }
        }
    }
    else    // encrypt
    {
        for (const auto& it : message)
        {
            p = is_in_alphabet(it);
            if (p.first != -1)
            {
                if (p.second + shift >= static_cast<int>(AllAlphabets[p.first].size()))
                {
                    returnedString.push_back(AllAlphabets[p.first][(p.second - shift + AllAlphabets[p.first].size()) % AllAlphabets[p.first].size()]);
                }
                else
                {
                    if (p.second - shift < 0)
                    {
                        returnedString.push_back(AllAlphabets[p.first][p.second - shift + AllAlphabets[p.first].size()]);
                    }
                    else
                    {
                        returnedString.push_back(AllAlphabets[p.first][p.second - shift]);
                    }
                    
                }
            }
            else
            {
                char letter = checkPunctuation(it);
                if (letter != -1)
                {
                    returnedString.push_back(letter);
                }
                else
                {
                    returnedString.push_back(' ');
                }
            }
        }
    }
    
    return returnedString;
}

// returned value:
//  int1:   number of alphabet from the vector AllAlphabets (English - 0, EnglishUpperLettes - 1)
//  int2:   number of letter in alphabet (a - 0, b - 1, ..., z - 25) 
std::pair<int, int> is_in_alphabet(const char& letter)
{
    for (int i = 0; i < static_cast<int>(AllAlphabets.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(AllAlphabets[i].size()); ++j)
        {
            if (AllAlphabets[i][j] == letter)
            {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

char checkPunctuation(const char& letter)
{
    for (const auto& it : punctuation)
    {
        if (it == letter)
        {
            return letter;
        }
    }
    return -1;
}