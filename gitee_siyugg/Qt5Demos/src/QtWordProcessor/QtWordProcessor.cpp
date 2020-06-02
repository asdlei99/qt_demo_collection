/*************************************************************************
    > File Name: QtWordProcessor.cpp
    > Author: 关山月朦胧
    > Mail: 1036014410@qq.com
    > Created Time: 2016年06月18日 星期六 15时07分53秒
 ************************************************************************/

#include "QtWordProcessor.h"
#include <QStyle>
#include <QMenuBar>
#include <QIcon>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextListFormat>
#include <QTextList>
#include <QDebug>
#include <QActionGroup>

QtWordProcessor::QtWordProcessor(QWidget *parent):QMainWindow(parent),textEdit(new QTextEdit(this))
{
	setWindowTitle(tr("QtWPS"));
	setCentralWidget(textEdit);
	createActions();
	createMenus();
	createFontItems();
	createSortItems();
	createToolBars();

	showMaximized();

	connect(openFileAction,SIGNAL(triggered()),this,SLOT(slot_openFile()));
	connect(newFileAction,SIGNAL(triggered()),this,SLOT(slot_newFile()));
	connect(printTextAction,SIGNAL(triggered()),this,SLOT(slot_printText()));
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
	connect(undoAction,SIGNAL(triggered()),textEdit,SLOT(undo()));
	connect(redoAction,SIGNAL(triggered()),textEdit,SLOT(redo()));
	connect(fontNameCombox,SIGNAL(activated(QString)),this,SLOT(slot_setFontName(QString)));
	connect(fontSizeCombox,SIGNAL(activated(QString)),this,SLOT(slot_setFontSize(QString)));
	connect(italicBtn,SIGNAL(clicked()),this,SLOT(slot_setItalic()));
	connect(boldBtn,SIGNAL(clicked()),this,SLOT(slot_setBold()));
	connect(underlineBtn,SIGNAL(clicked()),this,SLOT(slot_setUnderline()));
	connect(colorBtn,SIGNAL(clicked()),this,SLOT(slot_setTextColor()));
	connect(textEdit,SIGNAL(currentCharFormatChanged(const QTextCharFormat&)),this,SLOT(slot_showCurrentFmtChanged(const QTextCharFormat&)));
	connect(alignLeftAction,SIGNAL(triggered()),this,SLOT(slot_setAlignLeft()));
	connect(alignRightAction,SIGNAL(triggered()),this,SLOT(slot_setAlignRight()));
	connect(alignCenterAction,SIGNAL(triggered()),this,SLOT(slot_setAlignCenter()));
	connect(alignFillAction,SIGNAL(triggered()),this,SLOT(slot_setAlignFill()));
	connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(slot_showCursorPosChanged()));
	connect(sortComBox,SIGNAL(activated(int)),this,SLOT(slot_setSortList(int)));
}
QtWordProcessor::~QtWordProcessor()
{
}
void QtWordProcessor::createActions()
{
	openFileAction = new QAction(QIcon(":/image/open.png"),tr("Open"),this);
	openFileAction->setShortcut(tr("Ctrl+O"));
	openFileAction->setStatusTip(tr("打开一个文件"));

	newFileAction = new QAction(QIcon(":/image/new.png"),tr("New"),this);
	newFileAction->setShortcut(tr("Ctrl+N"));
	newFileAction->setStatusTip(tr("新建一个文件"));

	saveFileAction = new QAction(QIcon(":/image/save.png"),tr("Save"),this);
	saveFileAction->setShortcut(tr("Ctrl+S"));
	saveFileAction->setStatusTip(tr("保存文件"));

	printTextAction = new QAction(QIcon(":image/document-print.png"),tr("Print Text"),this);
//	printImageAction = new QAction(tr("Print Image"),this);

	exitAction = new QAction(tr("Exit"),this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("退出"));

	copyAction = new QAction(QIcon(":/image/copy.png"),tr("Copy"),this);
	cutAction = new QAction(QIcon(":/image/cut.png"),tr("Cut"),this);
	pasteAction = new QAction(QIcon(":/image/paste.png"),tr("Paste"),this);
	aboutAction = new QAction(tr("About"),this);
/*	zoomInAction = new QAction(tr("Zoom In"),this);
	zoomOutAction = new QAction(tr("Zoom Out"),this);
	rotate90Action = new QAction(tr("Rotate 90"),this);
	rotate180Action = new QAction(tr("Rotate 180"),this);
	rotate270Action = new QAction(tr("Rotate 270"),this);
	mirrorVerticalAction = new QAction(tr("Mirror Vertical"),this);
	mirrorHorizontalAction = new QAction(tr("Mirror Horizontal"),this);*/

	QActionGroup *alignActGroup = new QActionGroup(this);
	alignLeftAction = new QAction(QIcon(":/image/format-justify-left.png"),tr("Align Left"),this);
	alignLeftAction->setCheckable(true);
	alignRightAction = new QAction(QIcon(":/image/format-justify-right.png"),tr("Align Right"),this);
	alignRightAction->setCheckable(true);
	alignFillAction = new QAction(QIcon(":/image/format-justify-fill.png"),tr("Align Fill"),this);
	alignFillAction->setCheckable(true);
	alignCenterAction = new QAction(QIcon(":/image/format-justify-center.png"),tr("Align Center"),this);
	alignCenterAction->setCheckable(true);
	alignActGroup->addAction(alignLeftAction);
	alignActGroup->addAction(alignRightAction);
	alignActGroup->addAction(alignCenterAction);
	alignActGroup->addAction(alignFillAction);

	undoAction = new QAction(QIcon(":/image/edit-undo.png"),tr("Undo"),this);
	redoAction = new QAction(QIcon(":/image/edit-redo.png"),tr("Redo"),this);


}
void QtWordProcessor::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(saveFileAction);
	fileMenu->addSeparator();
	fileMenu->addAction(printTextAction);
