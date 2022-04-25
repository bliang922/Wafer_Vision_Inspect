//
// Coreco API - Video Input Conditioning control functions.
//

#ifndef _CAPIVIC_H_
#define _CAPIVIC_H_

#include <capidef.h>
#include <capiacqd.h>

/****************************************************************************
*	Video Input Conditioning Capabilities
*
*	Last capability #: 0
****************************************************************************/
#define CORVIC_CAP_FIRST					0
#define CORVIC_CAP( n, size)				((((n) + CORVIC_CAP_FIRST) << 16) | (size))

/****************************************************************************
*
*	Video Input Conditioning Parameters
*
****************************************************************************/
#define CORVIC_PRM_FIRST					CORACQ_PRM_VIC_FIRST
#define CORVIC_PRM( n, size)				((((n) + CORVIC_PRM_FIRST) << 16) | (size))

#define CORVIC_PRM_CAMSEL					CORACQ_PRM_CAMSEL
#define CORVIC_PRM_PIXEL_MASK				CORACQ_PRM_PIXEL_MASK
#define CORVIC_PRM_DC_REST_MODE		  	CORACQ_PRM_DC_REST_MODE
#define CORVIC_PRM_BRIGHTNESS				CORACQ_PRM_BRIGHTNESS
#define CORVIC_PRM_BRIGHTNESS_RED	  	CORACQ_PRM_BRIGHTNESS_RED
#define CORVIC_PRM_BRIGHTNESS_GREEN	  	CORACQ_PRM_BRIGHTNESS_GREEN
#define CORVIC_PRM_BRIGHTNESS_BLUE	  	CORACQ_PRM_BRIGHTNESS_BLUE
#define CORVIC_PRM_CONTRAST			  	CORACQ_PRM_CONTRAST
#define CORVIC_PRM_CONTRAST_RED		  	CORACQ_PRM_CONTRAST_RED
#define CORVIC_PRM_CONTRAST_GREEN	  	CORACQ_PRM_CONTRAST_GREEN
#define CORVIC_PRM_CONTRAST_BLUE			CORACQ_PRM_CONTRAST_BLUE
#define CORVIC_PRM_HUE						CORACQ_PRM_HUE
#define CORVIC_PRM_SATURATION				CORACQ_PRM_SATURATION
#define CORVIC_PRM_FIX_FILTER_ENABLE  	CORACQ_PRM_FIX_FILTER_ENABLE
#define CORVIC_PRM_FIX_FILTER_SELECTOR	CORACQ_PRM_FIX_FILTER_SELECTOR
#define CORVIC_PRM_PROG_FILTER_ENABLE 	CORACQ_PRM_PROG_FILTER_ENABLE
#define CORVIC_PRM_PROG_FILTER_FREQ	  	CORACQ_PRM_PROG_FILTER_FREQ
#define CORVIC_PRM_CROP_LEFT				CORACQ_PRM_CROP_LEFT
#define CORVIC_PRM_CROP_TOP			  	CORACQ_PRM_CROP_TOP
#define CORVIC_PRM_CROP_WIDTH				CORACQ_PRM_CROP_WIDTH
#define CORVIC_PRM_CROP_HEIGHT		  	CORACQ_PRM_CROP_HEIGHT
#define CORVIC_PRM_SCALE_HORZ				CORACQ_PRM_SCALE_HORZ
#define CORVIC_PRM_SCALE_VERT				CORACQ_PRM_SCALE_VERT
#define CORVIC_PRM_SCALE_HORZ_METHOD  	CORACQ_PRM_SCALE_HORZ_METHOD
#define CORVIC_PRM_SCALE_VERT_METHOD  	CORACQ_PRM_SCALE_VERT_METHOD
#define CORVIC_PRM_DECIMATE_METHOD	  	CORACQ_PRM_DECIMATE_METHOD
#define CORVIC_PRM_DECIMATE_COUNT	  	CORACQ_PRM_DECIMATE_COUNT
#define CORVIC_PRM_LUT_ENABLE				CORACQ_PRM_LUT_ENABLE
#define CORVIC_PRM_LUT_NUMBER				CORACQ_PRM_LUT_NUMBER
#define CORVIC_PRM_STROBE_ENABLE			CORACQ_PRM_STROBE_ENABLE
#define CORVIC_PRM_STROBE_METHOD			CORACQ_PRM_STROBE_METHOD
#define CORVIC_PRM_STROBE_POLARITY	 	CORACQ_PRM_STROBE_POLARITY
#define CORVIC_PRM_STROBE_DURATION	 	CORACQ_PRM_STROBE_DURATION
#define CORVIC_PRM_STROBE_DELAY		 	CORACQ_PRM_STROBE_DELAY
#define CORVIC_PRM_FRAME_INTEGRATE_ENABLE		CORACQ_PRM_FRAME_INTEGRATE_ENABLE
#define CORVIC_PRM_FRAME_INTEGRATE_COUNT		CORACQ_PRM_FRAME_INTEGRATE_COUNT
#define CORVIC_PRM_TIME_INTEGRATE_ENABLE		CORACQ_PRM_TIME_INTEGRATE_ENABLE
#define CORVIC_PRM_TIME_INTEGRATE_DURATION	CORACQ_PRM_TIME_INTEGRATE_DURATION
#define CORVIC_PRM_CAM_TRIGGER_ENABLE			CORACQ_PRM_CAM_TRIGGER_ENABLE
#define CORVIC_PRM_CAM_RESET_ENABLE				CORACQ_PRM_CAM_RESET_ENABLE
#define CORVIC_PRM_OUTPUT_FORMAT					CORACQ_PRM_OUTPUT_FORMAT
#define CORVIC_PRM_CAMSEL_AUTOSWITCH_ENABLE	CORACQ_PRM_CAMSEL_AUTOSWITCH_ENABLE
#define CORVIC_PRM_CAMSEL_AUTOSWITCH_FIRST	CORACQ_PRM_CAMSEL_AUTOSWITCH_FIRST
#define CORVIC_PRM_CAMSEL_AUTOSWITCH_LAST		CORACQ_PRM_CAMSEL_AUTOSWITCH_LAST
#define CORVIC_PRM_OUTPUT_ENABLE					CORACQ_PRM_OUTPUT_ENABLE         // Obsolete, use CORVIC_PRM_EXT_TRIGGER_ENABLE
#define CORVIC_PRM_EXT_TRIGGER_ENABLE			CORACQ_PRM_EXT_TRIGGER_ENABLE
#define CORVIC_PRM_VIC_NAME						CORACQ_PRM_VIC_NAME
#define CORVIC_PRM_LUT_MAX							CORACQ_PRM_LUT_MAX
#define CORVIC_PRM_EXT_TRIGGER_DETECTION		CORACQ_PRM_EXT_TRIGGER_DETECTION
#define CORVIC_PRM_DC_REST_START					CORACQ_PRM_DC_REST_START
#define CORVIC_PRM_DC_REST_WIDTH					CORACQ_PRM_DC_REST_WIDTH
#define CORVIC_PRM_VSYNC_REF						CORACQ_PRM_VSYNC_REF
#define CORVIC_PRM_HSYNC_REF						CORACQ_PRM_HSYNC_REF
#define CORVIC_PRM_LINE_INTEGRATE_ENABLE		CORACQ_PRM_LINE_INTEGRATE_ENABLE
#define CORVIC_PRM_LINE_INTEGRATE_DURATION	CORACQ_PRM_LINE_INTEGRATE_DURATION
#define CORVIC_PRM_LINE_TRIGGER_ENABLE			CORACQ_PRM_LINE_TRIGGER_ENABLE
#define CORVIC_PRM_EXT_FRAME_TRIGGER_ENABLE		CORACQ_PRM_EXT_FRAME_TRIGGER_ENABLE
#define CORVIC_PRM_EXT_FRAME_TRIGGER_DETECTION	CORACQ_PRM_EXT_FRAME_TRIGGER_DETECTION
#define CORVIC_PRM_EXT_LINE_TRIGGER_ENABLE		CORACQ_PRM_EXT_LINE_TRIGGER_ENABLE
#define CORVIC_PRM_EXT_LINE_TRIGGER_DETECTION	CORACQ_PRM_EXT_LINE_TRIGGER_DETECTION
#define CORVIC_PRM_SNAP_COUNT						CORACQ_PRM_SNAP_COUNT
#define CORVIC_PRM_INT_LINE_TRIGGER_ENABLE		CORACQ_PRM_INT_LINE_TRIGGER_ENABLE
#define CORVIC_PRM_INT_LINE_TRIGGER_MODE		CORACQ_PRM_INT_LINE_TRIGGER_MODE
#define CORVIC_PRM_INT_LINE_TRIGGER_FREQ		CORACQ_PRM_INT_LINE_TRIGGER_FREQ
#define CORVIC_PRM_LINESCAN_DIRECTION_OUTPUT	CORACQ_PRM_LINESCAN_DIRECTION_OUTPUT
#define CORVIC_PRM_BIT_ORDERING					CORACQ_PRM_BIT_ORDERING
#define CORVIC_PRM_EXT_TRIGGER_LEVEL			CORACQ_PRM_EXT_TRIGGER_LEVEL
#define CORVIC_PRM_STROBE_LEVEL					CORACQ_PRM_STROBE_LEVEL
#define CORVIC_PRM_EXT_FRAME_TRIGGER_LEVEL	CORACQ_PRM_EXT_FRAME_TRIGGER_LEVEL
#define CORVIC_PRM_EXT_LINE_TRIGGER_LEVEL		CORACQ_PRM_EXT_LINE_TRIGGER_LEVEL
#define CORVIC_PRM_INT_LINE_TRIGGER_FREQ_MIN	CORACQ_PRM_INT_LINE_TRIGGER_FREQ_MIN
#define CORVIC_PRM_INT_LINE_TRIGGER_FREQ_MAX	CORACQ_PRM_INT_LINE_TRIGGER_FREQ_MAX
#define CORVIC_PRM_MASTER_MODE					CORACQ_PRM_MASTER_MODE
#define CORVIC_PRM_MASTER_MODE_HSYNC_POLARITY	CORACQ_PRM_MASTER_MODE_HSYNC_POLARITY
#define CORVIC_PRM_MASTER_MODE_VSYNC_POLARITY	CORACQ_PRM_MASTER_MODE_VSYNC_POLARITY
#define CORVIC_PRM_SHAFT_ENCODER_DROP			CORACQ_PRM_SHAFT_ENCODER_DROP
#define CORVIC_PRM_SHAFT_ENCODER_ENABLE		CORACQ_PRM_SHAFT_ENCODER_ENABLE
#define CORVIC_PRM_EXT_TRIGGER_FRAME_COUNT	CORACQ_PRM_EXT_TRIGGER_FRAME_COUNT
#define CORVIC_PRM_INT_FRAME_TRIGGER_ENABLE	CORACQ_PRM_INT_FRAME_TRIGGER_ENABLE		
#define CORVIC_PRM_INT_FRAME_TRIGGER_FREQ		CORACQ_PRM_INT_FRAME_TRIGGER_FREQ		
#define CORVIC_PRM_SHARED_EXT_TRIGGER			CORACQ_PRM_SHARED_EXT_TRIGGER
#define CORVIC_PRM_SHARED_CAM_RESET				CORACQ_PRM_SHARED_CAM_RESET
#define CORVIC_PRM_SHARED_CAM_TRIGGER			CORACQ_PRM_SHARED_CAM_TRIGGER
#define CORVIC_PRM_SHARED_TIME_INTEGRATE		CORACQ_PRM_SHARED_TIME_INTEGRATE
#define CORVIC_PRM_SHARED_FRAME_INTEGRATE		CORACQ_PRM_SHARED_FRAME_INTEGRATE
#define CORVIC_PRM_SHARED_STROBE					CORACQ_PRM_SHARED_STROBE
#define CORVIC_PRM_STROBE_DELAY_2				CORACQ_PRM_STROBE_DELAY_2
#define CORVIC_PRM_FRAME_LENGTH					CORACQ_PRM_FRAME_LENGTH
#define CORVIC_PRM_FLIP                      CORACQ_PRM_FLIP       						
#define CORVIC_PRM_SHARPNESS                 CORACQ_PRM_SHARPNESS  						
#define CORVIC_PRM_EXT_TRIGGER_DURATION      CORACQ_PRM_EXT_TRIGGER_DURATION		
#define CORVIC_PRM_TIME_INTEGRATE_DELAY      CORACQ_PRM_TIME_INTEGRATE_DELAY         
#define CORVIC_PRM_CAM_RESET_DELAY           CORACQ_PRM_CAM_RESET_DELAY					
#define CORVIC_PRM_CAM_TRIGGER_DELAY         CORACQ_PRM_CAM_TRIGGER_DELAY			
#define CORVIC_PRM_SHAFT_ENCODER_LEVEL       CORACQ_PRM_SHAFT_ENCODER_LEVEL
#define CORVIC_PRM_WEN_ENABLE                CORACQ_PRM_WEN_ENABLE
#define CORVIC_PRM_LUT_NENTRIES              CORACQ_PRM_LUT_NENTRIES
#define CORVIC_PRM_EXT_FRAME_TRIGGER_SOURCE  CORACQ_PRM_EXT_FRAME_TRIGGER_SOURCE
#define CORVIC_PRM_EXT_LINE_TRIGGER_SOURCE   CORACQ_PRM_EXT_LINE_TRIGGER_SOURCE
#define CORVIC_PRM_EXT_TRIGGER_SOURCE        CORACQ_PRM_EXT_TRIGGER_SOURCE
#define CORVIC_PRM_SHAFT_ENCODER_MULTIPLY	   CORACQ_PRM_SHAFT_ENCODER_MULTIPLY
#define CORVIC_PRM_PLANAR_INPUT_SOURCES      CORACQ_PRM_PLANAR_INPUT_SOURCES
#define CORVIC_PRM_EXT_TRIGGER_DELAY			CORACQ_PRM_EXT_TRIGGER_DELAY			
#define CORVIC_PRM_EXT_TRIGGER_DELAY_TIME_BASE CORACQ_PRM_EXT_TRIGGER_DELAY_TIME_BASE
#define CORVIC_PRM_COLOR_DECODER_ENABLE			CORACQ_PRM_COLOR_DECODER_ENABLE		
#define CORVIC_PRM_BAYER_DECODER_ENABLE         CORACQ_PRM_BAYER_DECODER_ENABLE     // Obsolete Name
#define CORVIC_PRM_COLOR_DECODER_METHOD			CORACQ_PRM_COLOR_DECODER_METHOD		
#define CORVIC_PRM_BAYER_DECODER_METHOD         CORACQ_PRM_BAYER_DECODER_METHOD     // Obsolete Name
#define CORVIC_PRM_WB_GAIN_RED		            CORACQ_PRM_WB_GAIN_RED		
#define CORVIC_PRM_BAYER_DECODER_WB_GAIN_RED		CORACQ_PRM_BAYER_DECODER_WB_GAIN_RED   // Obsolete Name		
#define CORVIC_PRM_WB_GAIN_GREEN	               CORACQ_PRM_WB_GAIN_GREEN	
#define CORVIC_PRM_BAYER_DECODER_WB_GAIN_GREEN	CORACQ_PRM_BAYER_DECODER_WB_GAIN_GREEN // Obsolete Name	
#define CORVIC_PRM_WB_GAIN_BLUE	               CORACQ_PRM_WB_GAIN_BLUE	               // Obsolete Name
#define CORVIC_PRM_BAYER_DECODER_WB_GAIN_BLUE	CORACQ_PRM_BAYER_DECODER_WB_GAIN_BLUE	
#define CORVIC_PRM_WB_OFFSET_RED	               CORACQ_PRM_WB_OFFSET_RED	
#define CORVIC_PRM_BAYER_DECODER_WB_OFFSET_RED	CORACQ_PRM_BAYER_DECODER_WB_OFFSET_RED // Obsolete Name	   
#define CORVIC_PRM_WB_OFFSET_GREEN              CORACQ_PRM_WB_OFFSET_GREEN             // Obsolete Name
#define CORVIC_PRM_BAYER_DECODER_WB_OFFSET_GREEN CORACQ_PRM_BAYER_DECODER_WB_OFFSET_GREEN
#define CORVIC_PRM_WB_OFFSET_BLUE	            CORACQ_PRM_WB_OFFSET_BLUE	
#define CORVIC_PRM_BAYER_DECODER_WB_OFFSET_BLUE	 CORACQ_PRM_BAYER_DECODER_WB_OFFSET_BLUE  // Obsolete Name	
#define CORVIC_PRM_CAM_CONTROL_PULSE0_HD_ALIGN        CORACQ_PRM_CAM_CONTROL_PULSE0_HD_ALIGN
#define CORVIC_PRM_CAM_CONTROL_PULSE1_HD_ALIGN        CORACQ_PRM_CAM_CONTROL_PULSE1_HD_ALIGN
#define CORVIC_PRM_EXT_TRIGGER_IGNORE_DELAY           CORACQ_PRM_EXT_TRIGGER_IGNORE_DELAY
#define CORVIC_PRM_BOARD_SYNC_OUTPUT1_SOURCE          CORACQ_PRM_BOARD_SYNC_OUTPUT1_SOURCE
#define CORVIC_PRM_BOARD_SYNC_OUTPUT2_SOURCE          CORACQ_PRM_BOARD_SYNC_OUTPUT2_SOURCE
#define CORVIC_PRM_CONTROL_SIGNAL_OUTPUT1             CORVIC_PRM_BOARD_SYNC_OUTPUT1_SOURCE      //obsolete name
#define CORVIC_PRM_CONTROL_SIGNAL_OUTPUT2             CORVIC_PRM_BOARD_SYNC_OUTPUT2_SOURCE      //obsolete name
#define CORVIC_PRM_FIX_FILTER_SELECTOR_STR            CORACQ_PRM_FIX_FILTER_SELECTOR_STR
#define CORVIC_PRM_EXT_LINE_TRIGGER_SOURCE_STR        CORACQ_PRM_EXT_LINE_TRIGGER_SOURCE_STR
#define CORVIC_PRM_EXT_TRIGGER_SOURCE_STR             CORACQ_PRM_EXT_TRIGGER_SOURCE_STR
#define CORVIC_PRM_VERTICAL_TIMEOUT_DELAY             CORACQ_PRM_VERTICAL_TIMEOUT_DELAY
#define CORVIC_PRM_BAYER_DECODER_SATURATION_FACTOR    CORACQ_PRM_BAYER_DECODER_SATURATION_FACTOR
#define CORVIC_PRM_BAYER_DECODER_SATURATION_WEIGHT_RED CORACQ_PRM_BAYER_DECODER_SATURATION_WEIGHT_RED
#define CORVIC_PRM_BAYER_DECODER_SATURATION_WEIGHT_GREEN CORACQ_PRM_BAYER_DECODER_SATURATION_WEIGHT_GREEN
#define CORVIC_PRM_BAYER_DECODER_SATURATION_WEIGHT_BLUE CORACQ_PRM_BAYER_DECODER_SATURATION_WEIGHT_BLUE
#define CORVIC_PRM_POCL_ENABLE								CORACQ_PRM_POCL_ENABLE
#define CORVIC_PRM_CROP_ACTIVATION                    CORACQ_PRM_CROP_ACTIVATION
#define CORVIC_PRM_SHAFT_ENCODER_SOURCE				   CORACQ_PRM_SHAFT_ENCODER_SOURCE
#define CORVIC_PRM_SHAFT_ENCODER_SOURCE_STR           CORACQ_PRM_SHAFT_ENCODER_SOURCE_STR
#define CORVIC_PRM_SHAFT_ENCODER_DIRECTION			   CORACQ_PRM_SHAFT_ENCODER_DIRECTION
#define CORVIC_PRM_LINE_TRIGGER_AUTO_DELAY			   CORACQ_PRM_LINE_TRIGGER_AUTO_DELAY
#define CORVIC_PRM_TIME_STAMP_BASE                    CORACQ_PRM_TIME_STAMP_BASE
#define CORVIC_PRM_SHAFT_ENCODER_ORDER                CORACQ_PRM_SHAFT_ENCODER_ORDER
#define CORVIC_PRM_CAM_FRAMES_PER_TRIGGER             CORACQ_PRM_CAM_FRAMES_PER_TRIGGER
#define CORVIC_PRM_LINE_INTEGRATE_TIME_BASE           CORACQ_PRM_LINE_INTEGRATE_TIME_BASE
#define CORVIC_PRM_BOARD_SYNC_OUTPUT1_SOURCE_STR      CORACQ_PRM_BOARD_SYNC_OUTPUT1_SOURCE_STR
#define CORVIC_PRM_BOARD_SYNC_OUTPUT2_SOURCE_STR      CORACQ_PRM_BOARD_SYNC_OUTPUT2_SOURCE_STR
#define CORVIC_PRM_SHAFT_ENCODER_ORDER                CORACQ_PRM_SHAFT_ENCODER_ORDER
#define CORVIC_PRM_CAM_FRAMES_PER_TRIGGER             CORACQ_PRM_CAM_FRAMES_PER_TRIGGER
#define CORVIC_PRM_LINE_INTEGRATE_TIME_BASE           CORACQ_PRM_LINE_INTEGRATE_TIME_BASE
#define CORVIC_PRM_EXT_TRIGGER_IGNORE_REGION_DURATION CORACQ_PRM_EXT_TRIGGER_IGNORE_REGION_DURATION
#define CORVIC_PRM_STROBE_DESTINATION_STR 		      CORACQ_PRM_STROBE_DESTINATION_STR
#define CORVIC_PRM_STROBE_DESTINATION				      CORACQ_PRM_STROBE_DESTINATION
#define CORVIC_PRM_SHAFT_ENCODER_AVERAGING_ENABLE     CORACQ_PRM_SHAFT_ENCODER_AVERAGING_ENABLE
#define CORVIC_PRM_SHAFT_ENCODER_AVERAGING_PULSES   	CORACQ_PRM_SHAFT_ENCODER_AVERAGING_PULSES
#define CORVIC_PRM_SHAFT_ENCODER_AVERAGING_PERIOD_MIN	CORACQ_PRM_SHAFT_ENCODER_AVERAGING_PERIOD_MIN
#define CORVIC_PRM_SHAFT_ENCODER_AVERAGING_PERIOD_MAX	CORACQ_PRM_SHAFT_ENCODER_AVERAGING_PERIOD_MAX
#define CORVIC_PRM_HDR_ENABLE	                        CORACQ_PRM_HDR_ENABLE
#define CORVIC_PRM_HDR_METHOD	                        CORACQ_PRM_HDR_METHOD
#define CORVIC_PRM_HDR_WEIGHT	                        CORACQ_PRM_HDR_WEIGHT
#define CORVIC_PRM_CYCLING_PRESET_ENABLE				   CORACQ_PRM_CYCLING_PRESET_ENABLE					
#define CORVIC_PRM_CYCLING_PRESET_COUNT					CORACQ_PRM_CYCLING_PRESET_COUNT					
#define CORVIC_PRM_CYCLING_PRESET_SELECT				   CORACQ_PRM_CYCLING_PRESET_SELECT					
#define CORVIC_PRM_CYCLING_PRESET_INCREMENTAL_SOURCE	CORACQ_PRM_CYCLING_PRESET_INCREMENTAL_SOURCE	
#define CORVIC_PRM_CYCLING_PRESET_REPEATER				CORACQ_PRM_CYCLING_PRESET_REPEATER				
#define CORVIC_PRM_CYCLING_PRESET_RESET_SOURCE			CORACQ_PRM_CYCLING_PRESET_RESET_SOURCE			
#define CORVIC_PRM_CYCLING_PRESET_STROBE_START_INDEX	CORACQ_PRM_CYCLING_PRESET_STROBE_START_INDEX	
#define CORVIC_PRM_CYCLING_PRESET_STROBE_DESTINATION_INDEX	CORACQ_PRM_CYCLING_PRESET_STROBE_DESTINATION_INDEX
#define CORVIC_PRM_CYCLING_PRESET_STROBE_DURATION		CORACQ_PRM_CYCLING_PRESET_STROBE_DURATION		
#define CORVIC_PRM_CYCLING_PRESET_STROBE_DELAY			CORACQ_PRM_CYCLING_PRESET_STROBE_DELAY			
#define CORVIC_PRM_CYCLING_PRESET_STROBE_POLARITY		CORACQ_PRM_CYCLING_PRESET_STROBE_POLARITY		
#define CORVIC_PRM_CYCLING_PRESET_LINE_INTEGRATE_DURATION	CORACQ_PRM_CYCLING_PRESET_LINE_INTEGRATE_DURATION	
#define CORVIC_PRM_CYCLING_PRESET_LINE_INTEGRATE_DELAY CORACQ_PRM_CYCLING_PRESET_LINE_INTEGRATE_DELAY		

