using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal class CardPile {
        private readonly List<Card> _cards = [];
        public CardPileType Type { get; }
        public int Count => _cards.Count;
        public Card this[int index] => _cards[index];
        public CardPile(CardPileType type) {
            Type = type;
        }

        public override string ToString() {
            return $"Колода карт: {Type}. Количество карт: {_cards.Count}";
        }
        public void AddCard(Card card) {
            if (card == null) {
                Console.WriteLine("Нельзя добавить null");

                return;
            }
            
            _cards.Add(card);
        }

        public Card? RemoveCardAt(int index) {
            if (index < 0 || index >= _cards.Count) {
                Console.WriteLine("Индекс выходит за границы.");

                return null;
            }
            var removedCard = _cards[index];
            
            _cards.RemoveAt(index);

            return removedCard;
        }

        public Card? DrawCard() {
            if (_cards.Count == 0) {
                Console.WriteLine("Стопка пуста, добирать нечего.");

                return null;
            }
            var drawedCard = _cards[_cards.Count - 1];

            _cards.RemoveAt(_cards.Count - 1);

            return drawedCard;
        }

        public void Shuffle() {
            if (_cards.Count < 2) {
                Console.WriteLine("Слишком мало карт для тасовки");

                return;
            }
            for (int i = _cards.Count - 1; i > 0; i--) {
                int j = Random.Shared.Next(i + 1);

                (_cards[i], _cards[j]) = (_cards[j],  _cards[i]);
            }
        }
    }
}
