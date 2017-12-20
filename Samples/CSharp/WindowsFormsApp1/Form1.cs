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

        private void readBuffer(object indexObj)
        {
            var index = Convert.ToInt32(indexObj);

            var file = File.OpenRead(H264File);

            var buffer = new byte[4096];
            var position = 0;
            var len = 0;

            _isRendering = true;
            while (_isRendering && (len = file.Read(buffer, 0, buffer.Length)) > 0)
            {
                position += len;
                H264PlayerM.Decode(index, buffer, len);
            }
            H264PlayerM.Release();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            _isRendering = false;
        }

        private void btnStopLeft_Click(object sender, EventArgs e)
        {
            H264PlayerM.ReleaseDecoder(0);
        }

        private void btnStopCenter_Click(object sender, EventArgs e)
        {
            H264PlayerM.ReleaseDecoder(1);
        }

        private void pnlLeft_Resize(object sender, EventArgs e)
        {
            H264PlayerM.ResetViewport(0);
        }

        private void pnlCenter_Resize(object sender, EventArgs e)
        {
            H264PlayerM.ResetViewport(1);
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            var is0 = H264PlayerM.Init(2);
            var is1 = H264PlayerM.InitDecoder(0, pnlLeft.Handle, 30, 0, 0);
            var is2 = H264PlayerM.InitDecoder(1, pnlCenter.Handle, 30, 0, 0);

            new Thread(new ParameterizedThreadStart(readBuffer)).Start(0);
            new Thread(new ParameterizedThreadStart(readBuffer)).Start(1);
        }
    }
}
