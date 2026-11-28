// CourseProjectCPP.cpp: определяет точку входа для приложения.
//
#include "CourseProjectCPP.h"

int main()
{
    std::cout << "\n========== Function Overloading ==========\n";

    cards::CardPile searchPile{cards::CardPile::CardPileType::eDeck, 2};

    auto searchManaRay = std::make_shared<cards::ManaRayCard>();
    auto searchBarrier = std::make_shared<cards::BarrierCard>();

    searchPile.AddCard(std::weak_ptr<cards::BaseCard>{searchBarrier});
    searchPile.AddCard(std::weak_ptr<cards::BaseCard>{searchManaRay});
    

    auto foundByName = searchPile.FindFirstCard("Barrier").lock();

    if (foundByName)
    {
        std::cout << "Found by name: " << foundByName->GetName() << '\n';
    }

    auto foundByType = searchPile.FindFirstCard(cards::BaseCard::CardType::eAttack).lock();

    if (foundByType)
    {
        std::cout << "Found by type: " << foundByType->GetName() << '\n';
    }

    std::cout << "\n========== Operator Overloading ==========\n";

    entities::Coins balance{ 100 };
    entities::Coins reward{ 50 };

    entities::Coins total = balance + reward;

    std::cout << "Balance + reward: " << total << '\n';

    balance += reward;

    std::cout << "Balance after +=: " << balance << '\n';

    std::cout << std::boolalpha;
    std::cout << "Balance == total: " << (balance == total) << '\n';

    const auto comparison = reward <=> balance;

    if (comparison == std::strong_ordering::less)
    {
        std::cout << "Reward is less than balance.\n";
    }
    else if (comparison == std::strong_ordering::greater)
    {
        std::cout << "Reward is greater than balance.\n";
    }
    else
    {
        std::cout << "Reward equals balance.\n";
    }

    std::cout << "\n========== Friend Output Operator ==========\n";

    entities::Coins displayedCoins{ 250 };

    std::cout << "Player coins: " << displayedCoins << '\n';

    cards::ManaRayCard displayedManaRay;
    cards::BarrierCard displayedBarrier;

    const cards::BaseCard& firstCard = displayedManaRay;
    const cards::BaseCard& secondCard = displayedBarrier;

    std::cout << firstCard << '\n';
    std::cout << secondCard << '\n';

    std::cout << "\n========== Function Template ==========\n";

    const double integerPercent = utils::Percent(3, 12);

    std::cout << "Integer percent: " << integerPercent << "%\n";

    const double floatingPercent = utils::Percent(1.5, 6.0);

    // Недопустимый тип: Coins не удовлетворяет концепту Numeric.
    // utils::Percent(entities::Coins{3}, entities::Coins{12});

    std::cout << "Floating-point percent: " << floatingPercent << "%\n";

    std::cout << "\n========== Class Template ==========\n";

    shop::ShopCatalog<cards::BaseCard> generalShop;

    generalShop.AddOffer(std::make_unique<cards::ManaRayCard>(), entities::Coins{ 50 }, 3);

    generalShop.AddOffer(std::make_unique<cards::BarrierCard>(),entities::Coins{ 35 }, 2);

    generalShop.AddOffer(std::make_unique<cards::FireballCard>(), entities::Coins{ 75 }, 1);

    const auto attackOffers = generalShop.FindOffersOf<cards::ManaRayCard>();

    const auto defenseOffers = generalShop.FindOffersOf<cards::BarrierCard>();

    std::cout << "Attack offers: " << attackOffers.size() << '\n';
    std::cout << "Defense offers: " << defenseOffers.size() << '\n';

    if (!attackOffers.empty())
    {
        const std::size_t index = attackOffers.front();

        std::cout << "Card: " << generalShop.GetPrototype(index).GetName() << '\n';

        std::cout << "Price: " << generalShop.GetPrice(index) << '\n';

        std::cout << "Stock: " << generalShop.GetStock(index) << '\n';

        auto purchasedCard = generalShop.Buy(index);

        if (purchasedCard)
        {
            std::cout << "Purchased card:\n";
            std::cout << *purchasedCard << '\n';
        }

        std::cout << "Stock after purchase: " << generalShop.GetStock(index) << '\n';

        generalShop.Restock(index, 2);

        std::cout << "Stock after restocking: " << generalShop.GetStock(index) << '\n';
    }

    shop::ShopCatalog<cards::ManaRayCard> attackShop;

    attackShop.AddOffer(std::make_unique<cards::ManaRayCard>(), entities::Coins{ 50 }, 2);

    std::cout << "ManaRay catalog offers: " << attackShop.GetOfferCount() << '\n';

    shop::ShopCatalog<cards::BarrierCard> defenseShop;

    defenseShop.AddOffer(std::make_unique<cards::BarrierCard>(), entities::Coins{ 35 }, 2);

    std::cout << "Barrier catalog offers: " << defenseShop.GetOfferCount() << '\n';

    // Недопустимый тип: Coins не наследуется от BaseCard.
    // shop::ShopCatalog<entities::Coins> invalidCatalog;

	return 0;
}
