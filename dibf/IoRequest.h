#pragma once
#include "stdafx.h"
#include "common.h"
#include "FuzzingProvider.h"

#define MAX_IOCTLS 512
#define DEEP_BF_MAX ((DWORD)32)
#define DEFAULT_OUTLEN ((DWORD)256)

class IoRequest
{
public:
    IoRequest();
    IoRequest(HANDLE);
    IoRequest(HANDLE, DWORD);
    ~IoRequest();
    OVERLAPPED overlp; // oop?
    DWORD GetIoCode() {return iocode;}
    VOID SetIoCode(DWORD iocode) {this->iocode=iocode;}
    BOOL testSendForValidRequest(BOOL);
    BOOL testSendForValidBufferSize(DWORD);
    VOID reset();
    BOOL sendSync();
    DWORD sendAsync();
    BOOL fuzz(FuzzingProvider*, mt19937*);
private:
    // Static arrays of known interesting errors
    static const DWORD invalidIoctlErrorCodes[];
    static const DWORD invalidBufSizeErrorCodes[];
    // Members
    HANDLE hDev;
    DWORD iocode;
    vector<UCHAR> inBuf;
    vector<UCHAR> outBuf;
    // Functions
    BOOL allocBuffers(DWORD, DWORD);
    BOOL sendRequest(BOOL, PDWORD);
    DWORD getInputBufferLength(){return inBuf.size()*sizeof(UCHAR);}
    DWORD getOutputBufferLength(){return outBuf.size()*sizeof(UCHAR);}
};