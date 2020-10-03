import processing.net.*; 
import controlP5.*;
Client myClient; 
ControlP5 cp5;
Knob myKnobA;
String command= "";

void setup() {
   size(500, 500,P3D);
   background(0);
    myClient = new Client(this, "192.168.4.1", 80); 
   println(myClient.ip());  
     cp5 = new ControlP5(this);
  myKnobA = cp5.addKnob("knobValue")
               .setRange(0,100)
               .setValue(0)
               .setPosition(200,200)
               .setRadius(50)
               .setNumberOfTickMarks(50)
               .setTickMarkLength(4)
               .snapToTickMarks(true)
               .setColorForeground(color(255))
               .setColorBackground(color(0, 160, 100))
               .setColorActive(color(255,255,0))
               .setDragDirection(Knob.HORIZONTAL)
               ;
    
}

 void draw() {

 


 
 }

void knobValue(int theValue) {
  println("a knob event. "+theValue);
  command =  0+ "*" + 0+ "*" + theValue + "?" ;
    myClient.write(command);
 
}