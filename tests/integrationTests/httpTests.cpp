#define CATCH_CONFIG_MAIN

#include <iostream>
#include "../catch.hpp"
#include "../../includes/model/cafeModel.h"
#include "../../includes/controller/http_lib.hpp"

TEST_CASE("Runner aopi get")
{
    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{"http://www.google.com"};

        // send a get request
        const auto response = request.send("GET");
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

TEST_CASE("api post"){
    try
    {
        http::Request request{"http://httpbin.org/post"};
        const string body = "foo=1&bar=baz";
        const auto response = request.send("POST", body, {
                {"Content-Type", "application/x-www-form-urlencoded"}
        });
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

TEST_CASE("stream play"){
    stringstream ss;
    ss << "123";
    string text;
    ss >> text;
    CHECK(text == "123");
}