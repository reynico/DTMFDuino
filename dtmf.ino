/*
	Simple Arduino sketch to understand DTMF codes from
	a MT8870 and convert it to commands to enable, disable
	and check the status from some outputs.
	Nicolas Rey, 2013.
	rey.nico@gmail.com
*/
#include <Time.h>  

int bin0 = A4;
int bin1 = A3;
int bin2 = A2;
int bin3 = A1;
int STD  = A0;

int Out1 =  2;
int Out2 =  3;
int Out3 =  4;
int Out4 =  5;
int Out5 =  6;
int Out6 =  7;
int Out7 =  8;
int Out8 =  9;
int Out9 =  10;
int Out10 = 11;
int checkOff = 12;
int checkOn =  13;

int i    = 1;
char dtmf[5];

byte irqState;

void setup() {
	Serial.begin(9600);
	pinMode(bin0,  INPUT);
	pinMode(bin1,  INPUT);
	pinMode(bin2,  INPUT);
	pinMode(bin3,  INPUT);
	pinMode(STD,   INPUT);
	pinMode(Out1,  OUTPUT);
	pinMode(Out2,  OUTPUT);
	pinMode(Out3,  OUTPUT);
	pinMode(Out4,  OUTPUT);
	pinMode(Out5,  OUTPUT);
	pinMode(Out6,  OUTPUT);
	pinMode(Out7,  OUTPUT);
	pinMode(Out8,  OUTPUT);
	pinMode(Out9,  OUTPUT);
	pinMode(Out10, OUTPUT);
	pinMode(checkOff, OUTPUT);
	pinMode(checkOn, OUTPUT);
}

void loop() {
	irqState = digitalRead(STD); //Get the first trigger tone
	if (irqState == 1) {
		dtmf[i++] = mapKey(); //Store the command
		//Send data to the console
		char code = mapKey(); //Get the code number
		Serial.print("Dato: ");
		Serial.println(code);
		setTime(0); //Reset the timeout counter
		delay(200); //Delay to sync the STD data
	} 
	if ((second() > 3) && (i > 1)) {
		i = 1;  //Resets the read counter	
		Serial.println("I've reseted the counter");
		setTime(0);
	}
	if (i == 4) { //When you reach the last digit..
		i = 1;  //Resets the read counter	
		setTime(0);
		controller();
	}
}

int getState(int checkPin) {
// Check the output state from each pin
	int out;
	switch (checkPin) {
		case 2:
			out = bitRead(PORTD,2);
		break;
		case 3:
			out = bitRead(PORTD,3);
		break;
		case 4:
			out = bitRead(PORTD,4);
		break;
		case 5:
			out = bitRead(PORTD,5);
		break;
		case 6:
			out = bitRead(PORTD,6);
		break;
		case 7:
			out = bitRead(PORTD,7);
		break;
		case 8:
			out = bitRead(PORTB,0);
		break;
		case 9:
			out = bitRead(PORTB,1);
		break;
		case 10:
			out = bitRead(PORTB,2);
		break;
	}

	if (out == 0) {
		digitalWrite(checkOff,HIGH);
		delay(500);
		digitalWrite(checkOff,LOW);
	} else {
		digitalWrite(checkOn,HIGH);
		delay(500);
		digitalWrite(checkOn,LOW);
	}
	return out;
}

