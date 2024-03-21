#ifndef PARSE_JSON_HPP
# define PARSE_JSON_HPP

#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <string>

class ParseJson
{
	private:
		std::vector<std::string>	_json_responses;
		std::string					_prices_as_json;
		std::string					_final_json;
		std::vector<std::string>	_symbols;
		std::vector<std::string>	_prices_as_str;
		std::vector<double>			_prices;
		
	public:
		// --CONSTRUCTORS-- //
		ParseJson(const std::vector<std::string> json_responses);
		// --DESTRUCTORS-- //
		~ParseJson();

		// --OVERLOADS-- //

		// --MEMBER FUNCTIONS-- //
		// -Initializers- //
		void initSymbols();
		// -Getters- ///
		// -Setters- ///
		// -Actions- ///
		bool parseJsonRes();
		double extractPrice(const Json::Value &parsedRoot, const std::string &symbol);
		
		void formatPrice();

		void convertResToJson();
		void formatJsonForDiscord();

		// --NOT USED-- //
		std::string extractPriceAsStr(const Json::Value &parsedRoot, const std::string &symbol);
};









#endif