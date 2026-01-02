#include <curl/curl.h>
#include <iostream>
#include <string>
using namespace std;
// Callback to write response data into a std::string
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    string* html = static_cast<std::string*>(userp);
    html->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to init curl\n";
        return 1;
    }
    string url;
    cout << "ENTER URL:\n";
    getline(std::cin, url);
    string html;

    // Target URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Write response into our string
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

    // Important options for real websites
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/120.0 Safari/537.36");

    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "curl error: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return 1;
    }

    curl_easy_cleanup(curl);

    cout << html << std::endl;

    return 0;
}
