#include "VideoRecorderBridge.h"
#import "VideoRecorder.h"

void VideoRecorderBridge::begin()
{
    [[VideoRecorder getInstance] start];
}
void VideoRecorderBridge::end()
{
    [[VideoRecorder getInstance] stop];
}