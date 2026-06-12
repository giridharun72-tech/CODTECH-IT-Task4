/**
 * @file sketch.ino
 * @brief Contactless Touchless Automatic Sanitizer Dispenser Node
 * @domain Internet of Things (IoT) - CODTECH Internship Task 4
 * * Hardware Target: ESP32 (Simulated via Wokwi)
 * Peripherals: HC-SR04 Ultrasonic Sensor, Relay/Pump Indicator LED
 */

// --- Hardware Pin Configurations ---
const int TRIGER_PIN = 5;      // GPIO 5 mapped to HC-SR04 Trigger line
const int ECHO_PIN   = 18;     // GPIO 18 mapped to HC-SR04 Echo pulse line
const int PUMP_LED_PIN = 23;   // GPIO 23 acting as Dispenser Pump Relay output

// --- Operation Parameters ---
const int ACTIVATION_DISTANCE_CM = 10; // Trigger dispenser if a hand is within 10cm
const unsigned long DISPENSE_DURATION = 1500; // Dispense fluid for 1.5 seconds

void setup() {
  // Initialize communication for system log telemetry
  Serial.begin(115200);
  
  // Configure signaling hardware paths
  pinMode(TRIGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PUMP_LED_PIN, OUTPUT);
  
  // Enforce locked baseline off safety state at system boot
  digitalWrite(PUMP_LED_PIN, LOW);
  digitalWrite(TRIGER_PIN, LOW);

  Serial.println(F("============================================="));
  Serial.println(F(" SYSTEM STATUS: TOUCHLESS DISPENSER ACTIVE   "));
  Serial.println(F("============================================="));
}

void loop() {
  // 1. Clear Trigger Line Pin
  digitalWrite(TRIGER_PIN, LOW);
  delayMicroseconds(2);
  
  // 2. Transmit 10-Microsecond Sonic Burst Burst
  digitalWrite(TRIGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGER_PIN, LOW);
  
  // 3. Measure High Signal Echo Echo Pulse Duration
  long pulseDuration = pulseIn(ECHO_PIN, HIGH);
  
  // 4. Calculate Distance Object Metric (Speed of sound = 0.0343 cm/us)
  int measuredDistanceCm = pulseDuration * 0.0343 / 2;
  
  // Suppress erroneous out-of-bounds echo pulses
  if (measuredDistanceCm <= 0) measuredDistanceCm = 999;

  Serial.print(F("[PROXIMITY] Target Object Proximity: "));
  Serial.print(measuredDistanceCm);
  Serial.println(F(" cm"));

  // 5. Automation Interlocking Loop State Engine
  if (measuredDistanceCm <= ACTIVATION_DISTANCE_CM) {
    Serial.println(F("🧼 [DISPENSING] Hand Detected! Initiating Automated Sanitization Cycle..."));
    
    // Fire the dispenser pump load 
    digitalWrite(PUMP_LED_PIN, HIGH);
    delay(DISPENSE_DURATION);
    digitalWrite(PUMP_LED_PIN, LOW);
    
    Serial.println(F("[SUCCESS] Dispense loop complete. Entering safety cool-down phase..."));
    delay(3000); // 3-second delay prevents continuous flooding loops
  } else {
    digitalWrite(PUMP_LED_PIN, LOW);
    delay(500); // Nominal stabilization synchronization delay
  }
}
