#pragma once

#include "network.hpp"
#include "config.hpp"

namespace hypixel_api
{
	static auto check_apikey(const std::string& api_key)
		-> bool
	{
        try
        {
            const std::string result{ network::get(std::format("/v2/key?key={}", api_key), network::url::HYPIXEL) };
            if (nlohmann::json::accept(result))
            {
                const nlohmann::json json_response{ nlohmann::json::parse(result, nullptr, false) };
                if (json_response["cause"] == "Invalid API key")
                {
                    return false;
                }

                config::set<std::string>("api.hypixel", api_key);

                return true;
            }

            return false;
        }
        catch (...)
        {
            return false;
        }
	}
}