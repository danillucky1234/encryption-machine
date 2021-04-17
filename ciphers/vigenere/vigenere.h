#pragma once

#include "../../stdafx.h"

std::string vigenere(const bool& bDecrypt, const std::string& message, const std::string& keyword);

std::string decrypt_vigenere(const std::string& message, const std::string& keyword);

std::string encrypt_vigenere(const std::string& message, const std::string& keyword);

int getTheCharacterNumber(const char& symbol);

const std::vector<char> allSymbols = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                            ' ', '`', '\'', '\"', '~', ',', '.', '/', '\\', '-', '=', '+', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '?',
                                                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};