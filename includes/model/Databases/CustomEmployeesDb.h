#ifndef CUSTOMEMPLOYEESDB_H
#define CUSTOMEMPLOYEESDB_H
#include "iDatabase.h"
#include "../Customer/table.h"
#include "../Employee/Employee.h"
#include "../MenuItem/exceptions.h"
#include "templateDatabase.h"

class CustomEmployeesDb : public TemplateDatabase<Employee> {
public:
    void AddWaiter(const string &name, const string &surname, int gender, Price baseSalary,
                   unsigned baseAmountOfShifts, bool canServeAlcohol);
};


#endif //CUSTOMEMPLOYEESDB_H
