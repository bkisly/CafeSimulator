#include "CustomEmployeesDb.h"
#include "../Employee/Waiter.h"
#include "../Employee/Cook.h"
#include "../Employee/Exceptions.h"

void CustomEmployeesDb::addWaiter(const string &name, const string &surname, int gender,
                                  Price baseSalary, unsigned int baseAmountOfShifts,
                                  bool canServeAlcohol) {
    TemplateDatabase<Employee>::AddItem(make_shared<Waiter>(newIdToAssign, name, surname, gender, baseSalary,
                                        baseAmountOfShifts, canServeAlcohol));
}

void CustomEmployeesDb::addCook(const string &name, const string &surname, int gender,
                                Price baseSalary, unsigned int baseAmountOfShifts,
                                unsigned int knownCuisines) {
    TemplateDatabase<Employee>::AddItem(make_shared<Cook>(newIdToAssign, name, surname, gender, baseSalary,
                                      baseAmountOfShifts, knownCuisines));

}

int CustomEmployeesDb::getWorkerState(int id) {
    for (auto &worker : items){
        if (worker->GetId() == id){
            return  worker->getState();
        }
    }
    throw IdException(id);
}


void CustomEmployeesDb::advanceCycleAll() {
    for (auto &worker_ptr: items) {
        if (worker_ptr->getCyclesLeft() > 0) {
            worker_ptr->cyclesLeft--;
        }
        if (worker_ptr->getCyclesLeft() == 0) {
//            cook version
            Cook *cook = dynamic_cast<Cook *>(&*worker_ptr);
            if (cook) {
                cook->currentState = Cook::CookState::free;
            }
                // waiter version
            else{
                Waiter *waiter = dynamic_cast<Waiter *>(&*worker_ptr);
                if (waiter) {
                    switch (waiter->currentState) {
                        case Waiter::WaiterState::awaiting:
                            if (waiter->assignedTable) {
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
                            if (waiter->assignedTable->GetAmountOfItemsToPrepare() !=0) {
                                shared_ptr<MenuItem> item =
                                        waiter->assignedTable->PopLastItemToPrepare();
                                waiter->cyclesLeft = item->GetCyclesToPrepare();
                                this->assignDishToFreeCook(item);
                            }
                            else{
                                waiter->currentState++;
                            }
                            break;
                        case Waiter::WaiterState::handInOrder:
                            waiter->currentState++;
                            break;
                        case Waiter::WaiterState::ReadyToTakeReceipt:
                            waiter->calcReceipt();
                            waiter->currentState++;
                            break;
                        case Waiter::WaiterState::TakenReceipt:
                            // if new clients come, serve them, otherwise leave table
                            if (waiter->assignedTable->GetCustomers().size() == 0){
                                waiter->assignedTable.reset();
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

void CustomEmployeesDb::assignDishToFreeCook(shared_ptr<MenuItem> menuItem) {
    Cook* leastBusyCook= nullptr;
    for (auto &worker_ptr: items) {
        Cook* cook = dynamic_cast<Cook*>(&*worker_ptr);
        if (cook){
            // if found free - best option - done
            if(cook->getState() == Cook::CookState::free){
                cook->setAssignedMenuItem(menuItem);
                return;
            }
            else{
                // if initialized the least busy cook
                if(leastBusyCook){
                    if (cook->cyclesLeft < leastBusyCook->cyclesLeft){
                        leastBusyCook = cook;
                    }
                }
                // if not initialized
                else{
                    leastBusyCook = cook;
                }
            }
        }
    }
}

#if DEBUG

Cook *CustomEmployeesDb::getCook(int id) {
    return dynamic_cast<Cook*>(&*items[id]);
}

Waiter *CustomEmployeesDb::getWaiter(int id) {
    return dynamic_cast<Waiter*>(&*items[id]);
}


#endif