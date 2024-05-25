
int t_inicial = 500; // Periodo de medio segundo en milisegundos
int contador = 0;
int totalRevoluciones = 0; // Variable para almacenar el total de revoluciones
unsigned long tiempoAnterior = 0;
unsigned long tiempoUltimaRevolucion = 0;
bool estadoAnterior = HIGH; // Variable para almacenar el estado anterior del pin de entrada
const float radio = 0.03; // Radio de la trayectoria circular (en metros)

void setup() {
  pinMode(27, INPUT_PULLUP); // Configura el pin 27 como entrada con resistencia pull-up
  Serial.begin(9600); // Inicializa la comunicación serial a 9600 baudios
}

void loop() {
  unsigned long tiempoActual = millis(); // Almacena el tiempo actual

  // Cada un periodo imprime
  if (tiempoActual - tiempoAnterior >= t_inicial) { // Comprueba si ha pasado el periodo de tiempo
    Serial.print("Revoluciones en el periodo: ");
    Serial.println(contador); // Imprime el valor actual del contador en el puerto serie
    Serial.print("Total de revoluciones: ");
    Serial.println(totalRevoluciones); // Imprime el total de revoluciones en el puerto serie
    tiempoAnterior = tiempoActual; // Actualiza el tiempo actual
    contador = 0; // Reinicia el contador a 0 para empezar a contar de nuevo
  }

  bool estadoActual = digitalRead(27); // Lee el estado actual del pin de entrada

  if (estadoAnterior == HIGH && estadoActual == LOW) { // Detecta el flanco descendente (paso de HIGH a LOW)
    unsigned long tiempoEntreRevoluciones = tiempoActual - tiempoUltimaRevolucion; // Calcula el tiempo entre revoluciones
    tiempoUltimaRevolucion = tiempoActual; // Actualiza el tiempo de la última revolución
    
    // Calcula la velocidad lineal usando la fórmula v = (2 * 2.14 * r) / t
    float tiempoSegundos = tiempoEntreRevoluciones / 1000.0; // Convierte el tiempo a segundos
    float velocidadLineal = (2 * 2.14 * radio) / tiempoSegundos;
    
    // Imprime el tiempo entre revoluciones y la velocidad lineal en el puerto serie
    Serial.print("Tiempo entre revoluciones (ms): ");
    Serial.println(tiempoEntreRevoluciones);
    Serial.print("Velocidad lineal (m/s): ");
    Serial.println(velocidadLineal);
    
    contador++; // Incrementa el contador en 1
    totalRevoluciones++; // Incrementa el total de revoluciones en 1

    // Debounce usando delay corto
    delay(50); // Espera un corto período de tiempo para evitar falsas detecciones (ajusta según sea necesario)
  }

  estadoAnterior = estadoActual; // Actualiza el estado anterior
}
