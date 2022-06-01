//
// Created by bkisl on 27.04.2022.
//

#include "../../includes/model/MenuItem/menuItem.h"
#include "../../includes/model/MenuItem/exceptions.h"

using namespace std;

// Private members

void MenuItem::dataValidation(string itemName, Price price, unsigned int cycles) {
    if(itemName.empty()) throw ArgumentEmptyException("Menu item name cannot be empty");
    if(price == Price(0, 0)) throw InvalidPriceException("Menu item price must be a number greater than 0.");
    if(cycles == 0) throw invalid_argument("Preparation time for a menu item must be a number greater than 0.");
}

// Public members

MenuItem::MenuItem(string name, PortionUnit portionUnit, Price pricePerPortion, unsigned int cyclesToPrepare) {
    dataValidation(name, pricePerPortion, cyclesToPrepare);

    this->name = name;
    this->portionUnit = portionUnit;
    this->pricePerPortion = pricePerPortion;
    this->cyclesToPrepare = cyclesToPrepare;
}

string MenuItem::GetName() const {
    return name;
}

PortionUnit MenuItem::GetPortionUnit() const {
    return portionUnit;
}

Price MenuItem::GetPricePerPortion() const {
    return pricePerPortion;
}

unsigned int MenuItem::GetCyclesToPrepare() const {
    return cyclesToPrepare;
}

string MenuItem::ToString() {
    return "Name: " + name + ", price per " + unitsToString[portionUnit] + ": " + pricePerPortion.ToString();
}

ostream &operator<<(ostream &os, const shared_ptr<MenuItem> &item) {
    return item->Write(os);
}

istream &operator>>(istream &is, shared_ptr<MenuItem> &item) {
    return item->Read(is);
}
