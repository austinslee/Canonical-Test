#ifndef __FETCHER_HPP__
#define __FETCHER_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


//Base Class
class Fetcher {
    public:
        virtual std::vector<std::string> returnSupportedReleases() = 0;
        virtual std::string returnCurrLTS() = 0;
        virtual std::string returnDisk1Sha256(std::string) = 0;
};
//Derived Class
class SimpleStreamsFormatFetcher : public Fetcher {
    public:
        std::vector<std::string> returnSupportedReleases()  override;
        std::string returnCurrLTS() override;
        std::string returnDisk1Sha256(std::string) override;
};


#endif //__FETCHER_HPP__
