
#define EN0_PIN 5
#define EN1_PIN 6

#define M1_0_PIN 2 
#define M1_1_PIN 4

#define M2_0_PIN 7
#define M2_1_PIN 8

void setup()
{
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
	float val = map(raw, 0, 1023, 0.0, 50.0);
  	Serial.println(val);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

