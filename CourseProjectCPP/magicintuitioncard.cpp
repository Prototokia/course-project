#include "magicintuitioncard.hpp"
#include "player.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace cards
{
MagicIntuitionCard::MagicIntuitionCard()
    : BaseCard{"Magic Intuition", "Draw 1 card immediately", BaseCard::CardType::eTalent, 2, 1}
{
    std::cout << "[MagicIntuitionCard] default-constructed\n";
}

MagicIntuitionCard::MagicIntuitionCard(std::int32_t manaCost)
    : BaseCard{"Magic Intuition", "Draw 1 card immediately", BaseCard::CardType::eTalent, manaCost, 1}
{
    std::cout << "[MagicIntuitionCard] constructed\n";
}

MagicIntuitionCard::MagicIntuitionCard(const MagicIntuitionCard& other)
    : BaseCard{ other }
{
    std::cout << "[MagicIntuitionCard] copy-constructed\n";
}

MagicIntuitionCard::MagicIntuitionCard(MagicIntuitionCard&& other) noexcept
    : BaseCard{ std::move(other) }
{
    std::cout << "[MagicIntuitionCard] move-constructed\n";
}

MagicIntuitionCard& MagicIntuitionCard::operator=(
    const MagicIntuitionCard& other)
{
    if (this == &other)
    {
        return *this;
    }

    BaseCard::operator=(other);

    return *this;
}

MagicIntuitionCard& MagicIntuitionCard::operator=(
    MagicIntuitionCard&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    BaseCard::operator=(std::move(other));

    return *this;
}

MagicIntuitionCard::~MagicIntuitionCard()
{
    std::cout << "[MagicIntuitionCard] destroyed\n";
}

bool MagicIntuitionCard::ApplyEffect(entities::Player& player)
{
    std::int32_t drawnCards = 0;

    for (std::int32_t i = 0; i < GetValue(); i++)
    {
        if (!player.DrawCard())
        {
            break;
        }

        drawnCards++;
    }

    if (drawnCards == 0)
    {
        std::cout << "[MagicIntuitionCard] no cards available.\n";
        return false;
    }

    std::cout << "[MagicIntuitionCard] drew " << drawnCards << " card(s).\n";

    return true;
}

bool MagicIntuitionCard::ApplyUpgrade()
{
    const auto newCost = GetCost() - 1;
    const auto newValue = GetValue() + 1;

    SetCost(newCost);
    SetValue(newValue);

    std::string ability = "Draw " + std::to_string(newValue);
    ability += (newValue == 1) ? " card immediately" : " cards immediately";

    SetTextAbility(ability);

    return true;
}

std::unique_ptr<BaseCard> MagicIntuitionCard::Clone() const
{
    return std::make_unique<MagicIntuitionCard>(*this);
}

std::string MagicIntuitionCard::Describe() const
{
    return BaseCard::Describe()
        + "\nEffect: Draw "
        + std::to_string(GetValue())
        + (GetValue() == 1 ? " card." : " cards.");
}

}