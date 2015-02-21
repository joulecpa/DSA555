#include "pixmap.h"
#include <iostream>
using namespace std;

/*this fill function is currently a stub (function that compiles and operates
  in some expected manner but doesn't actually work).  It only fills in the top left 10x10 pixel
area with the fill colour passed in and its return value is always true
*/
bool fill(PixMap& image,Pixel fillColour,int x, int y){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			image.setPixel(fillColour,i,j);
		}
	}

	//My code

  Pixel p; 
  p = image.getPixel(400, 300); 
  cout << "R: " << (int) p.red_ << " G: " << (int) p.green_ << " B: " << 
    (int)  p.blue_ << endl;

	return true;
}
