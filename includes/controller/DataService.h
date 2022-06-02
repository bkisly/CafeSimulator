#ifndef DATASERVICE_H
#define DATASERVICE_H
#include "../../includes/model/Databases/templateDatabase.h"
#include "../../includes/model/Databases/CustomTableDb.h"
#include "../../includes/model/Databases/CustomEmployeesDb.h"
#include "../../includes/model/Databases/menuDatabase.h"
#include "../../includes/controller/OnlineService.h"
class DataService {
private:
    void validatePath(string filename);
    OnlineService cloud;
public:
    DataService();
    void ReadMenu(MenuDatabase &menuDb, string filename="menuDb.txt", bool
    syncCloud=false);
    void WriteMenu(MenuDatabase &menuDb, string filename="menuDb.txt", bool
    syncCloud=false);

    void ReadTables(CustomTableDb &tablesDb, string filename= "tablesDb.txt", bool
    syncCloud=false);
    void WriteTables(MenuDatabase &tablesDb, string filename="tables.txt", bool
    syncCloud=false);

    void ReadEmployees(CustomEmployeesDb &employeesDb, string filename= "employeesDb"
                                                                        ".txt", bool
                                                                        syncCloud=false);
    void WriteEmployees(CustomEmployeesDb &employeesDb, string filename= "employeesDb"
                                                                         ".txt", bool
                                                                         syncCloud=false);


};


#endif //DATASERVICE_H
