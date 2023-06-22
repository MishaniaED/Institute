using SharpGL;
using SharpGL.SceneGraph;
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
            Color color = Color.Red;
        }

        bool texture = true;
        private const int N = 5;
        private float rotate = 1.5f;                    // угол на который происходит поворот
        private float fi = 0.0f;                        // угол на который повернута фигура

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            texture = true;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            texture = false;
        }

        float function(float x, float y)
        {
            return (float)Math.Sin(x * y);
        }

        private void glRotation(ref OpenGL gl) // Реализация вращения
        {
            gl.Translate(0.0, 0.0, -7.0);
            if (radioButton5.Checked)
            {
                gl.Rotate(fi, 0.0f, 0.0f);
                fi += rotate;
            }
            else if (radioButton6.Checked)
            {
                gl.Rotate(0.0f, fi, 0.0f);
                fi += rotate;
            }
            else if (radioButton7.Checked)
            {
                gl.Rotate(0.0f, 0.0f, fi);
                fi += rotate;
            }
            else if (radioButton8.Checked)
            {
                return;
            }
        }

        private void openGLControl1_OpenGLDraw(object sender, SharpGL.RenderEventArgs args) // отрисовка фигур
        {
            OpenGL gl = this.openGLControl1.OpenGL;
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.LoadIdentity();

            gl.Translate(0.0f, 0.0f, -12.0f);

            glRotation(ref gl);
            Light_model(gl);

            for (float y = -N; y < N; y += 0.1f)
            {
                for (float x = -N; x < N; x += 0.1f)
                {
                    if (texture)
                    {
                        gl.Begin(SharpGL.Enumerations.BeginMode.Lines);
                    }
                    else
                    {
                        gl.Begin(SharpGL.Enumerations.BeginMode.Quads);
                    }

                    if (function(x, y) % 0.2 == 0)
                    {
                        gl.Color(Color.Red);
                    }
                    else
                        gl.Color(Color.DarkRed);


                    gl.Normal(0.0, 0.0, -1.0);
                    gl.Vertex(x, y, function(x, y));
                    gl.Vertex(x, y + 0.1f, function(x, y + 0.1f));

                    gl.Vertex(x + 0.1f, y + 0.1f, function(x + 0.1f, y + 0.1f));
                    gl.Vertex(x + 0.1f, y, function(x + 0.1f, y));
                }
            }
            gl.End();
            gl.Flush();
        }

        private void Light_model(OpenGL gl)
        {
            if (texture)
            {
                gl.Disable(OpenGL.GL_LIGHTING);
                return;
            }
            gl.Enable(OpenGL.GL_LIGHTING);
            gl.Enable(OpenGL.GL_LIGHT0);
            gl.LightModel(OpenGL.GL_LIGHT_MODEL_TWO_SIDE, OpenGL.GL_TRUE);
            gl.Enable(OpenGL.GL_NORMALIZE);
            gl.Enable(OpenGL.GL_DEPTH_TEST);
            gl.ShadeModel(OpenGL.GL_SMOOTH);
            float[] ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
            float[] light_pos = { 0.0f, 0.0f, 1.0f, 1.0f };
            float[] light_dif = { 0.2f, 0.2f, 0.2f, 1.0f };
            float[] light_spec = { 0.2f, 0.2f, 0.2f, 1.0f };
            float[] lmodel_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
            float[] direction = { 0.0f, 0.0f, 1.0f, 0.0f };


            gl.LightModel(OpenGL.GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);   // чтобы отражался цвет фигуры
            gl.LightModel(OpenGL.GL_LIGHT_MODEL_AMBIENT, ambient);          // цвет света
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_POSITION, light_pos);
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_DIFFUSE, light_dif);       // цвет диффузного освещения
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_SPECULAR, light_spec);     // цвет зеркального отражения
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_SPOT_DIRECTION, direction);
            gl.Material(OpenGL.GL_FRONT, OpenGL.GL_SHININESS, 40);
        }
    }
}
