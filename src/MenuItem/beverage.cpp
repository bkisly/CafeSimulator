//
// Created by bkisl on 27.04.2022.
//

#include "../../includes/model/MenuItem/beverage.h"

using namespace std;

Beverage::Beverage(std::string name, Price pricePerPortion, CupType cupType, unsigned int cyclesToPrepare) : MenuItem(name, PortionUnit::Liter, pricePerPortion, cyclesToPrepare) {
    this->cupType = cupType;
}

CupType Beverage::GetCupType() const {
    return cupType;
}

ostream &Beverage::Write(ostream &os) {
    // TODO: implement writing to stream
    return os;
}

istream &Beverage::Read(istream &is) {
    // TODO: implement reading from stream
    return is;
}

string Beverage::ToString() {
    return MenuItem::ToString() + ", cup type: " + cupTypesToStrings[cupType];
}