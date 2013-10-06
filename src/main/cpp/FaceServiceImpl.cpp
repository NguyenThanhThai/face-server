/* 
 * File:   FaceServiceImpl.cpp
 * Author: mamad
 * 
 * Created on 06 October 2013, 20:34
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


#include "FaceServiceImpl.h"
#include "service_types.h"

int readImageFromRequest(TFaceDetectResponse& _return, const TImage& request, Mat* dst);

FaceServiceImpl::FaceServiceImpl(const int8_t threads) {
     pClassifier = new CascadeClassifier("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
}

FaceServiceImpl::~FaceServiceImpl() {
    if (pClassifier != NULL) {
        delete pClassifier;
    }
}

int8_t FaceServiceImpl::handlePing() {
    return 0;
}

void FaceServiceImpl::handleDetectFaces(TFaceDetectResponse& _return, const TImage& request) {
    Mat* img = new Mat();
    if (readImageFromRequest(_return, request, img) != 0) {
        delete img;
        return;
    }

    vector<Rect> faces;
    pClassifier->detectMultiScale(*img, faces);
    printf("Faces detected:%d\n", faces.size());
    vector<TFaceRect> tFaces;
    for (size_t i = 0; i < faces.size(); i++){
        TFaceRect tFace;        
        tFace.__set_x(faces[i].x);
        tFace.__set_y(faces[i].y);
        tFace.__set_w(faces[i].width);
        tFace.__set_h(faces[i].height);
        tFaces.push_back(tFace);
    }
    
    _return.__set_faces(tFaces);
    delete img;
}

int readImageFromRequest(TFaceDetectResponse& _return, const TImage& request, Mat* dst) {
    if (request.data.size() < 1) {
        _return.__set_error("Invalid data");
        return -1;
    }
    char* data = (char*) & request.data[0];
    Mat mat((int) request.width, (int) request.height, CV_8U, data);

    imdecode(mat, CV_LOAD_IMAGE_COLOR, dst);
    printf("image dimensions (%d, %d)\n", dst->rows, dst->cols);
    return 0;
}
