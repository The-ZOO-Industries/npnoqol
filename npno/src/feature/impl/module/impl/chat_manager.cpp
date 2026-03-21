#include "chat_manager.hpp"

npno::chat_manager::chat_manager()
    : npno::module{ true }
{
    this->blacklisted_lines = config::blacklisted_lines;
    this->auto_gg_lines = config::auto_gg_lines;
}

npno::chat_manager::~chat_manager() = default;

auto npno::chat_manager::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
    -> bool
{
    const std::string message{ chat_component->get_unformatted_text() };

    this->watchdog_lover(message);
    this->auto_gg(message);
    this->welcome_guild(message);
    this->boop_friend(message);

    for (const std::regex& blacklisted_line : this->blacklisted_lines)
    {
        if (std::regex_search(message, blacklisted_line))
        {
            return true;
        }
    }

    return false;
};

auto npno::chat_manager::watchdog_lover(const std::string& text) const
    -> void
{
    static std::chrono::time_point<std::chrono::steady_clock> last_sent_time{ std::chrono::steady_clock::now() - std::chrono::seconds{ 5 } };

    const std::chrono::time_point<std::chrono::steady_clock> now{ std::chrono::steady_clock::now() };
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_sent_time).count() < 5)
    {
        return;
    }

    if (text == "[WATCHDOG ANNOUNCEMENT]")
    {
        mc->get_the_player()->send_chat_message("/ac Thank you Watchdog! <3");
    }
}

auto npno::chat_manager::auto_gg(const std::string& text) const 
    -> void
{
    static std::chrono::time_point<std::chrono::steady_clock> last_sent_time{ std::chrono::steady_clock::now() - std::chrono::seconds{ 5 } };

    const std::chrono::time_point<std::chrono::steady_clock> now{ std::chrono::steady_clock::now() };
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_sent_time).count() < 5)
    {
        return;
    }

    for (const std::regex& auto_gg_line : this->auto_gg_lines)
    {
        if (std::regex_search(text, auto_gg_line))
        {
            mc->get_the_player()->send_chat_message(std::format("/ac {}", this->random_case("good game")));
            last_sent_time = now;
            break;
        }
    }
}

auto npno::chat_manager::welcome_guild(const std::string& text) const
    -> void
{
    static std::chrono::time_point<std::chrono::steady_clock> last_sent_time{ std::chrono::steady_clock::now() - std::chrono::seconds{ 5 } };

    const std::chrono::time_point<std::chrono::steady_clock> now{ std::chrono::steady_clock::now() };
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_sent_time).count() < 5)
    {
        return;
    }

    const std::string prefix{ "Guild > " };
    const std::string suffix{ " joined." };

    if (text.starts_with(prefix))
    {
        const std::size_t start{ prefix.size() };
        const std::size_t end{ text.find(suffix, start) };

        if (end != std::string::npos)
        {
            const std::string name{ text.substr(start, end - start) };
            mc->get_the_player()->send_chat_message(std::format("/gc {} o/", name));
        }
    }
}

auto npno::chat_manager::boop_friend(const std::string& text) const
    -> void
{
    static std::chrono::time_point<std::chrono::steady_clock> last_sent_time{ std::chrono::steady_clock::now() - std::chrono::seconds{ 5 } };

    const std::chrono::time_point<std::chrono::steady_clock> now{ std::chrono::steady_clock::now() };
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_sent_time).count() < 5)
    {
        return;
    }

    const std::string prefix{ "Friend > " };
    const std::string suffix{ " joined." };

    if (text.starts_with(prefix))
    {
        const std::size_t start{ prefix.size() };
        const std::size_t end{ text.find(suffix, start) };

        if (end != std::string::npos)
        {
            const std::string name{ text.substr(start, end - start) };
            mc->get_the_player()->send_chat_message(std::format("/boop {}", name));
        }
    }
}

auto npno::chat_manager::random_case(const std::string& text) const
    -> std::string
{
    std::string result{};
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<int> dist{ 0, 1 };

    for (const auto& c : text)
    {
        if (std::isalpha(c))
        {
            if (dist(gen) == 0)
            {
                result += std::tolower(c);
            }
            else
            {
                result += std::toupper(c);
            }
        }
        else
        {
            result += c;
        }
    }

    return result;
}