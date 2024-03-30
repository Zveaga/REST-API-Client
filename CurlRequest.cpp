
#include"CurlRequest.hpp"

// =========CONSTRUCTORS========= //

/**
 * [describe function]
*/
CurlRequest::CurlRequest()
{
	_symbols = 
	{
		"BTC",
		"ETH",
		"ADA",
		"HNT",
		"YGG",
	};
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
 * [describe function]
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
 * [describe function]
*/
void 	CurlRequest::initWebhook()
{
	_webhook_url = "https://discord.com/api/webhooks/1219633152776208467/CCKCnAmKqdMHC1UBHteE4Xq-ipFj23jMBE-F56aSUgX5V6aAI76r4ycCzJK-pp2eZf14";
}

/**
 * [describe function]
*/
void 	CurlRequest::initApiKey()
{
	_api_key = loadApiKey();
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


// /**
//  * [describe function]
// */
// void 	CurlRequest::setWebhookURL(std::string webhook_url)
// {
// 	_webhook_url = webhook_url;
// }

// ---------------Getters--------------- //
/**CurlRequest
 * [describe function]
*/
std::string CurlRequest::getApiKey() const
{
	return (_api_key);
}

/**
 * [describe function]
*/
std::string CurlRequest::getWebhookURL() const
{
	return (_webhook_url);
}


std::vector<std::string> CurlRequest::getJsonResponses() const
{
	return (_curl_json_responses);
}

// std::vector<std::string> CurlRequest::getSymbols() const
// {
// 	return (_symbols);
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
	// for (const std::string &response: _curl_json_responses)
	// {
	// 	std::cout << response << std::endl;
	// 	std::cout << "\n\n\n\n";
	// }
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


std::string	CurlRequest::loadApiKey()
{
	std::string api_key;
	std::ifstream file("api_key.txt");

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
