# Technical Test, Canonical
Dependencies:
	libcurl
	nlohmann-json


Instructions to install dependencies:

	sudo apt-get install libcurl4-openssl-dev 

	sudo apt install nlohmann-json3-dev
	

Instructions to run program:

	g++ -std=c++17 main.cpp fetcher.cpp -lcurl
 	./a.out



