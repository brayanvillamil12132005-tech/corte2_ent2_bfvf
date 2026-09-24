#include <iostream>
#include <string>
#include <utility>

using namespace std;

enum class Bearing {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Robot {
private:
    pair<int, int> position;
    Bearing bearing;

public:
    Robot(pair<int, int> initial_position, Bearing initial_bearing) 
        : position(initial_position), bearing(initial_bearing) {}

    pair<int, int> get_position() const {
        return position;
    }

    Bearing get_bearing() const {
        return bearing;
    }

    void turn_right() {
        bearing = static_cast<Bearing>((static_cast<int>(bearing) + 1) % 4);
    }

    void turn_left() {
        bearing = static_cast<Bearing>((static_cast<int>(bearing) + 3) % 4);
    }

    void advance() {
        switch (bearing) {
            case Bearing::NORTH: position.second += 1; break; // Y aumenta hacia el Norte
            case Bearing::EAST:  position.first += 1;  break; // X aumenta hacia el Este
            case Bearing::SOUTH: position.second -= 1; break; // Y disminuye hacia el Sur
            case Bearing::WEST:  position.first -= 1;  break; // X disminuye hacia el Oeste
        }
    }

    void execute_instructions(const string& instructions) {
        for (char instruction : instructions) {
            switch (instruction) {
                case 'R': turn_right(); break;
                case 'L': turn_left();  break;
                case 'A': advance();    break;
            }
        }
    }
};

string bearing_to_string(Bearing b) {
    switch (b) {
        case Bearing::NORTH: return "NORTH";
        case Bearing::EAST:  return "EAST";
        case Bearing::SOUTH: return "SOUTH";
        case Bearing::WEST:  return "WEST";
    }
    return "";
}

int main() {
    // Ejemplo enunciado: posición inicial {7, 3} mirando al Norte con instrucciones "RAALAL"
    Robot robot({7, 3}, Bearing::NORTH);
    
    robot.execute_instructions("RAALAL");

    pair<int, int> final_pos = robot.get_position();
    Bearing final_bearing = robot.get_bearing();

    cout << "Posicion final: {" << final_pos.first << ", " << final_pos.second << "}" << endl;
    cout << "Orientacion final: " << bearing_to_string(final_bearing) << endl;

    // Esperado: {9, 4} mirando al WEST
    return 0;
}