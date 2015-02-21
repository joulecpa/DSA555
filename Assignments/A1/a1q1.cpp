#include "pixmap.h"
#include <iostream>
#include <stack>
using namespace std;

/*this fill function is currently a stub (function that compiles and operates
  in some expected manner but doesn't actually work).  It only fills in the top left 10x10 pixel
area with the fill colour passed in and its return value is always true
*/

struct Point{
  int x;
  int y;
  Point(int x_, int y_){
    x = x_;
    y = y_;
  }
};


bool fill(PixMap& image,Pixel fillColour,int x, int y){

  //Check if the starting position is within the image if not do nothing
  if (x < image.width() && y < image.height()){

	  //Find out the colour of the starting point
    Pixel start = image.getPixel(x, y); 

    //If the fill and start colours are different then we attempt to fill
    if (start != fillColour){

      //Create stack to hold the points to be filled
      stack<Point> stax;
      //track which points have been already processed
      bool processed[image.width()][image.height()]; 

      //Initalize all to false ie unprocessed
      for (int i = 0; i < image.width(); i++)
        for (int j = 0; j < image.height(); j++)
          processed[i][j] = false;
      
      //Our starting point
      stax.push(Point(x, y));
			processed[x][y] = true; //set as processed 
      int count = 0;
			
      //While there are still points to be filled keep going
      while(!stax.empty()){

        Point p = stax.top();
        stax.pop();
        Pixel pt = image.getPixel(p.x, p.y);
        
        //Set the colour at the x,y point then pop those pts as they're finished
        if (pt == start){
          image.setPixel(fillColour, p.x, p.y);

          //East of the current point and only add to stack if not yet processed
          if (p.x + 1 < image.width() && !processed[p.x+1][p.y]){
            stax.push(Point(p.x + 1, p.y));
            processed[p.x+1][p.y] = true;
            count++;
          }

          //West
          if (p.x - 1 >= 0 && !processed[p.x-1][p.y]){
            stax.push(Point(p.x - 1, p.y));
            processed[p.x-1][p.y] = true;
            count++;
          }

          //South
          if (p.y + 1 < image.height() && !processed[p.x][p.y+1]){
            stax.push(Point(p.x, p.y + 1));
            processed[p.x][p.y+1] = true;
            count++;
          }

          //North
          if (p.y - 1 >= 0 && !processed[p.x][p.y-1]){
            stax.push(Point(p.x, p.y - 1));
            processed[p.x][p.y-1] = true;
            count++;
          }
        }
      }

      cout << "Number of nodes pushed to stack is: " << count + 1 << endl;
      cout << "Number of pixels in image is: " << image.width() * image.height() <<endl;

      return true;

    }

  }
  else
    cout << "The coordinates entered are outside the of the image.\nIf attempting to use"
      << " boundary numbers ie 640 400 in a 640x400 image, use 639,399 as the image's "
      << "coordinates start at 0,0.\n";

	return false;
}
