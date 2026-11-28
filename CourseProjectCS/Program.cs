using CourseProjectCS.Cards;
using CourseProjectCS.Combat;
using CourseProjectCS.Entities;
using CourseProjectCS.Exceptions;
using CourseProjectCS.Policies;
using CourseProjectCS.Shop;
using CourseProjectCS.Utils;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using CardCollection = System.Collections.Generic.List<CourseProjectCS.Cards.BaseCard>;

namespace CourseProjectCS {
    internal class Program {
        static void Main(string[] args) {
            Console.WriteLine("\n========== Перегрузка методов ==========");

            CardPile searchPile = new CardPile(CardPileType.Deck);

            searchPile.AddCard(new ManaRayCard("Mana Ray", "Наносит 5 урона", 1, 5));

            searchPile.AddCard(new BarrierCard("Barrier", "Даёт 5 защиты", 1, 5));

            searchPile.AddCard(new FireballCard("Fireball", "Наносит 12 урона", 2, 12));

            BaseCard? foundByName = searchPile.FindFirstCard("Mana Ray");

            Console.WriteLine($"Поиск по названию: {foundByName?.Name ?? "Карта не найдена"}");

            BaseCard? foundByType = searchPile.FindFirstCard(CardType.Attack);

            Console.WriteLine($"Поиск по типу: {foundByType?.Name ?? "Карта не найдена"}");

            Console.WriteLine("\n========== Перегрузка операторов ==========");

            Coins balance = new Coins(100);
            Coins reward = new Coins(50);

            Coins total = balance + reward;

            Console.WriteLine($"Баланс + награда: {total}");

            balance += reward;

            Console.WriteLine($"Баланс после +=: {balance}");

            Console.WriteLine($"Баланс равен общей сумме: {(balance == total ? "Да" : "Нет")}");

            Console.WriteLine($"Баланс отличается от награды: {(balance != reward ? "Да" : "Нет")}");

            int comparison = reward.CompareTo(balance);

            if (comparison < 0) {
                Console.WriteLine("Награда меньше баланса.");
            }
            else if (comparison > 0) {
                Console.WriteLine("Награда больше баланса.");
            }
            else {
                Console.WriteLine("Награда равна балансу.");
            }

            Console.WriteLine("\n========== Доступ внутри сборки  ==========");

            CardMetadata metadata = new CardMetadata();

            metadata.FlavorText = "Описание древней магии";

            Console.WriteLine($"Описание метаданных: {metadata.FlavorText}");

            Console.WriteLine("\n========== Обобщённая функция ==========");

            double integerPercent = NumericUtils.Percent(3, 12);

            Console.WriteLine($"Процент для целых чисел: {integerPercent}%");

            double floatingPercent = NumericUtils.Percent(1.5, 6.0);

            Console.WriteLine($"Процент для дробных чисел: {floatingPercent}%");

            // Недопустимый тип: Coins не реализует INumber<Coins>.
            // NumericUtils.Percent(new Coins(3), new Coins(12));

            Console.WriteLine("\n========== Обобщённый класс ==========");

            ShopCatalog<BaseCard> generalShop = new ShopCatalog<BaseCard>();

            generalShop.AddOffer(new ManaRayCard("Mana Ray", "Наносит 5 урона", 1, 5), new Coins(50), 3);

            generalShop.AddOffer(new BarrierCard("Barrier", "Даёт 5 защиты", 1, 5), new Coins(35), 2);

            generalShop.AddOffer(new FireballCard("Fireball", "Наносит 12 урона", 2, 12), new Coins(75), 1);

            List<int> attackOffers = generalShop.FindOffersOf<ManaRayCard>();

            List<int> defenseOffers = generalShop.FindOffersOf<BarrierCard>();

            Console.WriteLine($"Количество предложений с атакующими картами: {attackOffers.Count}");

            Console.WriteLine($"Количество предложений с защитными картами: {defenseOffers.Count}");

            if (attackOffers.Count > 0) {
                int index = attackOffers[0];

                var offer = generalShop[index];

                Console.WriteLine($"Название карты: {offer.cardName}");
                Console.WriteLine($"Цена: {offer.price}");
                Console.WriteLine($"Количество в наличии: {offer.stock}");

                BaseCard? purchasedCard = generalShop.Buy(index);

                if (purchasedCard != null) {
                    Console.WriteLine("Карта успешно приобретена:");
                    Console.WriteLine(purchasedCard.Describe());
                }

                Console.WriteLine($"Остаток после покупки: {generalShop[index].stock}");

                generalShop.Restock(index, 2);

                Console.WriteLine($"Остаток после пополнения: {generalShop[index].stock}");
            }

            ShopCatalog<ManaRayCard> attackShop = new ShopCatalog<ManaRayCard>();

            attackShop.AddOffer(new ManaRayCard("Mana Ray", "Наносит 5 урона", 1, 5), new Coins(50), 2);

            Console.WriteLine($"Количество предложений в каталоге атакующих карт: {attackShop.OfferCount}");

            ShopCatalog<BarrierCard> defenseShop = new ShopCatalog<BarrierCard>();

            defenseShop.AddOffer(new BarrierCard("Barrier", "Даёт 5 защиты", 1, 5), new Coins(35), 2);

            Console.WriteLine($"Количество предложений в каталоге защитных карт: {defenseShop.OfferCount}");

            // Недопустимый тип для шаблонного класса:
            // ShopCatalog<Coins> invalidShop = new ShopCatalog<Coins>();

            // Недопустимый тип для шаблонного метода:
            // generalShop.FindOffersOf<Coins>();
        }
    }
}
