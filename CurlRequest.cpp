
#include"CurlRequest.hpp"

// --Conststructors-- //

/**
 * [describe function]
*/
CurlRequest::CurlRequest()
{
	
}

// --Destructor-- //

/**
 * [describe function]
*/
CurlRequest::~CurlRequest()
{

}

// --Overloads-- /

// --Member Functions-- //

/**
 * [describe function]
*/
std::vector<std::string>CurlRequest::initApiUrl()
{
	_api_urls =  
	{
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=BTC",
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=ETH"
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=ADA"
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=HNT"
		"https://pro-api.coinmarketcap.com/v2/cryptocurrency/quotes/latest?symbol=YGG"		
	};
}

/**
 * [describe function]
*/
void 	CurlRequest::initWebhook()
{
	
}

/**
 * [describe function]
*/
void 	CurlRequest::setApiKey(std::string api_key)
{
	_api_key = api_key;
}

/**
 * [describe function]
*/
void 	CurlRequest::setWebhookURL(std::string webhook_url)
{
	_webhook_url = webhook_url;
}

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


/**
 * This function will be used by curl to retrieve and store the requested data
*/
size_t CurlRequest::curlWriteCallBack(void *retrieved_content, size_t elem_size, size_t elem_count, void *data)
{
    ((std::string*)data)->append((char*)retrieved_content, elem_size * elem_count);
    return (elem_size * elem_count);
}

void CurlRequest::setCurlGetOptions()
{

}

void CurlRequest::setCurlPostOptions()
{

}


bool CurlRequest::performCurlRequest(const std::vector<std::string> &api_urls, std::vector<std::string> &curl_json_responses)
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

