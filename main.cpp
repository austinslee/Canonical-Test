#include <iostream>
#include "fetcher.hpp"


int main() {
	SimpleStreamsFormatFetcher test;
	std::string option;
	std::cout << "Welcome to SimpleStreamsFormatFetcher CLI\n" << "The following commands are:\n";
	while(1) {
		std::cout << "1. Return a list of all currently supported Ubuntu releases.\n2. Return the current Ubuntu LTS version.\n3. Return the sha256 of the disk1.img item of a given Ubuntu release.\n4. Break\n";
		std::cout << "To run command please enter the number associated with desired command.\n";
		std::cin >> option;
		if(option == "1") {
			std::vector<std::string> list = test.returnSupportedReleases();
			for(unsigned i = 0; i < list.size(); ++i) {
				std::cout << list.at(i) << "\n";
			}
		} else if (option == "2") {
		} else if (option == "3") {
			std::cout << "Please enter release_title\n";
			std::cin >> option;
			std::cout << test.returnDisk1Sha256(option) << "\n";
		} else if (option == "break") {
			break;
		}
	}

	return 0;
}
