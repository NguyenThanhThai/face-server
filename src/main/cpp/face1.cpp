#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    printf("OpenCV Face Detector v0.1\n");
    if (argc < 2) {
        printf("\nUsage: face-detector <input image>\n\n");
        return -1;
    }
    char* filename = argv[1];

    Mat img = imread(filename);
    CascadeClassifier classifier("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
    vector<Rect> faces;
    classifier.detectMultiScale(img, faces);
    printf("Faces detected:%d\n", faces.size());

    Scalar border(0,255,0);
    for (size_t i = 0; i < faces.size(); i++){
        rectangle(img, faces[i], border);
    }
    
    imshow("Detection Based Tracker", img); // Show the results.
    
    while(waitKey(100) != 27){};
    
    return 0;
}
