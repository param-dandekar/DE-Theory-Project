#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


map<string, int> get_codes() {
    map<string, int> codes;
    codes["NOP"]  = 0x0;
    codes["LDA"]  = 0x1;
    codes["LDB"]  = 0x2;
    codes["LDC"]  = 0x3;
    codes["LDIA"] = 0x4;
    codes["LDIB"] = 0x5;
    codes["LDIC"] = 0x6;
    codes["STA"]  = 0x7;
    codes["STB"]  = 0x8;
    codes["STC"]  = 0x9;
    codes["ADD"]  = 0xA;
    codes["SUB"]  = 0xB;
    codes["JMP"]  = 0xC;
    codes["JMNZ"] = 0xD;
    codes["SWP"]  = 0xE;
    codes["SWPC"] = 0xF;

    return codes;
}

int parse_line(string current_line, map<string, int> codes) {
    int n = current_line.length();
    if (n == 0) return 0;
    bool reading_instruction = true;
    string instruction = "", data = "";
    for (int i = 0; i < n; i++) {
        char c = current_line[i];
        if (c == ' ') {
            reading_instruction = false;
            continue;
        }
        if (reading_instruction) {
            instruction += c;
        }
        else {
            data += c;
        }
    }
    
    uint8_t ins_hex = codes[instruction];
    if (ins_hex == 0) return 0;

    uint16_t data_hex;
    if (data.length()) data_hex = std::stoul(data, nullptr, 16);

    return (ins_hex << 12) + data_hex;
}

void assemble(string program_file_name, string extension) {
    ifstream program_file((program_file_name+"."+extension).c_str());
    ofstream assembled_file((program_file_name+".bin").c_str());
    string current_line;
    uint64_t next_instruction;
    
    while (getline(program_file, current_line)) {
        next_instruction = parse_line(current_line, get_codes());
        // cout << next_instruction << endl;
        assembled_file << next_instruction << endl;
    }
}