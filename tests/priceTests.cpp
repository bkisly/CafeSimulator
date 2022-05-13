//
// Created by bkisl on 27.04.2022.
//

#define CATCH_CONFIG_MAIN
#include "../includes/model/MenuItem/price.h"
#include "catch.hpp"

TEST_CASE("Boolean operators")
{
    Price price1(2, 49);
    Price price2(5, 18);
    Price price3(2, 49);

    SECTION("Equality")
    {
        CHECK(price1 == price3);
        CHECK_FALSE(price1 == price2);

        CHECK(price1 != price2);
        CHECK_FALSE(price1 != price3);
    }

    SECTION("Relational")
    {
        CHECK(price1 < price2);
        CHECK_FALSE(price1 < price3);
        CHECK_FALSE(price2 < price3);

        CHECK(price1 <= price2);
        CHECK(price1 <= price3);
        CHECK_FALSE(price2 <= price3);

        CHECK_FALSE(price1 > price2);
        CHECK_FALSE(price1 > price3);
        CHECK(price2 > price3);

        CHECK_FALSE(price1 >= price2);
        CHECK(price1 >= price3);
        CHECK(price2 > price3);
    }
}

TEST_CASE("Arithmetical")
{
    Price price1(2, 49);
    Price price2(4, 0);
    Price price3(0, 0);
    Price price4(0, 1);
    Price price5(5, 73);

    SECTION("Addition")
    {
        CHECK((price1 + price2).GetDollars() == 6);
        CHECK((price1 + price2).GetCents() == 49);

        CHECK((price1 + price5).GetDollars() == 8);
        CHECK((price1 + price5).GetCents() == 22);

        CHECK((price1 + price3) == price1);
    }

    SECTION("Subtraction")
    {
        CHECK((price2 - price1).GetDollars() == 1);
        CHECK((price2 - price1).GetCents() == 51);

        CHECK((price1 - price3) == price1);

        CHECK_THROWS_AS(price1 - price2, invalid_argument);
    }

    SECTION("Multiplication")
    {
        CHECK((price1 * 2).GetDollars() == 4);
        CHECK((price1 * 2).GetCents() == 98);
        CHECK((price1 * 0) == price3);
        CHECK((price3 * 20) == price3);
    }

    SECTION("Division")
    {
        CHECK((price1 / 2).GetDollars() == 1);
        CHECK((price1 / 2).GetCents() == 24);
        CHECK((price2 / 2).GetDollars() == 2);
        CHECK((price2 / 2).GetCents() == 0);
        CHECK((price3 / 20) == price3);
        CHECK_THROWS_AS(price1 / 0, invalid_argument);
    }
}

TEST_CASE("To-string")
{
    Price price1(5, 99);
    Price price2(5, 9);
    Price price3(0, 0);

    CHECK(price1.ToString() == "$5.99");
    CHECK(price2.ToString() == "$5.09");
    CHECK(price3.ToString() == "$0.00");
}