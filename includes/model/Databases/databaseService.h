//
// Created by bkisl on 01.06.2022.
//

#ifndef CAFE_DATABASESERVICE_H
#define CAFE_DATABASESERVICE_H

#include <fstream>
#include "menuDatabase.h"

class DatabaseService {
public:
    static const string MENU_FILENAME;
    static bool FileExists(string fileName);

    void WriteSimulationLog(string log, string fileName);
    void WriteMenu(MenuDatabase &menuDb);

    MenuDatabase ReadMenu();
};


#endif //CAFE_DATABASESERVICE_H
