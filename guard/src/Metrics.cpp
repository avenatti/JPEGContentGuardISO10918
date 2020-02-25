


/// @file Metrics.cpp
///
/// @brief Implements of various guard metrics.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/24/2020 	Initial version.


#include "Metrics.hpp"
#include "logging.hpp"


// Name spaces.
using namespace std;


/// Logs the metric contents.
/// @return void.
void Metrics::Log ()
{
   METRIC_LOG ("accepted = " << accepted);
   METRIC_LOG ("dropped = " << dropped);
   METRIC_LOG ("droppedInvalid = " << droppedInvalid);
   METRIC_LOG ("droppedSequentialDct = " << droppedSequentialDct);
   METRIC_LOG ("droppedProgressiveDct = " <<  droppedProgressiveDct);
   METRIC_LOG ("droppedLossless = " << droppedLossless);
   METRIC_LOG ("droppedHierarchical = " << droppedHierarchical);
   METRIC_LOG ("droppedHuffman = " << droppedHuffman);
   METRIC_LOG ("droppedArithmetic = " << droppedArithmetic);
}


/// Resets all the values to 0.
/// @return void.
void Metrics::Reset ()
{
   accepted = 0;
   dropped = 0;
   droppedInvalid = 0;
   droppedSequentialDct = 0;
   droppedProgressiveDct = 0;
   droppedLossless = 0; 
   droppedHierarchical = 0;
   droppedHuffman = 0; 
   droppedArithmetic = 0;
}




