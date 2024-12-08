const int relePin1 = 7;  // Pin del relé 1
const int relePin2 = 8;  // Pin del relé 2
const int relePin3 = 9;  // Pin del relé 3
const int relePin4 = 10; // Pin del relé 4
const int relePin5 = 4;  // Pin del relé 5
const int relePin6 = 5;  // Pin del relé 6
const int relePin7 = 6;  // Pin del relé 7
const int relePin8 = 11;  // Pin del relé 5
const int relePin9 = 12;  // Pin del relé 6
const int relePin10 = 3;  // Pin del relé 7

const int caudalPin = 2; // Pin del caudalímetro
volatile unsigned int pulsos = 0; // Contador de pulsos
float factorCalibracion = 7.5; // Cambia según tu caudalímetro (pulsos/segundo por litro/minuto)

unsigned long tiempoAnterior = 0; // Para calcular el caudal

void contarPulsos() {
  pulsos++; // Incrementa el contador cada vez que hay un pulso
}


void setup() {
  Serial.begin(9600);         // Inicializa la comunicación serial
  pinMode(relePin1, OUTPUT);  // Configura los pines de los relés como salidas
  pinMode(relePin2, OUTPUT);
  pinMode(relePin3, OUTPUT);
  pinMode(relePin4, OUTPUT);
  pinMode(relePin5, OUTPUT);  // Configura los pines de los relés como salidas
  pinMode(relePin6, OUTPUT);
  pinMode(relePin7, OUTPUT);
  pinMode(relePin8, OUTPUT);  // Configura los pines de los relés como salidas
  pinMode(relePin9, OUTPUT);
  pinMode(relePin10, OUTPUT);

  // Inicialmente, todos los relés están apagados
  digitalWrite(relePin1, HIGH);
  digitalWrite(relePin2, HIGH);
  digitalWrite(relePin3, HIGH);
  digitalWrite(relePin4, HIGH);
  digitalWrite(relePin5, HIGH);
  digitalWrite(relePin6, HIGH);
  digitalWrite(relePin7, HIGH);
  digitalWrite(relePin8, HIGH);
  digitalWrite(relePin9, HIGH);
  digitalWrite(relePin10, HIGH);

  pinMode(caudalPin, INPUT_PULLUP); // Configura el pin del caudalímetro como entrada con resistencia pull-up
  attachInterrupt(digitalPinToInterrupt(caudalPin), contarPulsos, RISING); // Configura la interrupción para contar pulsos

}

void loop() {

  // Calcular caudal cada segundo
  if (millis() - tiempoAnterior >= 1000) {
    tiempoAnterior = millis();
    float caudal = (pulsos / factorCalibracion); // Calcula el caudal en litros/minuto
    pulsos = 0; // Resetea el contador de pulsos

    Serial.print("Caudal: ");
    Serial.print(caudal);
    Serial.println(" L/min");
  }



  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n'); // Lee el comando completo hasta el salto de línea

    // Convierte el comando en un número entero
    int comandoInt = comando.toInt();

    switch (comandoInt) {
      case 1:
        digitalWrite(relePin1, LOW);
        Serial.println("Valvula 1 de Mezcla Abierta/ Llenando Krisol 1");
        break;
      case 2:
        digitalWrite(relePin1, HIGH);
        Serial.println("Valvula 1 de Mezcla Cerrada");
        break;
      case 3:
        digitalWrite(relePin2, LOW);
        Serial.println("Valvula 2 de Mezcla Abierta/ Llenando Krisol 2");
        break;
      case 4:
        digitalWrite(relePin2, HIGH);
        Serial.println("Valvula 2 de Mezcla Cerrada");
        break;
      case 5:
        digitalWrite(relePin3, LOW);
        Serial.println("Valvula 3 de Mezcla Abierta/ Llenando Krisol 3");
        break;
      case 6:
        digitalWrite(relePin3, HIGH);
        Serial.println("Valvula 3 de Mezcla Cerrada");
        break;
      case 7:
        digitalWrite(relePin4, LOW);
        Serial.println("Valvula Agua Fria Abierta");
        break;
      case 8:
        digitalWrite(relePin4, HIGH);
        Serial.println("Valvula Agua Fria Cerrada");
        break;
      case 9:
        digitalWrite(relePin5, LOW);
        Serial.println("Caudalimetro 3 Activo");
        break;
      case 10:
        digitalWrite(relePin5, HIGH);
        Serial.println("Caudalimetro 3 Apagado");
        break;
      case 11:
        digitalWrite(relePin6, LOW);
        Serial.println("Caudalimetro 2 Activo");
        break;
      case 12:
        digitalWrite(relePin6, HIGH);
        Serial.println("Caudalimetro 2 Apagado");
        break;
      case 13:
        digitalWrite(relePin7, LOW);
        Serial.println("Caudalimetro 1 Activo");
        break;
      case 14:
        digitalWrite(relePin7, HIGH);
        Serial.println("Caudalimetro 1 Apagado");
        break;
      case 15:
        digitalWrite(relePin8, LOW);
        Serial.println("Inyectando Vapor en Krisol 1");
        break;
      case 16:
        digitalWrite(relePin8, HIGH);
        Serial.println("Vapor 1 Sellado");
        break;
      case 17:
        digitalWrite(relePin9, LOW);
        Serial.println("Inyectando Vapor en Krisol 2");
        break;
      case 18:
        digitalWrite(relePin9, HIGH);
        Serial.println("Vapor 2 Sellado");
        break;
      case 19:
        digitalWrite(relePin10, LOW);
        Serial.println("Inyectando Vapor en Krisol 3");
        break;
      case 20:
        digitalWrite(relePin10, HIGH);
        Serial.println("Vapor 3 Sellado");
        break;
      case 22:
        Serial.println("Has elegido hacer una te");

        Serial.println("Ingresa la temperatura de la bebida:");
        // Esperar a que el usuario ingrese la temperatura
        while (Serial.available() == 0) {
        // No hacer nada mientras no haya datos en el buffer serial
        }
        String inputTemp = Serial.readStringUntil('\n'); // Leer el valor ingresado
        int temperatura = inputTemp.toInt();            // Convertir la entrada a número

        Serial.print("Temperatura ingresada: ");
        Serial.println(temperatura);

        Serial.println("Ingresa la cantidad de la bebida:");
        // Esperar a que el usuario ingrese la temperatura
        while (Serial.available() == 0) {
        // No hacer nada mientras no haya datos en el buffer serial
        }
        String inputCantidad = Serial.readStringUntil('\n'); // Leer el valor ingresado
        int cantidad = inputCantidad.toInt();            // Convertir la entrada a número

        Serial.print("Cantidad ingresada: ");
        Serial.println(cantidad);

        Serial.println("Ingresa el tiempo de reposo de la bebida:");
        // Esperar a que el usuario ingrese la temperatura
        while (Serial.available() == 0) {
        // No hacer nada mientras no haya datos en el buffer serial
        }
        String inputTiempo = Serial.readStringUntil('\n'); // Leer el valor ingresado
        int tiempo = inputTiempo.toInt();            // Convertir la entrada a número

        Serial.print("Tiempo ingresado: ");
        Serial.println(tiempo);

        Serial.println("Procediendo a preparar....");
        Serial.println("");

        digitalWrite(relePin4, LOW);
        Serial.println("Valvula Agua Fria Abierta");

        break;
      
      default:
        Serial.println("Comando no reconocido");
        break;
    }
  }
}