import processing.serial.*;
ArrayList<Taiko> taikos;
Serial myPort;

void setup()
{
  size(displayWidth,displayHeight);
  background(255,255,255);
  taikos = new ArrayList<Taiko>();
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil(10);
  myPort.clear();
  
  fill(color(232,204,215));
  ellipse(25,displayHeight,25,25);
}

void draw()
{
  if(random(4.0)>3.80)
  {
      creaTaiko();
  }
  background(155, 226, 244);
  fill(color(232,204,215));
  ellipse(200,displayHeight/2,175,175);

  for (int i = 0; i<taikos.size(); i++)
  {
    Taiko g = taikos.get(i);
    g.update();
    g.draw();
  }
}
void mousePressed()
{
 creaTaiko(); 
}

void serialEvent(Serial p)
{
  String datoS = p.readString();
  datoS = datoS.trim();
  //println(datoS);
  if (datoS.equals("Knock!"))
  {
      creaTaiko();
  }
}

void creaTaiko()
{
  if(random(2.0)>=1.0)
  {
    taikos.add(new Taiko(color(0,0,255)));
    println(taikos.size());
  }
  else
  {
    
    taikos.add(new Taiko(color(255,0,0)));
    println(taikos.size());
  }
}
