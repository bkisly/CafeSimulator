//
// Created by bkisl on 27.04.2022.
//

#define CATCH_CONFIG_MAIN

#include <string>
#include <sstream>
#include <iostream>
#include "../catch.hpp"
#include "../../includes/model/MenuItem/beverage.h"
#include "../../includes/model/MenuItem/dessert.h"
#include "../../includes/model/MenuItem/dish.h"
#include "../../includes/model/helpers/exceptions.h"

using namespace std;

TEST_CASE("Initialization")
{
    Price validPrice(5, 49);
    Price invalidPrice(0, 0);

    SECTION("Beverage")
    {
        SECTION("Constructor tests")
        {
            CHECK_NOTHROW(Beverage("Coffee", validPrice, CupType::Mug, 3));
            CHECK_THROWS_AS(Beverage("", validPrice, CupType::Mug, 3), ArgumentEmptyException);
            CHECK_THROWS_AS(Beverage("Coffee", invalidPrice, CupType::Glass, 3), InvalidPriceException);
            CHECK_THROWS_AS(Beverage("Coffee", validPrice, CupType::Mug, 0), invalid_argument);
        }

        SECTION("Getters tests")
        {
            Beverage beverage("Coffee", validPrice, CupType::Mug, 3);

            CHECK(beverage.GetName() == "Coffee");
            CHECK(beverage.GetPortionUnit() == PortionUnit::Liter);
            CHECK(beverage.GetPricePerPortion() == validPrice);
            CHECK(beverage.GetCupType() == CupType::Mug);
            CHECK(beverage.GetCyclesToPrepare() == 3);
        }
    }

    SECTION("Dessert")
    {
        SECTION("Constructor tests")
        {
            CHECK_NOTHROW(Dessert("Cake", validPrice, 3));
            CHECK_THROWS_AS(Dessert("", validPrice, 3), ArgumentEmptyException);
            CHECK_THROWS_AS(Dessert("Cake", invalidPrice, 3), InvalidPriceException);
            CHECK_THROWS_AS(Dessert("Cake", validPrice, 0), invalid_argument);
        }

        SECTION("Getters tests")
        {
            Dessert dessert("Cake", validPrice, 3);

            CHECK(dessert.GetName() == "Cake");
            CHECK(dessert.GetPortionUnit() == PortionUnit::Piece);
            CHECK(dessert.GetPricePerPortion() == validPrice);
            CHECK(dessert.GetCyclesToPrepare() == 3);
        }
    }

    SECTION("Dish")
    {
        SECTION("Constructor tests")
        {
            CHECK_NOTHROW(Dish("Caesar salad", validPrice, false, 3));
            CHECK_THROWS_AS(Dish("", validPrice, false, 3), ArgumentEmptyException);
            CHECK_THROWS_AS(Dish("Caesar salad", invalidPrice, false, 3), InvalidPriceException);
            CHECK_THROWS_AS(Dish("Caesar salad", validPrice, false, 0), invalid_argument);
        }

        SECTION("Getters tests")
        {
            Dish dish("Caesar salad", validPrice, false, 3);

            CHECK(dish.GetName() == "Caesar salad");
            CHECK(dish.GetPortionUnit() == PortionUnit::Portion);
            CHECK(dish.GetPricePerPortion() == validPrice);
            CHECK_FALSE(dish.IsVegetarian());
            CHECK(dish.GetCyclesToPrepare() == 3);
        }
    }
}

TEST_CASE("Overrides")
{
    SECTION("Beverage")
    {
        Beverage beverage1("Coffee", Price(2, 49), CupType::Cup, 3);
        Beverage beverage2("Gourmet coffee", Price(10, 0), CupType::Mug, 3);

        SECTION("To string")
        {
            CHECK(beverage1.ToString() == "Name: Coffee, price per liter: $2.49, cup type: Cup");
            CHECK(beverage2.ToString() == "Name: Gourmet coffee, price per liter: $10.00, cup type: Mug");
        }
    }

    SECTION("Dessert")
    {
        Dessert dessert1("Cake", Price(4, 99), 3);
        Dessert dessert2("Old cake", Price(0, 1), 3);

        SECTION("To string")
        {
            CHECK(dessert1.ToString() == "Name: Cake, price per piece: $4.99");
            CHECK(dessert2.ToString() == "Name: Old cake, price per piece: $0.01");
        }
    }

    SECTION("Dish")
    {
        Dish dish1("Caesar salad", Price(10, 49), false, 2);
        Dish dish2("Fruit salad", Price(4, 0), true, 2);

        SECTION("To string")
        {
            CHECK(dish1.ToString() == "Name: Caesar salad, price per portion: $10.49, vegetarian: no");
            CHECK(dish2.ToString() == "Name: Fruit salad, price per portion: $4.00, vegetarian: yes");
        }
    }
}

TEST_CASE("Stream operators")
{
    stringstream ss;

    SECTION("Output")
    {
        Beverage coffee("Coffee", Price(2, 49), CupType::Cup, 3);
        coffee.Write(ss);
        CHECK(ss.str() == "Coffee\n2 49 3 0");

        Dessert cake("Cake", Price(10, 0), 2);
        ss = stringstream();
        cake.Write(ss);
        CHECK(ss.str() == "Cake\n10 0 2");

        Dish salad("Caesar salad", Price(15, 99), false, 5);
        ss = stringstream();
        salad.Write(ss);
        CHECK(ss.str() == "Caesar salad\n15 99 5 0");
    }

    SECTION("Input")
    {
        ss = stringstream();
        Beverage coffee("Coffee", Price(5, 99), CupType::Cup, 3);
        Beverage gourmetCoffee("Gourmet coffee", Price(12, 99), CupType::Mug, 5);
        gourmetCoffee.Write(ss);
        coffee.Read(ss);

        CHECK(coffee.GetName() == gourmetCoffee.GetName());
        CHECK(coffee.GetPricePerPortion() == gourmetCoffee.GetPricePerPortion());
        CHECK(coffee.GetCyclesToPrepare() == gourmetCoffee.GetCyclesToPrepare());
        CHECK(coffee.GetCupType() == gourmetCoffee.GetCupType());

        ss = stringstream();
        Dessert cake("Cake", Price(6, 25), 2);
        Dessert anotherCake("Gourmet cake", Price(9, 99), 4);
        anotherCake.Write(ss);
        cake.Read(ss);

        CHECK(cake.GetName() == anotherCake.GetName());
        CHECK(cake.GetPricePerPortion() == anotherCake.GetPricePerPortion());
        CHECK(cake.GetCyclesToPrepare() == anotherCake.GetCyclesToPrepare());

        ss = stringstream();
        Dish salad("Normal salad", Price(10, 0), true, 4);
        Dish unusualSalad("Unusual salad", Price(15, 0), false, 6);
        unusualSalad.Write(ss);
        salad.Read(ss);

        CHECK(salad.GetName() == unusualSalad.GetName());
        CHECK(salad.GetPricePerPortion() == unusualSalad.GetPricePerPortion());
        CHECK(salad.GetCyclesToPrepare() == unusualSalad.GetCyclesToPrepare());
        CHECK(salad.IsVegetarian() == unusualSalad.IsVegetarian());
    }
}