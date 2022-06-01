#ifndef CUSTOMTABLEDB_H
#define CUSTOMTABLEDB_H
#include "templateDatabase.h"

class CustomTableDb  : public TemplateDatabase<Table>{
public:
    void AdvanceStateAllTables();
    bool TryAssignCustomersGroup(CustomersGroup customersGroup);
    friend std::ostream &operator<<(std::ostream &os, CustomTableDb &db);
    friend std::istream &operator>>(std::istream &in, CustomTableDb &db);
};


#endif //CUSTOMTABLEDB_H
