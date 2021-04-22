#pragma once

#include "../../stdafx.h"

std::string hill(const bool& bDecrypt, const std::string& message, const std::string& keyword);
std::pair<int, int> is_in_alphabet(const char& letter);
int checkPunctuationInt(const char& letter);
int findDet(int** a, int n);
void clearMemory(int** a, int n);
void extended_euclid(int a, int b, int* x);