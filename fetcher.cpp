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
	std::string SimpleStreamsFormatFetcher::returnCurrLTS() {
		return "";
	}
	std::string SimpleStreamsFormatFetcher::returnDisk1Sha256(std::string) {
		return "";
	}

