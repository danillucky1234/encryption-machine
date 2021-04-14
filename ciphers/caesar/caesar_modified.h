#pragma once

#include "../../stdafx.h"

std::string caesar_modified(const bool& bDecrypt, const std::string& message, const std::string& keyword);

std::pair<int, int> is_in_alphabet(const char& letter);

char checkPunctuation(const char& letter);

