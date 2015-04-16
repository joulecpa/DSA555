/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.0                                         */
/*                                                       */
/*  All data files are stored at:                        */
/*   scs.senecac.on.ca/~catherine.leung/a3data.zip       */
/*   tester source(a3main.cpp and timer.h/cpp)           */
/*   can be found in course repo                         */
/*                                                       */
/* the speed test will run 100 times, and this could     */
/* take some time.                                       */
/*                                                       */
/*   DSA555 - Winter 2015                                */
/*                                                       */
/*   Please put all your code in the files a3.h and      */
/*   and a3.cpp.  Note that if you didn't put it into    */
/*   put the building struct into a3.h, you will need    */
/*   to do so and include a3.h in your a3.cpp            */
/*                                                       */
/*   There are 4 data files, 2 ascii, 2 binary.  The     */
/*   binary version reads a lot faster but I will only   */
/*   have binary for matrix, not windows.                */
/*   so you may need to do ascii mode instead.           */
/*   reading is set to ascii mode by default but feel    */
/*   free to change it.  
/*                                                       */
/*   NOTE:  If you find an error, please let me know     */
/*          asap.  I will use this main when I test      */
/*          test so do not make any changes  yourself.   */
/*          Let me know and I'll fix the bug             */
/*                                                       */
/*   To compile this program:                            */
/*          g++ a3main.cpp a3.cpp timer.cpp              */
/*                                                       */
/*********************************************************/
#include "a3.h"
#include "timer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#define NUMBUILDINGS 200000
#define MAXWIDTH 500000
#define BINARY 1
#define ASCII 0
#define READFORMAT ASCII
#define TIMEDITERATIONS 100
using namespace std;
int main(void){
	Building testerList[4]={{1,4,4},{7,12,6},{6,8,10},{5,14,3}};
	int testerSilhouette[14]={0};
	int testerCorrect[14]={0, 4, 4, 4, 0, 3, 10, 10, 6, 6, 6, 6, 3, 3};

	bool completed=true;
	Building* bList=new Building[NUMBUILDINGS];
	int* silhouette=new int[MAXWIDTH];
	int* correct=new int[MAXWIDTH];

	findSilhouette(testerList,4,testerSilhouette);
	for(int i=0;i<14;i++){
		if(testerSilhouette[i] != testerCorrect[i]){
			completed=false;
			cout << "silhouette error" << endl;
			cout << "at position: " << i << endl;
			cout << "your height: "  << testerSilhouette[i] << endl;
			cout << "correct height: "<< testerCorrect[i] << endl;
		}
	}
	if(completed){
#if READFORMAT == BINARY
		ifstream fs ("a3data.dat",ios::binary);
		ifstream fs2 ("a3output.dat",ios::binary);
#else
		ifstream fs ("a3data.txt");
		ifstream fs2 ("a3output.txt");
#endif

		for(int i=0;i<MAXWIDTH;i++){
			silhouette[i]=0;
		}
		for(int i=0;i<NUMBUILDINGS;i++){
#if READFORMAT == BINARY
			fs.read((char*)(bList+i),sizeof(int)*3);
#else
			fs >> bList[i].left_ >> bList[i].right_ >> bList[i].height_;
#endif
		}

		findSilhouette(bList,NUMBUILDINGS,silhouette);
#if READFORMAT == BINARY
		fs2.read((char*)correct,sizeof(int)*MAXWIDTH);
#else
		for(int i=0;i<MAXWIDTH;i++){
			fs2 >> correct[i];
		}
#endif
		for(int i=0;i<MAXWIDTH;i++){
			if(silhouette[i] != correct[i]){
				completed=false;
				cout << "silhouette error" << endl;
				cout << "at position: " << i << endl;
				cout << "your height: "  << silhouette[i] << endl;
				cout << "correct height: "<< correct[i] << endl;
			}
		}
	}
	if(completed){
		cout << "Testing passed, now to check speed..." << endl;
		cout << "The main will now call your findSilhouette() " << TIMEDITERATIONS << " times" << endl;
		Timer t;
		t.start();
		for(int i=0;i<TIMEDITERATIONS;i++){
			findSilhouette(bList,NUMBUILDINGS,silhouette);
		}
		t.stop();
		cout << TIMEDITERATIONS << " calls to findSilhouette() took : " << t.currtime() << " seconds" << endl;
	}
	return 0;
}