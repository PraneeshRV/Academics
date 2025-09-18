#include <iostream>
#include <string>
using namespace std;

class Weather {
private:
    string station_id;
    string station_name;
    float humidity;
    float temperature;
    float pressure;

public:
    
    void useDefaultStation() {
        station_id = "dsssd";
        station_name = "22ed";

        cout << "Enter the pressure: ";
        cin >> pressure;
        cout << "Enter the temperature: ";
        cin >> temperature;
        cout << "Enter the humidity: ";
        cin >> humidity;
    }

   
    void enterStationDetails() {
        cout << "Enter station ID: ";
        cin >> station_id;
        cout << "Enter station name: ";
        cin >> station_name;

        cout << "Enter the pressure: ";
        cin >> pressure;
        cout << "Enter the temperature: ";
        cin >> temperature;
        cout << "Enter the humidity: ";
        cin >> humidity;
    }

    void display() {
        if (temperature > 20.0 && temperature < 25.0 &&
            pressure > 1000.0 && pressure < 1020.0 &&
            humidity > 30.0 && humidity < 50.0) {
            cout << "Station ID: " << station_id << "\n";
            cout << "Station name: " << station_name << "\n";
            cout << "Pressure: " << pressure << "\n";
            cout << "Temperature: " << temperature << "\n";
            cout << "Humidity: " << humidity << "\n";
        } else {
            cout << "Conditions are not within the specified ranges, can't display." << endl;
        }
    }
};

int main() {
    Weather w;
    string opt;

    cout << "Do you want the default station (y) or do you want to enter it (n)? ";
    cin >> opt;

    if (opt == "y") {
        w.useDefaultStation();
    } else {
        w.enterStationDetails();
    }

    w.display();

    return 0;
}