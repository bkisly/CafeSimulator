#ifndef WAITER_H
#define WAITER_H

#include "Employee.h"
#include "DbWorkers.h"
#include "../helpers/Table.h"
#include <memory>

class Waiter : public Employee {

public:
//    stream handling
    std::ostream &write(std::ostream &os) const noexcept;
    std::istream &read(std::istream &in);

//    printProperties method for db listing
    string printProperties() const noexcept;
//    method for logs in simulation
    string printStateLog() const;

//    waiter properties
    enum WaiterState{
        awaiting = 0,
        giveMenu,
        collectOrder,
        prepareOrder,
        handInOrder,
        takeReceipt,
        last = takeReceipt
    };
    void setAssignedTable(unique_ptr<Table> newAssignedTable);

//  constructors, operators ...
    Waiter();
    Waiter(int id, const string &name, const string &surname, int gender, Price baseSalary,
           unsigned baseAmountOfShifts, bool canServeAlcohol);
    bool operator==(const Waiter &rhs) const;
    bool operator!=(const Waiter &rhs) const;

//    legacy methods
    bool is_can_serve_alcohol() const;
    void set_can_serve_alcohol(bool canServeAlcohol);
    Price calculate_salary() const noexcept;
    unsigned int calculate_shifts_per_week() const noexcept;


private:
    std::unique_ptr<Table> assignedTable;
    void updateState();
    bool hasAssignedTable;

//    legacy
    bool can_serve_alcohol;
};


#endif //WAITER_H
