


/// @file Gauntlet.hpp
///
/// @brief Definition for Gauntlet class that is used to parse and determine whether
///        a given jpeg image should be dropped or accepted based on user 
///        configuration settings.
///
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/22/2020 	Initial version.


#ifndef __GAUNTLET_HPP__
#define __GAUNTLET_HPP__


#include "Config.hpp"
#include "Metrics.hpp"
#include <string>
#include <fstream>


enum GauntletExceptionType
{
   UNKNOWN = 0,
   ACCEPTED = 1,
   INVALID = 2,
   SEQUENTIAL_DCT = 3,
   PROGRESSIVE_DCT = 4,
   LOSSLESS = 5,
   HIERARCHICAL = 6,
   HUFFMAN = 7,
   ARITHMETIC = 8 
};


struct GauntletException
{
   GauntletExceptionType eType;
   std::string image;
   std::string msg;

   
   // Constructor.
   // @param[in] etype Gauntlet exception type.
   // @param[in] image Image associated with the exception.
   // @param[in] emsg String message of the exception.
   GauntletException (GauntletExceptionType etype, std::string image, std::string emsg);


   // Constructor.
   GauntletException ();
};


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


class Gauntlet
{
   public:
      
      /// Constructor.
      /// @param[in] settings Guard settings.
      Gauntlet (Settings& settings);


      /// Destructor.
      ~Gauntlet ();


      /// Runs an image throught he gauntlet.
      /// @param[in] image Image path/name to run.
      /// @return true if accepted, false otherwise.
      bool Run (std::string& image);


      /// Gets the current metrics.
      /// @return current metrics.
      Metrics GetMetrics ();


   private:
   
      Settings m_settings;   ///< Parsed config settings.
      Metrics m_metrics;     ///< Metric information.


      /// Constructor (private).
      Gauntlet ();


      /// Runs an image throught he gauntlet.
      /// @param[in] stream Opened image stream.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return true if accepted, false otherwise.
      bool Check (std::ifstream& stream, GauntletException& e);


      /// Looks for the expected first marker in jpeg file.
      /// @param[in] stream Opened image stream.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return bytes read.
      int ProcessFirstMarker (std::ifstream& stream, GauntletException& e);


      /// Looks for the next marker in jpeg file.
      /// @param[in] stream Opened image stream.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @param[out] c2 Lower half of next marker identifier.
      /// @param[out] len Length of next marker.
      /// @return bytes read.
      int GetNextMarker (std::ifstream& stream, 
                         GauntletException& e,
                         unsigned char& c2,
                         int& len);


      /// Reads in a specified number of bytes, not processing them.
      /// @param[in] stream Opened image stream.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @param[in] skipBytes Numbers of types to read and skip.
      /// @return bytes read in.
      int SkipBytes (std::ifstream& stream, 
                     GauntletException& e,
                     int skipBytes);


      /// Processees a gaunlet exception thrown by a gauntlet run.
      /// @param[in] e Gauntlet exception to process.
      /// @return true if accepted, false otherwise.
      bool ProcessGauntletException (GauntletException& e);


      /// Checks if Sequential DCT is enabled, dropping image if not enabled.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return void.
      void CheckSequentialDct (GauntletException& e);


      /// Checks if Progressive DCT is enabled, dropping image if not enabled.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return void.
      void CheckProgressiveDct (GauntletException& e);


      /// Checks if Lossless is enabled, dropping image if not enabled.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return void.
      void CheckLossless (GauntletException& e);


      /// Checks if Huffman encoding is enabled, dropping image if not enabled.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return void.
      void CheckHuffman (GauntletException& e);


      /// Checks if Arithmetic encoding is enabled, dropping image if not enabled.
      /// @param[in] e Gauntlet error to throw upon drop.
      /// @return void.
      void CheckArithmetic (GauntletException& e);
};


#endif //__GAUNTLET_HPP__


