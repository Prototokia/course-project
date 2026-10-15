using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal class Card {
        private bool _isUpgraded;
        public string Name { get; private set; } 
        public string TextAbility { get; private set; } 
        public CardType Type { get; private set; } 
        public int Cost { get; private set; } 
        public int Value { get; private set; } 

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

        public bool CanPlay(int availableMana) {
            if (availableMana < Cost) {
                Console.WriteLine("Недостаточно маны");

                return false;
            }

            return true;
        }

        public void Play() {
            Console.WriteLine($"Карта {Name} была сыграна");
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
