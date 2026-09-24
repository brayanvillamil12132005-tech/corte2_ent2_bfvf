#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

class Spreadsheet {
private:
    // Mapea la referencia de la celda (ej: "A1", "B10") a su valor entero
    unordered_map<string, int> cells;

    // Función auxiliar para parsear un operando (sea un número directo o la referencia a una celda)
    int parseOperand(const string& token) {
        if (token.empty()) return 0;
        
        // Si el primer carácter es un número, convertimos el string a entero directamente
        if (isdigit(token[0])) {
            return stoi(token);
        }
        
        // Si es una referencia de celda (ej: "A1"), buscamos su valor
        if (cells.find(token) != cells.end()) {
            return cells[token];
        }
        
        // Si no se ha configurado explícitamente con setCell, se asume 0
        return 0;
    }

public:
    Spreadsheet(int rows) {
        // Inicialización de la hoja de cálculo
    }

    void setCell(string cell, int value) {
        cells[cell] = value;
    }

    void resetCell(string cell) {
        cells.erase(cell); // O asignamos 0 / eliminamos la llave
    }

    int getValue(string formula) {
        // La fórmula siempre tiene el formato "=X+Y"
        // Eliminamos el signo '=' inicial
        string expr = formula.substr(1);
        
        // Buscamos la posición del '+'
        size_t plusPos = expr.find('+');
        
        string tokenX = expr.substr(0, plusPos);
        string tokenY = expr.substr(plusPos + 1);

        int valX = parseOperand(tokenX);
        int valY = parseOperand(tokenY);

        return valX + valY;
    }
};

int main() {
    Spreadsheet spreadsheet(3);

    // Pruebas basándonos en el Ejemplo 1
    cout << "getValue(\"=5+7\"): " << spreadsheet.getValue("=5+7") << " (Esperado: 12)" << endl;

    spreadsheet.setCell("A1", 10);
    cout << "getValue(\"=A1+6\"): " << spreadsheet.getValue("=A1+6") << " (Esperado: 16)" << endl;

    spreadsheet.setCell("B2", 15);
    cout << "getValue(\"=A1+B2\"): " << spreadsheet.getValue("=A1+B2") << " (Esperado: 25)" << endl;

    spreadsheet.resetCell("A1");
    cout << "getValue(\"=A1+B2\"): " << spreadsheet.getValue("=A1+B2") << " (Esperado: 15)" << endl;

    return 0;
}