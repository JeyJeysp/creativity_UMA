class Score
{
  float _x, _y, _vx, _vy;
  int _val;
  color _col;
  Score(color col, int value)
  {
    _val = value;
    _col = col;
    _x = 200;
    _y = displayHeight/2;
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
      fill(color(255,0,0));
    }
    text(_val,10,10);
    //translate(0,_d/2+5);
    //triangle(0,-5,-5,0,5,0);
    pop();
  }
}
