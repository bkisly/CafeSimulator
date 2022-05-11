//
// Created by bkisl on 27.04.2022.
//

#include <iostream>
#include "../includes/price.h"

using namespace std;

// Private members

unsigned int Price::getTotalCents() const {
    return 100 * dollars + cents;
}

void Price::setDollarsAndCents(unsigned int dollars, unsigned int cents) {
    this->dollars = dollars + cents / 100;
    this->cents = cents % 100;
}

// Public members

Price::Price(unsigned int dollars, unsigned int cents) {
    setDollarsAndCents(dollars, cents);
}

unsigned int Price::GetDollars() const {
    return dollars;
}

unsigned int Price::GetCents() const {
    return cents;
}

string Price::ToString() const {
    string centsString = cents < 10 ? "0" +  to_string(cents) : to_string(cents);
    return "$" + to_string(dollars) + "." + centsString;
}

// Boolean operators

bool Price::operator==(const Price &rhs) const {
    return dollars == rhs.dollars && cents == rhs.cents;
}

bool Price::operator!=(const Price &rhs) const {
    return !(rhs == *this);
}

bool Price::operator<(const Price &rhs) const {
    if(getTotalCents() < rhs.getTotalCents()) return true;
    return false;
}

bool Price::operator>(const Price &rhs) const {
    return rhs < *this;
}

bool Price::operator<=(const Price &rhs) const {
    return !(rhs < *this);
}

bool Price::operator>=(const Price &rhs) const {
    return !(*this < rhs);
}

// Arithmetical operators

Price &Price::operator+=(const Price &rhs) {
    unsigned int newTotalCents = getTotalCents() + rhs.getTotalCents();
    setDollarsAndCents(newTotalCents / 100, newTotalCents % 100);
    return *this;
}

Price &Price::operator-=(const Price &rhs) {
    int newTotalCents = getTotalCents() - rhs.getTotalCents();
    if(newTotalCents < 0) throw invalid_argument("Result price after subtraction cannot be negative.");

    setDollarsAndCents(newTotalCents / 100, newTotalCents % 100);
    return *this;
}

Price &Price::operator*=(unsigned int factor) {
    unsigned int newTotalCents = getTotalCents() * factor;
    setDollarsAndCents(newTotalCents / 100, newTotalCents % 100);
    return *this;
}

Price &Price::operator/=(unsigned int factor) {
    if(factor == 0) throw invalid_argument("Price cannot be divided by 0.");

    unsigned int newTotalCents = getTotalCents() / factor;
    setDollarsAndCents(newTotalCents / 100, newTotalCents % 100);
    return *this;
}

Price Price::operator+(const Price &rhs) const {
    Price newPrice = *this;
    newPrice += rhs;
    return newPrice;
}

Price Price::operator-(const Price &rhs) const {
    Price newPrice = *this;
    newPrice -= rhs;
    return newPrice;
}

Price Price::operator*(unsigned int factor) const {
    Price newPrice = *this;
    newPrice *= factor;
    return newPrice;
}

Price Price::operator/(unsigned int factor) const {
    Price newPrice = *this;
    newPrice /= factor;
    return newPrice;
}
