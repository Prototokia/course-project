#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <string_view>

namespace cards 
{

class Card 
{
public:
	enum class CardType
	{
		eNone,
		eAttack,
		eSkill,
		eEffect,
	};

private:
	static constexpr auto BASE_NAME = "noname";
	static constexpr auto BASE_TEXT_ABILITY = "noability";
	static constexpr auto BASE_COST = 0;
	static constexpr auto BASE_VALUE = 0;
	
	std::string m_name{ BASE_NAME };
	std::string m_textAbility{ BASE_TEXT_ABILITY };
	
	CardType m_cardType{ CardType::eNone };

	std::int32_t m_manaCost{ BASE_COST };
	std::int32_t m_value{ BASE_VALUE };

	bool m_isUpgraded{ false };

public:
	Card(std::string_view name, std::string_view textAbility, CardType cardType, std::int32_t cost, std::int32_t value);

	Card()                       = delete;
	Card(const Card&)            = delete;
	Card(Card&&)                 = delete;
	Card& operator=(const Card&) = delete;
	Card& operator=(Card&&)      = delete;
	~Card();

	bool Play(std::int32_t& playerMana);
	bool Upgrade();

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
};

} // namespace cards