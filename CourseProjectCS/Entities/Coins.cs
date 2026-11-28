using CourseProjectCS.Exceptions;
using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Entities {
    internal readonly struct Coins : IEquatable<Coins>, IComparable<Coins> {
        public int Amount { get; }

        public Coins(int amount) {
            if (amount < 0) {
                throw new InvalidAmountException("Количество монет не может быть отрицательным");
            }

            Amount = amount;
        }

        public static Coins operator+(Coins left, Coins right) {
            return new Coins(checked(left.Amount + right.Amount));
        }

        public static bool operator==(Coins left, Coins right) {
            return left.Equals(right);
        }

        public static bool operator!=(Coins left, Coins right) {
            return !left.Equals(right);
        }
        public int CompareTo(Coins other) {
            return Amount.CompareTo(other.Amount);
        }

        public bool Equals(Coins other) {
            return Amount == other.Amount;
        }

        public override int GetHashCode() {
            return Amount.GetHashCode();
        }

        public override bool Equals(object? obj) {
            return obj is Coins other && Equals(other);
        }

        public override string ToString() {
            return $"{Amount} coins";
        }
    }
}