#define CORVIC_PRM_LAST											CORACQ_PRM_VIC_LAST

/****************************************************************************
*
*	Vic Values
*
****************************************************************************/
#define CORVIC_VAL_ACTIVE_LOW							CORACQ_VAL_ACTIVE_LOW
#define CORVIC_VAL_ACTIVE_HIGH						CORACQ_VAL_ACTIVE_HIGH	
#define CORVIC_VAL_RISING_EDGE						CORACQ_VAL_RISING_EDGE	
#define CORVIC_VAL_FALLING_EDGE						CORACQ_VAL_FALLING_EDGE	
#define CORVIC_VAL_DOUBLE_PULSE_RISING_EDGE     CORACQ_VAL_DOUBLE_PULSE_RISING_EDGE
#define CORVIC_VAL_DOUBLE_PULSE_FALLING_EDGE    CORACQ_VAL_DOUBLE_PULSE_FALLING_EDGE

#define CORVIC_VAL_BIT_ORDERING_STD					CORACQ_VAL_BIT_ORDERING_STD
#define CORVIC_VAL_BIT_ORDERING_9_10				CORACQ_VAL_BIT_ORDERING_9_10
#define CORVIC_VAL_BIT_ORDERING_MSB_10			   CORACQ_VAL_BIT_ORDERING_MSB_10	
#define CORVIC_VAL_BIT_ORDERING_MSB_12          CORACQ_VAL_BIT_ORDERING_MSB_12			
#define CORVIC_VAL_BIT_ORDERING_INVERT          CORACQ_VAL_BIT_ORDERING_INVERT			

