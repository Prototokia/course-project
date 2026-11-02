using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal sealed class CardMetadata {
        public string FlavorText { get; set; } = string.Empty;
        public CardMetadata() { }
        public CardMetadata(CardMetadata other) {
            FlavorText = other.FlavorText;
        }
    }
}
