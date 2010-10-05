using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace BlobbyWarriors
{
    class Main : OpenTK.GameWindow
    {
        public Main()
            : base(800, 600)
        {
            GL.ClearColor(Color.Red);
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            base.OnRenderFrame(e);
        }

        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            base.OnUpdateFrame(e);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            OpenTK.Graphics.GraphicsContext.CurrentContext.SwapBuffers();
        }
    }
}
