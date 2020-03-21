


/// @file main.cpp
///
/// @brief lean vesion JPEG content guard for ISO 10918.  Only allows sequential dct 
///        with huffman encoding.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	3/21/2020 	Initial version.

#include <fstream>
#include <experimental/filesystem>


// Name spaces.
using namespace std;
namespace fs = std::experimental::filesystem;


static int ACCEPT = 0;
static int DROP = 1;


enum JpegMarker
{
  M_SOF0  = 0xc0,
  M_SOF1  = 0xc1,
  M_SOF2  = 0xc2,
  M_SOF3  = 0xc3,
  M_SOF5  = 0xc5,
  M_SOF6  = 0xc6,
  M_SOF7  = 0xc7,
  M_JPG   = 0xc8,
  M_SOF9  = 0xc9,
  M_SOF10 = 0xca,
  M_SOF11 = 0xcb,
  M_SOF13 = 0xcd,
  M_SOF14 = 0xce,
  M_SOF15 = 0xcf,
  M_DHT   = 0xc4,
  M_DAC   = 0xcc,
  M_RST0  = 0xd0,
  M_RST1  = 0xd1,
  M_RST2  = 0xd2,
  M_RST3  = 0xd3,
  M_RST4  = 0xd4,
  M_RST5  = 0xd5,
  M_RST6  = 0xd6,
  M_RST7  = 0xd7,
  M_SOI   = 0xd8,
  M_EOI   = 0xd9,
  M_SOS   = 0xda,
  M_DQT   = 0xdb,
  M_DNL   = 0xdc,
  M_DRI   = 0xdd,
  M_DHP   = 0xde,
  M_EXP   = 0xdf,
  M_APP0  = 0xe0,
  M_APP1  = 0xe1,
  M_APP2  = 0xe2,
  M_APP3  = 0xe3,
  M_APP4  = 0xe4,
  M_APP5  = 0xe5,
  M_APP6  = 0xe6,
  M_APP7  = 0xe7,
  M_APP8  = 0xe8,
  M_APP9  = 0xe9,
  M_APP10 = 0xea,
  M_APP11 = 0xeb,
  M_APP12 = 0xec,
  M_APP13 = 0xed,
  M_APP14 = 0xee,
  M_APP15 = 0xef,
  M_JPG0  = 0xf0,
  M_JPG13 = 0xfd,
  M_COM   = 0xfe,
  M_TEM   = 0x01,
  M_ERROR = 0x100
};


/// Looks for the expected first marker in jpeg files.
/// @param[in] stream Opened image stream.
/// @return bytes read.
int ProcessFirstMarker (std::ifstream& stream)
{
   unsigned char c1;
   unsigned char c2;


   // Read first 2 bytes.
   stream.read (reinterpret_cast<char *>(&c1), 1);
   stream.read (reinterpret_cast<char *>(&c2), 1);

   if ((c1 != 0xFF) || (c2 != M_SOI) || (stream.fail ()))
      throw "Invalid jpeg image";

   return (2);
}


/// Looks for the next marker in jpeg file.
/// @param[in] stream Opened image stream.
/// @param[out] c2 Lower half of next marker identifier.
/// @param[out] len Length of next marker.
/// @return void.
int GetNextMarker (ifstream& stream, unsigned char& c2, int& len)
{
   unsigned char c1;
   unsigned char c3;


   // Read in first 2 byte marker and 2 byte length.
   stream.read (reinterpret_cast<char *>(&c1), 1);
   stream.read (reinterpret_cast<char *>(&c2), 1);
   stream.read (reinterpret_cast<char *>(&c3), 1);
   len = (c3 << sizeof (unsigned char));
   stream.read (reinterpret_cast<char *>(&c3), 1);
   len |= c3;

   if ((c1 != 0xFF) || (stream.fail ()))
      throw "Invalid jpeg image";

   return (4);
}


/// Reads in a specified number of bytes, not processing them.
/// @param[in] stream Opened image stream.
/// @param[in] skipBytes Numbers of types to read and skip.
/// @return bytes read in.
int SkipBytes (std::ifstream& stream, int skipBytes)
{
   unsigned char c1;


   // Read in the specified number of bytes.
   for (int i = 0; i < skipBytes; i++)
      stream.read (reinterpret_cast<char *>(&c1), 1);

   if (stream.fail ())
      throw "Invalid jpeg image";

   return (skipBytes);
}


/// Entry point for the guard application.
/// Usage:  lean-guard  image_path_filename
/// @return 0 upon accept, 1 upon drop.
int main (int argc, char* argv[])
{
   int result = DROP;
   ifstream infile;
   int fileSize;
   int bytesRead = 0;
   bool accepted = false;
   int len = 0;
   unsigned char c2;


   // Ensure proper calling arguments.
   if (argc == 2)
   {
      // Attempt to open the image file.
      try 
      {
         // Open the image file.
         infile.open (argv[1], ios::binary | ios::in);

         // Protect against any opening errors.   
         if (infile.fail () == false)
         {
            // Get the file size.
            fileSize = fs::file_size (argv[1]);

            // Read the first marker.
            bytesRead += ProcessFirstMarker (infile);

            // Read the rest of the file.
            while ((bytesRead < fileSize) && (accepted == false))
            {
               // Get next marker and length.
               bytesRead += GetNextMarker (infile, c2, len);

               // Perform maker specific special checks.
               switch (c2)
               {
                  case M_SOS:
                     result = ACCEPT;
                     accepted = true;
                     break;

                  case M_SOF2:
                  case M_SOF3:
                  case M_SOF6:
                  case M_SOF7:
                  case M_SOF9:
                  case M_SOF10:
                  case M_SOF11:
                  case M_SOF13:
                  case M_SOF14:
                  case M_SOF15:
                  case M_DAC:
                     throw "Dropped";
                     break;

                  case M_SOF0:
                  case M_SOF1:
                  case M_SOF5:
                  case M_DHT:
                  default:
                     break;
               }

               // Skip the specified number of bytes.
               bytesRead += SkipBytes (infile, (len - 2));
            }
         }
      }
      catch (...)
      {
         result = DROP;
      }
   }

   // Done.
   return (result);
}






