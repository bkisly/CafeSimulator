#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "Price.h"

using std::string;

class Employee {
public:
    int getId() const;

    friend std::ostream &operator<<(std::ostream &os, const Employee &worker);

    friend std::istream &operator>>(std::istream &in, Employee &worker);

    virtual std::ostream &write(std::ostream &os) const noexcept;

    virtual std::istream &read(std::istream &in);

    int getState() const;

    void setState(int state);

    enum Gender {
        female = 0, male
    };
    Employee();

    Employee(int id, const string &name, const string &surname, int gender, Price baseSalary,
             unsigned baseAmountOfShifts);

    virtual ~Employee();

    const string &get_name() const;

    void set_name(const string &name);

    const string &get_surname() const;

    void set_surname(const string &surname);

    Price get_base_salary() const;

    int get_gender() const;

    int get_base_amount_of_shifts() const;

    virtual Price calculate_salary() const noexcept;

    virtual unsigned int calculate_shifts_per_week() const noexcept;

    bool operator==(const Employee &rhs) const;

    bool operator!=(const Employee &rhs) const;

    virtual string print() const noexcept;

    virtual string printState() const;

protected:
    int id;
    string name;
    string surname;
    int gender;
    Price base_salary;
    unsigned int base_amount_of_shifts;
    int state;

};

std::ostream &operator<<(std::ostream &os, const Employee &worker);



#endif //EMPLOYEE_H