//	fileMenu->addAction(printImageAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

/*	zoomMenu = menuBar()->addMenu(tr("Edit"));
	zoomMenu->addAction(copyAction);
	zoomMenu->addAction(cutAction);
	zoomMenu->addAction(pasteAction);
	zoomMenu->addAction(aboutAction);
	zoomMenu->addSeparator();
	zoomMenu->addAction(zoomInAction);
	zoomMenu->addAction(zoomOutAction);

	rotateMenu = menuBar()->addMenu(tr("Rotate"));
	rotateMenu->addAction(rotate90Action);
	rotateMenu->addAction(rotate180Action);
	rotateMenu->addAction(rotate270Action);

	mirrorMenu = menuBar()->addMenu(tr("Mirror"));
	mirrorMenu->addAction(mirrorVerticalAction);
	mirrorMenu->addAction(mirrorHorizontalAction);*/
}
void QtWordProcessor::createFontItems()
{
	fontNameLabel = new QLabel(tr("FontName"),this);
	fontNameCombox = new QFontComboBox(this);
	fontNameCombox->setFontFilters(QFontComboBox::ScalableFonts);

	fontSizeLabel = new QLabel(tr("FontSize"));
	fontSizeCombox = new QComboBox;
	QFontDatabase fontDb;
	for (auto& size : fontDb.standardSizes())
		fontSizeCombox->addItem(QString::number(size));

	boldBtn = new QToolButton;
	boldBtn->setIcon(QIcon(":/image/format-text-bold.png"));
	boldBtn->setCheckable(true);
	italicBtn = new QToolButton;
	italicBtn->setIcon(QIcon(":/image/format-text-italic.png"));
	italicBtn->setCheckable(true);
	underlineBtn = new QToolButton;
	underlineBtn->setIcon(QIcon(":/image/format-text-underline.png"));
	underlineBtn->setCheckable(true);
	colorBtn = new QToolButton;
	colorBtn->setIcon(QIcon(":image/format-text-color.png"));
	colorBtn->setAutoFillBackground(true);
	colorBtn->setCheckable(true);
	colorBtn->setAutoRaise(true);
}
void QtWordProcessor::createSortItems()
{
	sortComBox = new QComboBox;
	sortComBox->addItem(tr("Standard"));
	sortComBox->addItem(tr("QTextListFormat::ListDisc"));
	sortComBox->addItem(tr("QTextListFormat::ListCircle"));
	sortComBox->addItem(tr("QTextListFormat::ListSquare"));
	sortComBox->addItem(tr("QTextListFormat::ListDecimal"));
	sortComBox->addItem(tr("QTextListFormat::ListLowerAlpha"));
	sortComBox->addItem(tr("QTextListFormat::ListUpperAlpha"));
	sortComBox->addItem(tr("QTextListFormat::ListLowerRoman"));
	sortComBox->addItem(tr("QTextListFormat::ListUpperRoman"));
}
void QtWordProcessor::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openFileAction);
	fileToolBar->addAction(newFileAction);
	fileToolBar->addAction(saveFileAction);
	fileToolBar->addAction(printTextAction);
