/*
 * Copyright (c) 2013. David Thomson jdavidthomson<at>hotmail<dot>com
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 */

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[]) {
    // Check for valid command line arguments, print usage
    // if no arguments were given.
    if (argc != 4) {
        cout << "usage: " << argv[0] << " </path/to/face_cascade> <path/to/eyes_cascade> </path/to/input/file>" << endl;
        cout << "\t </path/to/face_cascade> -- Path to the Cascade for face detection." << endl;
	cout << "\t </path/to/eyes_cascade> -- Path to the Cascade for eye detection." << endl;
	cout << "\t </path/to/input/file> -- Path to input file." << endl;
        exit(1);
    }
    // Get the path to your CSV:
    string face_haar = string(argv[1]);
    string eyes_haar = string(argv[2]);
    string inputFile = string(argv[3]);

    //create cascade classifiers
    CascadeClassifier facecc;
    CascadeClassifier eyescc;

    //load cascade classifiers
    facecc.load(face_haar);
    eyescc.load(eyes_haar);

        Mat original = imread(inputFile);
	Mat cropped;

        // Convert the current frame to grayscale:
        Mat gray;
        cvtColor(original, gray, CV_BGR2GRAY);
        // Find the faces in the frame:
        vector< Rect > faces;
	vector< Rect > eyes;
	vector< Rect > nose;

	//equalize the image historgram
	equalizeHist( gray,gray );

	//look for faces in image
        facecc.detectMultiScale(gray, faces);

	for( int i=0;i<faces.size();i++){

		cout << "there are: " << faces.size() << " faces" << endl;

		Rect face_i = faces[i];
                Mat face = gray(face_i);
                cropped = face;


		eyescc.detectMultiScale(cropped, eyes);

                cout << "there are: " << eyes.size() << " eyes" << endl;

		for(int j=0;j<eyes.size();j++){
		
			Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
		       	int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
		       	circle( gray, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );

		}			
		
		if(eyes.size() == 2) {
			string filename = "face_";
       	       		  ostringstream ostr;
       		         ostr << i;
	                filename += ostr.str();
       		         filename += ".jpg";
               		 imwrite(filename,gray);
		}

	}

    return 0;
}
