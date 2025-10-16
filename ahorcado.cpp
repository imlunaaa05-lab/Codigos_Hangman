#include <iostream>
#include <cstdlib>   
#include <ctime>
#include <cctype>     

using namespace std;

// Declaración de estructuras de datos
char palabras[10][50] = {
    "GATO", "PERRO", "CASA", "SOL", "LUNA",
    "ARBOL", "RATON", "NUBE", "CIELO", "FLOR"
};

// Variables de control inicializadas
char palabraSecreta[50];
char estadoPalabra[50];
char letrasIntentadas[26];
int intentosRestantes = 6;
int totalIntentos = 0;
bool victoria = false;
int longitud = 0;

// Función de selección e inicialización de palabra
void seleccionarPalabra() {
    srand(time(0));
    int indice = rand() % 10;
    int i = 0;
    
    while (palabras[indice][i] != '\0') {
        palabraSecreta[i] = palabras[indice][i];
        i++;
    }
    palabraSecreta[i] = '\0';
    
    // Calcular longitud
    longitud = 0;
    while (palabraSecreta[longitud] != '\0') {
        longitud++;
    }
    
    // Inicializar estado del juego
    for (int j = 0; j < longitud; j++) {
        estadoPalabra[j] = '_';
    }
    estadoPalabra[longitud] = '\0';
}

// Función básica de visualización
void mostrarEstado() {
    cout << "\n=== JUEGO DEL AHORCADO ===" << endl;
    cout << "Palabra: ";
    for (int i = 0; i < longitud; i++) {
        cout << estadoPalabra[i] << " ";
    }
    cout << endl;
    cout << "Intentos restantes: " << intentosRestantes << endl;
    cout << "Letras usadas: ";
    for (int i = 0; i < totalIntentos; i++) {
        cout << letrasIntentadas[i] << " ";
    }
    cout << endl;
}

// Sistema completo de validación
bool validarEntrada(char letra) {
    // Validación específica para números
    if (letra >= '0' && letra <= '9') {
        cout << "Error: No puedes ingresar números, solo letras del abecedario" << endl;
        return false;
    }
    
    // Validación de entrada de usuario para letras
    if (!(letra >= 'A' && letra <= 'Z')) {
        cout << "Error: Solo letras del abecedario están permitidas" << endl;
        return false;
    }
    
    // Control de letras repetidas
    for (int i = 0; i < totalIntentos; i++) {
        if (letrasIntentadas[i] == letra) {
            cout << "Ya intentaste con '" << letra << "'. Intenta otra." << endl;
            return false;
        }
    }
    
    return true;
}

// Verificación de letra y actualización de estado
bool procesarLetra(char letra) {
    letrasIntentadas[totalIntentos] = letra;
    totalIntentos++;
    
    bool acierto = false;
    // Búsqueda en palabra secreta
    for (int i = 0; palabraSecreta[i] != '\0'; i++) {
        if (palabraSecreta[i] == letra) {
            estadoPalabra[i] = letra;
            acierto = true;
        }
    }
    
    if (acierto) {
        cout << "¡Bien! La letra '" << letra << "' está en la palabra." << endl;
    } else {
        cout << "Fallaste. La letra '" << letra << "' no está." << endl;
        intentosRestantes--;
    }
    
    return acierto;
}

// Verificación de fin de juego
bool verificarVictoria() {
    for (int i = 0; estadoPalabra[i] != '\0'; i++) {
        if (estadoPalabra[i] == '_') {
            return false;
        }
    }
    return true;
}

// Función para reiniciar variables del juego
void reiniciarJuego() {
    intentosRestantes = 6;
    totalIntentos = 0;
    victoria = false;
    for (int i = 0; i < 26; i++) {
        letrasIntentadas[i] = '\0';
    }
}

int main() {
    char jugarOtra;
    
    do {
        // Inicialización del estado del juego
        reiniciarJuego();
        seleccionarPalabra();
        
        cout << "\n¡Bienvenido al juego del ahorcado!" << endl;
        cout << "Adivina la palabra de " << longitud << " letras" << endl;
        
        // Bucle principal del juego
        while (intentosRestantes > 0 && !victoria) {
            mostrarEstado();
            
            char letra;
            cout << "\nIngresa una letra: ";
            cin >> letra;
            if (cin.peek() != '\n') {
            cout << "Error: Solo puedes ingresar UNA letra." << endl;
            cin.ignore(1000, '\n');
                continue;
            }

            letra = toupper(letra);
            
            if (!validarEntrada(letra)) {
                continue;
            }
            
            procesarLetra(letra);
            victoria = verificarVictoria();
            
            if (victoria) {
                cout << "\n¡FELICIDADES! Adivinaste la palabra: " << palabraSecreta << endl;
                break;
            }
            
            if (intentosRestantes == 0) {
                cout << "\nPERDISTE. La palabra era: " << palabraSecreta << endl;
                break;
            }
        }
        
        // Opción de volver a jugar
        cout << "\n¿Quieres jugar otra vez? (S/N): ";
        cin >> jugarOtra;
        jugarOtra = toupper(jugarOtra);
        
    } while (jugarOtra == 'S');
    
    cout << "¡Gracias por jugar!" << endl;
    return 0;
}
