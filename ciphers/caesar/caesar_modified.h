#pragma once

#include "../../stdafx.h"

std::string caesar_modified(bool bDecrypt, std::string message, std::string keyword);

std::pair<int, int> is_in_alphabet(const char& letter);

char checkPunctuation(const char& letter);

