#include <iostream>
using namespace std;

double celsiusToFahrenheit(double celsius) {
    return (celsius * 9 / 5) + 32;
}

double celsiusToKelvin(double celsius) {
    return celsius + 273.15;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

double fahrenheitToKelvin(double fahrenheit) {
    return (fahrenheit - 32) * 5 / 9 + 273.15;
}

double kelvinToCelsius(double kelvin) {
    return kelvin - 273.15;
}

double kelvinToFahrenheit(double kelvin) {
    return (kelvin - 273.15) * 9 / 5 + 32;
}

int main() {
    double temperature;
    int choice;

    cout << "Temperature Conversion Program" << endl;
    cout << "1. Celsius to Fahrenheit" << endl;
    cout << "2. Celsius to Kelvin" << endl;
    cout << "3. Fahrenheit to Celsius" << endl;
    cout << "4. Fahrenheit to Kelvin" << endl;
    cout << "5. Kelvin to Celsius" << endl;
    cout << "6. Kelvin to Fahrenheit" << endl;
    cout << "Enter your choice (1-6): ";
    cin >> choice;

    cout << "Enter the temperature value: ";
    cin >> temperature;

    switch (choice) {
        case 1:
            cout << temperature << " Celsius = " << celsiusToFahrenheit(temperature) << " Fahrenheit" << endl;
            break;
        case 2:
            cout << temperature << " Celsius = " << celsiusToKelvin(temperature) << " Kelvin" << endl;
            break;
        case 3:
            cout << temperature << " Fahrenheit = " << fahrenheitToCelsius(temperature) << " Celsius" << endl;
            break;
        case 4:
            cout << temperature << " Fahrenheit = " << fahrenheitToKelvin(temperature) << " Kelvin" << endl;
            break;
        case 5:
            cout << temperature << " Kelvin = " << kelvinToCelsius(temperature) << " Celsius" << endl;
            break;
        case 6:
            cout << temperature << " Kelvin = " << kelvinToFahrenheit(temperature) << " Fahrenheit" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
    }

    return 0;
}

