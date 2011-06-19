// -*- C++ -*-
/*!
 * @file  RTCKinect.h
 * @brief RTC Kinect 4 Windows
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTCKINECT_H
#define RTCKINECT_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "KinectDataTypeStub.h"

// </rtc-template>

using namespace RTC;
using namespace Kinect;

/*!
 * @class RTCKinect
 * @brief RTC Kinect 4 Windows
 *
 */
class RTCKinect
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  RTCKinect(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~RTCKinect();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  debug
   * - DefaultValue: 0
   */
  int m_debug;
  /*!
   * 
   * - Name:  enable_camera
   * - DefaultValue: 1
   */
  int m_enable_camera;
  /*!
   * 
   * - Name:  enable_depth
   * - DefaultValue: 1
   */
  int m_enable_depth;
  /*!
   * 
   * - Name:  camera_width
   * - DefaultValue: 640
   */
  int m_camera_width;
  /*!
   * 
   * - Name:  camera_height
   * - DefaultValue: 480
   */
  int m_camera_height;
  /*!
   * 
   * - Name:  depth_width
   * - DefaultValue: 320
   */
  int m_depth_width;
  /*!
   * 
   * - Name:  depth_height
   * - DefaultValue: 240
   */
  int m_depth_height;  
  /*!
   * 
   * - Name:  player_index
   * - DefaultValue: 0
   */
  int m_player_index;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedLong m_targetElevation;
  /*!
   */
  InPort<TimedLong> m_targetElevationIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  CameraImage m_image;
  /*!
   * Camera Color Image
   * - Type: CameraImage
   */
  OutPort<CameraImage> m_imageOut;
  CameraImage m_depth;
  /*!
   * Depth Image
   * - Type: CameraImage
   */
  OutPort<CameraImage> m_depthOut;
  TimedLong m_currentElevation;
  /*!
   */
  OutPort<TimedLong> m_currentElevationOut;
  NuiSkeletonData m_skeleton;
  /*!
   */
  OutPort<NuiSkeletonData> m_skeletonOut;
  SoundSourceLocation m_soundSource;
  /*!
   */
  OutPort<SoundSourceLocation> m_soundSourceOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>
	HANDLE m_pVideoStreamHandle;
	HANDLE m_pDepthStreamHandle;

	HRESULT WriteColorImage();
	HRESULT WriteDepthImage();
	HRESULT WriteElevation();
	HRESULT WriteSkeleton();
};


extern "C"
{
  DLL_EXPORT void RTCKinectInit(RTC::Manager* manager);
};

#endif // RTCKINECT_H
