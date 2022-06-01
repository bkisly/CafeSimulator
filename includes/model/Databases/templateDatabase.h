#ifndef TEMPLATEDATABASE_H
#define TEMPLATEDATABASE_H
#include "iDatabase.h"
#include "../Customer/table.h"
#include "../Employee/Employee.h"
#include "../MenuItem/exceptions.h"
template<class T>
class TemplateDatabase  : public IDatabaseExtended<T>  {
protected:
    vector<shared_ptr<T>> items;
    int newIdToAssign;

    void validateId(shared_ptr<T> newItem) override;
public:
    TemplateDatabase();
    TemplateDatabase(std::shared_ptr<T> item);
    TemplateDatabase(std::vector<std::shared_ptr<T>> newItems);
    void AddItem(std::shared_ptr<T> item) override;
    int CountItems() override;;
    void RemoveItem(unsigned int index) override;
    std::vector<std::shared_ptr<T>> &GetItems() override;
    std::ostream &Write(std::ostream &os) override;
    std::istream &Read(std::istream &is) override;

//    friend std::ostream &operator<<(std::ostream &os, T &collection);
};


template<class T>
void TemplateDatabase<T>::AddItem(shared_ptr<T> item) {
    validateId(item);
    items.push_back(item);
    newIdToAssign++;
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
void TemplateDatabase<T>::RemoveItem(unsigned int index) {
   if ( index < 0 || index >= items.size() ){
       throw IndexOutOfRangeException("index out of range");
   }

   items.erase(items.begin() + index);

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
    newIdToAssign = 0;
}

template<class T>
TemplateDatabase<T>::TemplateDatabase(vector<std::shared_ptr<T>> newItems) {
    this->items = newItems;
    newIdToAssign = 0;
}

template<class T>
std::ostream &TemplateDatabase<T>::Write(ostream &os) {
    os << items.size() << "\n";
    for (const auto &item: items) {
        item->Write(os);
        os << "\n";
    }
    return os;
}

template<class T>
std::istream &TemplateDatabase<T>::Read(istream &is) {
    items.clear();
    int amount;
    is >> amount;
    while (amount>0){
        T newObject;
        newObject.Read(is);
        items.push_back(make_shared<T>(newObject));
        amount--;
    }
    return is;
}

template<class T>
TemplateDatabase<T>::TemplateDatabase() {
    newIdToAssign = 0;
}

//template<class T>
//std::ostream &operator<<(ostream &os, T &collection) {
//    return collection.Write(os);
//}


#endif //TEMPLATEDATABASE_H
