using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace CourseProjectCS.Utils {
    internal static class NumericUtils {
        public static double Percent<T>(T part, T whole) where T : INumber<T> {
            if (whole == T.Zero)
                throw new DivideByZeroException("Деление на ноль");

            return 100.0 * double.CreateChecked(part) / double.CreateChecked(whole);
        }
    }
}
