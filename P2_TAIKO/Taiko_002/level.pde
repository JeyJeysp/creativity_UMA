class Level
{
  float _x, _y, _vx, _vy;
  int _type;
  PFont mono;
  Level(int type, PFont f)
  {
    _type = type;
    _x = 1040;
    _y = displayHeight/2;
    mono = f;
  }
  void update()
  {
    _vy -= random(0.1, 1.0);
    _vx += random(-1.0, 1.0);
    _x = _x + _vx;
    _y = _y + _vy;
  }
  void draw()
  {
    push();
    translate(_x, _y);
    if(_type==0)
    {
      fill(color(124,252,0));
      textFont(mono);
      text("Level UP",300,300);
    }
    else
    {
      fill(color(128, 0, 128));
      textFont(mono);
      text("Level DOWN",300,300);
    }
    //text(_val,10,10);
    //translate(0,_d/2+5);
    //triangle(0,-5,-5,0,5,0);
    pop();
  }
}
