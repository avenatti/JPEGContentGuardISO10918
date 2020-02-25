


/// @file Gauntlet.cpp
///
/// @brief Implementation of Gauntlet class that is used to parse and determine whether
///        a given jpeg image should be dropped or accepted based on user 
///        configuration settings.
///
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/22/2020 	Initial version.


#include "Gauntlet.hpp"
#include "logging.hpp"
#include "utils.hpp"
#include <iomanip>
#include <experimental/filesystem>


// Name spaces.
using namespace std;
namespace fs = std::experimental::filesystem;


// Constructor.
// @param[in] etype Gauntlet exception type.
// @param[in] image Image associated with the exception.
// @param[in] emsg String message of the exception.
GauntletException::GauntletException (GauntletExceptionType etype, string image, string emsg)
 : eType (etype),
   image (image),
   msg (emsg)
{

}


// Constructor.
GauntletException::GauntletException ()
 : eType (UNKNOWN),
   image ("unset"),
   msg ("unset")
{

}


/// Constructor.
/// @param[in] settings Guard settings.
Gauntlet::Gauntlet (Settings& settings)
 : m_settings (settings)
{
   m_metrics.Reset ();
}


/// Constructor (private).
Gauntlet::Gauntlet ()
{

}


/// Destructor.
Gauntlet::~Gauntlet ()
{

}


/// Runs an image throught he gauntlet.
/// @param[in] image Image path/name to run.
/// @return true if accepted, false otherwise.
bool Gauntlet::Run (string& image)
{
   bool result = false;
   ifstream infile;
   GauntletException e;


   // Set the exception image field.
   e.image = image;

   // Run the gauntlet.
   try
   {
      // Open the image file.
      infile.open (image, ios::binary | ios::in);

      // Check for errors.
      if (infile.fail ())
      {
         // Open error.
         e.eType = INVALID;
         e.msg = "Failed to open image.";
         throw e;
      }

      // Start checking the image.
      result = Check (infile, e);
   }

   // User defined gauntlet exception.
   catch (GauntletException e)
   {
      // Process the user defined exception.
      result = ProcessGauntletException (e);
   }

   // Unhandled error.
   catch (...)
   {
      ERR_LOG ("Exception: Catch all.");
   }
   
   return (result);
}


/// Runs an image throught he gauntlet.
/// @param[in] stream Opened image stream.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return true if accepted, false otherwise.
bool Gauntlet::Check (ifstream& stream, GauntletException& e)
{
   bool result = true;
   unsigned char c2;
   int len;
   int fileSize;
   int bytesRead = 0;

   
   // Get the file size.
   fileSize = fs::file_size (e.image);
 
   // Read the first marker.
   bytesRead += ProcessFirstMarker (stream, e); 

   while (bytesRead < fileSize)
   {
      len = 0;
      // Get next marker and length.
      bytesRead += GetNextMarker (stream, e, c2, len);

      // Perform maker specific special checks.
      switch (c2)
      {
         case M_SOS:
            e.eType = ACCEPTED;
            e.msg = "Reached a start of scan marker.";
            throw e;
            break;

         case M_SOF0:
         case M_SOF1:
         case M_SOF5:
            CheckSequentialDct (e);
            CheckHuffman (e);
            break;

         case M_SOF2:
         case M_SOF6:
            CheckProgressiveDct (e);
            CheckHuffman (e);
            break;

         case M_SOF3:
         case M_SOF7:
            CheckLossless (e);
            CheckHuffman (e);
            break;

         case M_SOF9:
         case M_SOF13:
            CheckSequentialDct (e);
            CheckArithmetic (e);
            break;

         case M_SOF10:
         case M_SOF14:
            CheckProgressiveDct (e);
            CheckArithmetic (e);
            break;

         case M_SOF11:
         case M_SOF15:
            CheckLossless (e);
            CheckArithmetic (e);
            break;

         case M_DHT:
            CheckHuffman (e);
            break;

         case M_DAC:
            CheckArithmetic (e);
            break;

         default:
            break;
      }
 
      // Skip the specified number of bytes.
      bytesRead += SkipBytes (stream, e, (len - 2));

#if 0
      DEBUG_LOG ("Bytes Read: 0x" << hex << (int)bytesRead << " of 0x" << (int)fileSize);
#endif
   }

   return (result);
}


/// Looks for the expected first marker in jpeg files.
/// @param[in] stream Opened image stream.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return bytes read.
int Gauntlet::ProcessFirstMarker (std::ifstream& stream, GauntletException& e)
{
   unsigned char c1;
   unsigned char c2;

   
   // Read first 2 bytes.
   stream.read (reinterpret_cast<char *>(&c1), 1);
   stream.read (reinterpret_cast<char *>(&c2), 1);

#if 0
   DEBUG_LOG ("C1: 0x" << hex << (int)c1);
   DEBUG_LOG ("C2: 0x" << hex << (int)c2);
#endif

   if ((c1 != 0xFF) || (c2 != M_SOI) || (stream.fail ()))
   {
      e.eType = INVALID;
      e.msg = "Didn't find SOI marker at beginning of image.";
      throw e;
   }

   return (2);
}


