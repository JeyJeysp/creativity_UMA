class Score
{
  float _x, _y, _vx, _vy;
  int _val;
  color _col;
  float msg;
  PFont mono;
  Score(color col, int value, PFont f)
  {
    _val = value;
    _col = col;
    _x = 200;
    _y = displayHeight/2;
    msg=random(3.0);
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
    fill(_col);
    translate(_x, _y);
    if(_val>0.0)
    {
      fill(color(124,252,0));
    }
    else
    {
      fill(color(128, 0, 128));
    }
    textFont(mono);
    if(_val<0)
    {

      switch((int)msg)
      {
         case 0 : text("Que mal...",10,10); break;
         case 1 : text("Ui",10,10); break;
         case 2 : text("Mejor a la próxima",10,10); break;
         case 3 : text("Así no eh...",10,10); break;
      }
    } else 
    {
      switch((int)msg)
      {
         case 0 : text("Bravo!!!",10,10); break;
         case 1 : text("Sigue así!!",10,10); break;
         case 2 : text("EXCELENTE",10,10); break;
         case 3 : text("MAGNÍFICO",10,10); break;
      }
    }
    //text(_val,10,10);
    //translate(0,_d/2+5);
    //triangle(0,-5,-5,0,5,0);
    pop();
  }
}
