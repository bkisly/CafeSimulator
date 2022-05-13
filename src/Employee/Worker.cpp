#include "../../includes/model/Employee/Worker.h"
#include "../../includes/model/Employee/Price.h"
#include "../../includes/model/Employee/Exceptions.h"

#include <memory>

using std::unique_ptr;
Worker::Worker(int id, const string &name, const string &surname, int gender, Price baseSalary,
unsigned baseAmountOfShifts)
        : id(id), name(name), surname(surname), gender(gender), base_salary(baseSalary),
        base_amount_of_shifts(baseAmountOfShifts){
    if (gender != 0 && gender != 1){
        throw GenderException(gender);
    }
    state = 0;
}

const string &Worker::get_name() const {
    return name;
}

void Worker::set_name(const string &name) {
    Worker::name = name;
}

const string &Worker::get_surname() const {
    return surname;
}

void Worker::set_surname(const string &surname) {
    Worker::surname = surname;
}

Price Worker::get_base_salary() const {
    return base_salary;
}


int Worker::get_gender() const {
    return gender;
}

Worker::~Worker() {

}

Price Worker::calculate_salary() const noexcept{
    return base_salary;
}

unsigned int Worker::calculate_shifts_per_week() const noexcept{
    return base_amount_of_shifts;
}

int Worker::get_base_amount_of_shifts() const {
    return base_amount_of_shifts;
}


Worker::Worker() {

}

bool Worker::operator==(const Worker &rhs) const {
    return id == rhs.id && name == rhs.name && surname == rhs.surname && gender == rhs.gender &&
           base_salary == rhs.base_salary &&
           base_amount_of_shifts == rhs.base_amount_of_shifts;
}

bool Worker::operator!=(const Worker &rhs) const {
    return !(rhs == *this);
}

std::ostream &Worker::write(std::ostream &os) const noexcept {
    os << name << "\n" << surname << "\n" << id << " "
       << gender << " " << base_salary
       << " " << base_amount_of_shifts;
    return os;
}

std::istream &Worker::read(std::istream &in) {
    string name, surname;
    int id, gender;
    Price salary;
    unsigned shifts;
    std::getline(in, name);
    std::getline(in, surname);
    in >> id >> gender >> salary >> shifts;
    this -> name = name;
    this -> surname = surname;
    this -> id = id;
    this -> gender = gender;
    this -> base_salary = salary;
    this -> base_amount_of_shifts = shifts;
    return in;
}


std::ostream &operator<<(std::ostream &os, const Worker &worker) {
    return worker.write(os);
}

std::istream &operator>>(std::istream &in, Worker &worker) {
    worker.read(in);
    return in;
}

string Worker::print() const noexcept {
    string gender_str = (gender ==1 ) ? "male" : "female";
    return "name: "  + name + ", surname: " + surname + ", gender: " +
    ", id: " + std::to_string(id) +
    gender_str + ", base salary: " + base_salary.price_str() + "zl "
    + ",\nbase amount of shifts: " + std::to_string(base_amount_of_shifts) + "\n";
}

int Worker::getId() const {
    return id;
}

int Worker::getState() const {
    return state;
}

void Worker::setState(int state) {
    Worker::state = state;
}

string Worker::printState() const{
    return std::to_string(state);
}

