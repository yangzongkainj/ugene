/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2013 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
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

#include "ExportMSA2MSADialogFiller.h"
#include "api/GTWidget.h"
#include "api/GTLineEdit.h"
#include "api/GTRadioButton.h"

#include <QtCore/QDir>
#include <QtGui/QApplication>
#include <QtGui/QPushButton>

namespace U2 {

#define GT_CLASS_NAME "GTUtilsDialog::ExportToSequenceFormatFiller"

ExportMSA2MSADialogFiller::ExportMSA2MSADialogFiller(U2OpStatus &_os) : Filler(_os, "U2__ExportMSA2MSADialog") {}

#define GT_METHOD_NAME "run"
void ExportMSA2MSADialogFiller::run()
{
    QWidget *dialog = QApplication::activeModalWidget();
    GT_CHECK(dialog != NULL, "dialog not found");

    QPushButton *exportButton = dialog->findChild<QPushButton*>(QString::fromUtf8("exportButton"));
    GT_CHECK(exportButton != NULL, "export button not found");
    GTWidget::click(os, exportButton);
}
#undef GT_METHOD_NAME
#undef GT_CLASS_NAME

}
