//#pragma comment(lib, "d3d9.lib")

#include "H264VedioFrameRender.h"

char filepath_in[] = "D:/temp/720.h264";

//For test in application mode.
int main(int argc, char* argv[])
{
	InitDecoder((HWND)198886, 30, 0, 0);

	read264File();

	ReleaseDecoder();
}

//For test.
void read264File()
{
	const int in_buffer_size = 4096;

	int size;
	byte buffer[in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE] = { 0 };

	FILE *fp_in;

	fp_in = fopen(filepath_in, "rb");
	if (!fp_in) {
		printf("Could not open input stream\n");
		return;
	}

	while (IsWorking) {
		size = fread(buffer, 1, in_buffer_size, fp_in);
		if (size == 0) {
			break;
		}
		FeedDecoder(buffer, size);
	}

	fclose(fp_in);
}

IDirect3D9* _d3d = NULL;
IDirect3DDevice9* _device = NULL;
IDirect3DSurface9* _surface = NULL;

void releaseRender()
{
	if (_surface) {
		_surface->Release();
	}

	if (_device) {
		_device->Release();
	}

	if (_d3d) {
		_d3d->Release();
	}
}

//todo: try the dangerous part.
bool initRender()
{
	if (VideoWidth <= 0 || VideoHeight <= 0) {
		return false;
	}

	releaseRender();

	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (_d3d == NULL) {
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	GetClientRect(VideoRenderHandle, &VideoViewport);
	adjustRenderSize(VideoWidth, VideoHeight);

	if (FAILED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, VideoRenderHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_device))) {
		return false;
	}
	if (FAILED(_device->CreateOffscreenPlainSurface(VideoWidth, VideoHeight, RenderFormat, D3DPOOL_DEFAULT, &_surface, NULL))) {
		return false;
	}

	return true;
}

void adjustRenderSize(int videoWidth, int videoHeight)
{
	int w, h;

	if (MulDiv(videoWidth, VideoViewport.bottom - VideoViewport.top, videoHeight) <= VideoViewport.right - VideoViewport.left)
	{
		w = MulDiv(VideoViewport.bottom - VideoViewport.top, videoWidth, videoHeight);
		h = VideoViewport.bottom - VideoViewport.top;
	}
	else
	{
		w = VideoViewport.right - VideoViewport.left;
		h = MulDiv(VideoViewport.right - VideoViewport.left, videoHeight, videoWidth);
	}

	VideoRenderArea.left = VideoViewport.left + (VideoViewport.right - VideoViewport.left - w) / 2;
	VideoRenderArea.top = VideoViewport.top + (VideoViewport.bottom - VideoViewport.top - h) / 2;
	VideoRenderArea.right = VideoRenderArea.left + w;
	VideoRenderArea.bottom = VideoRenderArea.top + h;
}

bool render(AVFrame* const pFrame)
{
	if (_surface == NULL) {
		return false;
	}
	D3DLOCKED_RECT d3d_rect;
	if (FAILED(_surface->LockRect(&d3d_rect, NULL, D3DLOCK_DONOTWAIT))) {
		return false;
	}

	byte* pDest = (byte*)d3d_rect.pBits;
	int stride = d3d_rect.Pitch;

	int	w2 = pFrame->width / 2, h2 = pFrame->height / 2;
	int s2 = stride / 2;
	//Tip: I don't know which is u or v, so I guessed and created the variant names: dpu,dpv,spu,spv.
	int dpy = 0, dpu = dpy + stride * pFrame->height, dpv = dpu + s2 * h2;
	int spy = 0, spu = 0, spv = 0;

	for (int i = 0; i < pFrame->height; i++) {
		memcpy(pDest + dpy, pFrame->data[0] + spy, pFrame->width);
		dpy += stride;
		spy += pFrame->linesize[0];

		if (i < h2) {
			memcpy(pDest + dpv, pFrame->data[1] + spu, w2);
			dpv += s2;
			spu += pFrame->linesize[1];
			memcpy(pDest + dpu, pFrame->data[2] + spv, w2);
			dpu += s2;
			spv += pFrame->linesize[2];
		}
	}

	if (FAILED(_surface->UnlockRect())) {
		return false;
	}

	if (_device == NULL) {
		return false;
	}

	_device->Clear(0, NULL, D3DCLEAR_TARGET, VideoBackColor, 1.0f, 0);
	_device->BeginScene();
	IDirect3DSurface9 * pBackBuffer = NULL;
	_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	_device->StretchRect(_surface, NULL, pBackBuffer, &VideoRenderArea, D3DTEXF_LINEAR);
	_device->EndScene();
	_device->Present(NULL, NULL, NULL, NULL);

	return true;
}

