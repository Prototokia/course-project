using CourseProjectCS.Cards;
using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Entities {
    internal class Player {
        private const int MaxHandSize = 10;
        private readonly CardPile _deck = new CardPile(CardPileType.Deck);
        private readonly CardPile _hand = new CardPile(CardPileType.Hand);
        private readonly CardPile _draw = new CardPile(CardPileType.Draw);
        private readonly CardPile _discard = new CardPile(CardPileType.Discard);
        public int MaxHealth { get; private set; }
        public int CurrentHealth { get; private set; }
        public int MaxMana { get; private set; }
        public int CurrentMana { get; private set; }
        public int MaxCoins { get; private set; }
        public int CurrentCoins { get; private set; }

        public Player(int health, int mana, int coins) {
            MaxHealth = health;
            CurrentHealth = MaxHealth;
            MaxMana = mana;
            CurrentMana = MaxMana;
            MaxCoins = coins;
            CurrentCoins = MaxCoins;
        }

        public override string ToString() {
            return $"Характеристики игрока. Текущее здоровье: {CurrentHealth}, Текущая мана: {CurrentMana}, Текущее количество монет: {CurrentCoins}." +
                $"Количество карт в колоде: {_deck.Count}" +
                $"Количество карт в руке: {_hand.Count}" +
                $"Количество карт в доборе: {_draw.Count}" +
                $"Количество карт в сбросе: {_discard.Count}";
        }

        public void TakeDamage(int damageAmount) {
            if (damageAmount < 0) damageAmount = 0;
            
            CurrentHealth -= damageAmount;

            if (CurrentHealth < 0) CurrentHealth = 0;
        }

        public void Heal(int healAmount) {
            if (healAmount < 0) healAmount = 0;

            CurrentHealth += healAmount;

            if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;
        }

        public bool DrawCard() {
            if (_draw.Count == 0) {
                if (_discard.Count == 0) {
                    Console.WriteLine("Стопки добора и сброса пусты. Добирать нечего");

                    return false;
                }

                while (_discard.Count > 0) {
                    var recycledCard = _discard.DrawCard();
                    _draw.AddCard(recycledCard);
                }

                _draw.Shuffle();
            }

            var drawedCard = _draw.DrawCard();

            if (_hand.Count >= MaxHandSize) {
                Console.WriteLine("Рука заполнена!");

                _discard.AddCard(drawedCard);
            }
            else {
                _hand.AddCard(drawedCard);
            }

            return true;
        }

        public bool PlayCard(int cardIndex) {
            if (cardIndex < 0 || cardIndex >= _hand.Count) {
                Console.WriteLine("Индекс карты невалиден.");

                return false;
            }

            var cardToPlay = _hand[cardIndex];
            if (!cardToPlay.CanPlay(CurrentMana)) {
                return false;
            }

            CurrentMana -= cardToPlay.Cost;

            cardToPlay.Play();

            _hand.RemoveCardAt(cardIndex);
            _discard.AddCard(cardToPlay);

            return true;
        }

        public void AddCardToDeck(Card card) {
            _deck.AddCard(card);
        }

        public void PrepareForCombat() {
            for (int i = 0; i < _deck.Count; i++) {
                _draw.AddCard(_deck[i]);
            }
        }
    }
}
