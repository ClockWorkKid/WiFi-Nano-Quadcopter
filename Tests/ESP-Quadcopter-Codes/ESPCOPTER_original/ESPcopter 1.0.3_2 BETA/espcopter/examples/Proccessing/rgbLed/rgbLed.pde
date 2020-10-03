import processing.net.*; 
import controlP5.*;
Client myClient; 
ControlP5 cp5;

String command= "";

void setup() {
   size(500, 500,P3D);
   background(0);
    myClient = new Client(this, "192.168.4.1", 80); 
   println(myClient.ip());  
   
  cp5 = new ControlP5(this);
  cp5.addColorWheel("colorWheel", 125 , 125 , 225 ).setRGB(color(128,0,255));
  noStroke();
    
}

 void draw() {

   command =  cp5.get(ColorWheel.class,"colorWheel").b() + "*" + cp5.get(ColorWheel.class,"colorWheel").g() + "*" +cp5.get(ColorWheel.class,"colorWheel").r() + "?" ;


 
 }
 void colorWheel(int theValue) {
 println("from client: " + command);
 myClient.write(command);

}