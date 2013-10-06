/* 
 * File:   FaceServiceImpl.h
 * Author: mamad
 *
 * Created on 06 October 2013, 20:34
 */

#ifndef FACESERVICEIMPL_H
#define	FACESERVICEIMPL_H
#include "../../../build/gen-cpp/service_constants.h"
#include "../../../build/gen-cpp/service_types.h"
#include "../../../build/gen-cpp/FaceService.h"

class FaceServiceImpl : virtual public FaceServiceIf {
public:
    FaceServiceImpl(const int8_t threads);
    virtual ~FaceServiceImpl();

    int8_t ping() {
        return handlePing();
    };

    void detectFaces(TFaceDetectResponse& _return, const TImage& request) {
        handleDetectFaces(_return, request);
    };

private:
    int8_t handlePing();
    void handleDetectFaces(TFaceDetectResponse& _return, const TImage& request);
};

#endif	/* FACESERVICEIMPL_H */

