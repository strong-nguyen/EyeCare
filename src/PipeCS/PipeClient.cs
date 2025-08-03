using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PipeCS
{
    public class PipeClient
    {
        public PipeClient()
        {
            var client = new NamedPipeClientStream(".", "mypipe", PipeDirection.InOut);
            client.Connect();
            Console.WriteLine("Connected to server.");

            var reader = new StreamReader(client);
            var writer = new StreamWriter(client) { AutoFlush = true };

            writer.WriteLine("Hello from client!");
            string response = reader.ReadLine();
            Console.WriteLine($"Received from server: {response}");
        }
    }
}
