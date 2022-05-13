#ifndef WAITER_H
#define WAITER_H

#include "Employee.h"

class Waiter : public Employee {
private:
    bool can_serve_alcohol;
public:
    bool is_can_serve_alcohol() const;

    void set_can_serve_alcohol(bool canServeAlcohol);

    Waiter();

    Waiter(int id, const string &name, const string &surname, int gender, Price baseSalary,
           unsigned baseAmountOfShifts, bool canServeAlcohol);

    Price calculate_salary() const noexcept;

    unsigned int calculate_shifts_per_week() const noexcept;

    string printProperties() const noexcept;

//    stream handling
    std::ostream &write(std::ostream &os) const noexcept;
    std::istream &read(std::istream &in);

    bool operator==(const Waiter &rhs) const;

    bool operator!=(const Waiter &rhs) const;

    string printStateLog() const;

    enum WaiterState {
        awaiting = 0,
        giveMenu,
        collectOrder,
        handInOrder,
        takeReceipt
    };
};


#endif //WAITER_H
