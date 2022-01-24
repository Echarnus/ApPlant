using System.ComponentModel;
using System.IO.Ports;
using System.Management;

namespace ApPlant.Configurator.ESP
{
    public partial class MainPage : ContentPage, INotifyPropertyChanged
    {
        private SerialPort _serialPort;

        public string DeviceId { get; set; }
        public string DeviceUserFriendlyName { get; set; }

        private string _ssid;
        public string SSID
        {
            get => _ssid;
            set
            {
                _ssid = value;
                OnPropertyChanged();
            }
        }

        private string _ssidPassword;
        public string SSIDPassword
        {
            get => _ssidPassword;
            set
            {
                _ssidPassword = value;
                OnPropertyChanged();
            }
        }

        private string _log; 
        public string Log
        {
            get => _log;
            set
            {
                _log = value;
                OnPropertyChanged();
            }
        }

        public MainPage()
        {
            InitializeComponent();
            BindingContext = this;
        }

        private void ContentPage_Appearing(object sender, EventArgs e)
        {
            try
            {
                _serialPort = new SerialPort("COM3");
                _serialPort.BaudRate = 9600;
                _serialPort.DataReceived += OnDataReceived;
                _serialPort.Open();
            } catch
            {

            }
        }

        private void ContentPage_Disappearing(object sender, EventArgs e)
        {
            
        }

        private void OnDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var data = _serialPort.ReadLine();
            Log += $"\n{data}";
        }

        private async void Button_Clicked(object sender, EventArgs e)
        {
            try
            {
                _serialPort.WriteLine($"set ssid {SSID}");
                await Task.Delay(500);
                _serialPort.WriteLine($"set ssid_password {SSIDPassword}");
            } catch
            {

            }
        }
    }
}