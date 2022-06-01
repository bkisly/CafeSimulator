#ifndef CUSTOMTABLEDB_H
#define CUSTOMTABLEDB_H
#include "templateDatabase.h"

class CustomTableDb  : public TemplateDatabase<Table>{
public:
    void AdvanceStateAllTables();
    bool TryAssignCustomersGroup(CustomersGroup customersGroup);
};


#endif //CUSTOMTABLEDB_H
