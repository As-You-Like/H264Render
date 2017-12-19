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
            txtLeft.Text = pnlLeft.Handle.ToInt32().ToString();
            txtCenter.Text = pnlCenter.Handle.ToInt32().ToString();
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
                H264Player.Decode(0, buffer, len);
                H264Player.Decode(1, buffer, len);
            }
            H264Player.Release();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            _isRendering = false;
        }

        private void btnStopLeft_Click(object sender, EventArgs e)
        {
            H264Player.ReleaseDecoder(0);
        }

        private void btnStopCenter_Click(object sender, EventArgs e)
        {
            H264Player.ReleaseDecoder(1);
        }

        private void pnlLeft_Resize(object sender, EventArgs e)
        {
            H264Player.ResetViewport(0);
        }

        private void pnlCenter_Resize(object sender, EventArgs e)
        {
            H264Player.ResetViewport(1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var is0 = H264Player.Init(2);
            var is1 = H264Player.InitDecoder(0, pnlLeft.Handle, 30, 0, 0);
            var is2 = H264Player.InitDecoder(1, pnlCenter.Handle, 30, 0, 0);

            new Thread(new ThreadStart(readBuffer)).Start();
        }
    }
}
