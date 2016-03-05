using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VerifyBuild
{
    class Program
    {
        const int Boot1ValidSize = 422;
        const int Boot2MaxSize = 4 * 1024 ;
        static readonly byte[] BootSectorSignature = { 0x55, 0xAA };
        static readonly byte[] Boot2EntrySignature = { 0x55, 0x89 ,0xE5 };

        static string BuildPath { get; set; }
        static string Boot1Path { get; set; }
        static string Boot2Path { get; set; }

        static int Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("error: Invalid number of arguments!");
                return 1;
            }

            BuildPath = Path.GetFullPath(args[0]);
            Boot1Path = Path.Combine(BuildPath, "boot1.bin");
            Boot2Path = Path.Combine(BuildPath, "boot2.bin");

            Console.WriteLine("Validating build at {0}", BuildPath);

            var size = new FileInfo(Boot1Path).Length;
            if (size != Boot1ValidSize)
            {
                Console.WriteLine("error: boot1.bin is expected to be {0} bytes, but it is {1} bytes!", Boot1ValidSize, size);
                return 2;
            }

            byte[] bytes = File.ReadAllBytes(Boot1Path);
            for (int i = 0; i < BootSectorSignature.Length; ++i)
            {
                if (BootSectorSignature[i] != bytes[i + bytes.Length - BootSectorSignature.Length])
                {
                    Console.WriteLine("error: boot1.bin has invalid bootsignature!");
                    return 2;
                }
            }

            size = new FileInfo(Boot2Path).Length;
            if (size >= Boot2MaxSize)
            {
                Console.WriteLine("error: boot2.bin is exceeds {0} bytes ({1} bytes)!", Boot2MaxSize, size);
                return 2;
            }


            bytes = File.ReadAllBytes(Boot2Path);
            for (int i = 0; i < Boot2EntrySignature.Length; ++i)
            {
                if (Boot2EntrySignature[i] != bytes[i])
                {
                    Console.WriteLine("error: boot2.bin has invalid entry point!");
                    return 3;
                }
            }
            Console.WriteLine("boot2.size is {0} bytes.", size);

            Console.WriteLine("Validation complete!");

            return 0;
        }
    }
}
