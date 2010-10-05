using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace BlobbyWarriors
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Main m = new Main();
            m.Run();
        }
    }
}
