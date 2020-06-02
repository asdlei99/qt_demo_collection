/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/qt_ros_demo3/qnode.hpp"
#include <std_msgs/Float32.h>



/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros_demo3 {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
        ros::init(init_argc,init_argv,"qt_ros_demo3");
	if ( ! ros::master::check() ) {
		return false;
	}

    ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
    ros::NodeHandle subn;
	// Add your ros communications here.

    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    chatter_subscriber= subn.subscribe("chatter",100,&QNode::Callback,this);

    start();
	return true;
}



bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
        ros::init(remappings,"qt_ros_demo3");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
    ros::NodeHandle subn;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);

    chatter_subscriber= subn.subscribe("chatter",100,&QNode::Callback,this);
	start();
	return true;
}

void QNode::Callback(const std_msgs::StringConstPtr &submsg)
 {

    
    
    log_sub(Info,std::string("Listener:")+submsg->data.c_str());
 }



void QNode::run() {
	ros::Rate loop_rate(1);
	int count = 0;
    double msg_x=1.0;
    double msg_y=1.0;
    double distance;
    
	while ( ros::ok() ) {

        msg_x = 1.01 * msg_x;
        msg_y = 1.02 * msg_y;
        distance=sqrt(pow(msg_x,2)+pow(msg_y,2));

        
        std_msgs::String msg_pub;
        std::stringstream ss_pub;

        std_msgs::String msg_sub;
        std::stringstream ss_sub;


        ss_pub <<" LOCATION: x =" << msg_x<<",y="<<msg_y;
        ss_sub <<" Distance to origin = " << distance;
        msg_pub.data = ss_pub.str();
        msg_sub.data = ss_sub.str();
                chatter_publisher.publish(msg_sub);
                log(Info,std::string("TALKER: ")+msg_pub.data);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}



void QNode::log_sub( const LogLevel &level, const std::string &msg) {
    logging_model_sub.insertRows(logging_model_sub.rowCount(),1);
    std::stringstream logging_model_msg;
    switch ( level ) {
        case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model_sub.setData(logging_model_sub.index(logging_model_sub.rowCount()-1),new_row);
    Q_EMIT loggingUpdated_sub(); // used to readjust the scrollbar
}



}  // namespace qt_ros_demo2
