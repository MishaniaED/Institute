using lab1;
using System.Diagnostics;
using System.Text;

string path = "C:\\Users\\misha\\source\\repos\\University\\6 sem\\Crypto\\lab1\\lab1\\lab1\\Incoming.txt";
byte[] array = File.ReadAllBytes(path);
byte[] key = Encoding.UTF8.GetBytes("SomeKey1");

DES example = new DES(DES.Mode.ECB, key);

byte[] encryptedArray = example.Encrypt(array);
File.WriteAllBytes("C:\\Users\\misha\\source\\repos\\University\\6 sem\\Crypto\\lab1\\lab1\\lab1\\Encrypted.txt", encryptedArray);
//Process.Start("Encrypted.txt");
byte[] decryptedArray = example.Decrypt(encryptedArray);
File.WriteAllBytes("C:\\Users\\misha\\source\\repos\\University\\6 sem\\Crypto\\lab1\\lab1\\lab1\\Decrypted.txt", decryptedArray);
//Process.Start("Decrypted.txt");

