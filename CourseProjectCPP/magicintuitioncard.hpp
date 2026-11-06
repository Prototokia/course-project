#pragma once

#include "basecard.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace cards
{

class MagicIntuitionCard final : public BaseCard
{

public:
    MagicIntuitionCard();
    explicit MagicIntuitionCard(std::int32_t manaCost);

    MagicIntuitionCard(const MagicIntuitionCard& other);
    MagicIntuitionCard(MagicIntuitionCard&& other) noexcept;

    MagicIntuitionCard& operator=(const MagicIntuitionCard& other);
    MagicIntuitionCard& operator=(MagicIntuitionCard&& other) noexcept;

    ~MagicIntuitionCard() override;

    std::unique_ptr<BaseCard> Clone() const override;
    std::string Describe() const override;

private:
    bool ApplyEffect(entities::Player& player) override;
    bool ApplyUpgrade() override;
};

}
