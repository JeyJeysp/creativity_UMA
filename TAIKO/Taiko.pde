

class Taiko
{
  color col;
  float vy=displayHeight/2 , vx=displayWidth;
  Taiko(color Color)
  {
    col=Color;
  }
  void update()
  {
     vx -= 15;
  }
  void draw()
  {
      push();
      fill(col);
      ellipse(vx,vy,100,100);
      vx-=0.2;
      pop();
  }
}
