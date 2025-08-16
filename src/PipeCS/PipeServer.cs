using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PipeCS
{
    public class PipeServer
    {
        private NamedPipeServerStream _server = null;

        private Action<string> _onReceivedMsg = null;

        private bool _stop = false;
        public PipeServer(string pipeName, Action<string> onReceivedMsg)
        {
            _server = new NamedPipeServerStream(pipeName, PipeDirection.InOut, 10, PipeTransmissionMode.Message, PipeOptions.Asynchronous, 1024, 1024);
            _onReceivedMsg = onReceivedMsg;
        }

        public async Task Start()
        {
            while (!_stop)
            {
                Debug.WriteLine("Waiting for client connection...");
                await _server.WaitForConnectionAsync();
                Debug.WriteLine("Client connected.");

                var reader = new StreamReader(_server);

                string message = await reader.ReadLineAsync();
                Debug.WriteLine($"Received from client: {message}");

                _onReceivedMsg?.Invoke(message);

                _server.Disconnect();
            }
        }

        public void Stop()
        {
            _stop = true;
        }
    }
}
