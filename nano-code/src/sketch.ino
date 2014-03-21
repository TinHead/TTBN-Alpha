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
	// I2c init address 3
	Wire.begin(3);
	Wire.onReceive(receive_data);
//	Wire.onRequest();

	//debug serial
	Serial.begin(115200);
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
}

void get_battery()
{
	int raw = analogRead(0);
	float val = fmap(raw, 0, 1023, 0.00, 5.00);
  	Serial.println(val);
}


float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void execute_command(){
	// called when a complete packet has been received 
	switch (command.data[0]){
		case 1:
			get_battery();
		break;
		case 2:
		//drive motors in forward
			drive(1, command.data[1],command.data[2]);
		break;		
		case 3:
		//drive motors in backward
			drive(2, command.data[1],command.data[2]);
		break;
		case 4:
		//drive one motor fw one bw
			drive(3, command.data[1],command.data[2]);
		break;
		case 5:
			drive(4, command.data[1],command.data[2]);
		//drive one motor bw one fw
		break;
	}
}

void drive(int dir, int pwm1, int pwm2){
	analogWrite(EN0_PIN, pwm1);
	analogWrite(EN1_PIN, pwm2);
	switch (dir){
		case 1:	
			digitalWrite(M1_0_PIN, HIGH);
			digitalWrite(M1_1_PIN, LOW);
			digitalWrite(M2_0_PIN, HIGH);
			digitalWrite(M2_1_PIN, LOW);
		break;
		case 2:
			digitalWrite(M1_1_PIN, HIGH);
			digitalWrite(M1_0_PIN, LOW);
			digitalWrite(M2_1_PIN, HIGH);
			digitalWrite(M2_0_PIN, LOW);
		break;
		case 3:
			digitalWrite(M1_0_PIN, HIGH);
			digitalWrite(M1_1_PIN, LOW);
			digitalWrite(M2_1_PIN, HIGH);
			digitalWrite(M2_0_PIN, LOW);
		break;
		case 4:
			digitalWrite(M1_1_PIN, HIGH);
			digitalWrite(M1_0_PIN, LOW);
			digitalWrite(M2_0_PIN, HIGH);
			digitalWrite(M2_1_PIN, LOW);
		break;
	}
}

void process(int data){
	switch (data){
		case 0:
			command.complete=0;
			command.data_index=0;
		break;
		case 2:
			command.complete=1;
			//Serial.println("Command complete");
			execute_command();			
		default:
			if (command.complete==0) {
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
