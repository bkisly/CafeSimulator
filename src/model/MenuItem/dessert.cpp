//
// Created by bkisl on 27.04.2022.
//

#include "../../../includes/model/MenuItem/dessert.h"

Dessert::Dessert(string name, Price pricePerPortion, unsigned int cyclesToPrepare) : MenuItem(name, PortionUnit::Piece, pricePerPortion, cyclesToPrepare) {}

ostream &Dessert::Write(ostream &os) {
    os << name << endl;
    os << pricePerPortion << " " << cyclesToPrepare;
    return os;
}

istream &Dessert::Read(istream &is) {
    if(is.peek() == '\n')
        is.ignore();

    getline(is, name);
    is >> pricePerPortion >> cyclesToPrepare;
    return is;
}