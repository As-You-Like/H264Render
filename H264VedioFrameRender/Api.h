#pragma once

#include "windows.h"
#include "H264VedioFrameRender.h"

const int MaxStreamCount = 100;

H264VideoFrameRender** _streams;
int _streamCount = 0;
bool _isInitialized = false;
 
/*Initialize streams.
*/
extern "C" _declspec(dllexport) bool Init(int streamCount);

/*Stop all streams and release all.
*/
extern "C" _declspec(dllexport) void Release();

/* Initialize the render device for a stream.

@param videoRenderHandle, handle of the render target.
@param frameRate frame rate, max value is 1000.
Fill ZERO when use default(30).
Fill negative value to use realtime rendering, then Render will not wait interval time between frames.
@param videoWidth width of the video, fill ZERO when does not know.
@param videoHeight height of the video, fill ZERO when does not know.
*/
extern "C" _declspec(dllexport) bool InitDecoder(int streamIndex, HWND const videoRenderHandle, int const frameRate, int const videoWidth, int const videoHeight);

/* Feed decoder with H264 frame buffer, it will render when frame is decoded.
@warning This function is not thread safe!

@param Buffer address of H264 video buffer.
@param Byte size of the 264 data in buffer.
*/
extern "C" _declspec(dllexport) void FeedDecoder(int streamIndex, byte* const buffer, int const size);

/* Reset viewport of video render device on next frame.
Function will get client size from VideoRenderHandle, and create render device again, this action may take longer time between two frames.
*/
extern "C" _declspec(dllexport) void ResetViewport(int streamIndex);

/* Release decoder and render.
@warning This function is not thread safe!
*/
extern "C" _declspec(dllexport) void ReleaseDecoder(int streamIndex);