#ifndef __FETCHER_HPP__
#define __FETCHER_HPP__

#include <iostream>
#include <string>
#include <vector>

//Base Class
class Fetcher {
    public:
        virtual std::vector<std::string> returnSupportedReleases() const = 0;
        virtual std::string returnCurrLTS() const = 0;
        virtual std::string returnDisk1Sha256(std::string) const = 0;
        virtual ~Fetcher() = 0;

};
//Derived Class
class SimpleStreamsFormatFetecher : public Fetcher {
    public:
        std::vector<std::string> returnSupportedReleases()  const override;
        std::string returnCurrLTS() const override;
        std::string returnDisk1Sha256(std::string) const override;
        void CLI();
}


#endif //__FETCHER_HPP__
