// -*- C++ -*-
/*!
 * @file  RTCKinect.cpp
 * @brief RTC Kinect 4 Windows
 * @date $Date$
 *
 * $Id$
 */


#include <windows.h>
#include "MSR_NuiApi.h"


#include "RTCKinect.h"



// Module specification
// <rtc-template block="module_spec">
static const char* rtckinect_spec[] =
  {
    "implementation_id", "RTCKinect",
    "type_name",         "RTCKinect",
    "description",       "RTC Kinect 4 Windows",
    "version",           "1.0.0",
    "vendor",            "ysuga.net",
    "category",          "Experimental",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    "conf.default.enable_camera", "1",
    "conf.default.enable_depth", "1",
    "conf.default.camera_width", "640",
    "conf.default.camera_height", "480",
    "conf.default.depth_width", "320",
    "conf.default.depth_height", "240",
    "conf.default.player_index", "0",
    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.enable_camera", "text",
    "conf.__widget__.enable_depth", "text",
    "conf.__widget__.camera_width", "text",
    "conf.__widget__.camera_height", "text",
    "conf.__widget__.depth_width", "text",
    "conf.__widget__.depth_height", "text",
    "conf.__widget__.player_index", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTCKinect::RTCKinect(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetElevationIn("targetElevation", m_targetElevation),
    m_imageOut("image", m_image),
    m_depthOut("depth", m_depth),
    m_currentElevationOut("currentElevation", m_currentElevation),
    m_skeletonOut("skeleton", m_skeleton),
    m_soundSourceOut("dp_name", m_soundSource)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTCKinect::~RTCKinect()
{
}



RTC::ReturnCode_t RTCKinect::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetElevation", m_targetElevationIn);
  
  // Set OutPort buffer
  addOutPort("image", m_imageOut);
  addOutPort("depth", m_depthOut);
  addOutPort("currentElevation", m_currentElevationOut);
  addOutPort("skeleton", m_skeletonOut);
  addOutPort("dp_name", m_soundSourceOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  bindParameter("enable_camera", m_enable_camera, "1");
  bindParameter("enable_depth", m_enable_depth, "1");
  bindParameter("camera_width", m_camera_width, "640");
  bindParameter("camera_height", m_camera_height, "480");
  bindParameter("depth_width", m_depth_width, "320");
  bindParameter("depth_height", m_depth_height, "240");
  bindParameter("player_index", m_player_index, "0");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTCKinect::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTCKinect::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTCKinect::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTCKinect::onActivated(RTC::UniqueId ec_id)
{
    /**
	 * TODO: ここでコンフィグに合わせて機能の初期化を変える
	 */

	DWORD dwFlag = NUI_INITIALIZE_FLAG_USES_SKELETON;
	if(m_enable_camera) {
		dwFlag |= NUI_INITIALIZE_FLAG_USES_COLOR;
	}
	if(m_enable_depth) {
		if(m_player_index) {
			dwFlag |= NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX;
		} else {
			dwFlag |= NUI_INITIALIZE_FLAG_USES_DEPTH;
		}
	}

	HRESULT hr = NuiInitialize(dwFlag);
    if( FAILED( hr ) )
    {
		std::cout << "NUI Initialize Failed." << std::endl;
		return RTC::RTC_ERROR;
    }

	if(m_depth_width == 640 && m_depth_height == 480 && m_enable_depth && m_player_index) {
		std::cout << "If PlayerIndex and Depth Map is ON, resolution should be 320X240" << std::endl;
		return RTC::RTC_ERROR;
	}
	NUI_IMAGE_RESOLUTION eResolution;
	if(m_camera_width == 640 && m_camera_height == 480) {
		eResolution = NUI_IMAGE_RESOLUTION_640x480;
	} else {
		std::cout << "Invalid Image Resolution" << std::endl;
		return RTC::RTC_ERROR;
	}
	if(m_enable_camera) {
		hr = NuiImageStreamOpen(::NUI_IMAGE_TYPE_COLOR, eResolution, 0, 2, NULL, &m_pVideoStreamHandle );
		if( FAILED( hr ) )
		{
			std::cout << "NUI Image Stream Open Failed." << std::endl;
			return RTC::RTC_ERROR;
		}
	}

	if(m_depth_width == 640 && m_depth_height == 480) {
		eResolution = NUI_IMAGE_RESOLUTION_640x480;
	} else if(m_depth_width == 320 && m_depth_height == 240) {
		eResolution = NUI_IMAGE_RESOLUTION_320x240;
	} else {
		std::cout << "Invalid Image Resolution" << std::endl;
		return RTC::RTC_ERROR;
	}
	if(m_enable_depth) {
		if(m_player_index) {
			hr = NuiImageStreamOpen(::NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, eResolution, 0, 2, NULL, &m_pDepthStreamHandle );
		} else {
			hr = NuiImageStreamOpen(::NUI_IMAGE_TYPE_DEPTH, eResolution, 0, 2, NULL, &m_pDepthStreamHandle );
		}
	}
    if( FAILED( hr ) )
    {
		std::cout << "NUI Image Stream Open Failed." << std::endl;
		return RTC::RTC_ERROR;
    }

	this->m_image.width = m_camera_width;
	this->m_image.height = m_camera_height;
	this->m_image.pixels.length(m_camera_width*m_camera_height*3);

	this->m_depth.width = m_depth_width;
	this->m_depth.height = m_depth_height;
	this->m_depth.pixels.length(m_depth_width*m_depth_height*3);

	return RTC::RTC_OK;
}


RTC::ReturnCode_t RTCKinect::onDeactivated(RTC::UniqueId ec_id)
{
	NuiShutdown( );
	return RTC::RTC_OK;
}

HRESULT RTCKinect::WriteColorImage(void)
{
	static const long TIMEOUT_IN_MILLI = 100;
	const NUI_IMAGE_FRAME * pImageFrame = NULL;
    HRESULT hr = NuiImageStreamGetNextFrame(m_pVideoStreamHandle, TIMEOUT_IN_MILLI, &pImageFrame );
    if( FAILED( hr ) ) {
		std::cout << "NuiImageStreamGetNextFrame failed." << std::endl;
		return hr;
    }

    NuiImageBuffer * pTexture = pImageFrame->pFrameTexture;
    KINECT_LOCKED_RECT LockedRect;
    pTexture->LockRect( 0, &LockedRect, NULL, 0 );
    if( LockedRect.Pitch != 0 )
    {
        BYTE * pBuffer = (BYTE*) LockedRect.pBits;
		for(int h = 0;h < m_camera_height;h++) {
			for(int w = 0;w < m_camera_width;w++) {
				BYTE* pixel = pBuffer + (h * m_camera_width * 4) + w * 4;
				BYTE b = pixel[0];
				BYTE g = pixel[1];
				BYTE r = pixel[2];
				int offset = h*m_camera_width*3+w*3;
				m_image.pixels[offset + 0] = b;
				m_image.pixels[offset + 1] = g;
				m_image.pixels[offset + 2] = r;
			}
			m_imageOut.write();
		}

    }
    else {
		std::cout << "Buffer length of received texture is bogus\r\n" << std::endl;
    }

    NuiImageStreamReleaseFrame( m_pVideoStreamHandle, pImageFrame );

	return S_OK;
}

HRESULT RTCKinect::WriteDepthImage(void)
{
	static const long TIMEOUT_IN_MILLI = 100;
	const NUI_IMAGE_FRAME * pImageFrame = NULL;
    HRESULT hr = NuiImageStreamGetNextFrame(m_pDepthStreamHandle, TIMEOUT_IN_MILLI, &pImageFrame );
    if( FAILED( hr ) ) {
		std::cout << "NuiImageStreamGetNextFrame failed." << std::endl;
		return hr;
    }

    NuiImageBuffer * pTexture = pImageFrame->pFrameTexture;
    KINECT_LOCKED_RECT LockedRect;
    pTexture->LockRect( 0, &LockedRect, NULL, 0 );
    if( LockedRect.Pitch != 0 )
    {
        BYTE * pBuffer = (BYTE*) LockedRect.pBits;
		for(int h = 0;h < m_depth_height;h++) {
			for(int w = 0;w < m_depth_width;w++) {
				USHORT* pixel = (USHORT*)(pBuffer + (h * m_depth_width * sizeof(USHORT)) + w * sizeof(USHORT));

				USHORT RealDepth = (*pixel & 0xfff8) >> 3;
				USHORT Player = *pixel & 7;

				// transform 13-bit depth information into an 8-bit intensity appropriate
				// for display (we disregard information in most significant bit)
				BYTE depth = 255 - (BYTE)(256*RealDepth/0x0fff);

				unsigned char r, g, b;
				r=g=b = depth/2;
				int offset = h*m_depth_width*3+w*3;
				m_depth.pixels[offset + 0] = b;
				m_depth.pixels[offset + 1] = g;
				m_depth.pixels[offset + 2] = r;
			}
			m_depthOut.write();
		}

    }
    else {
		std::cout << "Buffer length of received texture is bogus\r\n" << std::endl;
    }

    NuiImageStreamReleaseFrame( m_pDepthStreamHandle, pImageFrame );

	return S_OK;
}

HRESULT RTCKinect::WriteElevation()
{
	HRESULT hr;
	LONG angle;
	if(m_targetElevationIn.isNew()) {
		hr = NuiCameraElevationSetAngle(m_targetElevation.data);
		if( FAILED(hr) ) {
			return hr;
		}
	}
	hr = NuiCameraElevationGetAngle(&angle);
	if( FAILED(hr) ) {
		return hr;
	}
	m_currentElevation.data = angle;
	m_currentElevationOut.write();
	return S_OK;
}


HRESULT RTCKinect::WriteSkeleton()
{
	// TODO: ここにスケルトンデータ書き込みを実装

	return S_OK;
}

RTC::ReturnCode_t RTCKinect::onExecute(RTC::UniqueId ec_id)
{
	if(m_enable_camera) {
		if( FAILED(WriteColorImage())) {
			return RTC::RTC_ERROR;
		}
	}

	if(m_enable_depth) {
		if( FAILED(WriteDepthImage())) {
			return RTC::RTC_ERROR;
		}
	}

	if( FAILED(WriteElevation()) ) {
		return RTC::RTC_ERROR;
	}

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTCKinect::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTCKinect::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTCKinect::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTCKinect::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTCKinect::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RTCKinectInit(RTC::Manager* manager)
  {
    coil::Properties profile(rtckinect_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTCKinect>,
                             RTC::Delete<RTCKinect>);
  }
  
};


