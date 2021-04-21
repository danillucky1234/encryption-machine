#pragma once

#include "../../stdafx.h"

std::string hill(bool bDecrypt, std::string message, std::string keyword);
std::pair<int, int> is_in_alphabet(const char& letter);
int checkPunctuation(const char& letter);
int findDet(int** a, int n);
void clearMemory(int** a, int n);
void extended_euclid(int a, int b, int* x);