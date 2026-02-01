#pragma once

#include <filesystem>
#include <fstream>

class ChatUtil final
{
public:
	ChatUtil();

	~ChatUtil();

	auto Update() -> void;

	static auto GetNewLines() -> std::vector<std::string>;

private:
	inline static std::vector<std::string> newLines{};
	inline static std::vector<std::string> allLines{};

	std::filesystem::path logFilePath;
};