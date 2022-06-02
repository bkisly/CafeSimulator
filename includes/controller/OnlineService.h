#ifndef ONLINESERVICE_H
#define ONLINESERVICE_H
#include <string>

class OnlineService {
public:
    std::string GET_REQUEST(std::string url);
    void POST_REQUEST(std::string url, std::string body);
};


#endif //ONLINESERVICE_H
