using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace task1_good_
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "45";
            textBox2.Text = "90";
            textBox3.Text = "150";
        }

        
        private int x2, y2, start_x, start_y;
        private double R, r, h, sin, cos, fi = 0; // R - радиус большого круга (статичный), r - радиус малого круга 

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            label1.Text = "Status: End";
            timer1.Enabled = false;

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }



        //(движется по внутренней части большого круга) , h - длина прямой
        //кот выходит из центра маленького круга
        private SolidBrush B = new SolidBrush(Color.Red);

        private void Form1_Load(object sender, EventArgs e)
        {
            start_x = pictureBox1.Width / 2;
            start_y = pictureBox1.Height / 2;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            R = Convert.ToDouble(textBox3.Text.ToString());
            r = Convert.ToDouble(textBox2.Text.ToString());
            h = Convert.ToDouble(textBox1.Text.ToString());
            if (R <= 0 || r <= 0 || h <= 0)
            {
                MessageBox.Show("Wrong value");
                return;
            }
            label1.Text = "Status: Rendered";
            timer1.Enabled = true;
            pictureBox1.Invalidate();
            fi = 0;
            sin = Math.Sin(fi);
            cos = Math.Cos(fi);
            x2 = start_x + (int)((R - r) * cos + h * (Math.Cos((R - r) / r * fi)));
            y2 = start_y - (int)((R - r) * sin - h * (Math.Sin((R - r) / r * fi)));

            Graphics  gr = pictureBox1.CreateGraphics();
            gr.Clear(Color.White);
            gr.FillEllipse(B, x2, y2, 5, 5);
            timer1.Enabled = true;
        }
        
        private void timer1_Tick(object sender, EventArgs e)
        {
            fi += 0.02;
            sin = Math.Sin(fi);
            cos = Math.Cos(fi);
            x2 = start_x + (int)((R - r) * cos + h * (Math.Cos((R - r) / r * fi)));
            y2 = start_y - (int)((R - r) * sin - h * (Math.Sin((R - r) / r * fi)));

            Graphics gr = pictureBox1.CreateGraphics();
            gr.FillEllipse(B, x2, y2, 5, 5);
            if (y2 > pictureBox1.Height || y2 < 0 || x2 > pictureBox1.Width || x2 < 0)
            {
                label1.Text = "Status: Out of range";
                timer1.Enabled = false;
            }
        }
    }
}
