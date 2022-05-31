#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Exceptions.h"

Waiter::Waiter(int id, const string &name, const string &surname, int gender, Price baseSalary,
               unsigned int baseAmountOfShifts, bool canServeAlcohol)
        : Employee(id, name, surname, gender, baseSalary, baseAmountOfShifts),
          can_serve_alcohol(canServeAlcohol) {
    receipt = Price(0, 0);
}

Price Waiter::calculate_salary() const noexcept {
    return (can_serve_alcohol) ? base_salary * 3 : base_salary * 2;
}

bool Waiter::is_can_serve_alcohol() const {
    return can_serve_alcohol;
}

void Waiter::set_can_serve_alcohol(bool canServeAlcohol) {
    can_serve_alcohol = canServeAlcohol;
}

unsigned int Waiter::calculate_shifts_per_week() const noexcept {
    return (can_serve_alcohol) ? base_amount_of_shifts + 1 : base_amount_of_shifts;
}

std::ostream &Waiter::write(std::ostream &os) const noexcept {
    Employee::write(os);
    os << " " << can_serve_alcohol;
    return os;
}


string Waiter::printProperties() const noexcept {
    return Employee::printProperties();
//    + "whether can serve alcohol: " + std::to_string
//            (can_serve_alcohol) + "\n";
}

std::istream &Waiter::read(std::istream &in) {
    Employee::read(in);
    in >> can_serve_alcohol;
    return in;
}

Waiter::Waiter() {
    assignedTable.reset();
}

bool Waiter::operator==(const Waiter &rhs) const {
    return static_cast<const Employee &>(*this) == static_cast<const Employee &>(rhs) &&
           can_serve_alcohol == rhs.can_serve_alcohol;
}

bool Waiter::operator!=(const Waiter &rhs) const {
    return !(rhs == *this);
}

string Waiter::printStateLog() const {
    string msg = "waiter " + std::to_string(id) + " - ";
    switch (currentState) {
        case WaiterState::awaiting:
            return msg + "awaiting\n";
        case WaiterState::giveMenu:
            return msg + "giving cards to table nr " +
                   to_string(assignedTable->GetId()) + "\n";
        case WaiterState::collectOrder:
            return msg + "collecting orders to table nr " +
                   to_string(assignedTable->GetId()) + "\n";
        case WaiterState::prepareOrder:
            return msg + "Preparing orders for table nr " +
                   to_string(assignedTable->GetId()) + "\n";
        case WaiterState::handInOrder:
            return msg + "handing in orders to table nr " +
                   to_string(assignedTable->GetId()) + "\n";
        case WaiterState::takeReceipt:
            return msg + "taking receipt to table nr " +
                   to_string(assignedTable->GetId()) + "\n";
        default:
            throw StateException(currentState);
    }
}



void Waiter::setAssignedTable(const shared_ptr<Table> &newAssignedTable) {
    if (currentState != WaiterState::awaiting) {
        throw BusyWaiterException();
    }

    newAssignedTable->SetHasAssignedWaiter(true);
    assignedTable = newAssignedTable;   // @important - the copy is made here
}

void Waiter::collectOrders() {
    for (auto &customer : assignedTable->GetCustomers()){
        if (customer.GetCurrentState() == CustomerState::ReadyToOrder){
            assignedTable->AddItemToPrepare(customer.GetPreferredMenuItem());
            customer.setCollectedOrder(true);
        }
    }
}

Price Waiter::calcReceipt() {
    for (auto &customer : this->assignedTable->GetCustomers()){
        if (customer.isCollectedOrder()){
            this->receipt += customer.GetPreferredMenuItem()->GetPricePerPortion();
            customer.setReceivedReceipt(true);
        }
    }
    return receipt;
}

shared_ptr<Table> Waiter::getAssignedTable() const {
    return assignedTable;
}

