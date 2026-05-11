#pragma once

#include <fstream>
#include <sstream>
#include <regex>

#include <nlohmann/json.hpp>

namespace config
{
	inline const std::string path{ "config.json" };

	static auto create()
		-> void
	{
		std::ifstream file{ config::path };
		if (!file.is_open())
		{
			std::ofstream out_file{ config::path };

			const nlohmann::json default_config{
				{
					"api",
					{
						{ "hypixel", "" },
						{ "zoo", "" }
					}
				}
			};

			out_file << default_config.dump(4);
		}
	}

	template<typename type>
	static auto get(const std::string& json_path)
		-> type
	{
		config::create();

		std::ifstream file{ config::path };

		nlohmann::json data{};
		file >> data;

		std::stringstream ss{ json_path };
		std::string segment{};
		nlohmann::json current{ data };

		while (std::getline(ss, segment, '.'))
		{
			if (!current.contains(segment))
			{
				return type{};
			}

			current = current[segment];
		}

		return current.get<type>();
	}

	template<typename type>
	static auto set(const std::string& json_path, const type& value)
		-> void
	{
		config::create();

		std::ifstream file{ config::path };

		nlohmann::json data{};
		file >> data;
		file.close();

		std::stringstream ss{ json_path };
		std::string segment{};
		nlohmann::json* current{ &data };

		std::vector<std::string> segments{};
		while (std::getline(ss, segment, '.'))
		{
			segments.push_back(segment);
		}

		for (std::size_t i{ 0 }; i < segments.size() - 1; ++i)
		{
			current = &(*current)[segments[i]];
		}

		(*current)[segments.back()] = value;

		std::ofstream out_file{ config::path };
		out_file << data.dump(4);
	}
}