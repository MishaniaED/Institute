using SharpGL;
using SharpGL.SceneGraph.Assets;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace task7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            colorDialog1.Color = Color.Red;
            colorDialog2.Color = Color.DarkRed;
        }

        private Texture Texture = null;                 // Наложенная текстура
        private float rotate = 3.0f;                    // угол на который происходит поворот
        private float fi = 0.0f;                        // угол на который повернута фигура
        private string radioButtonRotation = null;      // текст выбранной Radiobatton для вращения
        private bool ligh = false;                      // для проверки освещения
        private Color modelColor = Color.Aqua;          // Цвет фигуры
        private Color lightColor = Color.Purple;        // Цвет освещения

        private void button1_Click(object sender, EventArgs e) // цвет объекта
        {
            colorDialog1.ShowDialog();
            this.Texture = null;
        }
        
        private void button2_Click(object sender, EventArgs e) // цвет освещения
        {
            colorDialog2.ShowDialog();
            this.Texture = null;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e) // текстура
        {
            if (this.checkBox1.Checked == true)
            {
                this.checkBox2.Enabled = false;
                this.Texture = new Texture();
                this.button1.Enabled = false;
                this.button2.Enabled = false;
                this.radioButton4.Enabled = false;
            }
            else
            {
                this.checkBox2.Enabled = true;
                this.Texture = null;
                this.button1.Enabled = true;
                this.button2.Enabled = true;
                this.radioButton4.Enabled = true;
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e) // освещение
        {
            if (this.checkBox2.Checked == true)
            {
                this.ligh = true;
            }
            else
            {
                this.ligh = false;
            }
        }

        private void openGLControl1_OpenGLDraw(object sender, SharpGL.RenderEventArgs args) // отрисовка фигур
        {
            OpenGL gl = openGLControl1.OpenGL;

            
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.LoadIdentity();
            gl.Disable(OpenGL.GL_LIGHTING);
            gl.Disable(OpenGL.GL_LIGHT0);
            gl.EnableClientState(OpenGL.GL_NORMAL_ARRAY);

            Light(ref gl);
            glRotation(ref gl);

            if (this.radioButton1.Checked == true)                                      // проверка на выбранную фигуру
            {
                modelColor = colorDialog1.Color;                                        // устанавливаем цвет модели 
                if (this.radioButton3.Checked == true)                                  // проверка формата фигуры
                {
                    this.checkBox1.Enabled = true;
                    DrawPiramid(ref gl, modelColor, OpenGL.GL_QUADS, Texture);          // вызываем функцию отрисовки
                }
                else if (this.radioButton4.Checked == true)
                {
                    this.checkBox1.Enabled = false;
                    DrawPiramid(ref gl, modelColor, OpenGL.GL_LINE_LOOP, Texture);
                }
            }
            else if (this.radioButton2.Checked == true)
            {
                modelColor = colorDialog1.Color;

                
                if (this.radioButton3.Checked == true)
                {
                    this.checkBox1.Enabled = true;
                    glDrawTeaPot(ref gl, modelColor, OpenGL.GL_FILL, Texture);
                }
                else if (this.radioButton4.Checked == true)
                {
                    this.checkBox1.Enabled = false;
                    glDrawTeaPot(ref gl, modelColor, OpenGL.GL_LINE, Texture);
                }
            }
        }

        private void Light(ref OpenGL gl) // свет
        {
            gl.LightModel(OpenGL.GL_LIGHT_MODEL_TWO_SIDE, OpenGL.GL_TRUE);
            gl.Enable(OpenGL.GL_NORMALIZE);
              /*float[] material_diffuse= { 1.0f, 1.0f, 1.0f, 1.0f };

            gl.Material(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_DIFFUSE, material_diffuse);*/
            if (this.ligh == true)                  // если выбран свет
            {
                gl.Enable(OpenGL.GL_LIGHTING);
                gl.Enable(OpenGL.GL_LIGHT0);
                
                //gl.Enable(OpenGL.GL_COLOR_MATERIAL);
                gl.Enable(OpenGL.GL_DEPTH_TEST);

                

                this.lightColor = colorDialog2.Color;
                float[] ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
                float[] light_pos = { 0.0f, 0.0f, 1.0f, 1.0f };
                float[] light_ambient = { (float)(colorDialog1.Color.R / 255.0), (float)(colorDialog1.Color.G / 255.0), (float)(colorDialog1.Color.B / 255.0), 1.0f };
                float[] light_dif = { (float)(lightColor.R / 255.0), (float)(lightColor.G / 255.0), (float)(lightColor.B / 255.0), 1.0f };
                float[] light_spec = { 0.2f, 0.2f, 0.2f, 1.0f };
                float[] lmodel_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
                float[] direction = { 0.0f, 0.0f, 1.0f, 0.0f };


                
                gl.LightModel(OpenGL.GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);   // чтобы отражался цвет фигуры
                gl.LightModel(OpenGL.GL_LIGHT_MODEL_AMBIENT, ambient);          // цвет света
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_POSITION, light_pos);
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_AMBIENT, light_ambient);   // цвет фонового осведещиния
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_DIFFUSE, light_dif);       // цвет диффузного освещения
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_SPECULAR, light_spec);     // цвет зеркального отражения
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_SPOT_DIRECTION, direction);
                /*gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_CONSTANT_ATTENUATION, 0.0f);

                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_LINEAR_ATTENUATION, 0.2f);

                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_QUADRATIC_ATTENUATION, 0.4f);*/
                /*gl.Material(OpenGL.GL_FRONT, OpenGL.GL_SHININESS, 10);
                gl.Material(OpenGL.GL_FRONT, OpenGL.GL_SPECULAR, light_spec);*/
                gl.ShadeModel(OpenGL.GL_SMOOTH);
            }
            else
            {
                gl.Enable(OpenGL.GL_DEPTH_TEST);

                this.lightColor = colorDialog2.Color;
                float[] ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
                float[] light_pos = { 1.0f, 0.0f, 0.0f, 1.0f };
                float[] light_ambient = { (float)(colorDialog1.Color.R / 255.0), (float)(colorDialog1.Color.G / 255.0), (float)(colorDialog1.Color.B / 255.0), 1.0f };
                float[] light_diffuse = { (float)(colorDialog1.Color.R / 255.0), (float)(colorDialog1.Color.G / 255.0), (float)(colorDialog1.Color.B / 255.0), 1.0f };
                float[] light_specular = { 0.2f, 0.2f, 0.2f, 1.0f };
                float[] lmodel_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };

                
                gl.LightModel(OpenGL.GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); 
                gl.LightModel(OpenGL.GL_LIGHT_MODEL_AMBIENT, ambient);          
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_POSITION, light_pos);
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_AMBIENT, light_ambient);
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_DIFFUSE, light_diffuse);
                gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_SPECULAR, light_specular);
               
                gl.ShadeModel(OpenGL.GL_SMOOTH);
            }
        }

        private void DrawPiramid(ref SharpGL.OpenGL gl, Color color, uint type, Texture texture) // отрисовка моей фигуры
        {
            
            double[,,] points = { // задание поверхностей по 4-м точкам
                                  {{ 0,  1,  0}, { -1,  -1,  1}, { 1,  -1,  1}, { 0,  1,  0}},

                                  {{ 0,  1,  0}, { 1,  -1,  -1}, { 1,  -1,  1}, { 0,  1,  0}},

                                  {{ 0,  1,  0}, { 1,  -1, -1}, { -1,  -1,  -1}, { 0,  1,  0}},

                                  {{ 0,  1,  0}, { -1,  -1,  1}, { -1,  -1,  -1}, { 0,  1,  0}},

                                  {{ -1,  -1,  1}, { 1,  -1,  1}, { 1,  -1,  -1}, { -1,  -1,  -1}} };

            if (texture == null) // если текстура не выбрана
            {
                for (int i = 0; i < 5; ++i)
                {

                   /* switch (i)
                    {
                        case 0: gl.Normal(0, 0, 1); break;
                        case 1: gl.Normal(0, 1, 0); break;
                        case 2: gl.Normal(1, 0, 0); break;
                        case 3: gl.Normal(0, 1, 1); break;
                        case 4: gl.Normal(1, 0, 1); break;
                    }*/
                    gl.Begin(type);
                    if (this.ligh == true)
                        gl.Color((float)(colorDialog2.Color.R / 255.0), (float)(colorDialog2.Color.G / 255.0), (float)(colorDialog2.Color.B / 255.0));
                    else
                        gl.Color(color.R / 255.0 * 0.5, color.G / 255.0 * 0.5, color.B / 255.0 * 0.5);

                    gl.Vertex(points[i, 0, 0], points[i, 0, 1], points[i, 0, 2]);
                    gl.Vertex(points[i, 1, 0], points[i, 1, 1], points[i, 1, 2]);

                    gl.Color(color.R, color.G, color.B);
                    gl.Vertex(points[i, 2, 0], points[i, 2, 1], points[i, 2, 2]);
                    gl.Vertex(points[i, 3, 0], points[i, 3, 1], points[i, 3, 2]);
                    gl.End();
                }
                gl.Flush();
            }
            else // если текстура выбрана
            {
                texture.Create(gl, task7.Properties.Resources.texture);
                gl.TexEnv(OpenGL.GL_TEXTURE_ENV, OpenGL.GL_TEXTURE_ENV_MODE, (float)OpenGL.GL_REPLACE);
                gl.Enable(OpenGL.GL_TEXTURE_2D);
                gl.Begin(type);

                for (int i = 0; i < 5; ++i)
                {
                    gl.TexCoord(0, 0);
                    gl.Vertex(points[i, 0, 0], points[i, 0, 1], points[i, 0, 2]);
                    gl.TexCoord(0, 1);
                    gl.Vertex(points[i, 1, 0], points[i, 1, 1], points[i, 1, 2]);
                    gl.TexCoord(1, 0);
                    gl.Vertex(points[i, 2, 0], points[i, 2, 1], points[i, 2, 2]);
                    gl.TexCoord(1, 1);
                    gl.Vertex(points[i, 3, 0], points[i, 3, 1], points[i, 3, 2]);
                }
                gl.End();
                gl.Flush();
                gl.Disable(OpenGL.GL_TEXTURE_2D);
            }
        }

        private void glDrawTeaPot(ref OpenGL gl, Color color, uint type, Texture texture) // отрисовка чайника
        {
            SharpGL.SceneGraph.Primitives.Teapot teaPot = new SharpGL.SceneGraph.Primitives.Teapot();

            if (texture == null)
            {
                gl.Disable(OpenGL.GL_BLEND);
                gl.Color(color.R, color.G, color.B);
                teaPot.Draw(gl, 4, 1, type);
            }
            else
            {
                texture.Create(gl, task7.Properties.Resources.texture);
                gl.TexEnv(OpenGL.GL_TEXTURE_ENV, OpenGL.GL_TEXTURE_ENV_MODE, (float)OpenGL.GL_REPLACE);
                gl.Enable(OpenGL.GL_TEXTURE_2D);
                teaPot.Draw(gl, 4, 1, OpenGL.GL_FILL);
                gl.Disable(OpenGL.GL_TEXTURE_2D);
            }
        }

        private void radioButtonRotation_CheckedChanged(object sender, EventArgs e) // обновление после вращения 
        {
            if ((sender as RadioButton).Checked)
                radioButtonRotation = (sender as RadioButton).Text;
            openGLControl1.Invalidate();
        }
        private void glRotation(ref OpenGL gl) // Реализация вращения
        {
            gl.Translate(0.0, 0.0, -7.0);
            if (radioButtonRotation == "Вращение относительно оси X")
            {
                gl.Rotate(fi, 0.0f, 0.0f);
                fi += rotate;
            }
            else if (radioButtonRotation == "Вращение относительно оси Y")
            {
                gl.Rotate(0.0f, fi, 0.0f);
                fi += rotate;
            }
            else if (radioButtonRotation == "Вращение относительно оси Z")
            {
                gl.Rotate(0.0f, 0.0f, fi);
                fi += rotate;
            }
            else if (radioButtonRotation == "Без вращения")
            {
                return;
            }
        }
    }
}
