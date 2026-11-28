using CourseProjectCS.Cards;
using CourseProjectCS.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Shop {
    internal sealed class ShopCatalog<T> where T : BaseCard {
        private sealed class Offer {
            public T CardTemplate { get; }
            public Coins Price { get; }
            public int Stock { get; set; }

            public Offer(T cardTemplate, Coins price, int stock) {
                CardTemplate = cardTemplate;
                Price = price;
                Stock = stock;
            }
        }

        private readonly List<Offer> _offers = new();

        public int OfferCount => _offers.Count;

        public (string cardName, Coins price, int stock) this[int index] {
            get {
                Offer offer = _offers[index];

                return (offer.CardTemplate.Name, offer.Price, offer.Stock);
            }
        }

        public void AddOffer(T cardTemplate, Coins price, int stock) {
            if (cardTemplate == null)
                throw new ArgumentNullException();

            if (stock < 0) {
                throw new ArgumentOutOfRangeException(nameof(stock));
            }

            BaseCard copy = cardTemplate.Clone();

            if (copy is not T typedCopy) {
                throw new InvalidOperationException();
            }

            _offers.Add(new Offer(typedCopy, price, stock));
        }
        public BaseCard? Buy(int index) {
            Offer offer = _offers[index];

            if (offer.Stock == 0)
                return null;

            BaseCard purchasedCard = offer.CardTemplate.Clone();

            --offer.Stock;

            return purchasedCard;
        }

        public void Restock(int index, int amount) {
            if (amount < 0) {
                throw new ArgumentOutOfRangeException(nameof(amount));
            }

            Offer offer = _offers[index];

            offer.Stock = checked(offer.Stock + amount);
        }

        public List<int> FindOffersOf<U>() where U : T {
            List<int> result = new();

            for (int i = 0; i < _offers.Count; i++) {
                if (_offers[i].CardTemplate is U)
                    result.Add(i);
            }

            return result;
        }
    }
}
