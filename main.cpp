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
	parse.formatPrice();
	parse.formatJsonForDiscord();
	
	curl.setParsedJson(parse.getParsedJson());
	//std::cout << curl.getParsedJson() << std::endl;
	
	curl.initWebhook();
	curl.setCurlPostOptions();
	curl.setCurlPostHeaders();
	// curl.sendToDiscord();
	if (curl.sendToDiscord())
		std::cout << "Message successfully sent!" << std::endl;
	else
		std::cout << "\nMessage failed to be sent!" << std::endl;
	curl_global_cleanup();
	
}




