#include "../../includes/controller/DataService.h"
#include "../../includes/model/helpers/exceptions.h"
#include <filesystem>
#include <fstream>

void DataService::ReadMenu(MenuDatabase &menuDb, string filename) {
    filename = "../textFiles/" + filename;
    validatePath(filename);
    ifstream file;
    file.open(filename);
    file >> menuDb;
    file.close();
}

void DataService::validatePath(string filename) {
    if(!(std::filesystem::exists(filename))){
        throw FileException("non existing file");
    }
}

void DataService::WriteMenu(MenuDatabase &menuDb, string filename) {
    filename = "../textFiles/" + filename;
    validatePath(filename);
    ofstream file;
    file.open(filename);
    file << menuDb;
    file.close();
}

void DataService::ReadTables(CustomTableDb &tablesDb, string filename) {
    filename = "../textFiles/" + filename;
    validatePath(filename);
    ifstream file;
    file.open(filename);
    file >> tablesDb;
    file.close();
}

void DataService::WriteTables(CustomTableDb &tablesDb, string filename) {
    filename = "../textFiles/" + filename;
    validatePath(filename);
    ofstream file;
    file.open(filename);
    file << tablesDb;
    file.close();
}

void DataService::ReadEmployees(CustomEmployeesDb &employeesDb, string filename) {
    filename = "../textFiles/" + filename;
    validatePath(filename);
    ifstream file;
    file.open(filename);
    file >> employeesDb;
    file.close();
}

void DataService::WriteEmployees(CustomEmployeesDb &employeesDb, string filename) {
    filename = "../textFiles/" + filename;
    validatePath(filename);
    ofstream file;
    file.open(filename);
    file << employeesDb;
    file.close();
}

