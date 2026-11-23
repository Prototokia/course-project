// CourseProjectCPP.cpp: определяет точку входа для приложения.
//
#include "CourseProjectCPP.h"

void TryDealDamage(cards::BaseCard& card, combat::ITarget& target)
{
    auto* damageDealer = dynamic_cast<combat::IDamageDealer*>(&card);

    if (damageDealer == nullptr)
    {
        std::cout << "Card " << card.GetName() << " cannot deal damage\n";
        return;
    }

    damageDealer->DealDamage(target);
}

int main()
{
	std::cout << "\n========== Early and Late Binding ==========\n";

	cards::ManaRayCard manaRay;

	cards::BaseCard& baseReference = manaRay;

	std::cout << "\nEarly binding:\n";
	std::cout << "Base reference GetKind(): " << baseReference.GetKind() << '\n';

	std::cout << "Derived reference GetKind(): " << manaRay.GetKind() << '\n';

	std::cout << "\nLate binding:\n";
	std::cout << baseReference.Describe() << '\n';

	std::cout << "\n========== Interfaces and Dynamic Cast ==========\n";

	entities::Player player{ 100, 10, 0 };

	cards::FireballCard fireball;
	cards::BarrierCard barrier;
	cards::MagicIntuitionCard intuition;

	std::cout << "\nInitial player health: " << player.GetCurrentHealth() << '\n';

	std::cout << "\nAttacking with ManaRayCard:\n";

	TryDealDamage(manaRay, player);

	std::cout << "Player health: " << player.GetCurrentHealth() << '\n';

	std::cout << "\nAttacking with FireballCard:\n";

	TryDealDamage(fireball, player);

	std::cout << "Player health: " << player.GetCurrentHealth() << '\n';

	std::cout << "\nChecking cards without IDamageDealer:\n";

	TryDealDamage(barrier, player);
	TryDealDamage(intuition, player);

	std::cout << "\nFinal player health: " << player.GetCurrentHealth() << '\n';

	std::cout << "\n========== Dynamic Configuration ==========\n";

	entities::Player healingPlayer{ 100, 10, 0 };

	healingPlayer.SetCurrentHealth(50);

	std::cout << "Initial health: " << healingPlayer.GetCurrentHealth() << "/" << healingPlayer.GetMaxHealth() << '\n';

	std::cout << "\nStandard healing:\n";

	healingPlayer.Heal(20);

	std::cout << "Health after healing: " << healingPlayer.GetCurrentHealth() << '\n';

	healingPlayer.SetCurrentHealth(50);

	healingPlayer.SetHealingPolicy(std::make_unique<entities::EnhancedHealingPolicy>());

	std::cout << "\nEnhanced healing:\n";

	healingPlayer.Heal(20);

	std::cout << "Health after healing: " << healingPlayer.GetCurrentHealth() << '\n';

	std::cout << "\n========== Exceptions ==========\n";

    entities::Player exceptionPlayer{ 100, 10, 0 };

    std::cout << "\nTesting damage:\n";

    try
    {
        exceptionPlayer.TakeDamage(10);

        std::cout << "Damage applied successfully. HP: " << exceptionPlayer.GetCurrentHealth() << '\n';

        exceptionPlayer.TakeDamage(-5);
    }
    catch (const game::InvalidAmount& error)
    {
        std::cout << "Invalid amount caught: " << error.what() << '\n';
    }
    catch (const std::exception& error)
    {
        std::cout << "Unexpected standard exception: " << error.what() << '\n';
    }

    std::cout << "\nTesting healing:\n";

    try
    {
        exceptionPlayer.Heal(10);

        std::cout << "Healing completed. HP: " << exceptionPlayer.GetCurrentHealth() << '\n';

        exceptionPlayer.Heal(-10);
    }
    catch (const game::InvalidAmount& error)
    {
        std::cout << "Invalid amount caught: " << error.what() << '\n';
    }
    catch (const std::exception& error)
    {
        std::cout << "Unexpected standard exception: " << error.what() << '\n';
    }

    std::cout << "\nTesting card upgrade:\n";

    cards::ManaRayCard upgradeCard{ 1 };

    try
    {
        upgradeCard.Upgrade();

        std::cout << "Card upgraded successfully.\n";

        upgradeCard.Upgrade();
    }
    catch (const game::CardAlreadyUpgraded& error)
    {
        std::cout << "Upgrade error caught: " << error.what() << '\n';
    }
    catch (const std::exception& error)
    {
        std::cout << "Unexpected standard exception: " << error.what() << '\n';
    }

	return 0;
}
