#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// Pines I2C en el ESP32
#define SDA 19
#define SCL 18

// Crear un objeto para el sensor TSL2561
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); // Dirección por defecto (0x39)

void setup() {
  // Inicializar la comunicación serial
  Serial.begin(115200);
  Serial.println("Iniciando TSL2561...");

  // Inicializar el bus I2C con pines personalizados
  Wire.begin(SDA, SCL);

  // Inicializar el TSL2561
  if (!tsl.begin()) {
    Serial.println("No se encontró el sensor TSL2561. Verifica la conexión.");
    while (1);
  }
  Serial.println("TSL2561 inicializado correctamente.");

  // Configuración del sensor
  tsl.enableAutoRange(true); // Habilitar el ajuste automático de rango
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); // Tiempo de integración (más rápido, menos precisión)

  Serial.println("Configuración completada.");
}

void loop() {
  // Crear un objeto para almacenar los datos del sensor
  sensors_event_t event;
  tsl.getEvent(&event);

  // Verificar si se obtuvieron lecturas válidas
  if (event.light) {
    Serial.print("Luz detectada: ");
    Serial.print(event.light);
    Serial.println(" lux");
  } else {
    Serial.println("No se detectó luz (el sensor puede estar saturado o apagado).");
  }

  delay(1000); // Leer cada segundo
}
