#include <iostream>
#include <stdint.h>
using namespace std;

class Processor {
    static const uint8_t REG_COUNT = 4;
    private:
        uint8_t registers[REG_COUNT] {0x00, 0x00, 0x00, 0x00}; 
    public:
        Processor() {
            cout << "Creating processor..." << endl;
        }
        int print_registers() {
            cout << "Registers: ";
            for (int i = 0; i < REG_COUNT; i++) {
                cout << std::hex << (int) registers[i] << " ";
            }
            cout << endl;
            return 0;
        }
};

int main() {
    Processor p;
    p.print_registers();

    cout << 123;

    return 0;
}