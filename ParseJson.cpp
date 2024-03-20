
#include "ParseJson.hpp"


// --CONSTRUCTORS-- //
ParseJson::ParseJson(const std::vector<std::string> json_responses): _json_responses(json_responses) {}

// --DESTRUCTORS-- //
ParseJson::~ParseJson()
{


}

// --OVERLOADS-- //

// --MEMBER FUNCTIONS-- //
// -Initializers- //

void ParseJson::initSymbols()
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
// -Getters- ///
// -Setters- ///
// -Actions- ///
bool ParseJson::parseJsonRes()
{
	Json::Value parsedRoot;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	int i = 0;

	for (const std::string &response: _json_responses)
	{
		std::string errors;
		bool parsingSuccessful = reader->parse(response.c_str(),
							response.c_str() + response.size(),
							&parsedRoot, &errors);
		if (!parsingSuccessful)
		{
			std::cerr << "Failed to parse JSON: " << errors << std::endl;
    	    return (false);
		}
		
		_prices.push_back(findPrice(parsedRoot, _symbols[i++]));
		parsedRoot.clear();
	}
	delete reader;

	// for (const std::string &price: _prices)
	// 	std::cout << price << std::endl;
	return (true);
}

std::string ParseJson::findPrice(Json::Value &parsedRoot, const std::string &symbol)
{
	const Json::Value data = parsedRoot["data"];
	const Json::Value coin_data_array = data[symbol];
	const Json::Value coin_data = coin_data_array[0];
	const Json::Value quote_data = coin_data["quote"];
	const Json::Value usd_data = quote_data["USD"];
	const Json::Value price = usd_data["price"];

	return (price.asString());
}

void ParseJson::convertResToJson()
{
	Json::Value jsonArray(Json::arrayValue);

	for (const std::string &price: _prices)
		jsonArray.append(price);
	Json::StyledWriter writer;
	_formatted_json = writer.write(jsonArray);
	std::cout << _formatted_json;
}


