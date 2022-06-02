//
// Created by bkisl on 27.04.2022.
//

#include "../../../includes/model/MenuItem/beverage.h"

using namespace std;

Beverage::Beverage(std::string name, Price pricePerPortion, CupType cupType, unsigned int cyclesToPrepare) : MenuItem(name, PortionUnit::Liter, pricePerPortion, cyclesToPrepare) {
    this->cupType = cupType;
}

CupType Beverage::GetCupType() const {
    return cupType;
}

ostream &Beverage::Write(ostream &os) {
    os << name << endl;
    os << pricePerPortion << " " << cyclesToPrepare << " " << (int)cupType;
    return os;
}

istream &Beverage::Read(istream &is) {
    int cupTypeInt = 0;

    if(is.peek() == '\n')
       is.ignore();

    getline(is, name);
    is >> pricePerPortion >> cyclesToPrepare >> cupTypeInt;
    cupType = (CupType)cupTypeInt;
    return is;
}

string Beverage::ToString() {
    return MenuItem::ToString() + ", cup type: " + cupTypesToStrings[cupType];
}