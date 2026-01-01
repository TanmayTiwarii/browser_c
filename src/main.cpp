#include <iostream>
#include <curl/curl.h>

int main() {
    curl_version_info_data* data = curl_version_info(CURLVERSION_NOW);
    std::cout << "libcurl version: " << data->version << std::endl;
    return 0;
}