//	fileToolBar->addAction(printImageAction);

/*	zoomToolBar = addToolBar(tr("Edit"));
	zoomToolBar->addAction(copyAction);
	zoomToolBar->addAction(cutAction);
	zoomToolBar->addAction(pasteAction);
	zoomToolBar->addSeparator();
	zoomToolBar->addAction(zoomInAction);
	zoomToolBar->addAction(zoomOutAction);

	rotateToolBar = addToolBar(tr("Rotate"));
	rotateToolBar->addAction(rotate90Action);
	rotateToolBar->addAction(rotate180Action);
	rotateToolBar->addAction(rotate270Action);*/

	fontToolBar = addToolBar(tr("Font"));
	fontToolBar->addWidget(fontNameLabel);
	fontToolBar->addWidget(fontNameCombox);
	fontToolBar->addWidget(fontSizeLabel);
	fontToolBar->addWidget(fontSizeCombox);
	fontToolBar->addWidget(boldBtn);
	fontToolBar->addWidget(italicBtn);
	fontToolBar->addWidget(underlineBtn);
	fontToolBar->addWidget(colorBtn);

	alignToolBar = addToolBar(tr("Align"));
	alignToolBar->addAction(alignLeftAction);
	alignToolBar->addAction(alignRightAction);
	alignToolBar->addAction(alignCenterAction);
	alignToolBar->addAction(alignFillAction);

	sortToolBar = addToolBar(tr("Sort"));
	QLabel *sortLabel = new QLabel(tr("Sort"));
	sortToolBar->addWidget(sortLabel);
	sortToolBar->addWidget(sortComBox);

	doToolBar = addToolBar(tr("DoEdit"));
	doToolBar->addAction(undoAction);
	doToolBar->addAction(redoAction);
}
void QtWordProcessor::keyPressEvent(QKeyEvent *event)
{
	if (event->modifiers() == Qt::CTRL)
	{
		switch (event->key())
		{
			case(Qt::Key_Q):
				close();
			default:
				;
		}
	}
}
void QtWordProcessor::loadFile(QString fileName)
{
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream textStream(&file);
		while(!textStream.atEnd())
		{
			textEdit->append(textStream.readLine());
		}
	}
}
void QtWordProcessor::slot_openFile()
{
	fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
	{
		if (textEdit->document()->isEmpty())
			loadFile(fileName);
		else
		{
			QtWordProcessor * wordProcessor = new QtWordProcessor();
			wordProcessor->loadFile(fileName);
			wordProcessor->show();
		}
	}
}
void QtWordProcessor::slot_newFile()
{
	QtWordProcessor * newWordFile = new QtWordProcessor();
	newWordFile->show();
}
void QtWordProcessor::slot_printText()
{
	QPrinter printer;
	QPrintDialog printDlg(&printer,this);
	if (printDlg.exec())
	{
		QTextDocument *doc = textEdit->document();
		doc->print(&printer);
	}
}
void QtWordProcessor::mergeFormat(QTextCharFormat& format)
{
	QTextCursor cursor = textEdit->textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	textEdit->mergeCurrentCharFormat(format);
}
void QtWordProcessor::slot_setFontName(QString fontName)
{
	QTextCharFormat fmt;
	fmt.setFontFamily(fontName);
	mergeFormat(fmt);
}
void QtWordProcessor::slot_setFontSize(QString size)
{
	QTextCharFormat fmt;
	fmt.setFontPointSize(size.toFloat());
	mergeFormat(fmt);
}
void QtWordProcessor::slot_setItalic()
{
	QTextCharFormat fmt;
	fmt.setFontItalic(italicBtn->isChecked() ? true : false);
	mergeFormat(fmt);
}
void QtWordProcessor::slot_setBold()
{
	QTextCharFormat fmt;
	fmt.setFontWeight(boldBtn->isChecked() ? QFont::Bold : QFont::Normal);
	mergeFormat(fmt);
}
void QtWordProcessor::slot_setUnderline()
{
	QTextCharFormat fmt;
	fmt.setFontUnderline(underlineBtn->isChecked() ? true : false);
	mergeFormat(fmt);
}
void QtWordProcessor::slot_setTextColor()
{
	QColor color;
	QColorDialog colorDlg(this);
	color = colorDlg.getColor();
	if (color.isValid())
	{
		colorBtn->setChecked(false);
		QTextCharFormat fmt;
		QBrush brush(color);
		fmt.setForeground(brush);
		mergeFormat(fmt);
		QString colorStr(QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
		colorBtn->setStyleSheet(colorStr);
	}
}
void QtWordProcessor::slot_showCurrentFmtChanged(const QTextCharFormat& fmt)
{
	fontNameCombox->setCurrentIndex(fontNameCombox->findText(fmt.fontFamily()));
	fontSizeCombox->setCurrentIndex(fontSizeCombox->findText(QString::number(fmt.fontPointSize())));
	boldBtn->setChecked(fmt.font().bold());
	italicBtn->setChecked(fmt.fontItalic());
	underlineBtn->setChecked(fmt.fontUnderline());

}


void QtWordProcessor::slot_setAlignLeft()
{
	textEdit->setAlignment(Qt::AlignLeft);
}
void QtWordProcessor::slot_setAlignRight()
{
	textEdit->setAlignment(Qt::AlignRight);
}
void QtWordProcessor::slot_setAlignCenter()
{
	textEdit->setAlignment(Qt::AlignCenter);
}
void QtWordProcessor::slot_setAlignFill()
{
	textEdit->setAlignment(Qt::AlignJustify);
}
void QtWordProcessor::slot_showCursorPosChanged()
{
	switch (textEdit->alignment())
	{
		case (Qt::AlignLeft):
			alignLeftAction->setChecked(true);break;
		case (Qt::AlignRight):
			alignRightAction->setChecked(true);break;
		case (Qt::AlignCenter):
			alignCenterAction->setChecked(true);break;
		case (Qt::AlignJustify):
			alignFillAction->setChecked(true);break;
		default:
			break;
	}
}
void QtWordProcessor::slot_setSortList(int index)
{
	QTextCursor cursor = textEdit->textCursor();

	if (index)
	{
		typename QTextListFormat::Style style = QTextListFormat::ListDisc;
		switch (index)
		{
			default:
			case (1):
				style = QTextListFormat::ListDisc;break;
			case (2):
				style = QTextListFormat::ListSquare;break;
			case (3):
				style = QTextListFormat::ListDecimal;break;
			case (4):
				style = QTextListFormat::ListLowerAlpha;break;
			case (5):
				style = QTextListFormat::ListUpperAlpha;break;
			case (6):
				style = QTextListFormat::ListLowerRoman;break;
			case (7):
				style = QTextListFormat::ListUpperRoman;break;
		}
		cursor.beginEditBlock();

		QTextBlockFormat blockFmt = cursor.blockFormat();
		QTextListFormat listFmt;

		if (cursor.currentList())
			listFmt = cursor.currentList()->format();
		else
		{
			listFmt.setIndent(blockFmt.indent() + 1);
			blockFmt.setIndent(0);
			cursor.setBlockFormat(blockFmt);
		}
		listFmt.setStyle(style);
		cursor.createList(listFmt);

		cursor.endEditBlock();
	}
	else
	{
		QTextBlockFormat bFmt;
		bFmt.setObjectIndex(-1);
		cursor.mergeBlockFormat(bFmt);
	}
}
