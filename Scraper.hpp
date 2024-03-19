#ifndef SCRAPPER_HPP
# define SCRAPPER_HPP

#include<iostream>
#include<vector>
#include<string>

class Scraper
{
	private:
		const std::string api_key;
		const std::string api_key;


	
	public:
		// --Conststructors-- //
		Scraper();
		Scraper(std::);
		// --Destructor-- //
		~Scraper();

		// --Overloads-- //

		// --Member Functions-- //
		std::vector<std::string>	initURLs();
		void 						initWebhooks();
		void 						setApiKey();
		void 						setWebhookURL();
		std::string 				getApiKey();
		std::string 				getWebhookURL();


};









#endif