#include <Wire.h>

#define EN0_PIN 5
#define EN1_PIN 6

#define M1_0_PIN 2 
#define M1_1_PIN 4

#define M2_0_PIN 7
#define M2_1_PIN 8

struct packet {
	bool complete;
	int data_index;
	int data[3];	
};

packet command;

void setup()
{
	// I2c init address 2
	Wire.begin(3);
	Wire.onReceive(receive_data);

	//debug serial
	Serial.begin(9600);
	//setup Enable pins
	//min speed == 100 pwm 
	pinMode(EN0_PIN, OUTPUT);
        pinMode(EN1_PIN, OUTPUT);

	digitalWrite(EN0_PIN, LOW);
	digitalWrite(EN1_PIN, LOW);

	//direction pins
	pinMode(M1_0_PIN, OUTPUT);
	pinMode(M1_1_PIN, OUTPUT);
	pinMode(M2_0_PIN, OUTPUT);
	pinMode(M2_1_PIN, OUTPUT);

	digitalWrite(M1_0_PIN, HIGH);
	digitalWrite(M1_1_PIN, LOW);
	digitalWrite(M2_0_PIN, HIGH);
	digitalWrite(M2_1_PIN, LOW);

}

void loop()
{
	get_battery();
   	delay(1000);
	analogWrite(EN0_PIN, 0);
	analogWrite(EN1_PIN, 0);
//	delay(1000);
}

void get_battery()
{
	int raw = analogRead(0);
	float val = fmap(raw, 0, 1023, 0.00, 5.00);
  	Serial.println(val);
}

void go_forward(int speed)
{
	digitalWrite(M1_0_PIN, HIGH);
	digitalWrite(M1_1_PIN, LOW);
	digitalWrite(M2_0_PIN, HIGH);
	digitalWrite(M2_1_PIN, LOW);

	analogWrite(EN0_PIN, speed);
	analogWrite(EN1_PIN, speed);	
	
}

void go_backward(int speed)
{
	digitalWrite(M1_1_PIN, HIGH);
	digitalWrite(M1_0_PIN, LOW);
	digitalWrite(M2_1_PIN, HIGH);
	digitalWrite(M2_0_PIN, LOW);

	analogWrite(EN0_PIN, speed);
	analogWrite(EN1_PIN, speed);	
}

void go_left(int speed)
{
	digitalWrite(M1_0_PIN, HIGH);
	digitalWrite(M1_1_PIN, LOW);
	digitalWrite(M2_1_PIN, HIGH);
	digitalWrite(M2_0_PIN, LOW);

	analogWrite(EN0_PIN, speed);
	analogWrite(EN1_PIN, speed);	
	
}

void go_right(int speed)
{
	digitalWrite(M1_1_PIN, HIGH);
	digitalWrite(M1_0_PIN, LOW);
	digitalWrite(M2_0_PIN, HIGH);
	digitalWrite(M2_0_PIN, LOW);

	analogWrite(EN0_PIN, speed);
	analogWrite(EN1_PIN, speed);	
	
}

void stop()
{
	analogWrite(EN0_PIN, 0);
	analogWrite(EN1_PIN, 0);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void execute_command(){
	// called when a complete packet has been received 
}

void process(int data){
	switch (data){
		case 0:
			command.complete=0;
			command.data_index=0;
			Serial.println("Command begin");
		break;
		case 2:
			command.complete=1;
			Serial.println("Command complete");			
		default:
			if (command.complete=0) {
				Serial.println("Index is: ");
				Serial.print(command.data_index);
				Serial.println("Adding data:");
				Serial.println(data);
				command.data[command.data_index]=data;
				command.data_index++;
			}
	}
}

void receive_data(int byteCount)
{
  //read the command from wire
	int data = Wire.read(); 
	process(data);
}

