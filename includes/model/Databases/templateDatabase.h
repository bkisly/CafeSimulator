#ifndef TEMPLATEDATABASE_H
#define TEMPLATEDATABASE_H
#include "iDatabase.h"
#include "../Customer/table.h"
#include "../Employee/Employee.h"
#include "../MenuItem/exceptions.h"
template<class T>
class TemplateDatabase  : public IDatabaseDebug<T>  {
protected:
    vector<shared_ptr<T>> items;

    void validateId(shared_ptr<T> newItem) override;
public:
    TemplateDatabase() = default;
    TemplateDatabase(std::shared_ptr<T> item);
    TemplateDatabase(std::vector<std::shared_ptr<T>> newItems);
    void foo() override;
    void AddItem(std::shared_ptr<T> item) override;
    int CountItems() override;;
    void RemoveItem(unsigned int id) override;
    std::vector<std::shared_ptr<T>> &GetItems() override;
    std::ostream &Write(std::ostream &os) override;
    std::istream &Read(std::istream &is) override;
};

template<class T>
void TemplateDatabase<T>::foo() {
    int a =2;
    cout<< a;
}

template<class T>
void TemplateDatabase<T>::AddItem(shared_ptr<T> item) {
    validateId(item);
    items.push_back(item);
}

//template<class T>
//bool TemplateDatabase<T>::ItemExists(shared_ptr<T> searchedItem) {
//    for (auto &item : items){
//        if (item.get() == searchedItem.get()){
//            return true;
//        }
//    }
//    return false;
//}
//
template<class T>
void TemplateDatabase<T>::RemoveItem(unsigned int id) {
    int indexInVector = -1;
    int counter = 0;
    for (auto &item : items){
        if (item->GetId() == id){
            indexInVector = counter;
            break;
        }
        counter++;
    }

    if (indexInVector >=0){
        items.erase(items.begin() + indexInVector, items.begin() + indexInVector +1);
    }
    else{
        throw IndexOutOfRangeException("not found id" + to_string(counter));
    }

//    items.pop_back();
}

template<class T>
int TemplateDatabase<T>::CountItems() {
    return items.size();
}

template<class T>
vector<std::shared_ptr<T>> &TemplateDatabase<T>::GetItems() {
    return items;
}

template<class T>
void TemplateDatabase<T>::validateId(shared_ptr<T> newItem) {
    for (auto &item : items){
        if (item->GetId() == newItem->GetId() ){
            throw ItemExistenceException("duplicated id");
        }
    }
}

template<class T>
TemplateDatabase<T>::TemplateDatabase(shared_ptr<T> item) {
    items.push_back(item);
}

template<class T>
TemplateDatabase<T>::TemplateDatabase(vector<std::shared_ptr<T>> newItems) {
    this->items = newItems;
}

template<class T>
std::ostream &TemplateDatabase<T>::Write(ostream &os) {
    for (const auto &item: items) {
        item->Write(os);
    }
    return os;
}

template<class T>
std::istream &TemplateDatabase<T>::Read(istream &is) {
    items.clear();
    while(!cin.eof()){
        T newObject;
        newObject.Read(is);
        items.push_back(make_shared<T>(newObject));
    }
    return is;
}


#endif //TEMPLATEDATABASE_H
