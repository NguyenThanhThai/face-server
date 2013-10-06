/**
* Main service thrift definition file.
*/

struct TImage {
    1: required list<byte> data;
    2: optional i16 width;
    3: optional i16 height;
}

struct TFaceRect {
    1: i16 x;
    2: i16 y;
    3: i16 w;
    4: i16 h;
}

struct TFaceDetectResponse {
    1: optional list<TFaceRect> faces;
    2: optional string error;
}

service FaceService {
    /**
    * Check server health status
    * @return 0 if server is okay
    */
    byte ping(),

    TFaceDetectResponse detectFaces(1:TImage request),
    
}