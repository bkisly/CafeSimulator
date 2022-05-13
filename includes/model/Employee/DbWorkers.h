#ifndef DBWORKERS_H
#define DBWORKERS_H

#include <vector>
#include <memory>
#include <string>
#include <ostream>
#include "Worker.h"

using std::string, std::vector;

class DbWorkers {
private:
    vector<std::unique_ptr<Worker>> workers;
    vector<int> existingIDs;
    int newIdToAssign;

    void validateId(int id);
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

    int getWokerState(int id);
//    todo envoke polymorphic method for Worker base class (unique_ptr)

};

std::ostream &operator<<(std::ostream &os, const DbWorkers &workers);
std::istream &operator>>(std::istream &in, DbWorkers &workers);


#endif //DBWORKERS_H
