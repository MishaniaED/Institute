using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;

namespace task3
{
    
    //        g.FillClosedCurve(brush, p);
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        PointF[] points = new PointF[80]; // 2 точки: 1--elips, 2--rect 
      
        Graphics gr;
        SolidBrush fill = new SolidBrush(Color.Red);

        int height = 700;
        int width = 320;
        int size_x_1, size_x_2, size_y_1, size_y_2;
        int x_1, y_1;
        int x_2, y_2;




        private float To_X(float x, float x_max, float x_min)
        {
            
            float x1 = -18, x2 = (height+26) * 10 / width; 
            return (((x - x1) * (x_max - x_min)) / (x2 - x1)) + x_min;
        }

        private float To_Y(float y, float y_max, float y_min)
        {
            float y1 = 0, y2 = 18;
            return (y_max - (((y - y1) * (y_max - y_min)) / (y2 - y1)));
        }

       /* private void Graph_func()
        {
            PointF[] x = new PointF[6], y = new PointF[6];
            Pen pen = new Pen(Color.Black, 3.0f);
            int i, j = 0;

            for (i = -30; i < 30; i += 10)
                x[j++] = new PointF(To_X(0, height, 10), To_Y(i, width, 0));
            j = 0;

            for (i = -30; i < 30; i += 10)
                y[j++] = new PointF(To_X(i, height, 10), To_Y(0, width, 0));
            gr.DrawLines(pen, x);
            gr.DrawLines(pen, y);

        }*/
       /* private float function(float x)
        {
            if (x > -1 && x <= -0.5)
                return ((float)Math.Sqrt(1 * (1 - x * x) / 4));
            else if (x < 1 && x >= 0.5)
                return (float)Math.Sqrt(1 * (1 - x * x) / 4);
            return 0;
        }*/

        private void button1_Click(object sender, EventArgs e)
        {
            gr = this.pictureBox1.CreateGraphics();

            System.Drawing.Drawing2D.GraphicsPath[] graphics_paths = new System.Drawing.Drawing2D.GraphicsPath[3];
            for (int i = 0; i < graphics_paths.Length; i++)
                graphics_paths[i] = new GraphicsPath();

            height = pictureBox1.Height / 2; width = pictureBox1.Width / 2;
            size_x_1 = 100; size_x_2 = 50; size_y_1 = 50; size_y_2 = 50;
            x_1 = width - size_x_1 / 2; y_1 = height - size_y_1 / 2;
            x_2 = width - size_x_2 / 2; y_2 = height - size_y_2 / 2;

            gr.Clear(Color.White);

            points[0] = new PointF(x_1, y_1);
            points[1] = new PointF(x_2, y_2);

            gr.FillEllipse(fill, points[0].X, points[0].Y, size_x_1, size_y_1);
            fill = new SolidBrush(Color.White);
            gr.FillRectangle(fill, points[1].X, points[1].Y, size_x_2, size_y_2);


            gr.DrawLine(Pens.Black, width, 0, width, pictureBox1.Height);
            gr.DrawLine(Pens.Black, 0, height, pictureBox1.Width, height);

            textBox3.Text = "0,5";
            //button4_Click(sender, e);

            button1.Visible = true;
            button2.Visible = true;
            button4.Visible = true;
            button5.Visible = true;
            
            button7.Visible = true;
            button8.Visible = true;
            button9.Visible = true;
            button10.Visible = true;

            textBox1.Visible = true;
            textBox2.Visible = true;
            textBox3.Visible = true;
            textBox4.Visible = true;
            textBox5.Visible = true;
            textBox6.Visible = true;
        }

