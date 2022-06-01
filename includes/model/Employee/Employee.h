#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "../helpers/price.h"
//#include "../Employee/DbWorkers.h"

using std::string;

class Employee {
public:
    int GetId() const;
    int getCyclesLeft() const;


//    io methods
    friend std::ostream &operator<<(std::ostream &os, const Employee &worker);
    friend std::istream &operator>>(std::istream &in, Employee &worker);
    virtual std::ostream &Write(std::ostream &os) const noexcept;
    virtual std::istream &Read(std::istream &in);

//    printProperties method for db listing
    virtual string printProperties() const noexcept;
//    method for logs in simulation
    virtual string printStateLog() const;


//    employee currentState (waiter/cook)
    int getState() const;
    void setState(int state);

//  constructors, operators ...
    Employee();
    Employee(int id, const string &name, const string &surname, int gender, Price baseSalary,
             unsigned baseAmountOfShifts);
    virtual ~Employee();
    bool operator==(const Employee &rhs) const;
    bool operator!=(const Employee &rhs) const;


// legacy methods
    const string &get_name() const;
    void set_name(const string &name);
    const string &get_surname() const;
    void set_surname(const string &surname);
    Price get_base_salary() const;
    int get_gender() const;
    int get_base_amount_of_shifts() const;
    virtual Price calculate_salary() const noexcept;
    virtual unsigned int calculate_shifts_per_week() const noexcept;
    enum Gender {
        female = 0, male
    };

protected:
    int id, currentState, cyclesLeft;


//    legacy attributes
    string name;
    string surname;
    int gender;
    Price base_salary;
    unsigned int base_amount_of_shifts;

    friend class DbWorkers;
    friend class CustomEmployeesDb;

};

//std::ostream &operator<<(std::ostream &os, const Employee &worker);



#endif //EMPLOYEE_H
