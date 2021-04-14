#pragma once

#include "../../stdafx.h"

std::string ctc(const bool& bDecrypt, const std::string& message, const std::string& keyword);

std::map<int, int> getPermutationOrder(const std::string& keyword);

std::string encrypt_ctc(const std::string& message, const std::string& keyword, const std::map<int, int>& keyMap);

std::string decrypt_ctc(const std::string& message, const std::string& keyword, std::map<int, int> keyMap);

bool isTheSymbolPunctuation(const char& c);
