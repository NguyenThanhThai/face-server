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

using namespace std;
using namespace cv;


#include "FaceServiceImpl.h"

Mat* readImageFromRequest(TFaceDetectResponse& _return, const TImage& request);

FaceServiceImpl::FaceServiceImpl(const int8_t threads) {
}


FaceServiceImpl::~FaceServiceImpl() {
}

int8_t FaceServiceImpl::handlePing() {
    return 0;
}

void FaceServiceImpl::handleDetectFaces(TFaceDetectResponse& _return, const TImage& request) {
    //Mat* img = new Mat();
    //imdecode();
    Mat* img = readImageFromRequest(_return, request);
    if (img == NULL) {
        return;
    }
}

Mat* readImageFromRequest(TFaceDetectResponse& _return, const TImage& request) {
    if (request.data.size() < 1) {
        _return.__set_error("Invalid data");
        return NULL;
    }
    cout << "request image w:" << request.width << ", h:" << request.height << "\n";

    return NULL;
}
