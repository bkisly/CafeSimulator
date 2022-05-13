#include "../../includes/model/Employee/Price.h"
#include "../../includes/model/Employee/Exceptions.h"

#include <string>

Price::Price(unsigned int zl, unsigned int gr){
    if (gr >= 100){
        throw RangeGrException(gr);
    }
    value = zl * 100 + gr;
}

Price& Price::operator+=(const Price& second_argument) {
    value += second_argument.value;
    return *this;
}

Price Price::operator+(const Price &second_argument) const{
    Price sum = *this;
    sum += second_argument;
    return sum;
}

Price& Price::operator-=(const Price& second_argument) {
    value -= second_argument.value;
    return *this;
}

Price Price::operator-(const Price &second_argument) const{
    Price sum = *this;
    sum -= second_argument;
    return sum;
}


Price& Price::operator*=(float multiplier){
    value = int(multiplier * value);
    return *this;
}

Price Price::operator*(float multiplier) const {
    Price product = *this;
    product *= multiplier;
    return product;
}


bool Price::operator==(const Price &rhs) const {
    return value == rhs.value;
}

bool Price::operator!=(const Price &rhs) const {
    return !(rhs == *this);
}

std::string Price::price_str() const {
    return std::to_string(value / 100) + "." + std::to_string(value % 100) ;
}

//std::ostream &operator<<(std::ostream &os, const Price &price) {
//    os << price.value / 100 << " " << price.value % 100;
//    return os;
//}
//
//std::istream &operator>>(std::istream &in, Price &price) {
//    unsigned zl, gr;
//    in >> zl >> gr;
//    price = Price(zl, gr);
//    return in;
//}

Price::Price() {

}





