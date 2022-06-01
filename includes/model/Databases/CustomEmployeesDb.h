#ifndef CUSTOMEMPLOYEESDB_H
#define CUSTOMEMPLOYEESDB_H
#include "iDatabase.h"
#include "../Customer/table.h"
#include "../Employee/Employee.h"
#include "../MenuItem/Exceptions.h"
#include "templateDatabase.h"
#include "../Employee/Cook.h"
#include "../Employee/Waiter.h"

class CustomEmployeesDb : public TemplateDatabase<Employee> {
private:
    int getAmountOfCooks();
public:
    void addWaiter(const string &name, const string &surname, int gender, Price baseSalary,
                   unsigned baseAmountOfShifts, bool canServeAlcohol);
    void addCook(const string &name, const string &surname, int gender, Price baseSalary,
                 unsigned baseAmountOfShifts, unsigned int knownCuisines);
    int getWorkerState(int id);
    void advanceCycleAll();
    void assignItemsCooks(int cycles, string itemsList);

#if DEBUG
    Cook* getCook(int id);
    Waiter* getWaiter(int id);
#endif

};


#endif //CUSTOMEMPLOYEESDB_H
