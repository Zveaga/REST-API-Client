
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
void 	CurlRequest::initWebhooks()
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



