using Microsoft.AspNetCore.Mvc;

namespace ApPlant.Web.Api.Controllers
{
    public class DeviceController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
