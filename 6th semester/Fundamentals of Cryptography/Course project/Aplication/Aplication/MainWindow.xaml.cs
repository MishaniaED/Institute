using elGamal;
using Serpent;
using Microsoft.Win32;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.IO;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Numerics;
using System.Threading.Tasks;

namespace Aplication
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private RandomNumberGenerator randomNumberGenerator = RandomNumberGenerator.Create();
        private byte[] text;
        private byte[] IV = new byte[16];
        ElGamal elGamal = new ElGamal();
        SErpent serp;
        bool flag = false;

        public MainWindow()
        {
            InitializeComponent();
            EncryptMode.SelectedIndex = 0;
            randomNumberGenerator.GetBytes(IV);
            SErpent.onCount += PrograssInBarCBW;

            /*byte[] buffer = Encoding.Default.GetBytes("aaaaaaaaaa");
            var text = elGamal.Encrypt(buffer);
            var new_text = elGamal.Decrypt(text);*/
            /* SErpent serp = new SErpent(Encoding.Default.GetBytes("serpent1234"), EncryptionMode.ECB);
             byte[] buffer = Encoding.Default.GetBytes("aaaaaaaaaa");
             var text1 = serp.Encrypt(buffer);
             var new_text = serp.Decrypt(text1);*/
        }
        public void PrograssInBarCBW(long i, int len, int step)
        {

            ProgressBarEncryption.Maximum = len;
            ProgressBarEncryption.Minimum = 0;
            ProgressBarEncryption.Value = i;
        }

        private void btnOpenFile_Click(object sender, RoutedEventArgs e)
        {
            /*ProgressBarEncryption.Value = 0;*/
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true) { 
                string filename = openFileDialog.FileName;
                FileName.Text = filename;
                text = File.ReadAllBytes(filename);
                flag = true;
            }   
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (!flag)
            {
                MessageBox.Show("Не выбран файл для шифровнаия/расшифрования");
                return;
            }
            ProgressBarEncryption.Value = 0;
            byte[] new_text;
            if ((bool)RB_ElGamal.IsChecked) {
                new_text = elGamal.Encrypt(text);
                /*new_text = await elGamal.EncryptAsync(text);*/ // ???
            }
            else
            {
                SErpent serp;
                switch (EncryptMode.SelectedIndex)
                {
                    case 0:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.ECB);
                            break;
                        }
                    case 1:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.CBC, IV);
                            break;
                        }
                    case 2:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.CFB, IV);
                            break;
                        }
                    case 3:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.OFB, IV);
                            break;
                        }
                    case 4:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.CTR, IV);
                            break;
                        }
                    case 5:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.RD, IV);
                            break;
                        }
                    case 6:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.RDH, IV);
                            break;
                        }
                    default:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.ECB);
                            break;
                        }
                }
                /*new_text = serp.EncryptAsync(text);*/
                new_text = serp.Encrypt(text);
            }
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            if (saveFileDialog.ShowDialog() == true) {
                string filename = saveFileDialog.FileName;
                File.WriteAllBytes(filename, new_text);
                MessageBox.Show("Зашифрованный файл сохранен");
            }
            else MessageBox.Show("Возникла ошибка при сохранении файла");
        }

        private void Decrypt_Click(object sender, RoutedEventArgs e)
        {
            if (!flag)
            {
                MessageBox.Show("Не выбран файл для шифровнаия/расшифрования");
                return;
            }
            byte[] new_text;
            ProgressBarEncryption.Value = 0;
            if ((bool)RB_ElGamal.IsChecked)
            {
                new_text = elGamal.Decrypt(text);
                /*new_text = elGamal.DEncryptAsync(text);*/
            }
            else
            {                
                switch (EncryptMode.SelectedIndex)
                {
                    case 0:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.ECB);
                            break;
                        }
                    case 1:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.CBC, IV);
                            break;
                        }
                    case 2:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.CFB, IV);
                            break;
                        }
                    case 3:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.OFB, IV);
                            break;
                        }
                    case 4:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.CTR, IV);
                            break;
                        }
                    case 5:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.RD, IV);
                            break;
                        }
                    case 6:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.RDH, IV);
                            break;
                        }
                    default:
                        {
                            serp = new SErpent(Encoding.Default.GetBytes(KeyField.Text), EncryptionMode.ECB, IV);
                            break;
                        }
                }
                new_text = serp.Decrypt(text);
                /*new_text = elGamal.DEncryptAsync(text);*/
            }
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            if (saveFileDialog.ShowDialog() == true)
            {
                string filename = saveFileDialog.FileName;
                File.WriteAllBytes(filename, new_text);
                MessageBox.Show("Расшифрованный файл сохранен");
            }
            else MessageBox.Show("Возникла ошибка при сохранении файла");
        }
    }
}
