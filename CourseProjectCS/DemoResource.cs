using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS {
    internal class DemoResource : IDisposable {
        private readonly string _name;
        public DemoResource(string name) {
            _name = name;
            Console.WriteLine($"Открыт ресурс {_name}");
        }
        public void Dispose() {
            Console.WriteLine($"Ресурс {_name} освобожден");
        }

        public void Write(string message) {
            Console.WriteLine(message);
        }
        

    }
}
