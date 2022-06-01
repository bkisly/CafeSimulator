//
// Created by bkisl on 27.04.2022.
//

#include "../../includes/model/MenuItem/dish.h"

Dish::Dish(string name, Price pricePerPortion, bool vegetarian, unsigned int cyclesToPrepare) : MenuItem(name, PortionUnit::Portion, pricePerPortion, cyclesToPrepare) {
    this->vegetarian = vegetarian;
}

bool Dish::IsVegetarian() const {
    return vegetarian;
}

ostream &Dish::Write(ostream &os) {
    os << name << endl;
    os << pricePerPortion << " " << cyclesToPrepare << " " << vegetarian;
    return os;
}

istream &Dish::Read(istream &is) {
    if(is.peek() == '\n')
        is.ignore();

    getline(is, name);
    is >> pricePerPortion >> cyclesToPrepare >> vegetarian;
    return is;
}

string Dish::ToString() {
    string vegeString;
    vegeString = vegetarian ? "yes" : "no";
    return MenuItem::ToString() + ", vegetarian: " + vegeString;
}