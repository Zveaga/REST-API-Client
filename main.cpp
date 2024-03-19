#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <curl/curl.h>

/**
 * This function will be used by curl to retrieve and store the requested data
*/
size_t writeCallBack(void *retrieved_content, size_t elem_size, size_t elem_count, void *data)
{
    ((std::string*)data)->append((char*)retrieved_content, elem_size * elem_count);
    return (elem_size * elem_count);
}

/**
 * [describe function]
*/
bool CurlRequest(const std::string &url, std::string &response)
{
	// Initialize curl handle
	CURL *curl = curl_easy_init();
	std::string api_key = "";
	if (!curl)
	{
		std::cerr << "Failed to initialize the CURL handle\n";
		return (false);
	}

	// Add the api_key as a custom header to HTTP request
	struct curl_slist *headers = nullptr;
	headers = curl_slist_append(headers, ("X-CMC_PRO_API_KEY: " + api_key).c_str());	
	
	// Set up curl options
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallBack);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	// Execute the HTTP request
	CURLcode res = curl_easy_perform(curl);
	// Clean up
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	// Check if request was successful
	if (res != CURLE_OK)
	{
		std::cerr << "Failed to perform the HTTP get request: " << curl_easy_strerror(res) << std::endl;
        return false;
    }
	return (true);
}

bool sendToDiscord(const std::string &data)
{
	CURL *curl = curl_easy_init();
	std::string webhook_url = "";

	if (!curl)
	{
		std::cerr << "Failed to initialize the CURL handle\n";
		return (false);
	}
	struct curl_slist *headers = nullptr;
	headers = curl_slist_append(headers, "Content-Type: application/json");


	curl_easy_setopt(curl, CURLOPT_URL, webhook_url.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		std::cerr << "Failed to perform the HTTP post request: " << curl_easy_strerror(res) << std::endl;
        return false;
    }
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return (true);

}


/**
 * [describe function]
*/
bool parseJson(const std::string &jsonResponse, Json::Value &parsedRoot)
{
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	std::string errors;

	bool parsingSuccessful = reader->parse(jsonResponse.c_str(),
							jsonResponse.c_str() + jsonResponse.size(),
							&parsedRoot, &errors);
	if (!parsingSuccessful)
	{
		std::cerr << "Failed to parse JSON: " << errors << std::endl;
        return (false);
	}
	return (true);
}

// std::string formatJson(const Json::Value &parsedRoot)
// {
// 	Json::StyledWriter formatter;
// 	std::string formattedJson = formatter.write(parsedRoot);
// 	return (formattedJson);
// }


std::string convertToJson(const Json::Value &data)
{
	Json::StreamWriterBuilder builder;
	
	const std::string data_as_json_str = Json::writeString(builder, data);
	return (data_as_json_str);
}

int main(void)
{
	std::string api_url = "https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=BTC";
	std::string response;

	// std::string cryptoJson = R"({
    //     "content": "Bitcoin price: $50,000"
    // 	})";

	curl_global_init(CURL_GLOBAL_DEFAULT);
	if (CurlRequest(api_url, response))
	{
		Json::Value root;
		if (parseJson(response, root))
		{
			//std::cout << root << std::endl;
			const Json::Value data = root["data"];
			const Json::Value coin_data_array = data["BTC"];
			const Json::Value coin_data = coin_data_array[0];
			const Json::Value quote_data = coin_data["quote"];
			const Json::Value usd_data = quote_data["USD"];
			const Json::Value price = usd_data["price"];

			//std::string test = convertToJson(usd_data);
			//std::cout << test << std::endl;

			std::string cryptoJson = R"({
        	"content": "Bitcoin price: $)" + price.asString() + R"("
    		})";

			sendToDiscord(cryptoJson);


			// --PRINT KEY_VALUE PAIRS--//
			// for (Json::Value::const_iterator it = usd_data.begin(); it != usd_data.end(); ++it)
			// {
    		// 	const std::string& key = it.key().asString();
    		// 	const Json::Value& value = *it;
    		// 	std::cout << key << ": " << value << std::endl;
			// }


			// for (const Json::Value &entry : usd_data)
			// {
			// 	const Json::Value &value = usd_data[entry];
			// 	std::cout << entry.asString() << std::endl;
			// } 

			
			// for (const Json::Value &data_field : coin_data)
			// {
			// 	std::cout << data_field << std::endl;
			// }
			// if (root.isMember("status"))
			// {
			// 	Json::Value status = root["status"];
			// 	if (status.isMember("error_code"))
			// 	{
			// 		double error_code = status["error_code"].asDouble();
			// 		std::cout << "Status: " << error_code << std::endl;
			// 	}
			// }
		}
	}
	
}




