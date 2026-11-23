using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Exceptions {
    internal sealed class CardAlreadyUpgradedException : Exception {
        public CardAlreadyUpgradedException(string message) : base(message) { }
    }
}
