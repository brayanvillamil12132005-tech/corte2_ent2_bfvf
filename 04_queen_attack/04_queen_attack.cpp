#include <iostream>
#include <utility>
#include <cmath>

using namespace std;

class Queen {
private:
    pair<int, int> position; // {columna, fila} (base 0)

public:
    Queen(int col, int row) {
        if (col < 0 || col >= 8 || row < 0 || row >= 8) {
            throw invalid_argument("La posicion debe estar dentro del tablero (0 a 7)");
        }
        position = {col, row};
    }

    pair<int, int> get_position() const {
        return position;
    }

    bool can_attack(const Queen& other) const {
        // Misma columna
        if (position.first == other.position.first) return true;

        // Misma fila
        if (position.second == other.position.second) return true;

        // Misma diagonal: la diferencia absoluta de filas es igual a la de columnas
        if (abs(position.first - other.position.first) == abs(position.second - other.position.second)) {
            return true;
        }

        return false;
    }
};

int main() {
    try {
        // Ejemplo de la imagen: c5 -> col 2, fila 3 | f2 -> col 5, fila 6
        Queen white_queen(2, 3);
        Queen black_queen(5, 6);

        if (white_queen.can_attack(black_queen)) {
            cout << "Las reinas se pueden atacar entre si." << endl;
        } else {
            cout << "Las reinas NO se pueden atacar." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}