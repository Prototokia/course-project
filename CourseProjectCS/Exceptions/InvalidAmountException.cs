using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Exceptions {
    internal sealed class InvalidAmountException : Exception {
        public InvalidAmountException(string message) : base(message) { }

    }
}
