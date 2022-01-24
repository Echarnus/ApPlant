// See https://aka.ms/new-console-template for more information
using Microsoft.Azure.Devices.Client;
using Microsoft.Azure.Devices;
using Microsoft.Azure.Devices.Shared;
using Azure.Messaging.EventHubs;
using Azure.Messaging.EventHubs.Consumer;

string consumerGroup = EventHubConsumerClient.DefaultConsumerGroupName;


var consumerClient = new EventHubConsumerClient("webapp", "Endpoint=sb://ihsuprodblres004dednamespace.servicebus.windows.net/;SharedAccessKeyName=iothubowner;SharedAccessKey=CrvYGl2Edych6myLr3qJpbMWnZEZ8Oy2/lEOTHpHd2s=;EntityPath=iothub-ehub-applant-16323101-1152a1b927");
var tokenSource = new CancellationTokenSource();
var token = tokenSource.Token;
await foreach (var message in consumerClient.ReadEventsAsync(token))
{
    
    Console.WriteLine(message.Data.Properties.FirstOrDefault());
}

Console.Write("");

