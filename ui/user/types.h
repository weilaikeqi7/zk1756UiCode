//
// Created by jinxing on 2026/1/30.
//

#ifndef ZKSL_75_6LC_TYPES_H
#define ZKSL_75_6LC_TYPES_H
#include <stdint.h>

typedef struct {
    int sendMsgQueId;
    int recvMsgQueId;
    volatile int g_quit;
} GlobalParameters;

typedef struct {
    int language_index;
    int self_pass_index;
    int sendKey;
    int recvKey;
    int set_w_res;
    int set_h_res;
    const char * fonts_path;
} AppArgs;

extern GlobalParameters global_parameters;
extern AppArgs app_args;
#endif //ZKSL_75_6LC_TYPES_H