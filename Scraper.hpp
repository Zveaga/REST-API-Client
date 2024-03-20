#ifndef SCRAPPER_HPP
# define SCRAPPER_HPP

#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include<iostream>
#include<vector>
#include<string>
#include"ParseJson.hpp"
#include"CurlRequest.hpp"

class Scraper
{
	private:
		std::string retrieved_data_json;
	public:
		// --Conststructors-- //
		Scraper();
		// --Destructor-- //
		~Scraper();

		// --Overloads-- //

		// --Member Functions-- //
		bool sendDataToDiscord(std::vector<std::string> data_to_send);


};









#endif