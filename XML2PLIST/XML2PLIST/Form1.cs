using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace XML2PLIST
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private string str = "";

        struct frames
        {
            public string frame;
            public string offset;
            public string rotated;
            public string sourceColorRect;
            public string sourceSize;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            str = "";
            str += "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>\n";
            str += "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"> \n<plist version = \"1.0\">\n";
            StreamReader sr = new StreamReader(textBox1.Text, Encoding.Default);
            Stack<string> st = new Stack<string>();
            st.Push("</plist>\n");
            str += "<dict>\n";
            st.Push("</dict>\n");
            str += "<key>frames</key>\n";
            str += "<dict>\n";
            st.Push("</dict>\n");
            string line;
            frames fm = new frames();
            while ((line = sr.ReadLine()) != null)
            {
                //<instance name="EnemySpearKnightWaveExplosion_Sprite" index="5" posX="0" posY="0" anchorX="-13421772.8" anchorY="-13421772.8" width="1" height="1"/>
                if (line.IndexOf("instance") == -1) continue;
                string[] res = line.Split(' ');
                for(int i=0;i<res.Length;i++)
                {
                    string t = res[i];
                    if (t.IndexOf('=') == -1) continue;
                    string[] tt = t.Split('=');
                    tt[1]=tt[1].Replace('"', ' ');tt[1]=tt[1].Trim();
                    if(tt[0]=="name")
                    {
                        string[] ttt = res[++i].Split('=');
                        ttt[1]=ttt[1].Replace('"', ' ');ttt[1]=ttt[1].Trim();
                        str += "<key>" + tt[1] + "_" + ttt[1] + ".png" + "</key>\n";
                        str += "<dict>\n";
                        st.Push("</dict>\n");
                    }
                    if(tt[0]=="posX")
                    {
                        fm.frame = "<string>{{" + tt[1] + ",";
                        string[] ttt = res[++i].Split('=');
                        ttt[1]=ttt[1].Replace('"', ' '); ttt[1]=ttt[1].Trim();
                        fm.frame += ttt[1] + "},{";
                    }
                    if(tt[0]=="width")
                    {
                        fm.offset= "<string>{0,0}</string>\n";
                        fm.rotated = "<false/>\n";
                        fm.frame += tt[1] + ",";
                        fm.sourceColorRect += "<string>{{0,0},{"+tt[1] + ",";
                        fm.sourceSize = "<string>{" + tt[1] + ",";
                        string[] ttt = res[++i].Split('=');
                        ttt[1]=ttt[1].Replace('"', ' '); ttt[1]=ttt[1].Trim();
                        ttt[1] = ttt[1].Replace("/>", "");ttt[1] = ttt[1].Trim();
                        fm.frame += ttt[1] + "}}</string>\n";
                        fm.sourceColorRect += ttt[1] + "}}</string>\n";
                        fm.sourceSize += ttt[1] + "}</string>\n";

                        str += "<key>frame</key>\n";
                        str += fm.frame;
                        str += "<key>offset</key>\n";
                        str += fm.offset;
                        str += "<key>rotated</key>\n";
                        str += fm.rotated;
                        str += "<key>sourceColorRect</key>\n";
                        str += fm.sourceColorRect;
                        str += "<key>sourceSize</key>\n";
                        str += fm.sourceSize;
                        str += st.Pop();

                        fm = new frames();
                    }
                }
            }
            while(st.Count!=0)
            {
                str += st.Pop();
            }
            textBox1.Text = str;
            sr.Close();
        }
    }
}
