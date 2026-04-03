//Arduino: PID Control & Signal Conditioning 
const int sensorPin = A0;   
const int motorPin = 9;     

float filteredMoisture = 0;
float alpha = 0.15; // LPF factor
float Kp = 2.5, Ki = 0.8, Kd = 0.2, setpoint = 65.0;
float integral = 0, lastError = 0;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600); // Communication with ESP
  pinMode(motorPin, OUTPUT);
  lastTime = millis();
}

void loop() {
  // 1. Filtered Data Acquisition
  float raw = map(analogRead(sensorPin), 1023, 200, 0, 100);
  filteredMoisture = (alpha * raw) + ((1.0 - alpha) * filteredMoisture);

  // 2. Compute PID
  unsigned long now = millis();
  float dt = (float)(now - lastTime) / 1000.0;
  if (dt > 0) {
    float error = setpoint - filteredMoisture;
    float Pout = Kp * error;
    integral += error * dt;
    // Anti-Windup
    float Iout = constrain(Ki * integral, 0, 255);
    float Dout = Kd * (error - lastError) / dt;
    
    int output = constrain(Pout + Iout + Dout, 0, 255);
    analogWrite(motorPin, output);

    // 3. Send Telemetry to ESP
    Serial.println(filteredMoisture); 
    
    lastError = error;
    lastTime = now;
  }
  delay(100); 
}
