

class Taiko
{
  int type=-1,velocidad;
  float vy=displayHeight/2-240 , vx=displayWidth;
  PImage tipo;
  ArrayList<Taiko>lista;
  Taiko(PImage t, ArrayList<Taiko> d,int vel)
  {
    lista=d;
    tipo = t;
    velocidad=vel;
  }
  void update()
  {
     vx -= velocidad;
  }
  void draw()
  {
      push();
      /*fill(col);
      ellipse(vx,vy,100,100);*/
      image(tipo,vx,vy,500,170);
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
