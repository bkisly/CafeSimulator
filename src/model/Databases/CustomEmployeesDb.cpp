#include "../../../includes/model/Databases/CustomEmployeesDb.h"
#include "../../../includes/model/Employee/Waiter.h"
#include "../../../includes/model/Employee/Cook.h"
#include "../../../includes/model/Employee/employeeExceptions.h"

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
                               int totalCycles = 0;
                               string itemList = "";
                               while (waiter->assignedTable->GetAmountOfItemsToPrepare
                               () != 0){
                                   auto item =waiter->assignedTable->PopLastItemToPrepare();
                                   totalCycles += item->GetCyclesToPrepare();
                                   itemList += item->GetName() + ", ";
                               }
                               totalCycles /= getAmountOfCooks();
                               assignItemsCooks(totalCycles, itemList);
                               waiter->cyclesLeft = totalCycles;
                            }
                            else{
                                waiter->currentState++;
                            }
                            break;
                        case Waiter::WaiterState::handInOrder:
                            for(Customer &customer : waiter->assignedTable->GetCustomers())
                                customer.SetReceivedOrder(true);

                            waiter->currentState++;
                            break;
                        case Waiter::WaiterState::ReadyToTakeReceipt:
                            waiter->calcReceipt();

                            if(waiter->assignedTable->HaveAllEaten())
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

void CustomEmployeesDb::assignItemsCooks(int cycles, string itemsList) {
    Cook* leastBusyCook= nullptr;
    for (auto &worker_ptr: items) {
        Cook* cook = dynamic_cast<Cook*>(&*worker_ptr);
        if (cook){
            cook->preparingItems = itemsList;
            cook->cyclesLeft = cycles;
            cook->currentState = Cook::CookState::busy;
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

int CustomEmployeesDb::getAmountOfCooks() {
    int counter = 0;
    for (auto &worker_ptr: items) {
        Cook* cook = dynamic_cast<Cook*>(&*worker_ptr);
        if (cook){
           counter++;
        }
    }
    return counter;
}

std::ostream &operator<<(ostream &os, CustomEmployeesDb &db) {
    return db.Write(os);
}

std::istream &operator>>(std::istream &in, CustomEmployeesDb &db) {
    return db.Read(in);
}

std::istream &CustomEmployeesDb::Read(istream &is) {
    items.clear();
    int amount;
    char kind;
    is >> amount;
    while (amount>0){
        is >> kind;
        if (kind == 'w'){
            Waiter waiter;
            waiter.Read(is);
            items.push_back(make_shared<Waiter>(waiter));
        }
        else{
            Cook cook;
            cook.Read(is);
            items.push_back(make_shared<Cook>(cook));
        }
        amount--;
    }
    return is;
}


#endif