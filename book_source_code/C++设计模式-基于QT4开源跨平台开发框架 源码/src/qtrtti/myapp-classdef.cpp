class MyApplication : public QApplication {
  Q_OBJECT   /* Required for Qt RTTI */
  public:
    static MyApplication* instance();
    QString imagesURL() const;
//   other members go here...
};
//   ... in the implementation file:
MyApplication* MyApplication::instance() {
    static MyApplication* inst = 0;
    if (inst == 0) {
        inst = qobject_cast&lt;MyApplication*&gt;(qApp);
    }
    return inst;
}
