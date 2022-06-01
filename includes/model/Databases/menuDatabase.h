//
// Created by bkisl on 27.04.2022.
//

#ifndef CAFEMENU_MENU_H
#define CAFEMENU_MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "../MenuItem/menuItem.h"
#include "../MenuItem/beverage.h"
#include "../MenuItem/dessert.h"
#include "../MenuItem/dish.h"
#include "iDatabase.h"

using namespace std;

class MenuDatabase : public IDatabase<MenuItem> {
private:
    vector<shared_ptr<MenuItem>> items;
    void validateItems(const vector<shared_ptr<MenuItem>> &menuItems);

public:
    MenuDatabase(shared_ptr<MenuItem> initialItem);
    MenuDatabase(vector<shared_ptr<MenuItem>> &initialItems);

    const vector<shared_ptr<MenuItem>> &GetItems() override;
    bool ItemExists(string itemName) const;
    void AddItem(shared_ptr<MenuItem> item) override;
    void RemoveItem(unsigned int itemIndex) override;
    void RemoveItem(string itemName);

    ostream &Write(ostream &os) override;
    istream &Read(istream &is) override;

    friend ostream &operator<<(ostream &os, const MenuDatabase &menu);
    friend istream &operator>>(istream &is, MenuDatabase &menu);
};


#endif //CAFEMENU_MENU_H