#define CORVIC_VAL_CAM_CONTROL_HD_ALIGN_AUTO       CORACQ_VAL_CAM_CONTROL_HD_ALIGN_AUTO
#define CORVIC_VAL_CAM_CONTROL_HD_ALIGN_ON         CORACQ_VAL_CAM_CONTROL_HD_ALIGN_ON
#define CORVIC_VAL_CAM_CONTROL_HD_ALIGN_OFF        CORACQ_VAL_CAM_CONTROL_HD_ALIGN_OFF

#define CORVIC_VAL_CAM_RESET_METHOD_1           CORACQ_VAL_CAM_RESET_METHOD_1

#define CORVIC_VAL_CAM_TRIGGER_METHOD_1         CORACQ_VAL_CAM_TRIGGER_METHOD_1  		
#define CORVIC_VAL_CAM_TRIGGER_METHOD_2         CORACQ_VAL_CAM_TRIGGER_METHOD_2  		

#define CORVIC_VAL_CROP_ACTIVATION_AUTO         CORACQ_VAL_CROP_ACTIVATION_AUTO
#define CORVIC_VAL_CROP_ACTIVATION_LEVEL        CORACQ_VAL_CROP_ACTIVATION_LEVEL
#define CORVIC_VAL_CROP_ACTIVATION_EDGE         CORACQ_VAL_CROP_ACTIVATION_EDGE   

