//
// Created by bkisl on 28.04.2022.
//

#include "../../../includes/model/helpers/exceptions.h"

using namespace std;

ArgumentEmptyException::ArgumentEmptyException(const string &message) : invalid_argument(message) {}
InvalidPriceException::InvalidPriceException(const string &message) : invalid_argument(message) {}
ItemExistenceException::ItemExistenceException(const string &message) : invalid_argument(message) {}
IndexOutOfRangeException::IndexOutOfRangeException(const string &message) : invalid_argument(message) {}
FileException::FileException(const string &message) : invalid_argument(message) {}