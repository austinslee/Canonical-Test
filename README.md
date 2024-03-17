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


Assumptions made:

	Return the current Ubuntu LTS version. Assumed that the current Ubuntu LTS version is the latest version that has LTS in release_title

 	Return the sha256 of the disk1.img item of a given Ubuntu release. Some Ubuntu releases don't have disk1.img (example: 10.10). In these cases, error message is outputted. Some Ubuntu releases have multiple disk1.img (example: 23.10). In these cases, the highest number versions disk1.img is used.


