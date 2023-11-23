/* This code is to use the "arduino uno" board to measure the value of unknown resistor R2
   connected in series with a reference resistor (R1) using the analog input (A0-A5) */

int analogPin = A3; // connection to reference resistor to read potential on analog pin 3

int read_value = 0;  // read analog value converted to digital signal between 0 and 1024
int stored_value = read_value;  // updating with read_value if value changes more than user set limit

double error_percent = 1; // ignore variation in reading if change is below set percentage
double reference_resistor = 216; // reference resistance (R1) in Ohm
double reference_voltage = 4.88; // reference voltage in (Vref) in Volts, measured

double analog_voltage = 0;  // converted digital signal to voltage
double circuit_current = 0;  // calculate the current in the circuit
double R2 = 0;  // unknown resistor R2 in Ohm

void setup() {
  Serial.begin(9600);           //  setup serial
  error_percent = error_percent/100;
  
  Serial.println("#############################################################");
  Serial.println("# Tool to measure reseistance using Arduino UNO Analog input ");
  Serial.println("#");
  Serial.println("# Preset values: ");
  Serial.print("#   - Reference voltage (Vref): ");
  Serial.print(reference_voltage);
  Serial.println(" V");
  Serial.print("#   - Reference resistance (Rref): ");
  Serial.print(reference_resistor);
  Serial.println(" Ohm");
  Serial.println("#############################################################\n");
}

void loop() {
  read_value = analogRead(analogPin);  // read the input pin
  
  // Update only when the new value being read exceeds threshold
  if(read_value > (stored_value + stored_value * error_percent)
    || read_value < (stored_value - stored_value * error_percent) ) {

    stored_value = read_value;  // update old value with new read value
    
    Serial.println("# Measured");
        
    // reading analog to digital converter -> show for debugging purposes
    //Serial.print("Reading: ");
    //Serial.println(stored_value);
    
    // convert analog value to Va
    analog_voltage = convertToVoltage(stored_value);
    if(analog_voltage >= reference_voltage - reference_voltage * error_percent) { // overcome scenario when replacing resistor
      Serial.println("Open circuit");
    } else {
      Serial.print("V1 [V]: ");
      Serial.println(reference_voltage - analog_voltage);
      Serial.print("V2 [V]: ");
      Serial.println(analog_voltage);
      
      // calculate R2
      R2 = calculateR2();
      Serial.print("R2 [Ohm]: ");
      Serial.println(R2);
      
      // calculate current in circuit
      circuit_current = calculateCurrent();
      Serial.print("Current [mA]: ");
      Serial.println(circuit_current);
    }
    
    Serial.println("#---------\n\n");
    delay(5000);                // waits for 5 second [ms]
  }
}

double convertToVoltage(int stored_value){
  double voltage;
  double resolution = reference_voltage/1024; // [V] if the reference voltage on the analog pin is 5V, that is beacuse 5 volts / 1024 units or, 0.0049 volts (4.9 mV) per unit
  
  voltage = stored_value * resolution;
  
  return voltage;
}

double calculateCurrent(){
  double current;
  
  current = reference_voltage / (reference_resistor + R2) * 1000;
  
  return current;
}

double calculateR2(){
  double unknown_resistor;
  double constant;
  
  constant = analog_voltage / reference_voltage;
  
  unknown_resistor = (reference_resistor * constant) / (1 - constant);
  
  return unknown_resistor;
}
