#pragma once

#include "network.hpp"

#include <nlohmann/json.hpp>

namespace hypixel_api
{
    inline std::string current_api_key{};

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

                hypixel_api::current_api_key = api_key;
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