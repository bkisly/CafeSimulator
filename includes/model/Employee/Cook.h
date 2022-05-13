#ifndef COOK_H
#define COOK_H

#include "Worker.h"
#include <string>

class Cook : public Worker {
public:
    bool operator==(const Cook &rhs) const;

    bool operator!=(const Cook &rhs) const;

    enum CookState {
        free = 0, busy
    };
private:
    unsigned known_cuisines;
public:
    Cook();

    Cook(int id, const string &name, const string &surname, int gender, Price baseSalary,
         unsigned baseAmountOfShifts, unsigned int knownCuisines);

    Price calculate_salary() const noexcept;

    unsigned int calculate_shifts_per_week() const noexcept;

    string print() const noexcept;

//  stream proccesing
    std::istream &read(std::istream &in);

    std::ostream &write(std::ostream &os) const noexcept;

    int get_known_cuisines() const;

    void set_known_cuisines(int knownCuisines);

    string PrintState() const;

};


#endif //COOK_H
