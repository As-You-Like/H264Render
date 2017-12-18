/**
* Please leave this part, in memory of:
* 雷霄骅
* 中国传媒大学/数字电视技术
*
* Original source code will be found here:
* http://blog.csdn.net/leixiaohua1020/article/details/40279297
* http://blog.csdn.net/leixiaohua1020/article/details/42181571
*/

#pragma once
#include <stdio.h>
#include <tchar.h>
#include <d3d9.h>
#include <windows.h>  

#define __STDC_CONSTANT_MACROS
extern "C"
{

#include "libavcodec/avcodec.h" 
};

const AVCodecID codec_id = AV_CODEC_ID_H264;
const AVPixelFormat DecoderOutputType = AV_PIX_FMT_YUV420P;

const D3DFORMAT RenderFormat = (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2');
const int BitsPerPoint_YV12 = 12;

const int DefaultFrameRate = 30;

HWND VideoRenderHandle;
//Whole client area in render target.
RECT VideoViewport;
//Original size of the previous decoded video frame.
int VideoWidth, VideoHeight;
//Current render area where video is rendered within.
RECT VideoRenderArea;
int VideoFrameRate = DefaultFrameRate;

D3DCOLOR VideoBackColor = D3DCOLOR_XRGB(0, 0, 0);
//Set false when want to stop decoding work.
bool IsWorking = true;

//private fields.
AVCodec *pCodec;
AVCodecContext *pCodecCtx = NULL;
AVCodecParserContext *pCodecParserCtx = NULL;

//For internal use only, this field is used to contain decoded frame while decoding video.
AVFrame	*_decodedFrame;
//For internal use only, this field is only calculated on frame rate is set on init().
int _frameTime = 1000 / VideoFrameRate;
//For internal use only, this field is set true when ResetViewport() is called, then we'll reset render devices on next frame.
bool _isViewportResetRequired = false;

/* Initialize the render device.

@warning This method is only valid when VideoWidth and VideoHeight has valid value.
*/
bool initRender();
//Adjust the VideoRenderArea in VideoViewport, will keep the w-h ratio while adjusting.
void adjustRenderSize(int videoWidth, int videoHeight);
bool render(AVFrame* const pFrame);
void releaseRender();

/* Initialize decoder.
@warning This function is not thread safe!

@param videoRenderHandle, handle of the render target.
@param frameRate frame rate, max value is 1000.
		Fill ZERO when use default(30).
		Fill negative value to use realtime rendering, then Render will not wait interval time between frames.
@param videoWidth width of the video, fill ZERO when does not know.
@param videoHeight height of the video, fill ZERO when does not know.
*/
extern "C" _declspec(dllexport) bool InitDecoder(HWND const videoRenderHandle, int const frameRate, int const videoWidth, int const videoHeight);

/* Feed decoder with H264 frame buffer, it will render when frame is decoded.
@warning This function is not thread safe!

@param Buffer address of H264 video buffer.
@param Byte size of the 264 data in buffer.
*/
extern "C" _declspec(dllexport) void FeedDecoder(byte* const buffer, int const size);

/* Reset viewport of video render device.
   Function will get client size from VideoRenderHandle, and create render device again.
*/
extern "C" _declspec(dllexport) void ResetViewport();

/* Release decoder and render.
@warning This function is not thread safe!
*/
extern "C" _declspec(dllexport) void ReleaseDecoder();

//For test.
void read264File();