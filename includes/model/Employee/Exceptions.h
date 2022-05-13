#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

//
//struct ExistingElement : public std::exception {
//    const char *what() const throw() {
//        return "element already exists";
//    }
//};
//
//struct NonExistingElement : public std::exception {
//    const char *what() const throw() {
//        return "element already exists";
//    }
//};
//
//struct RangeError : public std::exception {
//    const char *what() const throw() {
//        return "range error";
//    }
//};
//
//
//struct TimeError : public std::exception {
//    const char *what() const throw() {
//        return "time error";
//    }
//};
//
//struct FileError : public std::exception {
//    const char *what() const throw() {
//        return "file error";
//    }
//};
//
//class NegativePriceException : public std::invalid_argument {
//public:
//    NegativePriceException(int wrong_price) : std::invalid_argument(
//            "Gr should be smaller than 100, but is: " + std::to_string(wrong_price)) {};
//
//};

class RangeGrException : public std::invalid_argument {
public:
    RangeGrException(int wrong_price) : std::invalid_argument(
            "Gr should be less than 100: " + std::to_string(wrong_price)) {};

};

class GenderException : public std::invalid_argument {
public:
    GenderException(int wrong_gender) : std::invalid_argument(
            "Gender representation should be 0 or 1, but is: " + std::to_string(wrong_gender)) {};

};

class IdException : public std::invalid_argument {
public:
    IdException(int wrong_price) : std::invalid_argument(
            "Non existing Id - : " +
            std::to_string
                    (wrong_price)) {};
};

class StateException : public std::invalid_argument {
public:
    StateException(int wrong_state) : std::invalid_argument(
            "currentState index out of range - use enum of states: " +
            std::to_string(wrong_state)) {};
};

#endif //EXCEPTIONS_H
