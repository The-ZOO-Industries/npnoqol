#pragma once

#include "network.hpp"
#include "config.hpp"
#include "enum_chat_formatting.hpp"

#include <string>
#include <vector>
#include <thread>
#include <mutex>

namespace zoo_api
{
    static auto check_apikey(const std::string& api_key)
        -> bool
    {
        try
        {
            const std::string result{
                network::get(
                    "/check_key",
                    network::url::ZOO,
                    {
                        std::format("x-api-key: {}", api_key)
                    }
                )
            };

            if (!nlohmann::json::accept(result))
            {
                return false;
            }

            const nlohmann::json json_response{
                nlohmann::json::parse(result, nullptr, false)
            };

            if (!json_response.value("valid", false))
            {
                return false;
            }

            if (!json_response.value("can_get", false))
            {
                return false;
            }

            config::set<std::string>("api.zoo", api_key);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
}