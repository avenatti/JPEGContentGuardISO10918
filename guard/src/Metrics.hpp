


/// @file Metrics.hpp
///
/// @brief Definition of various guard metrics.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/24/2020 	Initial version.


#ifndef __METRICS_HPP__
#define __METRICS_HPP__


struct Metrics
{
   unsigned int accepted = 0;
   unsigned int dropped = 0;
   unsigned int droppedInvalid = 0;
   unsigned int droppedSequentialDct = 0;
   unsigned int droppedProgressiveDct = 0;
   unsigned int droppedLossless = 0;
   unsigned int droppedHierarchical = 0;
   unsigned int droppedHuffman = 0;
   unsigned int droppedArithmetic = 0;


   /// Logs the metric contents.
   /// @return void.
   void Log ();


   /// Resets all the values to 0.
   /// @return void.
   void Reset ();
};



#endif //__METRICS_HPP__


