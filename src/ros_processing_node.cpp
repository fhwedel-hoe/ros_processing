#include <ros/ros.h>
#include <ros/package.h>
#include "std_msgs/Float32.h"
#include "typedjni.hpp"

int main(int argc, char **argv)
{
  std::string ros_processing_path = ros::package::getPath("ros_processing");
  std::string classpath_option_string = "-Djava.class.path="+ros_processing_path+"/processing/application.linux64/lib/processing.jar";

  JavaVMInitArgs vm_args;
  std::vector<JavaVMOption> options;
  JavaVMOption jvmo;
  jvmo.optionString = const_cast<char *>(classpath_option_string.c_str());
  options.push_back(jvmo);
  vm_args.options = options.data();
  vm_args.nOptions = options.size();
  vm_args.version = JNI_VERSION_1_8;
  TypedJNIEnv env(vm_args);
  auto pwcls = env.find_class("processing$Worker");
  auto constructor = pwcls.GetConstructor<jobject>("(Lprocessing;)V");
  auto pwobj = constructor(NULL);
  auto processInput = pwobj.GetMethod<void(jfloat)>("processInput");
  auto getState = pwobj.GetMethod<jfloat()>("getState");
  
  ros::init(argc, argv, "processing");
  ros::NodeHandle n("~");
  ros::Publisher processed_pub = n.advertise<std_msgs::Float32>("processed", 1);

  boost::function<void(const std_msgs::Float32ConstPtr&)> callback = [&](const std_msgs::Float32ConstPtr& msg) {
    std_msgs::Float32 out;
    processInput(msg->data);
    out.data = getState();
    processed_pub.publish(out);
  };
  ros::Subscriber sub = n.subscribe("process", 1, callback);
  ros::spin();

  return 0;
}