void controller () {
  Serial.println(" ");
	//Enable or disable outputs
	if (dtmf[1] == '*') { //First-enabler tone
		Serial.println("First char");
		if (dtmf[2] == '0') { //Disable output
			switch (dtmf[3]) {
				case '0': //Turn off all outputs
					digitalWrite(Out1,LOW);
					digitalWrite(Out2,LOW);
					digitalWrite(Out3,LOW);
					digitalWrite(Out4,LOW);
					digitalWrite(Out5,LOW);
					digitalWrite(Out6,LOW);
					digitalWrite(Out7,LOW);
					digitalWrite(Out8,LOW);
					digitalWrite(Out9,LOW);
					digitalWrite(Out10,LOW);
					Serial.println("All off");
					break;
				case '1':
					digitalWrite(Out1,LOW);
					Serial.println("Out1 off");
					break;
				case '2':
					digitalWrite(Out2,LOW);
					Serial.println("Out2 off");
					break;
				case '3':
					digitalWrite(Out3,LOW);
					Serial.println("Out3 off");
					break;
				case '4':
					digitalWrite(Out4,LOW);
					Serial.println("Out4 off");
					break;
				case '5':
					digitalWrite(Out5,LOW);
					Serial.println("Out5 off");
					break;
				case '6':
					digitalWrite(Out6,LOW);
					Serial.println("Out6 off");
					break;
				case '7':
					digitalWrite(Out7,LOW);
					Serial.println("Out7 off");
					break;
				case '8':
					digitalWrite(Out8,LOW);
					Serial.println("Out8 off");
					break;
				case '9':
					digitalWrite(Out9,LOW);
					Serial.println("Out9 off");
					break;
				case 'A':
					digitalWrite(Out10,LOW);
					Serial.println("Out10 off");
					break;
			}
		}
		if (dtmf[2] == '1') { //Enable output
			switch (dtmf[3]) {
				case '0': //Turn on all outputs
					digitalWrite(Out1,HIGH);
					digitalWrite(Out2,HIGH);
					digitalWrite(Out3,HIGH);
					digitalWrite(Out4,HIGH);
					digitalWrite(Out5,HIGH);
					digitalWrite(Out6,HIGH);
					digitalWrite(Out7,HIGH);
					digitalWrite(Out8,HIGH);
					digitalWrite(Out9,HIGH);
					digitalWrite(Out10,HIGH);
					Serial.println("All on");
					break;
				case '1':
					digitalWrite(Out1,HIGH);
					Serial.println("Out1 on");
					break;
				case '2':
					digitalWrite(Out2,HIGH);
					Serial.println("Out2 on");
					break;
				case '3':
					digitalWrite(Out3,HIGH);
					Serial.println("Out3 on");
					break;
				case '4':
					digitalWrite(Out4,HIGH);
					Serial.println("Out4 on");
					break;
				case '5':
					digitalWrite(Out5,HIGH);
					Serial.println("Out5 on");
					break;
				case '6':
					digitalWrite(Out6,HIGH);
					Serial.println("Out6 on");
					break;
				case '7':
					digitalWrite(Out7,HIGH);
					Serial.println("Out7 on");
					break;
				case '8':
					digitalWrite(Out8,HIGH);
					Serial.println("Out8 on");
					break;
				case '9':
					digitalWrite(Out9,HIGH);
					Serial.println("Out9 on");
					break;
				case 'A':
					digitalWrite(Out10,HIGH);
					Serial.println("Out10 on");
					break;
			}
		}
		if (dtmf[2] == '2') { //Check output
			switch (dtmf[3]) {
				case '1':
					if(getState(Out1) == 0) {
						Serial.println("Out1 is off");
					} else {
						Serial.println("Out1 is on");
					}
					break;
				case '2':
					if(getState(Out2) == 0) {
						Serial.println("Out2 is off");
					} else {
						Serial.println("Out2 is on");
					}
					break;
				case '3':
					if(getState(Out3) == 0) {
						Serial.println("Out3 is off");
					} else {
						Serial.println("Out3 is on");
					}
					break;
				case '4':
					if(getState(Out4) == 0) {
						Serial.println("Out4 is off");
					} else {
						Serial.println("Out4 is on");
					}
					break;
				case '5':
					if(getState(Out5) == 0) {
						Serial.println("Out5 is off");
					} else {
						Serial.println("Out5 is on");
					}
					break;
				case '6':
					if(getState(Out6) == 0) {
						Serial.println("Out6 is off");
					} else {
						Serial.println("Out6 is on");
					}
					break;
				case '7':
					if(getState(Out7) == 0) {
						Serial.println("Out7 is off");
					} else {
						Serial.println("Out7 is on");
					}
					break;
				case '8':
					if(getState(Out8) == 0) {
						Serial.println("Out8 is off");
					} else {
						Serial.println("Out8 is on");
					}
					break;
				case '9':
					if(getState(Out9) == 0) {
						Serial.println("Out9 is off");
					} else {
						Serial.println("Out9 is on");
					}
					break;
				case 'A':
					if(getState(Out10) == 0) {
						Serial.println("Out10 is off");
					} else {
						Serial.println("Out10 is on");
					}
					break;
			}
		}
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
