#include <memory>
#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/Employee/Exceptions.h"

int Cook::get_known_cuisines() const {
    return known_cuisines;
}

void Cook::set_known_cuisines(int knownCuisines) {
    known_cuisines = knownCuisines;
}

Cook::Cook(int id, const string &name, const string &surname, int gender, Price baseSalary,
               unsigned int baseAmountOfShifts, unsigned int knownCuisines)
        : Employee(id, name, surname, gender, baseSalary, baseAmountOfShifts),
          known_cuisines(knownCuisines) {
    dishToCollect = false;
}

Price Cook::calculate_salary() const noexcept {
    return base_salary * 2;
}

unsigned int Cook::calculate_shifts_per_week() const noexcept {
    return (known_cuisines > 25) ? base_amount_of_shifts + 1 : base_amount_of_shifts;
}

std::ostream &Cook::write(std::ostream &os) const noexcept{
    Employee::write(os);
    os << " " << known_cuisines;
    return os;
}

string Cook::printProperties() const noexcept {
    return Employee::printProperties();
//    + "known cuisines: " + std::to_string
//            (known_cuisines) + "\n";
}

std::istream &Cook::read(std::istream &in) {
    Employee::read(in);
    in >> known_cuisines;
    return in;
}

Cook::Cook() {

}

bool Cook::operator==(const Cook &rhs) const {
    return static_cast<const Employee &>(*this) == static_cast<const Employee &>(rhs) &&
           known_cuisines == rhs.known_cuisines;
}

bool Cook::operator!=(const Cook &rhs) const {
    return !(rhs == *this);
}

string Cook::printStateLog() const {
    string msg = "cook " + std::to_string(id) + " - ";
    switch (currentState) {
        case CookState::free:
            return msg + "free\n";
        case CookState::busy:
            return msg + "prepares " + assignedMenuItem->GetName() + "\n";
        default:
            throw StateException(currentState);
    }
}



void Cook::setAssignedMenuItem(std::unique_ptr<MenuItem> newAssignedMenuItem) {
    if (currentState == CookState::busy){
        throw BusyCookException();
    }
    cyclesLeft = newAssignedMenuItem->GetCyclesToPrepare();
    Cook::assignedMenuItem  = std::move(newAssignedMenuItem);
    currentState = CookState::busy;
}

void Cook::updateState() {
    if (currentState == CookState::busy){
        currentState = CookState::free;
        dishToCollect = true;
    }
    else{
        currentState = CookState::busy;
        dishToCollect = false;
    }
}

bool Cook::isDishToCollect() const {
    return dishToCollect;
}


