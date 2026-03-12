#include "chat_manager.hpp"

npno::chat_manager::chat_manager()
    : npno::module{ true }
{
    this->blacklisted_lines = config::blacklisted_lines;
}

npno::chat_manager::~chat_manager() = default;

auto npno::chat_manager::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
    -> bool
{
    const std::string message{ chat_component->get_unformatted_text() };

    for (const std::regex& blacklisted_line : this->blacklisted_lines)
    {
        if (std::regex_search(message, blacklisted_line))
        {
            return true;
        }
    }

    return false;
};