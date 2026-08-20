//
// Created by jinxing on 2026/1/30.
//

#ifndef ZKSL_75_6LC_TYPES_H
#define ZKSL_75_6LC_TYPES_H
#include <stdint.h>

typedef struct {
    int sendKey;
    int recvKey;
    int sendMsgQueId;
    int recvMsgQueId;
} GlobalParameters;

extern GlobalParameters global_parameters;
#endif //ZKSL_75_6LC_TYPES_H