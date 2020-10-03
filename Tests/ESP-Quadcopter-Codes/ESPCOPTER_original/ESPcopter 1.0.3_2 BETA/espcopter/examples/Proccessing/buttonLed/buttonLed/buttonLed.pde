import processing.net.*;
import controlP5.*;
Client myClient;
ControlP5 cp5;
String command= "";
int c1,c2;
void setup() {
size(400, 300,P3D);
background(0);
myClient = new Client(this, "192.168.4.1", 80);
println(myClient.ip());

cp5 = new ControlP5(this);

cp5.addToggle("colorA")
.setPosition(150,100)
.setSize(50,20)
.setValue(false)
.setMode(ControlP5.SWITCH)
;

cp5.addToggle("colorB")
.setPosition(150,150)
.setSize(50,20)
.setValue(false)
.setMode(ControlP5.SWITCH)
;

cp5.addToggle("colorC")
.setPosition(150,200)
.setSize(50,20)
.setValue(false)
.setMode(ControlP5.SWITCH)
;

}

void draw() {

}

// function colorA will receive changes from
// controller with name colorA
void colorA(boolean theFlag) {
println("a button event from colorA: "+theFlag);
background(0,255,0);
if(theFlag == true){
command = "A";
} else {
command = "a";
}

myClient.write(command);
}

// function colorB will receive changes from
// controller with name colorB
void colorB(boolean theFlag) {
println("a button event from colorB: "+theFlag);
background(0,0,255);
if(theFlag == true){
command = "B";
} else {
command = "b";
}
myClient.write(command);
}

// function colorC will receive changes from
// controller with name colorC
void colorC(boolean theFlag) {
println("a button event from colorC: "+theFlag);
background(255,0,0);
if(theFlag == true){
command = "C";
} else {
command = "c";
}

myClient.write(command);
}