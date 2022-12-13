
/*1-bit ALU code for the Arduino Nano
Rares-Mihail Neagu*/
//set the input and output pins
//OUTPUTS
int outputPin=2;
int carryOutPin=3;
//INPUTS
int buttonApin=12;
int buttonENApin=11;
int buttonBpin=10;
int buttonENBpin=9;
int buttonINVApin=8;
int buttonCarryInPin=7;
int buttonF0pin=6;
int buttonF1pin=5;

//temmporary variables
int cout;
int out;
int A;
int ENA;
int INVA;
int B;
int ENB;
int cin;
int F0;
int F1;
int inA;//the input A for the logical box
int inB;//the input B for the logical box

//logical unit variables
int orAB;
int andAB;
int notB;

//full adder variables
int Sum;

void setup() {
  // set the mode for the input and output
  //OUTPUT
  pinMode(outputPin, OUTPUT);
  pinMode(carryOutPin, OUTPUT);
  //INPUTS
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonENApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonENBpin, INPUT_PULLUP);
  pinMode(buttonINVApin, INPUT_PULLUP);
  pinMode(buttonCarryInPin, INPUT_PULLUP);
  pinMode(buttonF0pin, INPUT_PULLUP);
  pinMode(buttonF1pin, INPUT_PULLUP);


}

void loop() {
  //assigning the pins to the variables we created above
  A=digitalRead(buttonApin);
  ENA=digitalRead(buttonENApin);
  B=digitalRead(buttonBpin);
  ENB=digitalRead(buttonENBpin);
  INVA=digitalRead(buttonINVApin);
  cin=digitalRead(buttonCarryInPin);
  F0=digitalRead(buttonF0pin);
  F1=digitalRead(buttonF1pin);

  //set up inA and inB
  inA=((A & ENA) ^ INVA);
  inB=(B & ENB);

  //perform the logical operations
  andAB=inA & inB;
  orAB=inA | inB;
  notB=~inB;
  //perform the sum
  Sum=(inA ^ inB)^cin;
  cout=((inA & inB) & (F0 & F1)) | ((F0 & F1) & cin & (inA ^ inB));
  out= (Sum & (F0 & F1)) | (andAB & (~F0 & ~F1)) | (orAB & (~F0 & F1)) | (notB & (F0 & ~F1));

  //writing out the output to the output pins
  digitalWrite(carryOutPin, cout);
  digitalWrite(outputPin, out);

}
