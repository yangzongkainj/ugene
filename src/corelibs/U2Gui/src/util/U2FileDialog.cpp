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

#include "U2FileDialog.h"

#include <QApplication>
#include <QMainWindow>

#include <U2Core/AppContext.h>
#include <U2Core/Log.h>
#include <U2Core/Task.h>
#include <U2Core/U2SafePoints.h>

#include <U2Gui/MainWindow.h>

namespace U2 {

static QFileDialog::Options getEffectiveOptions(const QFileDialog::Options& options) {
    CHECK(!options.testFlag(QFileDialog::DontUseNativeDialog), options);

    bool useNonNativeDialog = qgetenv(ENV_GUI_TEST).toInt() == 1 && qgetenv(ENV_USE_NATIVE_DIALOGS).toInt() == 0;
    TaskScheduler* taskScheduler = AppContext::getTaskScheduler();
    if (!useNonNativeDialog && taskScheduler != nullptr && taskScheduler->isCallerInsideTaskSchedulerCallback()) {
        uiLog.trace("Using a non-native file dialog: the method is inside task processing callback");
        useNonNativeDialog = true;
    }
    return useNonNativeDialog ? options | QFileDialog::DontUseNativeDialog : options;
}

static void activateAppWindow() {
    if (isOsMac()) {
        QWidget* target = QApplication::activeModalWidget();
        if (target == nullptr) {
            MainWindow* mainWindow = AppContext::getMainWindow();
            CHECK(mainWindow != nullptr, );
            QMainWindow* qMainWindow = mainWindow->getQMainWindow();
            target = qobject_cast<QWidget*>(qMainWindow);
        }
        CHECK(target != nullptr, );
        target->activateWindow();
    }
}

QString U2FileDialog::getOpenFileName(QWidget* parent,
                                      const QString& caption,
                                      const QString& dir,
                                      const QString& filter,
                                      QString* selectedFilter,
                                      const QFileDialog::Options& options) {
    activateAppWindow();
    QFileDialog::Options effectiveOptions = getEffectiveOptions(options);
    return QFileDialog::getOpenFileName(parent, caption, dir, filter, selectedFilter, effectiveOptions);
}

QStringList U2FileDialog::getOpenFileNames(QWidget* parent,
                                           const QString& caption,
                                           const QString& dir,
                                           const QString& filter,
                                           QString* selectedFilter,
                                           const QFileDialog::Options& options) {
    activateAppWindow();
    QFileDialog::Options effectiveOptions = getEffectiveOptions(options);
    return QFileDialog::getOpenFileNames(parent, caption, dir, filter, selectedFilter, effectiveOptions);
}

QString U2FileDialog::getExistingDirectory(QWidget* parent,
                                           const QString& caption,
                                           const QString& dir,
                                           const QFileDialog::Options& options) {
    activateAppWindow();
    QFileDialog::Options effectiveOptions = getEffectiveOptions(options);
    return QFileDialog::getExistingDirectory(parent, caption, dir, effectiveOptions);
}

QString U2FileDialog::getSaveFileName(QWidget* parent,
                                      const QString& caption,
                                      const QString& dir,
                                      const QString& filter,
                                      QString* selectedFilter,
                                      const QFileDialog::Options& options) {
    activateAppWindow();
    QFileDialog::Options effectiveOptions = getEffectiveOptions(options);
    return QFileDialog::getSaveFileName(parent, caption, dir, filter, selectedFilter, effectiveOptions);
}

}  // namespace U2
