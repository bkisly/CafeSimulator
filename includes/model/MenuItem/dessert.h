//
// Created by bkisl on 27.04.2022.
//

#ifndef CAFEMENU_DESSERT_H
#define CAFEMENU_DESSERT_H

#include "menuItem.h"

using namespace std;

class Dessert : public MenuItem {
public:
    Dessert(string name, Price pricePerPortion, unsigned int cyclesToPrepare);

    ostream &Write(ostream &os) override;
    istream &Read(istream &is) override;
};


#endif //CAFEMENU_DESSERT_H
