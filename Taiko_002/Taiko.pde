

class Taiko
{
  color col;
  int type=-1;
  float vy=displayHeight/2 , vx=displayWidth;
  Taiko(color Color)
  {
    col=Color;
    if(col == color(0,0,255))
    {
      type=0;
    }
    else if(col == color(255,0,0))
    {
      type=1;
    }
    
  }
  void update()
  {
     vx -= 6;
  }
  void draw()
  {
      push();
      fill(col);
      ellipse(vx,vy,100,100);
      vx-=0.2;
      pop();
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
