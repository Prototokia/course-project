using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal class Card {
        private bool _isUpgraded = false;
        public string Name { get; private set; } = "";
        public string TextAbility { get; private set; } = "";
        public CardType Type { get; private set; } = CardType.None;
        public int Cost { get; private set; } = default;
        public int Value { get; private set; } = default;

        public Card(string name, string textAbility, CardType type, int cost, int value) {
            Name = name;
            TextAbility = textAbility;
            Type = type;
            Cost = cost;
            Value = value;
        }

        public override string ToString() {
            return $"Карта {Name}, Способность {TextAbility}, Тип {Type}, Цена {Cost}, Значение {Value}";
        }

        public bool Play(ref int playerMana) {
            if (playerMana < Cost) {
                Console.WriteLine("Недостаточно маны");

                return false;
            }

            playerMana -= Cost;

            Console.WriteLine($"Карта {Name} была разыграна. Оставшаяся мана: {playerMana}.");

            return true;
        }

        public bool Upgrade() {
            if (_isUpgraded) {
                Console.WriteLine("Карта уже улучшена!");

                return false;
            }

            _isUpgraded = true;

            Value += 5;

            return true;
        }
    }
}
