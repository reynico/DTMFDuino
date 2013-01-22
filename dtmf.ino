/*
	Simple Arduino sketch to understand DTMF codes from
	a MT8870 and convert it to commands to enable, disable
	and check the status from some outputs.
	Nicolas Rey, 2013.
	rey.nico@gmail.com
*/

int bin0 = A0;
int bin1 = A1;
int bin2 = A2;
int bin3 = A3;
int STD  = A4;
byte irqState;

void setup() {
	Serial.begin(9600);
	pinMode(bin0, INPUT);
	pinMode(bin1, INPUT);
	pinMode(bin2, INPUT);
	pinMode(bin3, INPUT);
	pinMode(STD,  INPUT);
}

void loop() {
	irqState = digitalRead(STD); //Get the first trigger tone
	if (irqState == 1) {
		controller(); //Do controller stuff
		//Send data to the console
		Serial.print("Dato: ");
		char code = mapKey(); //Get the code number
		Serial.println(code);
		delay(100); //delay to sync the STD data
	}
}

byte mapKey() {
	byte data;
	char key;
	// Get the binary code from MT8870
	byte D0,D1,D2,D3;
	D0 = digitalRead(bin0);
	D1 = digitalRead(bin1);
	D2 = digitalRead(bin2);
	D3 = digitalRead(bin3);

	// Convert binary values to integers
	bitWrite(data,0,D0);
	bitWrite(data,1,D1);
	bitWrite(data,2,D2);
	bitWrite(data,3,D3);
	
	// Convert the received key to understandable data for us
	if (data == 1 ) key = '1';
	if (data == 2 ) key = '2';
	if (data == 3 ) key = '3';
	if (data == 4 ) key = '4';
	if (data == 5 ) key = '5';
	if (data == 6 ) key = '6';
	if (data == 7 ) key = '7';
	if (data == 8 ) key = '8';
	if (data == 9 ) key = '9';
	if (data == 10) key = '0';
	if (data == 11) key = '*';
	if (data == 12) key = '#';
	if (data == 13) key = 'A';
	if (data == 14) key = 'B';
	if (data == 15) key = 'C';
	if (data == 0 ) key = 'D';
	
	return key;
}

int getState(int checkPin) {
// Check the output state from each pin
	int out;
	out = digitalRead(checkPin);
	return out;
}

void controller () {
	//Enable or disable outputs
	getState(9); //Get the output state of pin 9

}