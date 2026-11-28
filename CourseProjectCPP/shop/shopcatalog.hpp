#pragma once

#include "cards/basecard.hpp"
#include "entities/coins.hpp"

#include <concepts>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace shop
{
template <typename T> requires std::derived_from<T, cards::BaseCard>
class ShopCatalog
{

private:
	struct Offer
	{
		std::unique_ptr<T> prototype;
		entities::Coins price;
		std::size_t stock;
	};

	std::vector<Offer> m_offers;

public:
	ShopCatalog() = default;

	ShopCatalog(const ShopCatalog&) = delete;
	ShopCatalog& operator=(const ShopCatalog&) = delete;

	ShopCatalog(ShopCatalog&&) noexcept = default;
	ShopCatalog& operator=(ShopCatalog&&) noexcept = default;

	~ShopCatalog() noexcept = default;

	[[nodiscard]] std::size_t GetOfferCount() const
	{
		return m_offers.size();
	}

	[[nodiscard]] const T& GetPrototype(std::size_t index) const
	{
		return *m_offers.at(index).prototype;
	}

	[[nodiscard]] const entities::Coins& GetPrice(std::size_t index) const
	{
		return m_offers.at(index).price;
	}

	[[nodiscard]] std::size_t GetStock(std::size_t index) const
	{
		return m_offers.at(index).stock;
	}

	void AddOffer(std::unique_ptr<T> prototype, entities::Coins price, std::size_t stock)
	{
		if (!prototype)
		{
			throw std::invalid_argument("Cannot add null card to shop");
		}

		m_offers.push_back(Offer{ std::move(prototype), price, stock });
	}

	[[nodiscard]] std::unique_ptr<cards::BaseCard> Buy(std::size_t index)
	{
		auto& offer = m_offers.at(index);

		if (offer.stock == 0)
		{
			return {};
		}

		const cards::BaseCard& card = *offer.prototype;
		auto purchasedCard = card.Clone();

		if (!purchasedCard)
		{
			return {};
		}

		--offer.stock;

		return purchasedCard;

	}

	void Restock(std::size_t index, std::size_t amount)
	{
		auto& offer = m_offers.at(index);
		offer.stock += amount;
	}

	template <typename U> requires std::derived_from<U, T>
	[[nodiscard]] std::vector<std::size_t> FindOffersOf() const
	{
		std::vector<std::size_t> result{};

		for (std::size_t i = 0; i < m_offers.size(); i++)
		{
			if (dynamic_cast<const U*>(m_offers[i].prototype.get()) != nullptr)
			{
				result.push_back(i);
			}
		}

		return result;
	}
};
}