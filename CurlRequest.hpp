#ifndef CURL_REQUEST_HPP
# define CURL_REQUEST_HPP

#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class CurlRequest
{
	private:
		std::vector<std::string> 	_api_urls;
		std::vector<std::string> 	_curl_json_responses;
		std::string 				_api_key;
		std::string 				_webhook_url;
		std::string					_parsed_json;
		CURL						*_curl;
		struct curl_slist 			*_curl_headers;
		std::vector<std::string>	_symbols;

	public:
		// --CONSTRUCTORS-- //
		CurlRequest();

		// --DESTRUCTORS-- //
		~CurlRequest();

		// --OVERLOADS-- //

		// --MEMBER FUNCTIONS-- //

		// -Initializers- //
		void				initApiUrls();
		bool 				initCurlHandle();
		void 				initWebhook();
		void 				initApiKey();
		// void 				setWebhookURL(std::string webhook_url);
		// -Getters- ///
		std::string 		getApiKey() const;
		std::string 		getWebhookURL() const;
		std::string			getParsedJson();
		//std::vector<std::string> getSymbols() const;
		std::vector<std::string> getJsonResponses() const;
		// -Setters- ///
		void 				setCurlGetOptions();
		void 				setCurlGetHeaders();
		void 				setCurlPostOptions();
		void 				setCurlPostHeaders();
		void				setParsedJson(const std::string &parsed_json);
		// -Actions- ///
		bool 				performCurlRequests();
		static size_t 		curlWriteCallBack(void *retrieved_content,
							size_t elem_size, size_t elem_count, void *data);
		std::string			loadTextFile(const std::string &file);

		bool				sendToDiscord();
		

};









#endif