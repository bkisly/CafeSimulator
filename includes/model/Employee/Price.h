#ifndef PRICE_H
#define PRICE_H

#include <string>
#include <iostream>

class Price {
public:
    Price();
    Price(unsigned int zl, unsigned int gr);

    Price &operator+=(const Price &second_argument);

    Price operator+(const Price &second_argument) const;

//    friend std::ostream &operator<<(std::ostream &os, const Price &price);
//
//    friend std::istream &operator>>(std::istream &in, Price &price);

    Price &operator-=(const Price &second_argument);

    Price operator-(const Price &second_argument) const;

    Price &operator*=(float multiplier);

    Price operator*(float multiplier) const;

    bool operator==(const Price &rhs) const;

    bool operator!=(const Price &rhs) const;

    std::string price_str() const;

private:
    unsigned int value;
};

//std::ostream &operator<<(std::ostream &os, const Price &price);
//std::istream &operator>>(std::istream &in, Price &price);


#endif //PRICE_H
