//
// Created by bkisl on 27.04.2022.
//

#ifndef CAFEMENU_DISH_H
#define CAFEMENU_DISH_H

#include "menuItem.h"

using namespace std;

class Dish : public MenuItem {
private:
    bool vegetarian;

public:
    Dish(string name, Price pricePerPortion, bool vegetarian, unsigned int cyclesToPrepare);

    bool IsVegetarian() const;
    ostream &Write(ostream &os) override;
    istream &Read(istream &is) override;
    string ToString() override;
};


#endif //CAFEMENU_DISH_H
