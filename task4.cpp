#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "gumbo.h"

// Helper function to write data from libcurl to a string
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

// Function to fetch the HTML content from a URL
std::string fetch_html(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string html;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return html;
}

// Function to recursively search for nodes in the HTML and extract product data
void search_for_data(GumboNode* node, std::vector<std::string>& names, std::vector<std::string>& prices, std::vector<std::string>& ratings) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    GumboAttribute* classAttr;
    if (node->v.element.tag == GUMBO_TAG_DIV &&
        (classAttr = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        std::string(classAttr->value).find("product-name") != std::string::npos) {
        // Extract product name
        GumboNode* textNode = static_cast<GumboNode*>(node->v.element.children.data[0]);
        if (textNode->type == GUMBO_NODE_TEXT) {
            names.push_back(textNode->v.text.text);
        }
    } 
    // Add similar logic to extract prices and ratings
    // ...

    // Search children recursively
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        search_for_data(static_cast<GumboNode*>(children->data[i]), names, prices, ratings);
    }
}

// Function to write data to a CSV file
void write_to_csv(const std::string& filename, const std::vector<std::string>& names, const std::vector<std::string>& prices, const std::vector<std::string>& ratings) {
    std::ofstream file(filename);
    file << "Product Name,Price,Rating\n";
    for (size_t i = 0; i < names.size(); ++i) {
        file << names[i] << "," << prices[i] << "," << ratings[i] << "\n";
    }
    file.close();
}

int main() {
    std::string url = "https://www.example.com/products";
    std::string html = fetch_html(url);

    std::vector<std::string> product_names;
    std::vector<std::string> product_prices;
    std::vector<std::string> product_ratings;

    // Parse the HTML content
    GumboOutput* output = gumbo_parse(html.c_str());
    search_for_data(output->root, product_names, product_prices, product_ratings);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    // Write the extracted data to a CSV file
    write_to_csv("products.csv", product_names, product_prices, product_ratings);

    std::cout << "Data has been written to products.csv" << std::endl;

    return 0;
}

