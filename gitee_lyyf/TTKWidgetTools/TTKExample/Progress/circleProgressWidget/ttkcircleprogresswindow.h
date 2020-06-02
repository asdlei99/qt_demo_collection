#ifndef TTKCIRCLEPROCESSWINDOW_H
#define TTKCIRCLEPROCESSWINDOW_H

/* =================================================
 * This file is part of the TTK WidgetTools project
 * Copyright (C) 2015 - 2019 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include <QMainWindow>
#include "ttkglobaldefine.h"

namespace Ui {
class TTKCircleProgressWindow;
}

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTK_CORE_EXPORT TTKCircleProgressWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TTKCircleProgressWindow(QWidget *parent = nullptr);
    ~TTKCircleProgressWindow();

private:
    Ui::TTKCircleProgressWindow *ui;

};

#endif // TTKCIRCLEPROCESSWINDOW_H
