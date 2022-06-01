//
// Created by bkisl on 01.06.2022.
//

#include "../../includes/model/Databases/databaseService.h"

const string DatabaseService::MENU_FILENAME = "menu.txt";

bool DatabaseService::FileExists(string fileName) {
    fstream stream(fileName);
    return stream.good();
}

void DatabaseService::WriteSimulationLog(string log, string fileName) {
    ofstream fileStream(fileName);
    fileStream << log;
    fileStream.close();
}

void DatabaseService::WriteMenu(MenuDatabase &menuDb) {
    ofstream fileStream(MENU_FILENAME);
    fileStream << menuDb;
    fileStream.close();
}

MenuDatabase DatabaseService::ReadMenu() {
    if(!FileExists(MENU_FILENAME)) throw invalid_argument("Menu file doesn't exist");

    MenuDatabase db(make_shared<Beverage>("Coffee", Price(2, 39), CupType::Cup, 3));
    ifstream fileStream("menu.txt");
    fileStream >> db;
    fileStream.close();
    return db;
}