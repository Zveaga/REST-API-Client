
#include"CurlRequest.hpp"

// =========CONSTRUCTORS========= //

/**
 * [describe function]
*/
CurlRequest::CurlRequest()
{

}

// =========DESTRUCTORS========= //

/**
 * [describe function]
*/
CurlRequest::~CurlRequest()
{

}

// --OVERLOADS-- //

// =========MEMBER FUNCTIONS========= //

// ---------------Initializers--------------- //
/**
 * Initilalize the API urls
*/
void CurlRequest::initApiUrls()
{
	_api_urls =  
	{
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=BTC",
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=ETH",
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=ADA",
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=HNT",
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=YGG",		
	};
	
}



/**
 * Initilalize the coins symbols
*/
std::vector<std::string> CurlRequest::extractSymbols()
{
	std::vector<std::string> symbols;

	for (size_t i = 0; i < _api_urls.size(); ++i)
	{
		size_t start = _api_urls[i].find("symbol=");
		if (start != std::string::npos)
		{
			start += 7;
			symbols.push_back(_api_urls[i].substr(start, 3));
		}
		else
		{
			std::cerr << "Coin symbol was not found in URL! Exiting...\n";
			exit(EXIT_FAILURE);
		}
	}
	// for (const std::string &symbol: symbols)
	// 	std::cout << symbol << std::endl;
	return (symbols);
}

/**
 * [describe function]
*/
void 	CurlRequest::initWebhook()
{
	_webhook_url = loadTextFile("webhook.txt");
}

/**
 * [describe function]
*/
void 	CurlRequest::initApiKey()
{
	_api_key = loadTextFile("api_key.txt");
}

bool CurlRequest::initCurlHandle()
{
	_curl = curl_easy_init();
	if (!_curl)
	{
		std::cerr << "Failed to initialize the CURL handle\n";
		return (false);
	}
	return (true);
}

// ---------------Getters--------------- //
/**CurlRequest
 * [describe function]
*/
std::string CurlRequest::getApiKey() const
{
	return (_api_key);
}

std::string CurlRequest::getWebhookURL() const
{
	return (_webhook_url);
}

std::vector<std::string> CurlRequest::getJsonResponses() const
{
	return (_curl_json_responses);
}

// std::vector<Json::Value> CurlRequest::getJsonRoots() const
// {
// 	return (_curl_json_roots);
// }

std::string CurlRequest::getParsedJson()
{
	return(_parsed_json);
}

// ---------------Setters--------------- //
void CurlRequest::setCurlGetOptions()
{
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, curlWriteCallBack);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_curl_json_responses);
}

void CurlRequest::setCurlPostOptions()
{
		
	curl_easy_setopt(_curl, CURLOPT_URL, _webhook_url.c_str());
	curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, _parsed_json.c_str());
}


void CurlRequest::setCurlGetHeaders()
{
	_curl_headers = nullptr;
	_curl_headers = curl_slist_append(_curl_headers, ("X-CMC_PRO_API_KEY: " + _api_key).c_str());
	curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _curl_headers);
}


void CurlRequest::setCurlPostHeaders()
{
	_curl_headers = nullptr;
	_curl_headers = curl_slist_append(_curl_headers, "Content-Type: application/json");
	curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _curl_headers);
}

void CurlRequest::setParsedJson(const std::string &parsed_json)
{
	_parsed_json = parsed_json;
}

// ---------------Actions--------------- //
bool CurlRequest::performCurlRequests()
{
	for (size_t i = 0; i < _api_urls.size(); i++)
	{
		curl_easy_setopt(_curl, CURLOPT_URL, _api_urls[i].c_str());
		// Execute the HTTP request
		CURLcode res = curl_easy_perform(_curl);
		// Check if request was successful
		if (res != CURLE_OK)
		{
			curl_slist_free_all(_curl_headers);
			curl_easy_cleanup(_curl);
			std::cerr << "Failed to perform the HTTP get request: "
				<< curl_easy_strerror(res) << std::endl;
    	    return (false);
    	}
	}

	// Clean up
	curl_slist_free_all(_curl_headers);
	curl_easy_reset(_curl);
	// curl_easy_cleanup(_curl);
	return (true);
}

/**
 * This function will be used by curl to retrieve and store the requested data
*/
size_t CurlRequest::curlWriteCallBack(void *retrieved_content, size_t elem_size, size_t elem_count, void *data)
{
    ((std::vector<std::string>*)data)->emplace_back(static_cast<char*>(retrieved_content), elem_size * elem_count);
    return (elem_size * elem_count);
}

std::string	CurlRequest::loadTextFile(const std::string &file_name)
{
	std::string api_key;
	std::ifstream file(file_name);

	if (file.is_open())
	{
		std::getline(file, api_key);
		file.close();
	}
	return (api_key);
}

bool CurlRequest::sendToDiscord()
{
	CURLcode res = curl_easy_perform(_curl);
	if (res != CURLE_OK)
	{
		std::cerr << "Failed to perform the HTTP post request: " << curl_easy_strerror(res) << std::endl;
        return (false);
	}
	curl_slist_free_all(_curl_headers);
	curl_easy_cleanup(_curl);
	return (true);
}


void CurlRequest::printJsonRoots()
{
	Json::StyledWriter formatter;

	for (const std::string &root: _curl_json_responses)
	{
		//std::string formatted_root = formatter
		std::cout << root;
		std::cout << "\n====================================\n";
	}	
}
