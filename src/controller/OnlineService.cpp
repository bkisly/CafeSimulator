#include "../../includes/controller/OnlineService.h"
#include "../../includes/controller/http_lib.hpp"
#include "../../includes/model/helpers/exceptions.h"

std::string OnlineService::GET_REQUEST(std::string url) {
    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{url};

        // send a get request
        const auto response = request.send("GET");
        return std::string{response.body.begin(), response.body.end()};
    }
    catch (const std::exception& e)
    {
        throw NetworkException("api/connection issue");
    }
}

void OnlineService::POST_REQUEST(std::string url, std::string body) {
    try
    {
        http::Request request{url};
//        const string body = "foo=1&bar=baz";
        const auto response = request.send("POST", body, {
                {"Content-Type", "application/x-www-form-urlencoded"}
        });
    }
    catch (const std::exception& e)
    {
        throw NetworkException("api/connection issue");
    }
}
