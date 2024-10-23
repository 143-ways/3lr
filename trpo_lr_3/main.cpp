#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct RadioTechnics {
    int id;
    string name;            // название устройства
    string manufacturer;     // производитель
    string purpose;          // цель устройства
    float frequency;         // частота (Гц)
    double power;            // мощность (Вт)
    double weight;           // вес (кг)
};

// функция для чтения данных из файла
vector<RadioTechnics> readFromFile(const string& filename) {
    ifstream file(filename);
    vector<RadioTechnics> devices;

    if (!file.is_open()) {
        cout << "File opening error!" << endl;
        return devices;
    }

    RadioTechnics device;
    while (file >> device.id >> device.name >> device.manufacturer >> device.purpose
                >> device.frequency >> device.power >> device.weight) {
        devices.push_back(device);
    }

    file.close();
    return devices;
}

// функция для сохранения данных в файл
void saveToFile(const string& filename, const vector<RadioTechnics>& devices) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "File opening error!" << endl;
        return;
    }

    for (const auto& device : devices) {
        file << device.id << " " << device.name << " " << device.manufacturer << " "
             << device.purpose << " " << device.frequency << " " << device.power << " "
             << device.weight << endl;
    }

    file.close();
}

// функция для отображения всех записей
void displayDevices(const vector<RadioTechnics>& devices) {
    for (const auto& device : devices) {
        cout << "ID: " << device.id << ", Name: " << device.name << ", Manufacturer: "
             << device.manufacturer << ", Purpose: " << device.purpose
             << ", Frequency: " << device.frequency << " Hz, Power: "
             << device.power << " W, Weight: " << device.weight << " kg" << endl;
    }
}

// функция для редактирования записи по id
void editDevice(vector<RadioTechnics>& devices, int id) {
    for (auto& device : devices) {
        if (device.id == id) {
            cout << "Enter a new name: "; cin >> device.name;
            cout << "Enter a new manufacturer: "; cin >> device.manufacturer;
            cout << "Enter a new purpose: "; cin >> device.purpose;
            cout << "Enter a new frequency (Hz): "; cin >> device.frequency;
            cout << "Enter a new power (W): "; cin >> device.power;
            cout << "Enter a new weight (Kg): "; cin >> device.weight;
            return;
        }
    }
    cout << "Entry with ID " << id << " not found!" << endl;
}

// функция для добавления новой записи
void addDevice(vector<RadioTechnics>& devices) {
    RadioTechnics device;
    cout << "Enter ID: "; cin >> device.id;
    cout << "Enter name: "; cin >> device.name;
    cout << "Enter manufacturer: "; cin >> device.manufacturer;
    cout << "Enter purpose: "; cin >> device.purpose;
    cout << "Enter frequency (Hz): "; cin >> device.frequency;
    cout << "Enter power (W): "; cin >> device.power;
    cout << "Enter weight (Kg): "; cin >> device.weight;

    devices.push_back(device);
}

// функция для удаления записи по id
void deleteDevice(vector<RadioTechnics>& devices, int id) {
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        if (it->id == id) {
            devices.erase(it);
            return;
        }
    }
    cout << "Entry with ID " << id << " not found!" << endl;
}

// функция для подсчета общего числа записей
void countDevices(const vector<RadioTechnics>& devices) {
    cout << "Total number of entries: " << devices.size() << endl;
}

int main() {
    vector<RadioTechnics> devices;
    string filename;

    cout << "Enter name file to read: ";
    cin >> filename;

    // Чтение данных из файла
    devices = readFromFile(filename);

    if (devices.empty()) {
        cout << "No data to display." << endl;
        return 0;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Show all entry\n";
        cout << "2. Edit entry\n";
        cout << "3. Add entry\n";
        cout << "4. Delete entry\n";
        cout << "5. Count entry\n";
        cout << "6. Save data to file\n";
        cout << "7. Exit\n";
        cout << "Choose an action: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayDevices(devices);
                break;
            case 2: {
                int id;
                cout << "Enter entry ID to edit: ";
                cin >> id;
                editDevice(devices, id);
                break;
            }
            case 3:
                addDevice(devices);
                break;
            case 4: {
                int id;
                cout << "Enter entry ID to delete: ";
                cin >> id;
                deleteDevice(devices, id);
                break;
            }
            case 5:
                countDevices(devices);
                break;
            case 6: {
                cout << "Enter file name to save: ";
                cin >> filename;
                saveToFile(filename, devices);
                break;
            }
            case 7:
                cout << "Exit." << endl;
                break;
            default:
                cout << "Wrong choice. Try again!" << endl;
        }
    } while (choice != 7);

    return 0;
}
