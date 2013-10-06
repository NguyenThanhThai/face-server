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
    /*
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad( "haarcascade_frontalface_alt2.xml" );
    double scale = 1.3;

    static CvScalar colors[] = { {{0,0,255}}, {{0,128,255}}, {{0,255,255}}, 
    {{0,255,0}}, {{255,128,0}}, {{255,255,0}}, {{255,0,0}}, {{255,0,255}} };

    // Detect objects
    cvClearMemStorage( storage );
    CvSeq* objects = cvHaarDetectObjects( img, cascade, storage, 1.1, 4, 0, cvSize( 40, 50 ));

    CvRect* r;
    // Loop through objects and draw boxes
    for( int i = 0; i < (objects ? objects->total : 0 ); i++ ){
            r = ( CvRect* )cvGetSeqElem( objects, i );
            cvRectangle( img, cvPoint( r->x, r->y ), cvPoint( r->x + r->width, r->y + r->height ),
                    colors[i%8]);
    }
     */

    Scalar border(0,255,0);
    for (size_t i = 0; i < faces.size(); i++){
        rectangle(img, faces[i], border);
    }
    
    imshow("Detection Based Tracker", img); // Show the results.
    
    while(waitKey(100) != 27){};
    
    return 0;
}
