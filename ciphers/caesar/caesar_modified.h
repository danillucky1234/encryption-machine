#pragma once

#include "../../stdafx.h"

std::string caesar_modified(const bool& bDecrypt, const std::string& message, const std::string& keyword);

std::pair<int, int> is_in_alphabet(const char& letter);

char checkPunctuation(const char& letter);

// we pass 3 parameters to the function, so that we can use the pointer to the function in the main.cpp file in the main() function
std::string bruteforceCaesarModified(const bool& bDecrypt, const std::string& message, const std::string& keyword);