#define CORVIC_VAL_DC_REST_MODE_AUTO				CORACQ_VAL_DC_REST_MODE_AUTO
#define CORVIC_VAL_DC_REST_MODE_ON					CORACQ_VAL_DC_REST_MODE_ON
#define CORVIC_VAL_DC_REST_MODE_OFF					CORACQ_VAL_DC_REST_MODE_OFF

#define CORVIC_VAL_DECIMATE_DISABLE					CORACQ_VAL_DECIMATE_DISABLE	
#define CORVIC_VAL_DECIMATE_FIELD					CORACQ_VAL_DECIMATE_FIELD
#define CORVIC_VAL_DECIMATE_FRAME					CORACQ_VAL_DECIMATE_FRAME
#define CORVIC_VAL_DECIMATE_ODD						CORACQ_VAL_DECIMATE_ODD
#define CORVIC_VAL_DECIMATE_EVEN						CORACQ_VAL_DECIMATE_EVEN

#define CORVIC_VAL_EXT_TRIGGER_OFF              CORACQ_VAL_EXT_TRIGGER_OFF
#define CORVIC_VAL_EXT_TRIGGER_ON               CORACQ_VAL_EXT_TRIGGER_ON

#define CORVIC_VAL_FLIP_OFF                     CORACQ_VAL_FLIP_OFF                     
#define CORVIC_VAL_FLIP_HORZ                    CORACQ_VAL_FLIP_HORZ                    
#define CORVIC_VAL_FLIP_VERT                    CORACQ_VAL_FLIP_VERT                    

