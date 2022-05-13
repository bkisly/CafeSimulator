#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/Employee/DbWorkers.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Exceptions.h"
#include <algorithm>

using std::count;

using std::unique_ptr, std::make_unique, std::move;

void DbWorkers::addWorker(const string &name, const string &surname, int gender,
                          Price baseSalary, unsigned int baseAmountOfShifts) {
    unique_ptr<Employee> added_worker = make_unique<Employee>(newIdToAssign, name, surname, gender,
                                                              baseSalary, baseAmountOfShifts);
    workers.push_back(move(added_worker));
    existingIDs.push_back(newIdToAssign);
    newIdToAssign++;
}


void DbWorkers::addCook(const string &name, const string &surname, int gender,
                        Price baseSalary, unsigned baseAmountOfShifts,
                        unsigned knownCuisines) {
    unique_ptr<Cook> added_worker = make_unique<Cook>(newIdToAssign, name, surname, gender, baseSalary,
                                                      baseAmountOfShifts, knownCuisines);
    workers.push_back(move(added_worker));
    existingIDs.push_back(newIdToAssign);
    newIdToAssign++;
}

void DbWorkers::addWaiter(const string &name, const string &surname, int gender,
                          Price baseSalary, unsigned baseAmountOfShifts,
                          bool canServeAlcohol) {
    unique_ptr<Waiter> added_worker = make_unique<Waiter>(newIdToAssign, name, surname, gender,
                                                          baseSalary, baseAmountOfShifts,
                                                          canServeAlcohol);
    workers.push_back(move(added_worker));
    existingIDs.push_back(newIdToAssign);
    newIdToAssign++;
}

std::ostream &operator<<(std::ostream &os, const DbWorkers &workers) {
    for (const auto &worker_ptr: workers.workers) {
        os << *worker_ptr << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &in, DbWorkers &workers){
    return in;
//    todo: implement in for collection: 1 - types sequence; 2 - try catch blocks from
//     longest (probably stream clearing needed)
}


Price DbWorkers::sum_all_workers_salary() const noexcept {
    Price sum(0,0);
    for (const auto &worker_ptr: workers) {
        sum += worker_ptr->calculate_salary();
    }
    return sum;
}

unsigned DbWorkers::sum_all_shifts() const noexcept {
    int sum = 0;
    for (const auto &worker_ptr: workers) {
        sum += worker_ptr->calculate_shifts_per_week();
    }
    return sum;
}

void DbWorkers::removeWorkerById(int id) {
    validateId(id);
    workers.erase(workers.begin() + id);
}

string DbWorkers::printAll() const noexcept {
    if (workers.size() == 0){
        return "no data\n";
    }
    string output = "";
    int counter = 0;
    for (const auto &worker_ptr: workers) {
        output += std::to_string(counter) + "\n";
        output += worker_ptr->printProperties() + "\n";
        counter++;
    }
    return output;
}

DbWorkers::DbWorkers() {
    newIdToAssign = 0;
}

void DbWorkers::validateId(int id) {
    if ( std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end() ){
        throw IdException(id);
    }
}
