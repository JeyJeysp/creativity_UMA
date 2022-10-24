

class Taiko
{
  int type=-1;
  float vy=displayHeight/2-240 , vx=displayWidth;
  PImage tipo;
  ArrayList<Taiko>lista;
  Taiko(PImage t, ArrayList<Taiko> d)
  {
    lista=d;
    tipo = t;
  }
  void update()
  {
     vx -= 10;
  }
  void draw()
  {
      push();
      /*fill(col);
      ellipse(vx,vy,100,100);*/
      image(tipo,vx,vy,650,180);
      vx-=0.2;
      pop();
  }
  void suicide()
  {
    lista.remove(this); 
  }
  int type()
  {
      return type;  
  }
  float position()
  {
    return vx;
  }
}
