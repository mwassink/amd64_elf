#include <stdio.h>
#include <unistd.h>

struct Coord
{
  int x;
  int y;
  double distance;
};


int main()
{
  sleep(2);
  struct Coord points[2];
  
  struct Coord point;
  point.x = 0;
  point.y = 4;
  points[0] = point;


  int * ptr = &(points[0].x);

  return 0;
  
}
