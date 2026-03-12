#pragma once

#include <string>
#include <format>
#include <unordered_map>

#include <curl/curl.h>

namespace network
{
	inline const std::string hypixel_url{ "https://api.hypixel.net" };

	enum class url : std::int8_t
	{
		HYPIXEL
	};

	inline const std::unordered_map<network::url, std::string> url_to_string =
	{
		{ network::url::HYPIXEL, "https://api.hypixel.net" }
	};

	static auto write_callback(void* contents, std::size_t size, std::size_t nmemb, void* userp)
		-> std::size_t
	{
		std::size_t total_size{ size * nmemb };
		std::string* string{ static_cast<std::string*>(userp) };

		string->append(static_cast<char*>(contents), total_size);

		return total_size;
	}

	static auto get(const std::string& endpoint, const network::url url_type)
		-> std::string
	{
		const std::string url{ std::format("{}{}", network::url_to_string.at(url_type), endpoint) };

		std::string response{};
		CURL* curl{ curl_easy_init() };

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, network::write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		const CURLcode result{ curl_easy_perform(curl) };
        curl_easy_cleanup(curl);

		if (result == CURLE_OK)
		{
			return response;
		}

        return {};
	}
}