#define CORVIC_VAL_FRAME_INTEGRATE_METHOD_1     CORACQ_VAL_FRAME_INTEGRATE_METHOD_1		
#define CORVIC_VAL_FRAME_INTEGRATE_METHOD_2	   CORACQ_VAL_FRAME_INTEGRATE_METHOD_2	

#define CORVIC_VAL_FRAME_LENGTH_FIX					CORACQ_VAL_FRAME_LENGTH_FIX
#define CORVIC_VAL_FRAME_LENGTH_VARIABLE			CORACQ_VAL_FRAME_LENGTH_VARIABLE

#define CORVIC_VAL_LEVEL_TTL							CORACQ_VAL_LEVEL_TTL
#define CORVIC_VAL_LEVEL_422							CORACQ_VAL_LEVEL_422
#define CORVIC_VAL_LEVEL_LVDS							CORACQ_VAL_LEVEL_LVDS
#define CORVIC_VAL_LEVEL_12VOLTS						CORACQ_VAL_LEVEL_12VOLTS
#define CORVIC_VAL_LEVEL_24VOLTS						CORACQ_VAL_LEVEL_24VOLTS

#define CORVIC_VAL_LINE_INTEGRATE_METHOD_1      CORACQ_VAL_LINE_INTEGRATE_METHOD_1		
#define CORVIC_VAL_LINE_INTEGRATE_METHOD_2		CORACQ_VAL_LINE_INTEGRATE_METHOD_2
#define CORVIC_VAL_LINE_INTEGRATE_METHOD_3		CORACQ_VAL_LINE_INTEGRATE_METHOD_3
#define CORVIC_VAL_LINE_INTEGRATE_METHOD_4		CORACQ_VAL_LINE_INTEGRATE_METHOD_4
#define CORVIC_VAL_LINE_INTEGRATE_METHOD_5		CORACQ_VAL_LINE_INTEGRATE_METHOD_5
#define CORVIC_VAL_LINE_INTEGRATE_METHOD_6		CORACQ_VAL_LINE_INTEGRATE_METHOD_6
#define CORVIC_VAL_LINE_INTEGRATE_METHOD_7		CORACQ_VAL_LINE_INTEGRATE_METHOD_7

