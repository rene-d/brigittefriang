using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;

namespace Main.Tools
{

	internal static class Program
	{
		[STAThread]
		private static void Main(string[] args)
		{
			try
			{
				System.Console.WriteLine("hello");
                Locker.DecryptFile("informations_attaque.txt.evil", ".evil");
			}
			catch
			{
			}
		}
	}
	internal static class Locker
	{
		private static readonly string EncryptedFileListPath = "/tmp/EncryptedFileList.txt";

		private static readonly HashSet<string> EncryptedFiles = new HashSet<string>();

		private const string EncryptionFileExtension = ".evil";

		private const string EncryptionPassword = "RXZpbERlZmF1bHRQYXNzIQ==";


		public static bool EncryptFile(string path, string encryptionExtension)
		{
			try
			{
				using AesCryptoServiceProvider aesCryptoServiceProvider = new AesCryptoServiceProvider();
				aesCryptoServiceProvider.Key = Convert.FromBase64String("RXZpbERlZmF1bHRQYXNzIQ==");
				aesCryptoServiceProvider.IV = new byte[16]
				{
					0,
					1,
					0,
					3,
					5,
					3,
					0,
					1,
					0,
					0,
					2,
					0,
					6,
					7,
					6,
					0
				};
				EncryptFile(aesCryptoServiceProvider, path, path + encryptionExtension);
			}
			catch
			{
				return false;
			}
			try
			{
				File.Delete(path);
			}
			catch (Exception)
			{
				return false;
			}
			return true;
		}

		public static void DecryptFile(string path, string encryptionExtension)
		{
			try
			{
				if (!path.EndsWith(encryptionExtension))
				{
					return;
				}
				string outputFile = path.Remove(path.Length - 4);
				using AesCryptoServiceProvider aesCryptoServiceProvider = new AesCryptoServiceProvider();
				aesCryptoServiceProvider.Key = Convert.FromBase64String("RXZpbERlZmF1bHRQYXNzIQ==");
				aesCryptoServiceProvider.IV = new byte[16]
				{
					0,
					1,
					0,
					3,
					5,
					3,
					0,
					1,
					0,
					0,
					2,
					0,
					6,
					7,
					6,
					0
				};
				DecryptFile(aesCryptoServiceProvider, path, outputFile);
			}
			catch
			{
				return;
			}
			try
			{
				File.Delete(path);
			}
			catch (Exception)
			{
			}
		}

		private static void EncryptFile(SymmetricAlgorithm alg, string inputFile, string outputFile)
		{
			byte[] array = new byte[65536];
			using FileStream fileStream = new FileStream(inputFile, FileMode.Open);
			using FileStream stream = new FileStream(outputFile, FileMode.Create);
			using CryptoStream cryptoStream = new CryptoStream(stream, alg.CreateEncryptor(), CryptoStreamMode.Write);
			int num;
			do
			{
				num = fileStream.Read(array, 0, array.Length);
				if (num != 0)
				{
					cryptoStream.Write(array, 0, num);
				}
			}
			while (num != 0);
		}

		private static void DecryptFile(SymmetricAlgorithm alg, string inputFile, string outputFile)
		{
			byte[] array = new byte[65536];
			using FileStream fileStream = new FileStream(inputFile, FileMode.Open);
			using FileStream stream = new FileStream(outputFile, FileMode.Create);
			using CryptoStream cryptoStream = new CryptoStream(stream, alg.CreateDecryptor(), CryptoStreamMode.Write);
			int num;
			do
			{
				num = fileStream.Read(array, 0, array.Length);
				if (num != 0)
				{
					cryptoStream.Write(array, 0, num);
				}
			}
			while (num != 0);
		}
	}
}
