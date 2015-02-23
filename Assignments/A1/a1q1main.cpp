#include "pixmap.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
/*this tester will test your fill function.
  You will need the following image files:

  http://scs.senecac.on.ca/~catherine.leung/spiral.ppm
  http://scs.senecac.on.ca/~catherine.leung/sample.ppm

  To compile:

  c++ a1q1.cpp pixmap.cpp a1q1main.cpp

  Run the program.  Once your fill functions are completed,
  you will find the following files in your working directory:

  sample1.ppm, sample2.ppm, sample3.ppm, spiral1.ppm
  spiral2.ppm, spiral3.ppm, spiral4.ppm

  You can compare them against the images on this page in the wiki:


 Sumbit only your source file for the fill function when you are done.

  */
bool fill(PixMap& image,Pixel fillColour,int x, int y);

int main(int argc, char* argv[]){
	PixMap image("spiral.ppm");
	Pixel fillColour;
	fillColour.red_=255;

	fill(image,fillColour,283,200);
	image.write("spiral1.ppm");
	fillColour.green_=255;
	fillColour.red_=0;
	fill(image,fillColour,283,200);
	image.write("spiral2.ppm");
	fillColour.blue_=255;
	fillColour.green_=0;
	fill(image,fillColour,305,170);
	image.write("spiral3.ppm");
	fillColour.red_=255;
	fill(image,fillColour,0,0);
	image.write("spiral4.ppm");
	image.read("sample.ppm");
	fill(image,fillColour,247,238);
	image.write("sample1.ppm");
	fillColour.red_=0;
	fill(image,fillColour,307,177);
	image.write("sample2.ppm");
	fill(image,fillColour,639,399);
	image.write("sample3.ppm");
	return 0;
}