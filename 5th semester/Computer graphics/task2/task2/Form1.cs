using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace task2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Bitmap image;

        private void button1_Click(object sender, EventArgs e) // открытие изображения
        {
            OpenFileDialog open_dialog = new OpenFileDialog();
            open_dialog.Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*"; //формат загружаемого файла
            if (open_dialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    image = new Bitmap(open_dialog.FileName);
                    pictureBox1.Image = image;
                    pictureBox2.Image = image;
                }
                catch
                {
                    DialogResult rezult = MessageBox.Show("Невозможно открыть выбранный файл",
                    "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e) // сохранение 
        {
            if (pictureBox2.Image != null)
            {
                SaveFileDialog savedialog = new SaveFileDialog();
                savedialog.Title = "Сохранить картинку как...";
                savedialog.OverwritePrompt = true;
                savedialog.CheckPathExists = true;
                savedialog.Filter = "Image Files(*.BMP)|*.BMP|Image Files(*.JPG)|*.JPG|Image Files(*.GIF)|*.GIF|Image Files(*.PNG)|*.PNG|All files (*.*)|*.*";
                savedialog.ShowHelp = true;
                if (savedialog.ShowDialog() == DialogResult.OK) //если в диалоговом окне нажата кнопка "ОК"
                {
                    try
                    {
                        pictureBox2.Image.Save(savedialog.FileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                    }
                    catch
                    {
                        MessageBox.Show("Невозможно сохранить изображение", "Ошибка",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e) // чб
        {
            if (pictureBox2.Image != null)
                Chb((byte)trackBar1.Value);
        }

        public void Chb(byte level = 230)
        {
            var bmp = new Bitmap(pictureBox2.Image);
            var mass = new int[bmp.Width, bmp.Height];
            for (var y = 0; y < bmp.Width; y++)
            {
                for (var x = 0; x < bmp.Height; x++)
                {
                    var R = bmp.GetPixel(y, x).R; //извлекаем долю красного цвета
                    var G = bmp.GetPixel(y, x).G; //извлекаем долю зеленого цвета
                    var B = bmp.GetPixel(y, x).B; //извлекаем долю синего цвета
                    var Black = (R + G + B) / 3; // высчитываем среднее
                    Color color;
                    if (Black > level)
                        color = Color.FromArgb(trackBar2.Value, Black, Black, Black);
                    else
                        color = Color.FromArgb(trackBar2.Value, 0, 0, 0);
                    bmp.SetPixel(y, x, color);
                }
            }
            pictureBox2.Image = bmp;
        }

        private Color Filt(float[,] filt, Color[,] m, int level)
        {
            float R = 0, G = 0, B = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    float mf = filt[i, j];
                    float mnkd = (float)m[i, j].R;
                    R = R + filt[i, j] * (float)m[i, j].R;
                    G = G + filt[i, j] * (float)m[i, j].G;
                    B = B + filt[i, j] * (float)m[i, j].B;
                }
            }
            R = (int)Math.Round(R);
            G = (int)Math.Round(G);
            B = (int)Math.Round(B);

            if (R > 255) R = 255;
            if (R < 0) R = 0;
            if (G > 255) G = 100;
            if (G < 0) G = 0;
            if (B > 255) B = 100;
            if (B < 0) B = 0;

            var tmp = (R + G + B) / 3;
            if (level != -1)
                if ((R + G + B) / 3 > level)
                {
                    return (Color.FromArgb(trackBar2.Value, (int)tmp, (int)tmp, (int)tmp));
                }
                else return (Color.FromArgb(trackBar2.Value, (int)tmp, (int)tmp, (int)tmp));
            else return (Color.FromArgb(trackBar2.Value, (int)tmp, (int)tmp, (int)tmp));
        }

        private void trackBar2_Scroll(object sender, EventArgs e) // прозрачность
        {
            if (pictureBox2.Image != null)
            {
                Bitmap input = new Bitmap(pictureBox2.Image);

                Bitmap output = new Bitmap(input.Width, input.Height);
                for (int j = 0; j < input.Height; j++)
                    for (int i = 0; i < input.Width; i++)
                    {
                        Color p = Color.FromArgb(trackBar2.Value, input.GetPixel(i, j).R, input.GetPixel(i, j).G, input.GetPixel(i, j).B);
                        output.SetPixel(i, j, p);
                    }
                pictureBox2.Image = output;
            }
        }


        private void button3_Click_1(object sender, EventArgs e) // негатив
        {
            if (pictureBox2.Image != null)
            {
                Bitmap input = new Bitmap(pictureBox2.Image);
                Bitmap output = new Bitmap(input.Width, input.Height);

                Color[,] m = new Color[3, 3];
                float[,] filter = new float[3, 3]/* { {-2 / 4, 2 / 4, 2 / 4},
                             {-4 / 4, 2 / 4, 4 / 4},
                             {-2 / 4, 2 / 4, 2 / 4} };*/{ {-10 , 0, 10 },
                             {-10 , 0, 10 },
                             {-10 , 0, 10 } };

                /* int a = pictureBox2.Height;
                 int b = pictureBox2.Width;*/

                for (int i = 1; i < input.Width - 2; ++i)
                {
                    for (int j = 1; j < input.Height - 2; ++j)
                    {
                        m[0, 0] = input.GetPixel(i - 1, j - 1);
                        m[0, 1] = input.GetPixel(i, j - 1);
                        m[0, 2] = input.GetPixel(i + 1, j - 1);

                        m[1, 0] = input.GetPixel(i - 1, j);
                        m[1, 1] = input.GetPixel(i, j);
                        m[1, 2] = input.GetPixel(i + 1, j);

                        m[2, 0] = input.GetPixel(i - 1, j + 1);
                        m[2, 1] = input.GetPixel(i, j + 1);
                        m[2, 2] = input.GetPixel(i + 1, j + 1);
                        output.SetPixel(i, j, Filt(filter, m, -1));
                    }
                }
                pictureBox2.Image = output;

                /* for (int j = 0; j < input.Height; j++)
                     for (int i = 0; i < input.Width; i++)
                     {
                         UInt32 pixel = (UInt32)(input.GetPixel(i, j).ToArgb());
                         // получаем компоненты цветов пикселя
                         float R = (float)((pixel & 0x00FF0000) >> 16); // красный
                         float G = (float)((pixel & 0x0000FF00) >> 8); // зеленый
                         float B = (float)(pixel & 0x000000FF); // синий

                         R = 255 - R;
                         G = 255 - G;
                         B = 255 - B;

                         UInt32 newPixel = 0xFF000000 | ((UInt32)R << 16) | ((UInt32)G << 8) | ((UInt32)B);

                         output.SetPixel(i, j, Color.FromArgb((int)newPixel));
                     }
                 pictureBox2.Image = output;*/
            }
        }

        /* public Color Mul(float[,] filter, Color[,] m, int k)
         {
             Color res = Color.FromArgb(0);
             float tmp = res.ToArgb();
             for(int i = 0; i < 3; ++i)
             {
                 for(int j = 0; j < 3; ++j)
                 {
                     tmp += filter[i, j] * m[i, j].ToArgb();
                 }
             }
             res = Color.FromArgb((int)(tmp%256));
             return res;
         }*/

        private void button4_Click(object sender, EventArgs e)
        {
            pictureBox2.Image = pictureBox1.Image;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (pictureBox2.Image != null)
            {
                Bitmap input = new Bitmap(pictureBox2.Image);
                Bitmap output = new Bitmap(input.Width, input.Height);

                Color[,] m = new Color[3, 3];
                float[,] filter = new float[3, 3] { { 0, -1, 0 }, { -1, 5, -1 }, { 0, -1, 0 } };

                /* int a = pictureBox2.Height;
                 int b = pictureBox2.Width;*/

                for (int i = 1; i < input.Width - 2; ++i)
                {
                    for (int j = 1; j < input.Height - 2; ++j)
                    {
                        m[0, 0] = input.GetPixel(i - 1, j - 1);
                        m[0, 1] = input.GetPixel(i, j - 1);
                        m[0, 2] = input.GetPixel(i + 1, j - 1);

                        m[1, 0] = input.GetPixel(i - 1, j);
                        m[1, 1] = input.GetPixel(i, j);
                        m[1, 2] = input.GetPixel(i + 1, j);

                        m[2, 0] = input.GetPixel(i - 1, j + 1);
                        m[2, 1] = input.GetPixel(i, j + 1);
                        m[2, 2] = input.GetPixel(i + 1, j + 1);
                        output.SetPixel(i, j, Filt(filter, m, -1));
                    }
                }
                pictureBox2.Image = output;
            }
        }
    }
}