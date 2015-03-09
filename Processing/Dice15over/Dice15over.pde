PFont myFont;
PImage numbers[] = new PImage[6];
import ddf.minim.*;    // for sounds
Minim minim;           // for sounds
AudioPlayer sound[] = new AudioPlayer[3];     // for sounds

void setup() {
  int i;
  String filename;
  size(500, 500);
  background(255, 255, 255);
  fill(0, 0, 0);
  smooth();
  noStroke();
  frameRate(24);
  myFont = createFont("MS Gothic", 24, true);
  textFont(myFont);
  for(i = 0; i < 6; i++) {     // loads the images
    filename = "images/" + str(i + 1) + ".png";
    numbers[i] = loadImage(filename);
  }
  minim = new Minim(this);
  sound[1] = minim.loadFile("se_maoudamashii_se_switch01.wav");   // loads the sound
  sound[2] = minim.loadFile("BGM.mp3");
}

int r1 = 0;  // random number
int r2 = 0;  // random number
int r3 = 0;  // random number
int r4 = 0;  // random number
int rollButtonX = 310;
int rollButtonY = 160;
int rollButtonW = 180;
int rollButtonH = 60;

int rollButtonX2 = 310;
int rollButtonY2 = 390;
int rollButtonW2 = 180;
int rollButtonH2 = 60;

int rollButtonX3 = 2;//onemore
int rollButtonY3 = 463;
int rollButtonW3 = 495;
int rollButtonH3 = 35;

int startButtonX = 5;
int startButtonY = 130;
int startButtonW = 490;
int startButtonH = 95;

int buttonRed = 153;          // button color
int buttonGreen = 51;        // button color
int buttonBlue = 0;       // button color
int buttonTextColor = 255;

int buttonRed2 = 102;          // button color
int buttonGreen2 = 102;        // button color
int buttonBlue2 = 51;       // button color

int r1math = 0;
int r2math = 0;
int counter = 0;
int counter2 = 0;
int first = 0;
int second = 0;
int home =0;

void draw() {
 
  if(home == 0){
    
    fill(255);
    rect(265,250,230,137);
    rect(265,393,230,102);
    rect(5,250,255,245);
    
    stroke(0);
    
    line(5,290,260,290);//topline
    line(5,390,260,390);//midlleline
    
    
    line(265,290,495,290);//againsetumeiline
    
    fill(0);
    
    line(100,250,100,490);
    line(260,250,260,490);
    
    textSize(30);
    text("Player",10,283); 
    text("ButtonKey",115,283); 
    text("RetryGame",315,283);
    
    textSize(70);
    text("P1",20,370); 
    text("P2",20,470); 
    
    textSize(50);
    text("a || s",105,360); 
    text(": || ]",105,460); 
    
    text("EnterKey",280,360);
    
    textSize(20);
    text("Score>=15 End",270,413); 
    text("P1Counter>P2Counter",270,433);
    text("P2=Win P1=Lose",270,453);
    text("P2Counter>P1Counter",270,472);
    text("P1=Win P2=Lose",270,492);
    
    textSize(100);
    text("Dice15over",5,100);
    
    textSize(70);
    startButton(startButtonX, startButtonY,
             startButtonW, startButtonH,
             "Start");
             
   
  
  }
  
  if(home == 1){
  
  background(255);
  fill(0);
  
  image(numbers[r1], 20, 5, 120, 120);
  image(numbers[r2], 20, 110, 120, 120);
  image(numbers[r3], 20, 230, 120, 120);
  image(numbers[r4], 20, 340, 120, 120);
  
  
  line(0,height/2-20,width,height/2-20);//center
  line(width/2-90,height/2-220,width,height/2-220); //scoreline
  line(width/2-90,height/2-100,width,height/2-100); //counterline1
  line(width/2-90,height/2-130,width,height/2-130); //counterline2
  
  line(0,height-40,width,height-40);//under
  line(width/2-90,height/2+10,width,height/2+10);//p2scoreline
  line(width/2-90,height/2+100,width,height/2+100); //p2counterline1
  line(width/2-90,height/2+130,width,height/2+130); //p2counterline2
  
  
  line(width/2-90,0,width/2-90,height-40);//left
  line(width/2+50,0,width/2+50,height-40);//right
  
  
  textSize(25); 
  text("Score",width/2-50,23); //p1score
  text("Counter",width/2-65,height/2-105); //p1counter
  text("Judgement",width/2+85,23); //p1judgement
  text("Start",width/2+120,height/2-105); //p1score
  textSize(80);
  text(r1math,width/2-70,height/2-144); //p1score
  text(counter,width/2-70,height/2-30);//p1counter
  
  textSize(25);
  text("Score",width/2-50,height/2+6); //p2counter
  text("Counter",width/2-65,height/2+125); //p2score
  text("Judgement",width/2+85,height/2+3); //p1judgement
  text("Start",width/2+120,height/2+125); //p1score
  textSize(80);
  text(r2math,width/2-70,height-163); //p2score
  text(counter2,width/2-70,height-50); //p2counter
 
  
   if (counter2 > counter && r1math >=15 && r2math >= 15) {
    text("Win",width/2+82,height/2-144);
    text("Lose",width/2+62,(height-40)-height/4);
  }   
  
  if (counter > counter2 && r1math >=15 && r2math >= 15) {
    text("Lose",width/2+62,height/2-144);
    text("Win",width/2+82,(height-40)-height/4);
       
  }   
  
  if (counter2 == counter && r1math >=15 && r2math >= 15) {
    text("Draw",width/2+62,height-144);
    text("Draw",width/2+62,height-144);
  }   
  
  
  
    if (r1math >= 15) {
    first = 1;
  }   

       if (r2math >= 15) {
    second = 1;
  }   
  

  
  
    textSize(30);
  drawButton(rollButtonX, rollButtonY,
             rollButtonW, rollButtonH,
             "P1");
             
 drawButton2(rollButtonX2, rollButtonY2,
             rollButtonW2, rollButtonH2,
             "P2");            

 drawButton3(rollButtonX3, rollButtonY3,
             rollButtonW3, rollButtonH3,
             "Try again");

  stroke(0);

  sound[2].play();
  
  }
  
}