/// Looks for the next marker in jpeg file.
/// @param[in] stream Opened image stream.
/// @param[in] e Gauntlet error to throw upon drop.
/// @param[out] c2 Lower half of next marker identifier.
/// @param[out] len Length of next marker.
/// @return void.
int Gauntlet::GetNextMarker (ifstream& stream, 
                             GauntletException& e,
                             unsigned char& c2,
                             int& len)
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

#if 0
   DEBUG_LOG ("C1: 0x" << hex << (int)c1);
   DEBUG_LOG ("C2: 0x" << hex << (int)c2);
   DEBUG_LOG ("Len: " << to_string (len) << " (0x" << hex << (int)len << ")");
#endif 

   if ((c1 != 0xFF) || (stream.fail ()))
   {
      e.eType = INVALID;
      e.msg = "Get next marker failure.";
      throw e;
   }

   return (4);
}


/// Reads in a specified number of bytes, not processing them.
/// @param[in] stream Opened image stream.
/// @param[in] e Gauntlet error to throw upon drop.
/// @param[in] skipBytes Numbers of types to read and skip.
/// @return bytes read in.
int Gauntlet::SkipBytes (std::ifstream& stream,
                         GauntletException& e,
                         int skipBytes)
{
   unsigned char c1;


   // Read in the specified number of bytes.
   for (int i = 0; i < skipBytes; i++)
   {
      stream.read (reinterpret_cast<char *>(&c1), 1);
#if 0
      DEBUG_LOG ("    C1: 0x" << hex << (int)c1);
#endif 
   }

   if (stream.fail ())
   {
      e.eType = INVALID;
      e.msg = "Failed skipping byte read.";
      throw e;
   }

   return (skipBytes);
}


/// Processees a gaunlet exception thrown by a gauntlet run.
/// @param[in] e Gauntlet exception to process.
/// @return true if accepted, false otherwise.
bool Gauntlet::ProcessGauntletException (GauntletException& e)
{
   bool result = false;


   // Which type was thrown?
   switch (e.eType)
   {
      case ACCEPTED:
         DEBUG_LOG ("Accepted image \"" << e.image << "\"."); //MWB
         m_metrics.accepted++;
         result = true;
         break;

      case INVALID:
         DEBUG_LOG ("Dropped-Invalid image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedInvalid++;
         break;

      case SEQUENTIAL_DCT:
         DEBUG_LOG ("Dropped-Sequential-Dct image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedSequentialDct++;
         break;

      case PROGRESSIVE_DCT:
         DEBUG_LOG ("Dropped-Progressive-Dct image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedProgressiveDct++;
         break;

      case LOSSLESS:
         DEBUG_LOG ("Dropped-Lossless image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedLossless++;
         break;

      case HIERARCHICAL:
         DEBUG_LOG ("Dropped-Hierarchical image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedHierarchical++;
         break;

      case HUFFMAN:
         DEBUG_LOG ("Dropped-Huffman image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedHuffman++;
         break;

      case ARITHMETIC:
         DEBUG_LOG ("Dropped-Arithmetic image \"" << e.image << "\"."); //MWB
         m_metrics.dropped++;
         m_metrics.droppedArithmetic++;
         break;

      default:
         ERR_LOG ("Unhandled gauntlet exception was thrown.");
         break;
   }

   return (result);
}


/// Gets the current metrics.
/// @return current metrics.
Metrics Gauntlet::GetMetrics ()
{
   return (m_metrics);
}


/// Checks if Sequential DCT is enabled, dropping image if not enabled.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return void.
void Gauntlet::CheckSequentialDct (GauntletException& e)
{
   if (m_settings.sequentialDctMode == false)
   {
      e.eType = SEQUENTIAL_DCT;
      e.msg = "Dropped sequential dct.";
      throw e;
   }
}


/// Checks if Progressive DCT is enabled, dropping image if not enabled.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return void.
void Gauntlet::CheckProgressiveDct (GauntletException& e)
{
   if (m_settings.progressiveDctMode == false)
   {
      e.eType = PROGRESSIVE_DCT;
      e.msg = "Dropped progressive dct.";
      throw e;
   }
}


/// Checks if Lossless is enabled, dropping image if not enabled.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return void.
void Gauntlet::CheckLossless (GauntletException& e)
{
   if (m_settings.losslessMode == false)
   {
      e.eType = LOSSLESS;
      e.msg = "Dropped lossless.";
      throw e;
   }
}


/// Checks if Huffman encoding is enabled, dropping image if not enabled.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return void.
void Gauntlet::CheckHuffman (GauntletException& e)
{
   if (m_settings.huffmanEncoding == false)
   {
      e.eType = HUFFMAN;
      e.msg = "Dropped huffman encoding.";
      throw e;
   }
}


/// Checks if Arithmetic encoding is enabled, dropping image if not enabled.
/// @param[in] e Gauntlet error to throw upon drop.
/// @return void.
void Gauntlet::CheckArithmetic (GauntletException& e)
{
   if (m_settings.arithmeticEncoding == false)
   {
      e.eType = ARITHMETIC;
      e.msg = "Dropped arithmetic encoding.";
      throw e;
   }
}



