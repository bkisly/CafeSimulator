//
// Created by bkisl on 28.04.2022.
//

#ifndef CAFEMENU_EXCEPTIONS_H
#define CAFEMENU_EXCEPTIONS_H

#include <iostream>

using namespace std;

class ArgumentEmptyException : public invalid_argument {
public:
    ArgumentEmptyException(const string &message);
};

class InvalidPriceException : public invalid_argument {
public:
    InvalidPriceException(const string &message);
};

class ItemExistenceException : public invalid_argument {
public:
    ItemExistenceException(const string &message);
};

class IndexOutOfRangeException : public invalid_argument {
public:
    IndexOutOfRangeException(const string &message);
};

class FileException : public invalid_argument {
public:
    FileException(const string &message);
};

class NetworkException : public invalid_argument {
public:
    NetworkException(const string &message);
};


#endif //CAFEMENU_EXCEPTIONS_H
