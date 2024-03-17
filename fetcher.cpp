#include "fetcher.hpp"

//Callback function for libcurl
size_t writecb(void *contents, size_t size, size_t nmemb, std::string *buffer) {
	size_t realSize = size * nmemb;
	buffer->append((char*)contents, realSize);
	return realSize;
}

//if arch == amd64 and supported == true, return release_title
std::vector<std::string> SimpleStreamsFormatFetcher::returnSupportedReleases()  {
	CURL *curl = curl_easy_init();
	CURLcode res;
	std::string responseBuffer;
	std::vector<std::string> toReturn;

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			printf("transfer fail: %s\n", curl_easy_strerror(res));
		}
		nlohmann::json jsonData = nlohmann::json::parse(responseBuffer);
		nlohmann::json jsonProductArray = jsonData["products"];
		for (const auto& product : jsonProductArray) {
			if (product["arch"].get<std::string>() == "amd64") {
				if(product["supported"].get<bool>() == true) {
					toReturn.push_back(product["release_title"].get<std::string>());
				}
			}
		}
		curl_easy_cleanup(curl);
	}
	return toReturn;
}

//Not sure how to find the Current Ubuntu LTS version. Working under the assumption that it is the latest version that has LTS in release_title
//return the Ubuntu release_title with LTS in the release_title and highest version number.
std::string SimpleStreamsFormatFetcher::returnCurrLTS() {
	CURL *curl = curl_easy_init();
	CURLcode res;
	std::string responseBuffer;
	std::string toReturn = "ERROR: Not Found\n";
	double maxVersion = 0.0;
	double temp;

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			printf("transfer fail: %s\n", curl_easy_strerror(res));
		}
		nlohmann::json jsonData = nlohmann::json::parse(responseBuffer);
		nlohmann::json jsonProductArray = jsonData["products"];

/* (str.find(substring) != std::string::npos) {
	std::cout << "String contains the substring \"" << substring << "\"" << std::endl;
}*/
		for (const auto& product : jsonProductArray) {
			//checks if arch == amd64, version number is the latest, and contains LTS in release title
			if (product["arch"].get<std::string>() == "amd64") {
				if(product["release_title"].get<std::string>().find("LTS") != std::string::npos) {
					temp = std::stod(product["version"].get<std::string>());
					if(temp > maxVersion) {
						toReturn = product["release_title"].get<std::string>();
					}
				}
			}
		}
	curl_easy_cleanup(curl);
	}
	return toReturn;
}



//given release_title, return the sha256 of the disk1.img
//Some of the Ubuntu releases don't have disk1.img. For example, Ubuntu 10.10
//Some of the Ubuntu releases have multiple disk1.img. For example Ubuntu 23.10
std::string SimpleStreamsFormatFetcher::returnDisk1Sha256(std::string release) {
	//std::string toReturn = "Ubuntu release_title not found";
	std::string toReturn = "";
	CURL *curl = curl_easy_init();
	CURLcode res;
	std::string responseBuffer;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			printf("transfer fail: %s\n", curl_easy_strerror(res));
		}
		nlohmann::json jsonData = nlohmann::json::parse(responseBuffer);
                nlohmann::json jsonProductArray = jsonData["products"];
       	        for (const auto& product : jsonProductArray) {
               	        if (product["release_title"].get<std::string>() == release && product["arch"].get<std::string>() == "amd64") {
				for(const auto& key : product["versions"])  {
					if(key["items"].contains("disk1.img")) {
						toReturn = key["items"]["disk1.img"]["sha256"].get<std::string>();
					} else {
						toReturn = "ERROR: disk1.img not found";
					}
				}
       	                }
               	}
                curl_easy_cleanup(curl);
	}
	return toReturn;
}

