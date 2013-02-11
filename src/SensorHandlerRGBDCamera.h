
#ifndef SENSORHANDLERRGBDCAMERA_H
#define SENSORHANDLERRGBDCAMERA_H

#include <g2o_frontend/g2o_sensor_data/SensorHandler.h>
#include <g2o_frontend/g2o_sensor_data/SensorRGBDCamera.h>
#include <g2o_frontend/g2o_sensor_data/PrioritySynchronousDataQueue.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/Image.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>

typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;

class SensorHandlerRGBDCamera : public SensorHandler {
public:
  SensorHandlerRGBDCamera(tf::TransformListener* tfListener_);

  virtual Sensor* getSensor();
  virtual bool setQueue(PriorityDataQueue* queue_);
  virtual bool setSensor(Sensor* sensor_s);
  void setNodeHandler(ros::NodeHandle* nptr_);
  ros::NodeHandle* getNodeHandler() { return _nh; };
  virtual void registerCallback();
  PriorityDataQueue* getQueue() { return _queue; };
  void callback(const sensor_msgs::ImageConstPtr& raw_intensity_image, const sensor_msgs::ImageConstPtr& raw_depth_image);
protected:
    void _sensorCallback(const sensor_msgs::ImageConstPtr& raw_intensity_image, const sensor_msgs::ImageConstPtr& raw_depth_image);
    void _calibrationCallback(const sensor_msgs::ImageConstPtr& raw_intensity_image, const sensor_msgs::ImageConstPtr& raw_depth_image);

    message_filters::Subscriber<sensor_msgs::Image>* _intensity_sub;
    message_filters::Subscriber<sensor_msgs::Image>* _depth_sub;
    message_filters::Synchronizer<MySyncPolicy>* _sync;
    ros::NodeHandle* _nh;
    tf::TransformListener* _tfListener;
    bool _isCalibrated; // ugly
};

#endif // SENSORHANDLERRGBDCAMERA_H
