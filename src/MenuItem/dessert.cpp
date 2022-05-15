//
// Created by bkisl on 27.04.2022.
//

#include "../../includes/model/MenuItem/dessert.h"

Dessert::Dessert(string name, Price pricePerPortion, unsigned int cyclesToPrepare) : MenuItem(name, PortionUnit::Piece, pricePerPortion, cyclesToPrepare) {}

ostream &Dessert::Write(ostream &os) {
    // TODO: implement writing to stream
    return os;
}

istream &Dessert::Read(istream &is) {
    // TODO: implement reading from stream
    return is;
}