void mouseReleased(){
  if(home == 1){
  if(first == 0){
  if(mouseX >= rollButtonX && mouseX <= rollButtonX + rollButtonW &&
     mouseY >= rollButtonY && mouseY <= rollButtonY + rollButtonH) {
    r1 = floor(random(0, 6));
    r2 = floor(random(0, 6));
    
    
    if(r1 == r2 && r1 == 0){
      r1math = r1math + 1;
    }
    if(r1 == r2 && r1 == 1){
      r1math = r1math + 2;
    }
    if(r1 == r2 && r1 == 2){
      
      r1math = r1math + 3;
    }
    if(r1 == r2 && r1 == 3){
      r1math = r1math + 4;
    }
    if(r1 == r2 && r1 == 4){
      r1math = r1math + 5;
    }
    if(r1 == r2 && r1 == 5){
      r1math = r1math + 6;
    }
    
counter++;
     }
  }
  
  
  if(second == 0){
    if(mouseX >= rollButtonX2 && mouseX <= rollButtonX2 + rollButtonW2 &&
     mouseY >= rollButtonY2 && mouseY <= rollButtonY2 + rollButtonH2) {
    
    r3 = floor(random(0, 6));
    r4 = floor(random(0, 6));
    
    if(r3 == r4 && r3 == 0){
      r2math = r2math + 1;
    }
    if(r3 == r4 && r3 == 1){
      r2math = r2math + 2;
    }
    if(r3 == r4 && r3 == 2){
      
      r2math = r2math + 3;
    }
    if(r3 == r4 && r3 == 3){
      r2math = r2math + 4;
    }
    if(r3 == r4 && r3 == 4){
      r2math = r2math + 5;
    }
    if(r3 == r4 && r3 == 5){
      r2math = r2math + 6;
    }
    
counter2++;
     }
  }
  }
  
  if(r1math >= 15 && r2math >= 15){
   if(mouseX >= rollButtonX3 && mouseX <= rollButtonX3 + rollButtonW3 &&
     mouseY >= rollButtonY3 && mouseY <= rollButtonY3 + rollButtonH3) {
    r1math = 0;
    r2math = 0;
    counter = 0;
    counter2 = 0;
    first = 0;
    second = 0;
    background(255);
    sound[2].close();
    minim.stop();
    home = 0;
    }  
 } 
  
  if(home == 0){
  if(mouseX >= startButtonX && mouseX <= startButtonX + startButtonW &&
     mouseY >= startButtonY && mouseY <= startButtonY + startButtonH) {
    home = 1;
    sound[2].play();
     } 
  }
}

void mousePressed(){

  
  if(home == 1){
  if(first==0){
  if(mouseX >= rollButtonX && mouseX <= rollButtonX + rollButtonW &&
     mouseY >= rollButtonY && mouseY <= rollButtonY + rollButtonH) {
    sound[1].rewind();
    sound[1].play();
     }
 }
 if(second==0){
     if(mouseX >= rollButtonX2 && mouseX <= rollButtonX2 + rollButtonW2 &&
     mouseY >= rollButtonY2 && mouseY <= rollButtonY2 + rollButtonH2) {
    sound[1].rewind();
    sound[1].play();
     }
  }
} 

if(r1math >= 15 && r2math >= 15){
   if(mouseX >= rollButtonX3 && mouseX <= rollButtonX3 + rollButtonW3 &&
     mouseY >= rollButtonY3 && mouseY <= rollButtonY3 + rollButtonH3) {
    sound[1].rewind();
    sound[1].play();
    }  
 } 
 
 if(home == 0){
 if(mouseX >= startButtonX && mouseX <= startButtonX + startButtonW &&
    mouseY >= startButtonY && mouseY <= startButtonY + startButtonH) {
    sound[1].rewind();
    sound[1].play();
     }
  } 
  
  
}
  
