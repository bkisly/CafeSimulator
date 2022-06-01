//
// Created by bkisl on 17.05.2022.
//

#ifndef CAFE_IDATABASE_H
#define CAFE_IDATABASE_H

#include <vector>
#include <iostream>
#include <memory>

template<class T>
class IDatabase {
public:
    virtual void AddItem(std::shared_ptr<T> item) = 0;
    virtual void RemoveItem(unsigned int index) = 0;
    virtual const std::vector<std::shared_ptr<T>> &GetItems() = 0;
    virtual std::ostream &Write(std::ostream &os) = 0;
    virtual std::istream &Read(std::istream &is) = 0;
};


template<class T>
class IDatabaseDebug {
protected:
    virtual void validateId(std::shared_ptr<T> newItem)=0;
public:
    virtual void foo()=0;
    virtual void AddItem(std::shared_ptr<T> item) = 0;
    virtual int CountItems()=0;
    virtual void RemoveItem(unsigned int id) = 0;
    virtual std::vector<std::shared_ptr<T>> &GetItems() = 0;

    virtual std::ostream &Write(std::ostream &os) = 0;
    virtual std::istream &Read(std::istream &is) = 0;
};

#endif //CAFE_IDATABASE_H
