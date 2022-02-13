/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2022 UniPro <ugene@unipro.ru>
 * http://ugene.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _U2_MWTOOLBAR_IMPL_H_
#define _U2_MWTOOLBAR_IMPL_H_

#include <QMainWindow>
#include <QToolBar>

#include <U2Gui/MainWindow.h>

namespace U2 {

class MWToolBarManagerImpl : public QObject {
public:
    MWToolBarManagerImpl(QMainWindow* mw);
    ~MWToolBarManagerImpl();

    QToolBar* getToolbar(const QString& sysName) const;

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    QToolBar* createToolBar(const QString& sysName);
    void updateToolbarVisibilty();

    QMainWindow* mw;
    QList<QToolBar*> toolbars;
};

}  // namespace U2

#endif
