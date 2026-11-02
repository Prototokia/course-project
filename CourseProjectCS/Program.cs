using CourseProjectCS.Cards;
using CourseProjectCS.Entities;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.IO;

using CardCollection = System.Collections.Generic.List<CourseProjectCS.Cards.BaseCard>;

namespace CourseProjectCS {
    internal class Program {
        static void Main(string[] args) {
            Console.WriteLine("===== Демонстрация наследования =====");

            CardCollection cardArray = new CardCollection {
                new ManaRayCard("Луч маны", "Нанесите 5 урона", 1, 5),
                new BarrierCard("Барьер", "Получите 5 защиты", 1, 5),
                new MagicIntuitionCard("Магическая интуиция", "Доберите 1 карту", 2, 1)
            };

            cardArray[0].FlavorText = "Базовое атакующее заклинание";
            cardArray[1].FlavorText = "Базовое оборонительное заклинание";
            cardArray[2].FlavorText = "Мудрость волшебника";

            Console.WriteLine("===== Описание карт =====");

            foreach (var card in cardArray) {
                Console.WriteLine(card.Describe());
                Console.WriteLine($"Дополнительный текст: {card.FlavorText}");
                Console.WriteLine();
            }

            Console.WriteLine("===== Улучшение карт =====");

            foreach (var card in cardArray) {
                card.Upgrade();
            }

            foreach (var card in cardArray) {
                Console.WriteLine(card.Describe());
                Console.WriteLine();
            }

            Console.WriteLine("===== Копирование =====");

            BaseCard original = new ManaRayCard("Копируемая карта", "Наносит 5 урона", 2, 5);

            original.FlavorText = "Исходные метаданные";

            BaseCard shallow = original.ShallowCopy();

            BaseCard deep = original.Clone();

            shallow.FlavorText = "Изменённые метаданные";

            Console.WriteLine($"Оригинал: {original.FlavorText}");
            Console.WriteLine($"Поверхностная копия: {shallow.FlavorText}");
            Console.WriteLine($"Глубокая копия: {deep.FlavorText}");

            Console.WriteLine($"Тип оригинала: {original.GetType().Name}");
            Console.WriteLine($"Тип поверхностной копии: {shallow.GetType().Name}");
            Console.WriteLine($"Тип глубокой копии: {deep.GetType().Name}");

            Console.WriteLine("===== Сравнение карт =====");

            BaseCard first = new ManaRayCard("Тестовая карта", "Описание 1", 1, 5);

            BaseCard second = new ManaRayCard("Тестовая карта", "Описание 2", 1, 10);

            BaseCard third = new BarrierCard("Тестовая карта", "Описание 3", 1, 5);

            Console.WriteLine($"first == second по Equals: {first.Equals(second)}");
            Console.WriteLine($"first == third по Equals: {first.Equals(third)}");

            Console.WriteLine($"Хеш-коды first и second совпадают: {first.GetHashCode() == second.GetHashCode()}");

            var uniqueCards = new HashSet<BaseCard>();

            uniqueCards.Add(first);
            uniqueCards.Add(second);
            uniqueCards.Add(third);

            Console.WriteLine($"Количество уникальных карт в HashSet: {uniqueCards.Count}");

            Console.WriteLine("===== Статическое поле и метод =====");

            BaseCard.PrintCreatedCount();

            Console.WriteLine($"Значение свойства: {BaseCard.CreatedCount}");

            Console.WriteLine("===== Освобождение ресурса =====");

            using (var stream = new MemoryStream()) {
                using (var writter = new StreamWriter(stream, leaveOpen: true)) {
                    foreach (var card in cardArray) {
                        writter.WriteLine(card.Describe());
                    }
                }

                stream.Position = 0;

                using (var reader = new StreamReader(stream, leaveOpen: true)) {
                    Console.WriteLine("Содержимое потока: ");
                    Console.WriteLine(reader.ReadToEnd());
                }
            }
        }
    }
}
