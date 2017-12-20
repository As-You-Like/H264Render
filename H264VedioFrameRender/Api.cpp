#include "Api.h"

char filepath_in[] = "D:/temp/720.h264";

//For test in application mode.
int main(int argc, char* argv[])
{
	Init(2);

	InitDecoder(0, (HWND)525740, 30, 0, 0);
	InitDecoder(1, (HWND)526340, 30, 0, 0);

	const int in_buffer_size = 4096;

	int size;
	byte buffer[in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE] = { 0 };

	FILE *fp_in;

	fp_in = fopen(filepath_in, "rb");
	if (!fp_in) {
		printf("Could not open input stream\n");
		return 1;
	}

	while (_isInitialized) {
		size = fread(buffer, 1, in_buffer_size, fp_in);
		if (size == 0) {
			break;
		}
		FeedDecoder(0, buffer, size);
		FeedDecoder(1, buffer, size);
	}

	fclose(fp_in);

	Release();
}

bool Init(int streamCount)
{
	if (streamCount > MaxStreamCount) {
		streamCount = MaxStreamCount;
	}

	if (streamCount < 1) {
		streamCount = 1;
	}

	_streamCount = streamCount;
	_streams = new H264VideoFrameRender*[streamCount];

	for (int i = 0; i < _streamCount; i++)
	{
		_streams[i] = new H264VideoFrameRender();
	}
	_isInitialized = true;
	return true;
}

void Release()
{
	_isInitialized = false;
	H264VideoFrameRender *render;
	for (int i = 0; i < _streamCount; i++)
	{
		render = _streams[i];
		if (render == NULL) {
			continue;
		}

		_streams[i] = NULL;
		render->ReleaseDecoder();
		delete[] render;
	}

	delete _streams;
}

bool InitDecoder(int streamIndex, HWND const videoRenderHandle, int const frameRate, int const videoWidth, int const videoHeight)
{
	if (!_isInitialized || streamIndex < 0 || streamIndex >= _streamCount)
	{
		return false;
	}

	if (_streams[streamIndex] == NULL) {
		_streams[streamIndex] = new H264VideoFrameRender();
	}

	return _streams[streamIndex]->InitDecoder(videoRenderHandle, frameRate, videoWidth, videoHeight);
}

void FeedDecoder(int streamIndex, byte* const buffer, int const size)
{
	if (!_isInitialized || _streams[streamIndex] == NULL || streamIndex < 0 || streamIndex >= _streamCount)
	{
		return;
	}

	_streams[streamIndex]->FeedDecoder(buffer, size);
}

void ResetViewport(int streamIndex)
{
	if (!_isInitialized || _streams[streamIndex] == NULL || streamIndex < 0 || streamIndex >= _streamCount)
	{
		return;
	}

	_streams[streamIndex]->ResetViewport();
}

void ReleaseDecoder(int streamIndex)
{
	if (!_isInitialized || _streams[streamIndex] == NULL || streamIndex < 0 || streamIndex >= _streamCount)
	{
		return;
	}

	H264VideoFrameRender* render = _streams[streamIndex];
	_streams[streamIndex] = NULL;

	render->ReleaseDecoder();
	delete[] render;
}