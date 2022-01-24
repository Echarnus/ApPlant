using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Devices.Client;
using System.Text;

namespace ApPlant.Web.Api.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class SimulatorController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        private static Random rnd = new Random();

        public SimulatorController(IConfiguration configuration)
        {
            this._configuration = configuration;
        }

        [HttpGet]
        public async Task Get()
        {
            DeviceClient deviceClient = DeviceClient.CreateFromConnectionString(_configuration.GetConnectionString("PlantSimulator"), TransportType.Amqp);
            
            var temperature = rnd.Next(20, 35);
            var humidity = rnd.Next(60, 80);
            var dataBuffer = string.Format("{{\"temperature\":{0},\"humidity\":{1}}}", temperature, humidity);
            Message eventMessage = new Message(Encoding.UTF8.GetBytes(dataBuffer));
            eventMessage.Properties.Add("temperatureAlert", (temperature > 30) ? "true" : "false");
            await deviceClient.SendEventAsync(eventMessage).ConfigureAwait(false);
        }
    }
}
