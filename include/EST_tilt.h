/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                         Copyright (c) 1996                            */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK        */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE     */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*                    Author :  Paul Taylor                              */
/*                    Date   :  February 1996                            */
/*-----------------------------------------------------------------------*/
/*              Intonational Event Include file                          */
/*                                                                       */
/*=======================================================================*/
#ifndef __RFC_H__
#define __RFC_H__

#include "ling_class/EST_Relation.h"
#include "EST_util_class.h"
#include "EST_speech_class.h"
#include "EST_Event.h"

/**@defgroup tiltfunctions Tilt functions

Functions for:

  - Generating RFC and Tilt parameters from F0 contours
  - Converting RFC to Tilt parameters and vice-versa
  - Synthesizing F0 contours from RFC and Tilt events

*/
///@{

/** Fill op with sensible default parameters for RFC analysis.
 */
void default_rfc_params(EST_Features &op);

/** Produce a set of RFC parameterized events given approximate event
    boundaries and a smoothed F0 contour. See \ref ov-rfc-analysis for a description of this process.

    @param f0: Smoothed continuous F0 contour. An error will occur
    if any unvoiced regions are detected in the contour. Use the
    function smooth_pda to smooth and interpolate a normal contour.
    @param ev_list: list of events, each containing approximate start
    and end times of the events. On completion each event in this list
    will have a set of RFC parameters.
    @param op: parameters used to control analysis process.
    
 */
void rfc_analysis(EST_Track &fz, EST_Relation &event_list, EST_Features &op);

/** \brief Fill op with sensible default parameters for RFC analysis 
 */
void tilt_analysis(EST_Track &fz, EST_Relation &event_list, EST_Features &op);

/** Fill op with sensible default parameters for RFC analysis 
 */
void fill_rise_fall_values(EST_Track &fz, float amp, float start_f0);

/** \brief Generate an F0 contour given a list RFC events.

@param f0 Generated F0 contour
@param ev_list list of events, each containing a set of RFC parameters
@param f_shift frame shift in seconds of the generated contour
@param no_conn Do not join events with straight lines if set to 1
*/
void rfc_synthesis(EST_Track &f0, EST_Relation &ev_list,
		 float f_shift, int no_conn);

/** \brief Generate an F0 contour given a list Tilt events.

This function simply calls \ref tilt_to_rfc  followed by \ref rfc_synthesis .

@param f0 Generated F0 contour
@param ev_list list of events, each containing a set of Tilt parameters
@param f_shift frame shift in seconds of the generated contour
@param no_conn Do not join events with straight lines if set to 1
*/
void tilt_synthesis(EST_Track &track, EST_Relation &ev_list,
		 float f_shift, int no_conn);

/** \brief Convert a single set of local tilt parameters to local RFC parameters.

@param tilt input tilt parameters, named `amp`, `dur` and `tilt`
@param rfc output RFC parameters, name `rise_amp`, `fall_amp`, `rise_dur` and `fall_dur`

*/
void tilt_to_rfc(EST_Features &tilt, EST_Features &rfc);

/** \brief Convert a single set of local RFC parameters to local tilt
parameters. See \ref ov-rfc-to-tilt for a description of
how this is performed.

@param rfc input RFC parameters, named ` rise_amp`, `fall_amp`, `rise_dur` and` fall_dur`
@param tilt output tilt parameters, named `amp`, `dur` and `tilt` */
void rfc_to_tilt(EST_Features &rfc, EST_Features &tilt);

/** For each tilt events in `ev_tilt`, produce a set of RFC parameters.
    The tilt parameters are stored as the following features in the event:

  - tilt.amp
  - tilt.dur
  - tilt.tilt

    A set of features with the following names are created:


  - rfc.rise_amp
  - rfc.rise_dur
  - rfc.fall_amp
  - rfc.fall_dur

    The original tilt features are not deleted.
*/
void tilt_to_rfc(EST_Relation &ev_tilt);

/** \brief  For each tilt events in `ev_rfc`, produce a set of Tiltparameters.
    The RFC parameters are stored as the following features in the event:

  - rfc.rise_amp
  - rfc.rise_dur
  - rfc.fall_amp
  - rfc.fall_dur

    A set of features with the following names are created:

  - tilt.amp
  - tilt.dur
  - tilt.tilt

    The original RFC features are not deleted.
    
*/
void rfc_to_tilt(EST_Relation &ev_rfc);

int validate_rfc_stream(EST_Relation &ev);
void fill_rfc_types(EST_Relation &ev);

///@}



#endif /* RFC */
