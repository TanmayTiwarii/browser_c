#include <curl/curl.h>
#include <iostream>
#include <string>
#include <fstream>

#include "tokenizer.h"
#include "token.h"

using namespace std;

// Callback to write response data into a std::string
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    string* html = static_cast<string*>(userp);
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
    getline(cin, url);

    string html;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
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

    auto tokens = parser::tokenize(html);

    for (const auto& token : tokens) {
        switch (token.type) {
            case parser::TokenType::TagOpen:
                cout << "TAG_OPEN  : " << token.value << "\n";
                break;
            case parser::TokenType::TagClose:
                cout << "TAG_CLOSE : " << token.value << "\n";
                break;
            case parser::TokenType::Text:
                cout << "TEXT      : " << token.value << "\n";
                break;
        }
    }


    // ✅ WRITE HTML TO FILE
    ofstream outFile("page.html");   // or "page.txt"
    if (!outFile) {
        cerr << "Failed to open file for writing\n";
        return 1;
    }

    outFile << html;
    outFile.close();

    cout << "HTML saved to page.html\n";

    return 0;
}
