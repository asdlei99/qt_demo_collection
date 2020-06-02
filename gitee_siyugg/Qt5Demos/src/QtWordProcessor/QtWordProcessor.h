/*************************************************************************
    > File Name: QtWordProcessor.h
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 15时07分53秒
 ************************************************************************/

#ifndef QTWORDPROCESSOR_H
#define QTWORDPROCESSOR_H

#include <QMainWindow>
#include <QTextEdit>
//#include <QImage>
#include <QString>
#include <QAction>
#include <QToolBar>
#include <QKeyEvent>
#include <QFont>
#include <QLabel>
#include <QComboBox>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCursor>

class QtWordProcessor:public QMainWindow
{
	Q_OBJECT
	private:
		QMenu *fileMenu;
//		QMenu *zoomMenu;
//		QMenu *rotateMenu;
//		QMenu *mirrorMenu;

//		QImage img;
		QString fileName;

		QAction *openFileAction;
		QAction *newFileAction;
		QAction *saveFileAction;
		QAction *printTextAction;
//		QAction *printImageAction;
		QAction *exitAction;
		QAction *copyAction;
		QAction *cutAction;
		QAction *pasteAction;
		QAction *aboutAction;
//		QAction *zoomInAction;
//		QAction *zoomOutAction;

/*		QAction *rotate90Action;
		QAction *rotate180Action;
		QAction *rotate270Action;

		QAction *mirrorVerticalAction;
		QAction *mirrorHorizontalAction;
*/

		QAction *alignLeftAction;
		QAction *alignRightAction;
		QAction *alignFillAction;
		QAction *alignCenterAction;

		QAction *undoAction;
		QAction *redoAction;

		QToolBar *fileToolBar;
//		QToolBar *zoomToolBar;
//		QToolBar *rotateToolBar;
//		QToolBar *mirrorToolBar;
		QToolBar *alignToolBar;
		QToolBar *doToolBar;

		QToolBar *fontToolBar;
		QLabel *fontNameLabel;
		QFontComboBox *fontNameCombox;
		QLabel *fontSizeLabel;
		QComboBox *fontSizeCombox;
		QToolButton *boldBtn;
		QToolButton *italicBtn;
		QToolButton *underlineBtn;
		QToolButton *colorBtn;

		QTextEdit *textEdit;

		QComboBox *sortComBox;
		QToolBar *sortToolBar;

		void loadFile(QString fileName);
		void mergeFormat(QTextCharFormat& format);
	public:
		QtWordProcessor(QWidget *parent = 0);
		~QtWordProcessor();

		void createActions();
		void createMenus();
		void createFontItems();
		void createToolBars();
		void createSortItems();

		void keyPressEvent(QKeyEvent *);
	public slots:
		void slot_openFile();
		void slot_newFile();
		void slot_printText();

		void slot_setFontName(QString);
		void slot_setFontSize(QString);
		void slot_setItalic();
		void slot_setBold();
		void slot_setUnderline();
		void slot_setTextColor();
		void slot_showCurrentFmtChanged(const QTextCharFormat&);

		void slot_setAlignLeft();
		void slot_setAlignRight();
		void slot_setAlignCenter();
		void slot_setAlignFill();
		void slot_showCursorPosChanged();

		void slot_setSortList(int);
};

#endif//QTWORDPROCESSOR_H