//todo: try the dangerous part.
bool InitDecoder(HWND const videoRenderHandle, int const frameRate, int const videoWidth, int const videoHeight)
{
	avcodec_register_all();

	pCodec = avcodec_find_decoder(codec_id);
	if (!pCodec) {
		printf("Codec not found\n");
		return false;
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (!pCodecCtx) {
		printf("Could not allocate video codec context\n");
		return false;
	}

	if (videoWidth > 0) {
		pCodecCtx->width = videoWidth;
		pCodecCtx->coded_width = videoWidth;
	}

	if (videoHeight > 0) {
		pCodecCtx->height = videoHeight;
		pCodecCtx->coded_height = videoHeight;
	}

	pCodecCtx->pix_fmt = DecoderOutputType;

	pCodecParserCtx = av_parser_init(codec_id);
	if (!pCodecParserCtx) {
		printf("Could not allocate video parser context\n");
		return false;
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec\n");
		return false;
	}
	_decodedFrame = av_frame_alloc();

	VideoRenderHandle = videoRenderHandle;

	VideoFrameRate = frameRate == 0 ? DefaultFrameRate : frameRate;
	if (VideoFrameRate > 1000) {
		VideoFrameRate = 1000;
	}
	_frameTime = 1000 / frameRate;
	VideoWidth = 0;
	VideoHeight = 0;

	IsWorking = true;

	return true;
}

//todo: buffer maybe unsafe or not accessable, so..
//todo: this method is not thread safe as feed while initializing may cause crash.
void FeedDecoder(byte* const buffer, int const size)
{
	AVPacket packet;

	av_init_packet(&packet);

	byte* bufferPosition = buffer;
	int leftSize = size;

	int decodeResult = 0, got_picture = 0;

	while (IsWorking && leftSize > 0) {
		int len = av_parser_parse2(pCodecParserCtx, pCodecCtx, &packet.data, &packet.size, bufferPosition, leftSize,
			AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);

		bufferPosition += len;
		leftSize -= len;

		if (packet.size == 0) {
			continue;
		}

		decodeResult = avcodec_decode_video2(pCodecCtx, _decodedFrame, &got_picture, &packet);
		if (decodeResult <= 0 || got_picture == 0) {
			continue;
		}

		//Not initialized.
		if (_device == NULL) {
			VideoWidth = _decodedFrame->width;
			VideoHeight = _decodedFrame->height;
			initRender();
		}
		//Reseting viewport
		else if (_isViewportResetRequired) {
			VideoWidth = _decodedFrame->width;
			VideoHeight = _decodedFrame->height;
			releaseRender();
			initRender();
			_isViewportResetRequired = false;
		}
		//Video size changed.
		else if (_decodedFrame->width != VideoWidth || _decodedFrame->height != VideoHeight) {
			VideoWidth = _decodedFrame->width;
			VideoHeight = _decodedFrame->height;
			adjustRenderSize(VideoWidth, VideoHeight);
		}

		render(_decodedFrame);

		if (_frameTime > 0) {
			Sleep(_frameTime);
		}
	}
}

void ResetViewport()
{
	_isViewportResetRequired = true;
}

void ReleaseDecoder()
{
	IsWorking = false;

	releaseRender();

	if (pCodecParserCtx) {
		av_parser_close(pCodecParserCtx);
	}

	if (pCodecCtx) {
		avcodec_close(pCodecCtx);
	}

	if (pCodecCtx) {
		av_free(pCodecCtx);
	}

	if (_decodedFrame) {
		av_frame_free(&_decodedFrame);
	}
}