//
// Created by bkisl on 01.06.2022.
//

#include "../../includes/controller/databaseSimulationService.h"

const string DatabaseSimulationService::MENU_FILENAME = "menu.txt";

bool DatabaseSimulationService::FileExists(string fileName) {
    fstream stream(fileName);
    return stream.good();
}

void DatabaseSimulationService::WriteSimulationLog(string log, string fileName) {
    ofstream fileStream(fileName);
    fileStream << log;
    fileStream.close();
}

void DatabaseSimulationService::WriteMenu(MenuDatabase &menuDb) {
    ofstream fileStream(MENU_FILENAME);
    fileStream << menuDb;
    fileStream.close();
}

MenuDatabase DatabaseSimulationService::ReadMenu() {
    if(!FileExists(MENU_FILENAME)) throw invalid_argument("Menu file doesn't exist");

    MenuDatabase db(make_shared<Beverage>("Coffee", Price(2, 39), CupType::Cup, 3));
    ifstream fileStream("menu.txt");
    fileStream >> db;
    fileStream.close();
    return db;
}