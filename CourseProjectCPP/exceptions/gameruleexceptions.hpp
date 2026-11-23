#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

namespace game
{

class InvalidAmount final : public std::logic_error
{
public:
    explicit InvalidAmount(std::string_view operation, std::int32_t amount)
        : std::logic_error{ std::string{ operation } + " amount cannot be negative: " + std::to_string(amount) }
    {}

    ~InvalidAmount() noexcept override = default;
};

class CardAlreadyUpgraded final : public std::logic_error
{
public:
    explicit CardAlreadyUpgraded(std::string_view cardName)
        : std::logic_error{
            "Card has already been upgraded: " + std::string{ cardName }
    }
    {}

    ~CardAlreadyUpgraded() noexcept override = default;
};

}

