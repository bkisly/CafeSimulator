//
// Created by bkisl on 27.04.2022.
//

#ifndef CAFEMENU_BEVERAGE_H
#define CAFEMENU_BEVERAGE_H

#include <string>
#include <map>
#include "menuItem.h"

using namespace std;

enum class CupType
{
    Cup,
    Mug,
    Glass
};

class Beverage : public MenuItem {
private:
    CupType cupType;

    map<CupType, string> cupTypesToStrings
    {
        {CupType::Cup, "Cup"},
        {CupType::Mug, "Mug"},
        {CupType::Glass, "Glass"},
    };

public:
    Beverage(string name, Price pricePerPortion, CupType cupType, unsigned int cyclesToPrepare);

    CupType GetCupType() const;
    ostream &Write(ostream &os) override;
    istream &Read(istream &is) override;
    string ToString() override;
};


#endif //CAFEMENU_BEVERAGE_H
