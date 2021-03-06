//
// Created by bkisl on 27.04.2022.
//

#ifndef CAFEMENU_MENUITEM_H
#define CAFEMENU_MENUITEM_H

#include <string>
#include <map>
#include <iostream>
#include <memory>
#include "../helpers/price.h"

using namespace std;

enum class PortionUnit
{
    Portion,
    Piece,
    Liter,
};

class MenuItem {
private:
    void dataValidation(string itemName, Price price, unsigned int cycles);

protected:
    string name = "";
    PortionUnit portionUnit;
    Price pricePerPortion = Price(0, 0);
    unsigned int cyclesToPrepare;

    map<PortionUnit, string> unitsToString
    {
        {PortionUnit::Portion, "portion"},
        {PortionUnit::Piece, "piece"},
        {PortionUnit::Liter, "liter"},
    };

public:
    MenuItem(string name, PortionUnit portionUnit, Price pricePerPortion, unsigned int cyclesToPrepare);
    virtual ~MenuItem() = default;

    string GetName() const;
    PortionUnit GetPortionUnit() const;
    Price GetPricePerPortion() const;
    unsigned int GetCyclesToPrepare() const;

    virtual ostream &Write(ostream &os) = 0;
    virtual istream &Read(istream &is) = 0;
    virtual string ToString();

    friend ostream &operator<<(ostream &os, const shared_ptr<MenuItem> &item);
    friend istream &operator>>(istream &is, shared_ptr<MenuItem> &item);

};


#endif //CAFEMENU_MENUITEM_H
