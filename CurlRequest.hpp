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
		std::vector<std::string> 	_symbols;
		std::vector<std::string> 	_curl_json_responses;
		// std::vector<Json::Value> 	_curl_json_roots;
		std::string 				_api_key;
		std::string 				_webhook_url;
		std::string					_parsed_json;
		CURL						*_curl;
		struct curl_slist 			*_curl_headers;

	public:
		// --CONSTRUCTORS-- //
		CurlRequest();

		// --DESTRUCTORS-- //
		~CurlRequest();

		// --OVERLOADS-- //

		// --MEMBER FUNCTIONS-- //

		// -Initializers- //
		void				initApiUrls();
		std::vector<std::string> extractSymbols();

		bool 				initCurlHandle();
		void 				initWebhook();
		void 				initApiKey();
		// -Getters- //
		std::string 		getApiKey() const;
		std::string 		getWebhookURL() const;
		std::string			getParsedJson();
		std::vector<std::string> getJsonResponses() const;
		// std::vector<Json::Value> getJsonRoots() const;

		// -Setters- //
		void 				setCurlGetOptions();
		void 				setCurlGetHeaders();
		void 				setCurlPostOptions();
		void 				setCurlPostHeaders();
		void				setParsedJson(const std::string &parsed_json);
		// -Actions- //
		bool 				performCurlRequests();
		static size_t 		curlWriteCallBack(void *retrieved_content,
							size_t elem_size, size_t elem_count, void *data);
		std::string			loadTextFile(const std::string &file);
		void 				printJsonRoots();


		bool				sendToDiscord();
		

};









#endif