#define CORVIC_VAL_LINE_TRIGGER_METHOD_1        CORACQ_VAL_LINE_TRIGGER_METHOD_1

#define CORVIC_VAL_LINESCAN_DIRECTION_FORWARD	CORACQ_VAL_LINESCAN_DIRECTION_FORWARD
#define CORVIC_VAL_LINESCAN_DIRECTION_REVERSE	CORACQ_VAL_LINESCAN_DIRECTION_REVERSE

#define CORVIC_VAL_MASTER_MODE_DISABLE				CORACQ_VAL_MASTER_MODE_DISABLE
#define CORVIC_VAL_MASTER_MODE_HSYNC_VSYNC		CORACQ_VAL_MASTER_MODE_HSYNC_VSYNC
#define CORVIC_VAL_MASTER_MODE_HSYNC				CORACQ_VAL_MASTER_MODE_HSYNC
#define CORVIC_VAL_MASTER_MODE_VSYNC				CORACQ_VAL_MASTER_MODE_VSYNC

//** Obsolete: use CORVIC_VAL_EXT_TRIGGER_xxx   
#define CORVIC_VAL_OUTPUT_ENABLE_AUTO				CORACQ_VAL_OUTPUT_ENABLE_AUTO
#define CORVIC_VAL_OUTPUT_ENABLE_ON					CORACQ_VAL_OUTPUT_ENABLE_ON
#define CORVIC_VAL_OUTPUT_ENABLE_OFF				CORACQ_VAL_OUTPUT_ENABLE_OFF
#define CORVIC_VAL_OUTPUT_ENABLE_ON_EXTRIG		CORACQ_VAL_OUTPUT_ENABLE_ON_EXTRIG

#define CORVIC_VAL_OUTPUT_FORMAT_MONO1				CORACQ_VAL_OUTPUT_FORMAT_MONO1					 
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8				CORACQ_VAL_OUTPUT_FORMAT_MONO8					 
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16			CORACQ_VAL_OUTPUT_FORMAT_MONO16	 
#define CORVIC_VAL_OUTPUT_FORMAT_MONO32			CORACQ_VAL_OUTPUT_FORMAT_MONO32	

#define CORVIC_VAL_OUTPUT_FORMAT_RGB5551			CORACQ_VAL_OUTPUT_FORMAT_RGB5551	
#define CORVIC_VAL_OUTPUT_FORMAT_RGB565			CORACQ_VAL_OUTPUT_FORMAT_RGB565	 
#define CORVIC_VAL_OUTPUT_FORMAT_RGB888			CORACQ_VAL_OUTPUT_FORMAT_RGB888	 
#define CORVIC_VAL_OUTPUT_FORMAT_RGBR888			CORACQ_VAL_OUTPUT_FORMAT_RGBR888
#define CORVIC_VAL_OUTPUT_FORMAT_RGB8888			CORACQ_VAL_OUTPUT_FORMAT_RGB8888	
#define CORVIC_VAL_OUTPUT_FORMAT_RGB101010		CORACQ_VAL_OUTPUT_FORMAT_RGB101010 
#define CORVIC_VAL_OUTPUT_FORMAT_RGB161616		CORACQ_VAL_OUTPUT_FORMAT_RGB161616 
#define CORVIC_VAL_OUTPUT_FORMAT_RGB16161616		CORACQ_VAL_OUTPUT_FORMAT_RGB16161616 

