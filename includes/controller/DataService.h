#ifndef DATASERVICE_H
#define DATASERVICE_H
#include "../../includes/model/Databases/templateDatabase.h"
#include "../../includes/model/Databases/CustomTableDb.h"
#include "../../includes/model/Databases/CustomEmployeesDb.h"
#include "../../includes/model/Databases/menuDatabase.h"
class DataService {
private:
    void validatePath(string filename);
public:
    DataService()=default;
    void ReadMenu(MenuDatabase &menuDb, string filename="menuDb.txt");
    void WriteMenu(MenuDatabase &menuDb, string filename="menuDb.txt");

    void ReadTables(CustomTableDb &tablesDb, string filename= "tablesDb.txt");
    void WriteTables(CustomTableDb &tablesDb, string filename="tables.txt");

    void ReadEmployees(CustomEmployeesDb &employeesDb, string filename= "employeesDb.txt");
    void WriteEmployees(CustomEmployeesDb &employeesDb, string filename= "employeesDb.txt");


};


#endif //DATASERVICE_H