void keyReleased() {
  
  if(first == 0){
  if(key =='a'||key =='s') {
    r1 = floor(random(0, 6));
    r2 = floor(random(0, 6));
    
    
    if(r1 == r2 && r1 == 0){
      r1math = r1math + 1;
    }
    if(r1 == r2 && r1 == 1){
      r1math = r1math + 2;
    }
    if(r1 == r2 && r1 == 2){
      
      r1math = r1math + 3;
    }
    if(r1 == r2 && r1 == 3){
      r1math = r1math + 4;
    }
    if(r1 == r2 && r1 == 4){
      r1math = r1math + 5;
    }
    if(r1 == r2 && r1 == 5){
      r1math = r1math + 6;
    }
    
counter++;
     }
  }
  if(second == 0){
    if(key ==':' || key==']') {
    
    r3 = floor(random(0, 6));
    r4 = floor(random(0, 6));
    
    if(r3 == r4 && r3 == 0){
      r2math = r2math + 1;
    }
    if(r3 == r4 && r3 == 1){
      r2math = r2math + 2;
    }
    if(r3 == r4 && r3 == 2){
      
      r2math = r2math + 3;
    }
    if(r3 == r4 && r3 == 3){
      r2math = r2math + 4;
    }
    if(r3 == r4 && r3 == 4){
      r2math = r2math + 5;
    }
    if(r3 == r4 && r3 == 5){
      r2math = r2math + 6;
    }
    
counter2++;
     }
  }
  
 if(r1math >= 15 && r2math >= 15){
   if(keyCode ==ENTER) {
    r1math = 0;
    r2math = 0;
    counter = 0;
    counter2 = 0;
    first = 0;
    second = 0;
    background(255);
    sound[2].close();
    minim.stop();
    home = 0;
    
    } 
 }
}
  



void keyPressed() {
  
 if(first==0){
  if(key =='a'||key =='s') {
    sound[1].rewind();
    sound[1].play();
     }
 }
 if(second==0){
     if(key ==':' || key==']') {
    sound[1].rewind();
    sound[1].play();
     }
 }
 
 if(r1math >= 15 && r2math >= 15){
   if(keyCode ==ENTER) {
    sound[1].rewind();
    sound[1].play();
   }
 }
}
 
 
void drawButton(int x, int y, int w, int h, String s) {

  if(first ==0){
  
  
 
  if(mousePressed == true &&
     mouseX >= rollButtonX && mouseX <= rollButtonX + rollButtonW &&
     mouseY >= rollButtonY && mouseY <= rollButtonY + rollButtonH || 
     keyPressed == true && key =='a' || keyPressed == true && key =='s') {
    fill(255);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(0);
  }
  else {
    fill(buttonRed, buttonGreen, buttonBlue);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(buttonTextColor);
  }
  text(s, x + 70, y + 40);
  }
  
  if(first ==1){
  fill(buttonRed, buttonGreen, buttonBlue);
  stroke(0);
  rect(x, y, w, h, 7);
  fill(buttonTextColor);
  text(s, x + 70, y + 40);
  }
  
}

void drawButton2(int x, int y, int w, int h, String s) {

  if(second ==0){

  if(mousePressed == true &&
     mouseX >= rollButtonX2 && mouseX <= rollButtonX2 + rollButtonW2 &&
     mouseY >= rollButtonY2 && mouseY <= rollButtonY2 + rollButtonH2 || 
     keyPressed == true && key ==':' || keyPressed == true && key==']') {
       fill(255);
       stroke(0);
       rect(x, y, w, h, 7);
       fill(0);
  }
  else {
    fill(buttonRed, buttonGreen, buttonBlue);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(buttonTextColor);
  }
  
  text(s, x + 70, y + 40);
  }
  
  if(second == 1){
    fill(buttonRed, buttonGreen, buttonBlue);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(buttonTextColor);
    text(s, x + 70, y + 40);
  }
  
  
}

void drawButton3(int x, int y, int w, int h, String s) {
  
  fill(buttonRed2, buttonGreen2, buttonBlue2);
  stroke(0);
  rect(x, y, w, h, 7);
  fill(buttonTextColor);
  text(s, x + 185, y + 27);

  if(r1math >= 15 && r2math >= 15){
  if(mousePressed == true &&
     mouseX >= rollButtonX3 && mouseX <= rollButtonX3 + rollButtonW3 &&
     mouseY >= rollButtonY3 && mouseY <= rollButtonY3 + rollButtonH3 ||
     keyPressed == true && keyCode ==ENTER) {
       fill(255);
       stroke(0);
       rect(x, y, w, h, 7);
       fill(0);
  }
  else {
    fill(buttonRed2, buttonGreen2, buttonBlue2);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(buttonTextColor);
  }
  text(s, x + 185, y + 27);
  }
 
}

void startButton(int x, int y, int w, int h, String s) {

  
  if(mousePressed == true &&
     mouseX >= startButtonX && mouseX <= startButtonX + startButtonW &&
     mouseY >= startButtonY && mouseY <= startButtonY + startButtonH) {
    fill(255);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(0);
  }
  else {
    fill(buttonRed, buttonGreen, buttonBlue);
    stroke(0);
    rect(x, y, w, h, 7);
    fill(buttonTextColor);
  }
  text(s, x + 150, y + 75);
  }
 

