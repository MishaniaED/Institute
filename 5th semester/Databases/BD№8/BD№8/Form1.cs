using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//using Microsoft.Data.SqlClient;
using System.Data.SqlClient;


namespace BD_8
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
        }

        string string_connection = @"Data Source=LAPTOP-2KN9A69Q\SQL_DEVELOPER;Initial Catalog=Dz_№1;Integrated Security=True";

        private void Form1_Load(object sender, EventArgs e)
        {
            listView1.GridLines = true;
            listView1.View = View.Details;
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e) // 1-й запрос
        {
            listView1.Clear();
            listView1.Columns.Add("IDпомещения");
            listView1.Columns.Add("ID");
            listView1.Columns.Add("Площадь");
            listView1.Columns.Add("Ближайшай_дата_аренды");
            listView1.Columns.Add("стоимость");

            SqlDataReader dataReader = null;
            string curr_command = "EXEC task1";

            using (SqlConnection connection = new SqlConnection(string_connection))
            {
                connection.Open();          
                SqlTransaction transaction = connection.BeginTransaction();
                SqlCommand command = connection.CreateCommand();

                command.Transaction = transaction;

                try
                {
                    command.CommandText = curr_command;
                    dataReader = command.ExecuteReader();
                    while (dataReader.Read())
                    {
                        ListViewItem item = new ListViewItem(new string[] 
                        {
                            Convert.ToString(dataReader["IDпомещения"]),
                            Convert.ToString(dataReader["ID"]),
                            Convert.ToString(dataReader["Площадь"]),
                            Convert.ToString(dataReader["Ближайшая_дата_аренды"]),
                            Convert.ToString(dataReader["стоимость"])
                        }
                        );
                        listView1.Items.Add(item);
                    }
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.Message);
                    transaction.Rollback();
                }
                finally
                {
                    if (dataReader != null && !dataReader.IsClosed)
                    {
                        dataReader.Close();
                    }
                }
                connection.Close();
            }
        }

        private void button1_Click(object sender, EventArgs e) // 3-й запрос
        {
            string curr_command = string.Format("INSERT INTO [Помещение]([IDпомещения], [Площадь], [ID]) VALUES({0},{1},{2})", Convert.ToInt32(textBox3.Text), Convert.ToDouble(textBox5.Text), Convert.ToInt32(textBox4.Text));
            System.Data.SqlClient.SqlConnection sqlConnection1 =
    new System.Data.SqlClient.SqlConnection(string_connection);

            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand();
            cmd.CommandType = System.Data.CommandType.Text;
            cmd.CommandText = curr_command;
            cmd.Connection = sqlConnection1;

            sqlConnection1.Open();
            cmd.ExecuteNonQuery();
            sqlConnection1.Close();

            listView1.Clear();
            listView1.Columns.Add("IDпомещения");
            listView1.Columns.Add("Площадь");
            listView1.Columns.Add("ID");

            //string curr_command = /*"INSERT INTO Помещение(IDпомещения, Площадь, ID) VALUES(12,22,2)";*/"INSERT INTO Помещение(IDпомещения, Площадь, ID) VALUES(" + textBox3.Text + "," + textBox5.Text + "," + textBox4.Text + ")";
            //string curr_command = string.Format("INSERT INTO [Помещение]([IDпомещения], [Площадь], [ID]) VALUES({0},{1},{2})", Convert.ToInt32(textBox3.Text), Convert.ToDouble(textBox5.Text), Convert.ToInt32(textBox4.Text));
            using (SqlConnection connection = new SqlConnection(string_connection))
            {
                connection.Open();
                SqlTransaction transaction = connection.BeginTransaction();
                SqlCommand command = connection.CreateCommand();

                command.Transaction = transaction;
                SqlDataReader dataReader = null;
                

                try
                {
                    /*command.CommandText = curr_command;
                    int number = command.ExecuteNonQuery();
                    MessageBox.Show("Команда insert, затронуто " + number.ToString() + " строк");*/
                    curr_command = "SELECT IDпомещения, Площадь, ID FROM Помещение";
                    command.CommandText = curr_command;
                    dataReader = command.ExecuteReader();
                    while (dataReader.Read())
                    {
                        ListViewItem item = new ListViewItem(new string[]
                        {
                            Convert.ToString(dataReader["IDпомещения"]),
                            Convert.ToString(dataReader["Площадь"]),
                            Convert.ToString(dataReader["ID"]),
                        }
                        );
                        listView1.Items.Add(item);
                    }
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.Message);
                    transaction.Rollback();
                }
                connection.Close();
            }
        }

        private void button3_Click(object sender, EventArgs e) // 2-й запрос
        {
            string curr_command = "EXEC" + textBox1.Text;
            using (SqlConnection connection = new SqlConnection(string_connection))
            {
                connection.Open();
                SqlTransaction transaction = connection.BeginTransaction();
                SqlCommand command = connection.CreateCommand();

                command.Transaction = transaction;

                try
                {
                    command.CommandText = curr_command;
                    command.ExecuteNonQuery();
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.Message);
                    transaction.Rollback();
                }
                connection.Close();
            }
        }
    }
}