#define CORVIC_VAL_OUTPUT_FORMAT_BICOLOR88      CORACQ_VAL_OUTPUT_FORMAT_BICOLOR88
#define CORVIC_VAL_OUTPUT_FORMAT_BICOLOR1616    CORACQ_VAL_OUTPUT_FORMAT_BICOLOR1616
#define CORVIC_VAL_OUTPUT_FORMAT_BICOLOR1212    CORACQ_VAL_OUTPUT_FORMAT_BICOLOR1212

#define CORVIC_VAL_OUTPUT_FORMAT_RGB888_MONO8      CORACQ_VAL_OUTPUT_FORMAT_RGB888_MONO8
#define CORVIC_VAL_OUTPUT_FORMAT_RGB161616_MONO16  CORACQ_VAL_OUTPUT_FORMAT_RGB161616_MONO16

#define CORVIC_VAL_OUTPUT_FORMAT_UYVY				CORACQ_VAL_OUTPUT_FORMAT_UYVY		
#define CORVIC_VAL_OUTPUT_FORMAT_YUY2				CORACQ_VAL_OUTPUT_FORMAT_YUY2		
#define CORVIC_VAL_OUTPUT_FORMAT_YVYU				CORACQ_VAL_OUTPUT_FORMAT_YVYU		
#define CORVIC_VAL_OUTPUT_FORMAT_YUYV				CORACQ_VAL_OUTPUT_FORMAT_YUYV		

#define CORVIC_VAL_OUTPUT_FORMAT_Y411				CORACQ_VAL_OUTPUT_FORMAT_Y411		
#define CORVIC_VAL_OUTPUT_FORMAT_Y211				CORACQ_VAL_OUTPUT_FORMAT_Y211		

#define CORVIC_VAL_OUTPUT_FORMAT_RGBP8				CORACQ_VAL_OUTPUT_FORMAT_RGBP8
#define CORVIC_VAL_OUTPUT_FORMAT_RGBP16			CORACQ_VAL_OUTPUT_FORMAT_RGBP16

#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P2			CORACQ_VAL_OUTPUT_FORMAT_MONO8P2
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P3			CORACQ_VAL_OUTPUT_FORMAT_MONO8P3
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P4			CORACQ_VAL_OUTPUT_FORMAT_MONO8P4
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P5			CORACQ_VAL_OUTPUT_FORMAT_MONO8P5
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P6			CORACQ_VAL_OUTPUT_FORMAT_MONO8P6
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P7			CORACQ_VAL_OUTPUT_FORMAT_MONO8P7
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P8			CORACQ_VAL_OUTPUT_FORMAT_MONO8P8
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P9			CORACQ_VAL_OUTPUT_FORMAT_MONO8P9
#define CORVIC_VAL_OUTPUT_FORMAT_MONO8P10			CORACQ_VAL_OUTPUT_FORMAT_MONO8P10

#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P2			CORACQ_VAL_OUTPUT_FORMAT_MONO16P2
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P3			CORACQ_VAL_OUTPUT_FORMAT_MONO16P3
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P4			CORACQ_VAL_OUTPUT_FORMAT_MONO16P4
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P5			CORACQ_VAL_OUTPUT_FORMAT_MONO16P5
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P6			CORACQ_VAL_OUTPUT_FORMAT_MONO16P6
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P7			CORACQ_VAL_OUTPUT_FORMAT_MONO16P7
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P8			CORACQ_VAL_OUTPUT_FORMAT_MONO16P8
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P9			CORACQ_VAL_OUTPUT_FORMAT_MONO16P9
#define CORVIC_VAL_OUTPUT_FORMAT_MONO16P10		CORACQ_VAL_OUTPUT_FORMAT_MONO16P10

#define CORVIC_VAL_OUTPUT_FORMAT_HSV				CORACQ_VAL_OUTPUT_FORMAT_HSV
#define CORVIC_VAL_OUTPUT_FORMAT_HSI				CORACQ_VAL_OUTPUT_FORMAT_HSI
#define CORVIC_VAL_OUTPUT_FORMAT_HSIP8				CORACQ_VAL_OUTPUT_FORMAT_HSIP8
#define CORVIC_VAL_OUTPUT_FORMAT_LAB				CORACQ_VAL_OUTPUT_FORMAT_LAB
#define CORVIC_VAL_OUTPUT_FORMAT_LABP8				CORACQ_VAL_OUTPUT_FORMAT_LABP8
#define CORVIC_VAL_OUTPUT_FORMAT_LABP16			CORACQ_VAL_OUTPUT_FORMAT_LABP16
#define CORVIC_VAL_OUTPUT_FORMAT_LAB16161616		CORACQ_VAL_OUTPUT_FORMAT_LAB16161616
#define CORVIC_VAL_OUTPUT_FORMAT_LAB101010		CORACQ_VAL_OUTPUT_FORMAT_LAB101010

#define CORVIC_VAL_OUTPUT_FORMAT_IYU1				CORACQ_VAL_OUTPUT_FORMAT_IYU1
#define CORVIC_VAL_OUTPUT_FORMAT_IYU2				CORACQ_VAL_OUTPUT_FORMAT_IYU2

#define CORVIC_VAL_OUTPUT_FORMAT_YUV				CORACQ_VAL_OUTPUT_FORMAT_YUV
#define CORVIC_VAL_OUTPUT_FORMAT_AYUV				CORACQ_VAL_OUTPUT_FORMAT_AYUV

#define CORVIC_VAL_OUTPUT_FORMAT_RGBAP8			CORACQ_VAL_OUTPUT_FORMAT_RGBAP8
#define CORVIC_VAL_OUTPUT_FORMAT_RGBAP16			CORACQ_VAL_OUTPUT_FORMAT_RGBAP16

