/**
 * @file /include/qt_ros_demo2/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_ros_demo2_QNODE_HPP_
#define qt_ros_demo2_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/String.h>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros_demo2 {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

        QStringListModel* loggingModel_sub() { return &logging_model_sub; }
        void log_sub( const LogLevel &level, const std::string &msg);
        void Callback(const std_msgs::StringConstPtr &submsg);

        //void callback(const qt_demo::qt_location::ConstPtr &msg)

//        void callback(const std_msgs::StringConstPtr &submsg)
//        {
//            std_msgs::Float32 distance;
//            distance.data = sqrt(pow(msg->x,2)+pow(msg->y,2));
//            ROS_INFO("Listener: Distance to origin = %f, state: %s",distance.data,msg->state.c_str());
//        }




Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();
    void loggingUpdated_sub();

private:
	int init_argc;
	char** init_argv;

        ros::Publisher chatter_publisher;
        ros::Subscriber chatter_subscriber;

    QStringListModel logging_model;
     QStringListModel logging_model_sub;
};

}  // namespace qt_ros_demo2

#endif /* qt_ros_demo2_QNODE_HPP_ */
