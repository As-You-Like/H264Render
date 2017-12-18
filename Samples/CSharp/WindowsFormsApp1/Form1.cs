using System;
using System.IO;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private const string H264File = "D:\\temp\\720.h264";

        bool _isRendering;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            H264Player.Init(panel1.Handle, 30, 0, 0);
            new Thread(new ThreadStart(readBuffer)).Start();
        }

        private void readBuffer()
        {
            var file = File.OpenRead(H264File);

            var buffer = new byte[4096];
            var position = 0;
            var len = 0;

            _isRendering = true;
            while (_isRendering && (len = file.Read(buffer, 0, buffer.Length)) > 0)
            {
                position += len;
                H264Player.Decode(buffer, len);
            }
            H264Player.Release();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            _isRendering = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            H264Player.ResetViewport();
        }
    }
}