#define CORVIC_VAL_OUTPUT_FORMAT_RGB888_MONO8P2      CORACQ_VAL_OUTPUT_FORMAT_RGB888_MONO8P2
#define CORVIC_VAL_OUTPUT_FORMAT_RGB161616_MONO16P2  CORACQ_VAL_OUTPUT_FORMAT_RGB161616_MONO16P2

#define CORVIC_VAL_SCALE_FACTOR						CORACQ_VAL_SCALE_FACTOR

#define CORVIC_VAL_SCALE_METHOD_DISABLE			CORACQ_VAL_SCALE_METHOD_DISABLE
#define CORVIC_VAL_SCALE_METHOD_SIMPLE				CORACQ_VAL_SCALE_METHOD_SIMPLE
#define CORVIC_VAL_SCALE_METHOD_INTERPOLATION	CORACQ_VAL_SCALE_METHOD_INTERPOLATION
#define CORVIC_VAL_SCALE_METHOD_POW2				CORACQ_VAL_SCALE_METHOD_POW2

#define CORVIC_VAL_SHAFT_ENCODER_ORDER_AUTO           CORACQ_VAL_SHAFT_ENCODER_ORDER_AUTO
#define CORVIC_VAL_SHAFT_ENCODER_ORDER_DROP_MULTIPLY  CORACQ_VAL_SHAFT_ENCODER_ORDER_DROP_MULTIPLY  
#define CORVIC_VAL_SHAFT_ENCODER_ORDER_MULTIPLY_DROP  CORACQ_VAL_SHAFT_ENCODER_ORDER_MULTIPLY_DROP

#define CORVIC_VAL_SHARED_CONTROL_DISABLE			CORACQ_VAL_SHARED_CONTROL_DISABLE

#define CORVIC_VAL_STROBE_METHOD_1					CORACQ_VAL_STROBE_METHOD_1
#define CORVIC_VAL_STROBE_METHOD_2					CORACQ_VAL_STROBE_METHOD_2

#define CORVIC_VAL_SYNC_REF_BEGIN					CORACQ_VAL_SYNC_REF_BEGIN
#define CORVIC_VAL_SYNC_REF_END						CORACQ_VAL_SYNC_REF_END
#define CORVIC_VAL_SYNC_REF_HV_DEPENDENT			CORACQ_VAL_SYNC_REF_HV_DEPENDENT

#define CORVIC_VAL_TIME_BASE_US						CORACQ_VAL_TIME_BASE_US
#define CORVIC_VAL_TIME_BASE_MS						CORACQ_VAL_TIME_BASE_MS
#define CORVIC_VAL_TIME_BASE_LINE      			CORACQ_VAL_TIME_BASE_LINE
#define CORVIC_VAL_TIME_BASE_LINE_VALID         CORACQ_VAL_TIME_BASE_LINE_VALID           //same as CORACQ_VAL_TIME_BASE_LINE
#define CORVIC_VAL_TIME_BASE_LINE_TRIGGER			CORACQ_VAL_TIME_BASE_LINE_TRIGGER
#define CORVIC_VAL_TIME_BASE_FRAME					CORACQ_VAL_TIME_BASE_FRAME
#define CORVIC_VAL_TIME_BASE_FRAME_VALID			CORACQ_VAL_TIME_BASE_FRAME_VALID          //same as CORACQ_VAL_TIME_BASE_FRAME
#define CORVIC_VAL_TIME_BASE_FRAME_TRIGGER		CORACQ_VAL_TIME_BASE_FRAME_TRIGGER
#define CORVIC_VAL_TIME_BASE_SHAFT_ENCODER		CORACQ_VAL_TIME_BASE_SHAFT_ENCODER
#define CORVIC_VAL_TIME_BASE_NS                 CORACQ_VAL_TIME_BASE_NS 
#define CORVIC_VAL_TIME_BASE_PIXEL_CLK          CORACQ_VAL_TIME_BASE_PIXEL_CLK

#define CORVIC_VAL_TIME_INTEGRATE_METHOD_1      CORACQ_VAL_TIME_INTEGRATE_METHOD_1		
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_2		CORACQ_VAL_TIME_INTEGRATE_METHOD_2
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_3		CORACQ_VAL_TIME_INTEGRATE_METHOD_3
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_4		CORACQ_VAL_TIME_INTEGRATE_METHOD_4
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_5	   CORACQ_VAL_TIME_INTEGRATE_METHOD_5	
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_6		CORACQ_VAL_TIME_INTEGRATE_METHOD_6
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_7		CORACQ_VAL_TIME_INTEGRATE_METHOD_7
#define CORVIC_VAL_TIME_INTEGRATE_METHOD_8		CORACQ_VAL_TIME_INTEGRATE_METHOD_8


#ifdef __cplusplus
extern "C" {
#endif

/* Application programming interface */

/* Object creation and destruction */
CORSTATUS CORAPIFUNC CorVicFree( CORVIC hVic);
CORSTATUS CORAPIFUNC CorVicNew( CORSERVER hServer, CORVIC *pVic);

/* Load/Save from/to file */
CORSTATUS CORAPIFUNC CorVicLoad( CORVIC hVic, PCSTR filename);
CORSTATUS CORAPIFUNC CorVicSave( CORVIC hVic, PCSTR filename);

/* Modify	Vic Parameters	*/
CORSTATUS CORAPIFUNC CorVicGetPrm  ( CORVIC hVic, UINT32 param, void *value); 
CORSTATUS CORAPIFUNC CorVicSetPrm  ( CORVIC hVic, UINT32 param, UINT32 value); 
CORSTATUS CORAPIFUNC CorVicSetPrmEx( CORVIC hVic, UINT32 prm, const void *value);
CORSTATUS CORAPIFUNC CorVicGetCap  ( CORVIC hVic, UINT32 cap, void *value);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIVIC_H_
