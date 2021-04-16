#pragma once

#include "../../stdafx.h"

std::string caesar_modified(const bool& bDecrypt, const std::string& message, const std::string& keyword);

std::pair<int, int> is_in_alphabet(const char& letter);

char checkPunctuation(const char& letter);

// we pass 3 parameters to the function, so that we can use the pointer to the function in the main.cpp file in the main() function
std::string bruteforceCaesarModified(const bool& bDecrypt, const std::string& message, const std::string& keyword);

const std::vector<std::string> namesOfTheCiphersWhichAreAllowed = {"caesar", "ctc", "caesar-modified", "hill"};

const std::vector<char> englishAlphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const std::vector<char> englishAlphabetUpperLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 

const std::vector<char> punctuation = {' ', '`', '\'', '\"', '~', ',', '.', '/', '\\', '-', '=', '+', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '?',
                                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// we create a vector which contains all alphabets what we have, because in this way we can iterate by alphabets
const std::vector<std::vector<char>> AllAlphabets = {englishAlphabet, englishAlphabetUpperLetters};