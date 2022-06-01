#include "../../includes/model/Employee/Employee.h"
#include "../../includes/model/helpers/price.h"
#include "../../includes/model/Employee/Exceptions.h"

#include <memory>

using std::unique_ptr;
Employee::Employee(int id, const string &name, const string &surname, int gender, Price baseSalary,
                   unsigned baseAmountOfShifts)
        : id(id), name(name), surname(surname), gender(gender), base_salary(baseSalary),
        base_amount_of_shifts(baseAmountOfShifts){
    if (gender != 0 && gender != 1){
        throw GenderException(gender);
    }
    currentState = 0;
    cyclesLeft = 0;
}

const string &Employee::get_name() const {
    return name;
}

void Employee::set_name(const string &name) {
    Employee::name = name;
}

const string &Employee::get_surname() const {
    return surname;
}

void Employee::set_surname(const string &surname) {
    Employee::surname = surname;
}

Price Employee::get_base_salary() const {
    return base_salary;
}


int Employee::get_gender() const {
    return gender;
}

Employee::~Employee() {

}

Price Employee::calculate_salary() const noexcept{
    return base_salary;
}

unsigned int Employee::calculate_shifts_per_week() const noexcept{
    return base_amount_of_shifts;
}

int Employee::get_base_amount_of_shifts() const {
    return base_amount_of_shifts;
}


Employee::Employee() {

}

bool Employee::operator==(const Employee &rhs) const {
    return id == rhs.id && name == rhs.name && surname == rhs.surname && gender == rhs.gender &&
           base_salary == rhs.base_salary &&
           base_amount_of_shifts == rhs.base_amount_of_shifts;
}

bool Employee::operator!=(const Employee &rhs) const {
    return !(rhs == *this);
}

std::ostream &Employee::Write(std::ostream &os) const noexcept {
    os << name << "\n" << surname << "\n" << id << " "
       << gender << " " << base_salary
       << " " << base_amount_of_shifts;
    return os;
}

std::istream &Employee::Read(std::istream &in) {
    string name, surname;
    int id, gender;
    Price salary;
    unsigned shifts;
    std::getline(in, name);
    std::getline(in, surname);
    in >> id >> gender >> salary >> shifts;
    this -> name = name;
    this -> surname = surname;
    this->currentState = 0;
    this -> cyclesLeft = 0;
    this -> id = id;
    this -> gender = gender;
    this -> base_salary = salary;
    this -> base_amount_of_shifts = shifts;
    return in;
}


std::ostream &operator<<(std::ostream &os, const Employee &worker) {
    return worker.Write(os);
}

std::istream &operator>>(std::istream &in, Employee &worker) {
    return worker.Read(in);
}

string Employee::printProperties() const noexcept {
    string gender_str = (gender ==1 ) ? "male" : "female";
    return "name: "  + name + ", surname: " + surname + ", gender: " +
    ", id: " + std::to_string(id) +
    gender_str + ", base salary: " + base_salary.ToString() + " "
    + ",\nbase amount of shifts: " + std::to_string(base_amount_of_shifts) + "\n";
}

int Employee::GetId() const {
    return id;
}

int Employee::getState() const {
    return currentState;
}

void Employee::setState(int state) {
    Employee::currentState = state;
}

string Employee::printStateLog() const{
    return std::to_string(currentState);
}

int Employee::getCyclesLeft() const {
    return cyclesLeft;
}