        private void Multiply( float[,] transform_matrix, float[,] res)
        {
            //double[,] res = new double[points.Length, 3];
            for (int i = 0; i < points.Length; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    res[i, j] += points[i].X * transform_matrix[0, j];
                    res[i, j] += points[i].Y * transform_matrix[1, j];
                    res[i, j] += 1 * transform_matrix[2, j];
                }
                points[i] = new PointF((float)res[i, 0], (float)res[i, 1]);
                
            }
        }

        private void button4_Click(object sender, EventArgs e) // масштабирование +
        {
            float[,] Matrix = new float[3, 3];
            double tmp;
            if (textBox3.Text == "" || !double.TryParse(textBox3.Text, out tmp))
            { 
                MessageBox.Show("Неверный формат данных");
                return;
            }
            float scx = (float)System.Convert.ToDouble(textBox3.Text);
            Matrix[0, 0] = 1; Matrix[0, 1] = 0; Matrix[0, 2] = 0;
            Matrix[1, 0] = 0; Matrix[1, 1] = 1; Matrix[1, 2] = 0;
            Matrix[2, 0] = 0; Matrix[2, 1] = 0; Matrix[2, 2] = scx;


            
            gr = this.pictureBox1.CreateGraphics();

            height = pictureBox1.Height / 2; width = pictureBox1.Width / 2;

            gr.Clear(Color.White);

            for (int i = 0; i < 2; ++i)
            {
                float[,] res = new float[points.Length, 3];
                float[,] xy = { { points[i].X, points[i].Y, 1 } };
                Multiply(Matrix, res);

                //points[i] = new PointF((res[0,0] / res[0,2]), (res[0,1] / res[0,2]));
                /*points[i].X += 320;
                points[i].Y += width;*/
            }

            /*size_x_1 = (int)(size_x_1 * scx);
            size_x_2 = (int)(size_x_2 * scx);
            size_y_1 = (int)(size_y_1 * scx);
            size_y_2 = (int)(size_y_2 * scx);
            x_1 = width - size_x_1 / 2; y_1 = height - size_y_1 / 2;
            x_2 = width - size_x_2 / 2; y_2 = height - size_y_2 / 2;*/

            gr.FillEllipse(fill, points[0].X, points[0].Y, size_x_1, size_x_2);
            fill = new SolidBrush(Color.White);
            gr.FillRectangle(fill, points[1].X, points[1].Y, size_y_1, size_y_2);


            gr.DrawLine(Pens.Black, width, 0, width, pictureBox1.Height);
            gr.DrawLine(Pens.Black, 0, height, pictureBox1.Width, height);

        }

        private void button5_Click(object sender, EventArgs e) // перемещение по осям +
        {
            int tmp;
            if (textBox1.Text == "" || !int.TryParse(textBox1.Text, out tmp) || textBox2.Text == ""|| !int.TryParse(textBox2.Text, out tmp))
            {
                MessageBox.Show("Неверный формат данных!");
                return;
            }

            int gox = System.Convert.ToInt32(textBox1.Text);
            int goy = -System.Convert.ToInt32(textBox2.Text);

            float[,] Matrix = new float[3, 3];
            Matrix[0,0] = 1; Matrix[0,1] = 0; Matrix[0,2] = 0;
            Matrix[1,0] = 0; Matrix[1,1] = 1; Matrix[1,2] = 0;
            Matrix[2,0] = gox; Matrix[2,1] = goy; Matrix[2,2] = 1;

            for (int i = 0; i < 2; ++i)
            {
                float[,] res = new float[points.Length, 3];
                float[,] xy = { { points[i].X, points[i].Y, 1 } };
                Multiply(Matrix, res);
                //points[i] = new PointF((res[0,0] / res[0,2]), (res[0,1] / res[0,2]));
                /* points[i].X += 320;
                 points[i].Y += width;*/
            }

            gr.Clear(Color.White);

            gr.FillEllipse(fill, points[0].X, points[0].Y, size_x_1, size_y_1);
            fill = new SolidBrush(Color.White);
            gr.FillRectangle(fill, points[1].X, points[1].Y, size_x_2, size_y_2);


            gr.DrawLine(Pens.Black, width, 0, width, pictureBox1.Height);
            gr.DrawLine(Pens.Black, 0, height, pictureBox1.Width, height);

            /* gr.Clear(Color.White);

             SolidBrush fill = new SolidBrush(Color.Red);
             System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
             path.AddLines(points);
             gr.FillPath(fill, path);
             Graph_func();*/
        }

        private void button8_Click(object sender, EventArgs e) // отражение относительно оси X +
        {
            float[,] Matrix = new float[3, 3];

            Matrix[0, 0] = 1; Matrix[0, 1] = 0; Matrix[0, 2] = 0;
            Matrix[1, 0] = 0; Matrix[1, 1] = -1; Matrix[1, 2] = 0;
            Matrix[2, 0] = 0; Matrix[2, 1] = 0; Matrix[2, 2] = 1;

            for (int i = 0; i < 80; ++i)
            {
                float[,] res = new float[1, 3] { { 0, 0, 0 } };
                float[,] xy = new float[1, 3] { { points[i].X, points[i].Y, 1 } };
                //Multiply(Matrix, xy, res);
                points[i] = new PointF(res[0,0], To_Y(0, width, 0) - (-res[0,1] - To_Y(0, width, 0)));
            }
            /*gr.Clear(Color.White);

            SolidBrush fill = new SolidBrush(Color.Red);
            System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
            path.AddLines(points);
            System.Drawing.Region rg = new System.Drawing.Region(path);
            gr.FillPath(fill, path);
            Graph_func();*/
        }

        private void button10_Click(object sender, EventArgs e) // поворот оносительно указанной точки +-
        {
            int tmp;
            if (textBox4.Text == "" || !int.TryParse(textBox4.Text, out tmp) || !int.TryParse(textBox6.Text, out tmp) || textBox6.Text == "" || textBox5.Text == "" || !int.TryParse(textBox5.Text, out tmp))
            {
                MessageBox.Show("Неверный формат данных!\nУбедитесь что, введен угол на который должен происходить поворот.");
                return;
            }
            float n = -System.Convert.ToInt32(textBox4.Text), m = System.Convert.ToInt32(textBox6.Text);
            float fi = (float)(System.Convert.ToInt32(textBox5.Text) * Math.PI / 180);

            float[,] Matrix = new float[3, 3];
            Matrix[0,0] = (float)Math.Cos(fi);                                  Matrix[0,1] = (float)Math.Sin(fi);                                  Matrix[0,2] = 0;
            Matrix[1,0] = -(float)Math.Sin(fi);                                 Matrix[1,1] = (float)Math.Cos(fi);                                  Matrix[1,2] = 0;
            Matrix[2,0] = (float)(-m * (Math.Cos(fi) - 1) + n * Math.Sin(fi));  Matrix[2,1] = (float)(-n * (Math.Cos(fi) - 1) - m * Math.Sin(fi));  Matrix[2,2] = 1;

            for (int i = 0; i < 80; ++i)
            {
                float[,] res = new float[1, 3] { { 0, 0, 0 } };
                float[,] xy = new float[1, 3] { { points[i].X - 320, points[i].Y - width, 1 } };
                //Multiply(Matrix, xy, res);
                points[i] = new PointF(res[0,0] + 320, res[0,1] + width);
            }
            /*gr.Clear(Color.White);

            SolidBrush fill = new SolidBrush(Color.Red);
            System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
            path.AddLines(points);
            System.Drawing.Region rg = new System.Drawing.Region(path);
            gr.FillPath(fill, path);
            Graph_func();*/
        }

        private void button9_Click(object sender, EventArgs e) // отражение относительно оси Y +
        {
            float[,] Matrix = new float[3, 3];

            Matrix[0, 0] = -1; Matrix[0, 1] = 0; Matrix[0, 2] = 0;
            Matrix[1, 0] = 0; Matrix[1, 1] = 1; Matrix[1, 2] = 0;
            Matrix[2, 0] = 0; Matrix[2, 1] = 0; Matrix[2, 2] = 1;

            for (int i = 0; i < 80; ++i)
            {
                float[,] res = new float[1, 3] { { 0, 0, 0 } };
                float[,] xy = new float[1, 3] { { points[i].X, points[i].Y, 1 } };
                //Multiply(Matrix, xy, res);
                points[i] = new PointF(To_X(0, height, 10) - (-res[0,0] - To_X(0, height, 10)), res[0,1]);
            }
           /* gr.Clear(Color.White);

            SolidBrush fill = new SolidBrush(Color.Red);
            System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
            path.AddLines(points);
            System.Drawing.Region rg = new System.Drawing.Region(path);
            gr.FillPath(fill, path);
            Graph_func();*/
        }

        private void button7_Click(object sender, EventArgs e) // поворот на заданный угол +
        {
            int tmp;
            if (textBox5.Text == "" || !int.TryParse(textBox5.Text, out tmp))
            {
                MessageBox.Show("Неверный формат данных!\nЧисло должны быть целым.");
                return;
            }

            float[,] Matrix = new float[3, 3];
            float fi = (float)(System.Convert.ToDouble(textBox5.Text) * Math.PI / 180);
            Matrix[0, 0] = (float)Math.Cos(fi); Matrix[0, 1] = (float)Math.Sin(fi); Matrix[0, 2] = 0;
            Matrix[1, 0] = -(float)Math.Sin(fi); Matrix[1, 1] = (float)Math.Cos(fi); Matrix[1, 2] = 0;
            Matrix[2, 0] = 0; Matrix[2, 1] = 0; Matrix[2, 2] = 1;

            for (int i = 0; i < 80; ++i)
            {
                float[,] res = new float[1, 3] { { 0, 0, 0 } };
                float[,] xy = new float[1, 3] { { points[i].X - 320, points[i].Y - width, 1 } };
                //Multiply(Matrix, xy, res);
                points[i] = new PointF(res[0, 0] + 320, res[0, 1] + width);
            }
            /*gr.Clear(Color.White);

            SolidBrush fill = new SolidBrush(Color.Red);
            System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
            path.AddLines(points);
            System.Drawing.Region rg = new System.Drawing.Region(path);
            gr.FillPath(fill, path);
            Graph_func();*/
            
        }

        private void button2_Click_1(object sender, EventArgs e) // отражение относительно Y=X +
        {
            float[,] Matrix = new float[3, 3];

            Matrix[0, 0] = 0; Matrix[0, 1] = 1; Matrix[0, 2] = 0;
            Matrix[1, 0] = 1; Matrix[1, 1] = 0; Matrix[1, 2] = 0;
            Matrix[2, 0] = 0; Matrix[2, 1] = 0; Matrix[2, 2] = 1;

            for (int i = 0; i < 2; ++i)
            {
                float[,] res = new float[points.Length, 3];
                Multiply(Matrix, res);
                //points[i] = new PointF(To_X(0, height, 10) - (res[0, 0] - To_Y(0, width, 0)), To_Y(0, width, 0) - (res[0, 1] - To_X(0, height, 10)));
            }
            gr.Clear(Color.White);

            gr.FillEllipse(fill, points[0].X, points[0].Y, size_x_1, size_y_1);
            fill = new SolidBrush(Color.White);
            gr.FillRectangle(fill, points[1].X, points[1].Y, size_x_2, size_y_2);


            gr.DrawLine(Pens.Black, width, 0, width, pictureBox1.Height);
            gr.DrawLine(Pens.Black, 0, height, pictureBox1.Width, height);
            /* gr.Clear(Color.White);

             SolidBrush fill = new SolidBrush(Color.Red);
             System.Drawing.Drawing2D.GraphicsPath path = new System.Drawing.Drawing2D.GraphicsPath();
             path.AddLines(points);
             System.Drawing.Region rg = new System.Drawing.Region(path);
             gr.FillPath(fill, path);
             Graph_func();*/
        }
    }
}