#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace entities
{
	class Player;
}
namespace cards
{

struct CardMetadata
{
    std::string flavorText;
};

class BaseCard;

class CardReceiver
{
public:
    void Receive(const BaseCard& card) const;
};

class BaseCard
{
public:
	enum class CardType
	{
		eNone,
		eAttack,
		eSkill,
		eTalent,
	};

private:
	static constexpr auto BASE_NAME = "noname";
	static constexpr auto BASE_TEXT_ABILITY = "noability";
	static constexpr auto BASE_COST = 0;
	static constexpr auto BASE_VALUE = 0;

	inline static std::int32_t m_createdCount = 0;

	std::string m_name{ BASE_NAME };
	std::string m_textAbility{ BASE_TEXT_ABILITY };
	CardType m_cardType{ CardType::eNone };
	std::int32_t m_manaCost{ BASE_COST };
	std::int32_t m_value{ BASE_VALUE };
	bool m_isUpgraded{ false };

    std::shared_ptr<CardMetadata> m_metadata{ std::make_shared<CardMetadata>() };
public:
	BaseCard(std::string_view name, std::string_view textAbility, CardType cardType, std::int32_t cost, std::int32_t value);
	BaseCard();
	virtual ~BaseCard();

	bool Play(entities::Player& player);
	bool Upgrade();

	virtual std::unique_ptr<BaseCard> Clone() const = 0;
	virtual std::string Describe() const;

    void SendTo(CardReceiver& receiver) const;

    [[nodiscard]] static std::int32_t GetCreatedCount()
    {
        return m_createdCount;
    }
	
    [[nodiscard]] std::string_view GetName() const
    {
        return m_name;
    }

    [[nodiscard]] std::string_view GetTextAbility() const
    {
        return m_textAbility;
    }

    [[nodiscard]] CardType GetCardType() const
    {
        return m_cardType;
    }

    [[nodiscard]] std::int32_t GetCost() const
    {
        return m_manaCost;
    }

    [[nodiscard]] std::int32_t GetValue() const
    {
        return m_value;
    }

    [[nodiscard]] std::shared_ptr<CardMetadata> ShareMetadata() const
    {
        return m_metadata;
    }

    void SetName(std::string_view name)
    {
        m_name = name;
    }

    void SetTextAbility(std::string_view textAbility)
    {
        m_textAbility = textAbility;
    }

    void SetCardType(CardType cardType)
    {
        m_cardType = cardType;
    }

    void SetCost(std::int32_t manaCost)
    {
        m_manaCost = manaCost;
    }

    void SetValue(std::int32_t value)
    {
        m_value = value;
    }



protected:
    BaseCard(const BaseCard& other);
    BaseCard(BaseCard&& other) noexcept;
    BaseCard& operator=(const BaseCard& other);
    BaseCard& operator=(BaseCard&& other) noexcept;

    virtual bool ApplyEffect(entities::Player& player) = 0;
    virtual bool ApplyUpgrade() = 0;

    std::string Header() const;

    [[nodiscard]] bool isUpgraded() const {
        return m_isUpgraded;
    }
};

}