#ifndef PARSE_JSON_HPP
# define PARSE_JSON_HPP

#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class ParseJson
{
	private:
		std::vector<std::string>	_json_responses;
		std::vector<Json::Value>	_json_roots;
		std::string					_prices_as_json;
		std::string					_final_json;
		std::vector<std::string>	_symbols;
		std::vector<std::string>	_prices_as_str;
		std::vector<double>			_prices;
		
	public:
		// --CONSTRUCTORS-- //
		ParseJson(const std::vector<std::string> json_responses);
		ParseJson(const std::vector<Json::Value> json_roots);

		// --DESTRUCTORS-- //
		~ParseJson();

		// --OVERLOADS-- //

		// --MEMBER FUNCTIONS-- //
		// -Initializers- //
		void initSymbols(const std::vector<std::string> symbols);
		// -Getters- ///
		std::string getParsedJson();
		// -Setters- ///
		// -Actions- ///
		bool parseJsonRes();
		double extractPrice(const Json::Value &parsedRoot, const std::string &symbol);
		
		std::string setPrecision(double price, int precision);
		void formatPrice();

		void convertResToJson();
		void formatJsonForDiscord();
		void printJsonRoot(const Json::Value &root);

		
		
		// --NOT USED-- //
		std::string extractPriceAsStr(const Json::Value &parsedRoot, const std::string &symbol);


};









#endif