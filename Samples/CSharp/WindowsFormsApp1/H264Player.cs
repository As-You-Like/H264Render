using System;
using System.Runtime.InteropServices;

namespace WindowsFormsApp1
{
    internal class H264Player
    {
        const string H264Decoder = "H264VedioFrameRender.dll";

        /// <summary>
        /// Initialize the decoder and render device.
        /// </summary>
        /// <param name="videoRenderHandle">Handle where video will be rendered on.</param>
        /// <param name="frameRate">Frame rate of video, Zero for default(30), nagetive for realtime(not interval between frames).</param>
        /// <param name="videoWidth">Fill video width if konw, or fill ZERO.</param>
        /// <param name="videoHeight"Fill video height if konw, or fill ZERO.></param>
        /// <returns>True when decoder is initialized.</returns>
        /// 
        /// <remarks>
        /// This method is not thread safe, do not try to <see cref="Init(IntPtr, int, int, int)"/> while decoding or rending.
        /// </remarks>
        [DllImport(H264Decoder, EntryPoint = "InitDecoder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Init(IntPtr videoRenderHandle, int frameRate, int videoWidth, int videoHeight);

        /// <summary>
        /// Decode data in buffer and render decoded frame on Render handle.
        /// </summary>
        /// <param name="buffer">H264 buffer.</param>
        /// <param name="size">Buffer data size in buffer.</param>
        /// 
        /// <remarks>
        /// This method is not thread safe, make sure<see cref="Init(IntPtr, int, int, int)"/> is called and <see cref="Release"/> must not be called when decode video buffer.
        /// </remarks>
        [DllImport(H264Decoder, EntryPoint = "FeedDecoder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]

        public static extern void Decode(byte[] buffer, int size);

        /// <summary>
        /// Reset render viewport, this method is not thread safe.
        /// </summary>
        /// <remarks>
        /// This method is only valid when video is rendering.
        /// </remarks>
        [DllImport(H264Decoder, EntryPoint = "ResetViewport", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResetViewport();

        /// <summary>
        /// Release render device and decoder.
        /// </summary>
        /// <remarks>
        /// This method is not thread safe, you must stop <see cref="Decode/> before <see cref="Release"/>.
        /// </remarks>
        [DllImport(H264Decoder, EntryPoint = "ReleaseDecoder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Release();
    }
}
