
#include "ParseJson.hpp"


// =========CONSTRUCTORS========= //
ParseJson::ParseJson(const std::vector<std::string> json_responses): _json_responses(json_responses) {}

// =========DESTRUCTORS========= //
ParseJson::~ParseJson()
{


}

// =========OVERLOADS========= //

// =========MEMBER FUNCTIONS========= //
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
		
		//_prices.push_back(extractPrice(parsedRoot, _symbols[i]));
		_prices_as_str.push_back(extractPriceAsStr(parsedRoot, _symbols[i++]));
		parsedRoot.clear();
	}
	delete reader;

	// for (const std::string &price: _prices)
	// 	std::cout << price << std::endl;
	return (true);
}



double ParseJson::extractPrice(const Json::Value &parsedRoot, const std::string &symbol)
{
	const Json::Value data = parsedRoot["data"];
	const Json::Value coin_data_array = data[symbol];
	const Json::Value coin_data = coin_data_array[0];
	const Json::Value quote_data = coin_data["quote"];
	const Json::Value usd_data = quote_data["USD"];
	const Json::Value price = usd_data["price"];

	return (price.asDouble());
}

void ParseJson::convertResToJson()
{
	Json::Value jsonArray(Json::arrayValue);

	for (const double &price: _prices)
	{
		//std::cout << price << std::endl;
		jsonArray.append(price);
	}
	Json::StyledWriter writer;
	_prices_as_json = writer.write(jsonArray);
	std::cout << _prices_as_json;
}

void ParseJson::formatPrice()
{
	for (size_t i = 0; i < _prices_as_str.size(); i++)
	{
		for (size_t j = 0; j < _prices_as_str[i].length(); j++)
		{
			if (_prices_as_str[i][j] == '.')
			{
				// // price.erase
				j += 3;
				if (j < _prices_as_str[i].length())
				{
					//std::cout << i << std::endl;
					_prices_as_str[i].erase(j, _prices_as_str[i].length());
					break ;
				}
				else
					break ;
			}
		}
		std::cout << _prices_as_str[i];
		std::cout << "\n";
		
	}
}

void ParseJson::formatJsonForDiscord()
{
	Json::Value jsonObject(Json::objectValue);

	for(size_t i = 0; i < _prices_as_str.size() ; i++)
	{
		//std::cout << _symbols[i];
		//std::cout << "\n";

		//std::cout << _prices_as_str[i];
		jsonObject[_symbols[i]] = _prices_as_str[i];
	}
	
	Json::StreamWriterBuilder writer;
	_prices_as_json = Json::writeString(writer, jsonObject);
	std::cout << _prices_as_json << std::endl;
}

// =========NOT USED========= //


std::string ParseJson::extractPriceAsStr(const Json::Value &parsedRoot, const std::string &symbol)
{
	const Json::Value data = parsedRoot["data"];
	const Json::Value coin_data_array = data[symbol];
	const Json::Value coin_data = coin_data_array[0];
	const Json::Value quote_data = coin_data["quote"];
	const Json::Value usd_data = quote_data["USD"];
	const Json::Value price = usd_data["price"];
	return (price.asString());
}
