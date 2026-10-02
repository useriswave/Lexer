#pragma once

#include <string_view>
#include <optional>
#include <charconv>

namespace Utils {

[[nodiscard]]
constexpr std::optional<double> sv_to_double(std::string_view view)
{
    double number{};
    const auto[ptr, ec] { std::from_chars(view.data(), view.data() + view.size(), number) };

    if (ec == std::errc() && ptr == view.data() + view.size()) {
        return number;
    }

    return {};
}

}
