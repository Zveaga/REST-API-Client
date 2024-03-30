#include "Scraper.hpp"
#include "CurlRequest.hpp"
#include "ParseJson.hpp"

int main(void)
{
	CurlRequest curl;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl.initCurlHandle();
	curl.initApiUrls();
	curl.initApiKey();


	curl.setCurlGetOptions();
	curl.setCurlGetHeaders();
	curl.performCurlRequests();
	
	ParseJson parse(curl.getJsonResponses());
	
	parse.initSymbols();
	parse.parseJsonRes();
	parse.formatJsonForDiscord();
	//parse.convertResToJson();
	//parse.formatPrice();
	
	curl.setParsedJson(parse.getParsedJson());
	std::cout << curl.getParsedJson() << std::endl;
	
	curl.initWebhook();
	curl.setCurlPostOptions();
	curl.setCurlPostHeaders();
	curl.sendToDiscord();
	curl_global_cleanup();
	
}




