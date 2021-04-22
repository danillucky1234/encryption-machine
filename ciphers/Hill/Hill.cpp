#include "Hill.h"

std::string hill(const bool& bDecrypt, const std::string& message, const std::string& keyword)
{
    std::string messageReturn = "";
    int x = sqrt(keyword.length());
    int col;
    std::vector<int> stringMessage, stringKey;
    std::pair<int, int> p;
    for (const auto& it : message)
    {
        p = is_in_alphabet(it);
        if (p.first != -1)
        {
            // if returned value isn't -1, then we found alphabet and number of letter in this alphabet
            // which means we only need to shift characters to the right
            if (p.first == 0)
            {

                stringMessage.push_back(p.second);
            }
            else
            {
                stringMessage.push_back(p.second + 26);
            }
        }
        else
        {
            int punkt = checkPunctuationInt(it);
            if (punkt != -1)
            {
                stringMessage.push_back(52 + punkt);
            }
            else
            {
                stringMessage.push_back(52);
            }
        }
    }
    for (const auto& it : keyword)
    {
        p = is_in_alphabet(it);
        if (p.first != -1)
        {
            if (p.first == 0)
            {

                stringKey.push_back(p.second);
            }
            else
            {
                stringKey.push_back(p.second + 26);
            }
        }
        else
        {
            int punkt = checkPunctuationInt(it);
            if (punkt != -1)
            {
                stringKey.push_back(52 + punkt);
            }
            else
            {
                stringKey.push_back(52);
            }
        }
    }
    int count = 0;
    col = stringMessage.size() / x;
    int** arrayKey = new int* [x];
    // encrypt
    if (bDecrypt == 0) {
        if ((stringMessage.size() - (col * x)) != 0)
        {
            col += 1;
            int o = (x * (col)-stringMessage.size());
            for (int i = 0; i < o; ++i) {
                stringMessage.push_back(52);
            }
        }



        int** arrayMessage = new int* [col];
        for (int i = 0; i < col; ++i)
        {
            arrayMessage[i] = new int[x];
            for (int j = 0; j < x; ++j)
            {
                arrayMessage[i][j] = stringMessage[count];
                count++;
            }
        }
        count = 0;
        for (int i = 0; i < x; ++i)
        {
            arrayKey[i] = new int[x];

            for (int j = 0; j < x; ++j)
            {
                arrayKey[i][j] = stringKey[count];
                count++;
            }
        }
        int** multi = new int* [col];

        for (int i = 0; i < col; i++)
        {
            multi[i] = new int[x];
            for (int j = 0; j < x; j++)
            {
                multi[i][j] = 0;
                for (int k = 0; k < x; k++)
                    multi[i][j] += arrayMessage[i][k] * arrayKey[k][j];
            }
        }

        for (int i = 0; i < col; ++i)
        {
            for (int j = 0; j < x; ++j)
            {
                multi[i][j] %= 67;
                messageReturn += std::to_string(multi[i][j]);
                messageReturn += " ";
            }
        }
        messageReturn = "";
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < x; j++)
            {
                if (multi[i][j] < 26) {
                    messageReturn += (AllAlphabets[0][multi[i][j]]);
                }
                else if (multi[i][j] < 52) {
                    messageReturn += (AllAlphabets[1][(multi[i][j] - 26)]);
                }
                else {
                    messageReturn += (punctuation[(multi[i][j] - 52)]);
                }
            }
        }

        clearMemory(multi, col);
        clearMemory(arrayMessage, col);

    }

    //decrypt
    else
    {
        int** arrayMessage = new int* [col];
        count = 0;
        int** multi = new int* [col];
        int** newarrayKey = new int* [x];
        for (int i = 0; i < x; ++i)
        {
            arrayKey[i] = new int[x];
            newarrayKey[i] = new int[x];
            for (int j = 0; j < x; ++j)
            {
                arrayKey[i][j] = stringKey[count];
                count++;
            }
        }
        int deter = findDet(arrayKey, x);
        int x1;
        extended_euclid(abs(deter), 67, &x1);
        int ober_elem;
        if (deter < 0 && x1 > 0) {
            ober_elem = x1;
        }
        else if (deter > 0 && x1 < 0) {
            ober_elem = (x1 + 67);
        }
        else if (deter > 0 && x1 > 0) {
            ober_elem = x1;
        }
        else {
            ober_elem = (0 - x1);
        }
        int k, k1;
        int** temp = new int* [x - 1];
        for (int i = 0; i < x - 1; i++)
            temp[i] = new int[x - 1];
        setlocale(LC_ALL, "Russian");
        for (int index1 = 0; index1 < x; index1++)
            for (int index2 = 0; index2 < x; index2++)
            {
                k = index1; k1 = index2;

                int s = 0, s1 = 0;
                for (int i = 0; i < x; ++i)
                    if (i != k)
                    {
                        s1 = 0;
                        for (int j = 0; j < x; ++j)
                            if (j != k1)
                            {
                                temp[s][s1] = arrayKey[i][j];
                                s1++;
                            }

                        s++;
                    }
                int res = 0;
                res = pow(-1., k + 1 + k1 + 1) * findDet(temp, x - 1);
                newarrayKey[index1][index2] = (res);
            }
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < x; j++) {
                newarrayKey[i][j] %= 67;
                newarrayKey[i][j] *= ober_elem;
                newarrayKey[i][j] %= 67;
            }
        }
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < x; j++) {
                arrayKey[i][j] = newarrayKey[j][i];
            }
        }
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < x; j++) {
                if (arrayKey[i][j] < 0) {
                    arrayKey[i][j] = (67 + arrayKey[i][j]);
                }
            }
        }
        count = 0;
        for (int i = 0; i < col; ++i)
        {
            arrayMessage[i] = new int[x];
            for (int j = 0; j < x; ++j)
            {
                arrayMessage[i][j] = stringMessage[count];
                count++;
            }
        }
        int** newarray = new int* [col];
        for (int i = 0; i < col; i++)
        {
            newarray[i] = new int[x];
            for (int j = 0; j < x; j++)
            {
                newarray[i][j] = 0;
                for (int k = 0; k < x; k++)
                {
                    newarray[i][j] += arrayMessage[i][k] * arrayKey[k][j];
                }
                newarray[i][j] %= 67;
            }
        }
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < x; j++)
            {
                if (newarray[i][j] < 26) {
                    messageReturn += (AllAlphabets[0][newarray[i][j]]);
                }
                else if (newarray[i][j] < 52) {
                    messageReturn += (AllAlphabets[1][(newarray[i][j] - 26)]);
                }
                else {
                    messageReturn += (punctuation[(newarray[i][j] - 52)]);
                }
            }
        }
        clearMemory(newarray, col);
        clearMemory(newarrayKey, x);
        clearMemory(temp, x - 1);
        clearMemory(arrayMessage, col);
    }
    clearMemory(arrayKey, x);
    return messageReturn;
}

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

int checkPunctuationInt(const char& letter)
{
    for (int j = 0; j < static_cast<int>(punctuation.size()); ++j)
    {
        if (punctuation[j] == letter)
        {
            return j;
        }
    }
    return -1;
}

void clearMemory(int** a, int n) {
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}

void extended_euclid(int a, int b, int* x)
{
    int q, r, x1, x2;
    if (b == 0) {
        * x = 1;
        return;
    }
    x2 = 1, x1 = 0;
    while (b > 0) {
        q = a / b, r = a - q * b;
        *x = x2 - q * x1;
        a = b, b = r;
        x2 = x1, x1 = *x;
    }
    * x = x2;
}
int findDet(int** a, int n) {
    if (n == 1)
        return a[0][0];
    else if (n == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    else {
        int d = 0;
        for (int k = 0; k < n; k++) {
            int** m = new int* [n - 1];
            for (int i = 0; i < n - 1; i++) {
                m[i] = new int[n - 1];
            }
            for (int i = 1; i < n; i++) {
                int t = 0;
                for (int j = 0; j < n; j++) {
                    if (j == k)
                        continue;
                    m[i - 1][t] = a[i][j];
                    t++;
                }
            }
            d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
            clearMemory(m, n - 1);
        }
        return d;
    }
}