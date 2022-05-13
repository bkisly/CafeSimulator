//
// Created by bkisl on 27.04.2022.
//

#ifndef CAFEMENU_PRICE_H
#define CAFEMENU_PRICE_H

#include <string>

using namespace std;

class Price {
private:
    unsigned int dollars;
    unsigned int cents;

    unsigned int getTotalCents() const;
    void setDollarsAndCents(unsigned int dollars, unsigned int cents);

public:
    Price(unsigned int dollars, unsigned int cents);

    unsigned int GetDollars() const;
    unsigned int GetCents() const;
    string ToString() const;

    bool operator==(const Price &rhs) const;
    bool operator!=(const Price &rhs) const;
    bool operator<(const Price &rhs) const;
    bool operator>(const Price &rhs) const;
    bool operator<=(const Price &rhs) const;
    bool operator>=(const Price &rhs) const;

    Price &operator+=(const Price &rhs);
    Price &operator-=(const Price &rhs);
    Price &operator*=(unsigned int factor);
    Price &operator/=(unsigned int factor);

    Price operator+(const Price &rhs) const;
    Price operator-(const Price &rhs) const;
    Price operator*(unsigned int factor) const;
    Price operator/(unsigned int factor) const;

    friend std::ostream &operator<<(std::ostream &os, const Price &price);
    friend std::istream &operator>>(std::istream &in, Price &price);
};

std::ostream &operator<<(std::ostream &os, const Price &price);
std::istream &operator>>(std::istream &in, Price &price);

#endif //CAFEMENU_PRICE_H
