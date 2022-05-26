#ifndef DBWORKERS_H
#define DBWORKERS_H

#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include "Employee.h"
#include "Waiter.h"
#include "../MenuItem/dish.h"

using std::string, std::vector;

class DbWorkers {
private:
    vector<int> existingIDs;
    std::vector<std::unique_ptr<Employee>> workers;
    int newIdToAssign;

    void checkIdExists(int id);
public:
    DbWorkers();

    void
    addWorker(const string &name, const string &surname, int gender, Price baseSalary,
              unsigned baseAmountOfShifts);


    void addCook(const string &name, const string &surname, int gender, Price baseSalary,
                 unsigned baseAmountOfShifts, unsigned int knownCuisines);

    void
    addWaiter(const string &name, const string &surname, int gender, Price baseSalary,
              unsigned baseAmountOfShifts, bool canServeAlcohol);

    void removeWorkerById(int index);

    Price sum_all_workers_salary() const noexcept;

    unsigned sum_all_shifts() const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const DbWorkers &workers);

    friend std::istream &operator>>(std::istream &in, DbWorkers &workers);

    string printAll() const noexcept;

    bool assignDishToFreeCook(unique_ptr<MenuItem> menuItem);
    // true - if success, false - fail to assign

    int getWorkerState(int id);

};

std::ostream &operator<<(std::ostream &os, const DbWorkers &workers);
std::istream &operator>>(std::istream &in, DbWorkers &workers);


#endif //DBWORKERS_H
