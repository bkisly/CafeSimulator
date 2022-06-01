#ifndef CUSTOMTABLEDB_H
#define CUSTOMTABLEDB_H
#include "templateDatabase.h"

class CustomTableDb  : public TemplateDatabase<Table>{
public:
    int GetFristTableId() {
        return items.front()->GetId();
    }
};


#endif //CUSTOMTABLEDB_H
