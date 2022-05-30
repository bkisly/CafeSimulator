#include "../../includes/model/Employee/Cook.h"
#include "../../includes/model/Employee/DbWorkers.h"
#include "../../includes/model/Employee/Waiter.h"
#include "../../includes/model/Employee/Exceptions.h"
#include <algorithm>

using std::count;

using std::unique_ptr, std::make_unique, std::move;

void DbWorkers::addCook(const string &name, const string &surname, int gender,
                        Price baseSalary, unsigned baseAmountOfShifts,
                        unsigned knownCuisines) {
    unique_ptr<Cook> added_worker = make_unique<Cook>(newIdToAssign, name, surname, gender, baseSalary,
                                                      baseAmountOfShifts, knownCuisines);
    workers.push_back(move(added_worker));
    existingIDs.push_back(newIdToAssign);
    newIdToAssign++;
}

vector<unique_ptr<Employee>> &DbWorkers::GetEmployees() {
    return workers;
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
    checkIdExists(id);
    workers.erase(workers.begin() + id);
    existingIDs.erase(existingIDs.begin() + id);
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

void DbWorkers::checkIdExists(int id) {
    if ( !(std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end() )){
        throw IdException(id);
    }
}

bool DbWorkers::assignDishToFreeCook(shared_ptr<MenuItem> menuItem) {
    for (auto &worker_ptr: workers) {
        Cook* cook = dynamic_cast<Cook*>(&*worker_ptr);
        if (cook){
            if(cook->getState() == Cook::CookState::free){
                cook->setAssignedMenuItem(menuItem);
                return true;
            }
        }
    }
    return false;
}

int DbWorkers::getWorkerState(int id) {
    checkIdExists(id);
    return workers[id]->getState();
}

void DbWorkers::advanceCycleAll() {
    for (auto &worker_ptr: workers) {
        if (worker_ptr->getCyclesLeft() > 0) {
            worker_ptr->cyclesLeft--;
        }
        if (worker_ptr->getCyclesLeft() == 0) {
//            cook version
            Cook *cook = dynamic_cast<Cook *>(&*worker_ptr);
            if (cook) {
                if (!(cook->assignedMenuItem)) {
                    // case when cook finished preparing meal
                    cook->dishToCollect = false;
                }
                else if (cook->currentState == Cook::CookState::busy) {
                    cook->currentState = Cook::CookState::free;
                    cook->dishToCollect = true;
                    cook->assignedMenuItem.reset();
                }
                else {
                    cook->currentState = Cook::CookState::busy;
                    cook->dishToCollect = false;
                }
            }
            // waiter version
            else{
                Waiter *waiter = dynamic_cast<Waiter *>(&*worker_ptr);
                if (waiter) {
                    switch (waiter->currentState) {
                        case Waiter::WaiterState::awaiting:
                            if (waiter->assignedTable.GetCapacity() != 0) {
                                waiter->currentState++;
                            }
                            break;
                        case Waiter::WaiterState::giveMenu:
                            waiter->currentState++;
                            break;
                        case Waiter::WaiterState::collectOrder:
                            waiter->collectOrders();
                            waiter->currentState++;
                            break;
                        case Waiter::WaiterState::prepareOrder:
                            // check if there are items to prepare
                            if (waiter->assignedTable.GetAmountOfItemsToPrepare()) {
                                // get item
                                shared_ptr<MenuItem> menuItem =
                                        waiter->assignedTable.GetLastItemToPrepare();
                                // try to pass dish along to cook
                                if (this->assignDishToFreeCook(menuItem)) {
                                    waiter->cyclesLeft = menuItem->GetCyclesToPrepare();
                                    waiter->assignedTable.RemoveLastItemToPrepare();
                                }
                            }
                            // no dishes left - update state
                            else {
                                waiter->currentState++;
                            }
                            break;
                        case Waiter::WaiterState::handInOrder:
                            waiter->currentState++;
                            break;
                        case Waiter::WaiterState::takeReceipt:
                            // TODO-TEMP invoke calc recipt (calc receipt - sum items, update customers property - receivdedReceipt
                            // if new clients come, serve them, otherwise leave table
                            if (waiter->assignedTable.GetCustomers().size() == 0){
                                waiter->assignedTable = Table();
                                waiter->currentState = Waiter::WaiterState::awaiting;
                            }
                            else {
                                waiter->currentState = Waiter::WaiterState::collectOrder;
                            }

                            break;
                        default:
                            throw StateException(waiter->currentState);
                    }
                }
            }
        }
    }
}

#if DEBUG

Cook *DbWorkers::getCook(int id) {
    return dynamic_cast<Cook*>(&*workers[id]);
}

Waiter *DbWorkers::getWaiter(int id) {
    return dynamic_cast<Waiter*>(&*workers[id]);
}


#endif
