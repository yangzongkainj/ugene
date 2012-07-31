/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2012 UniPro <ugene@unipro.ru>
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

#include "GTPlainTextEdit.h"
#include "GTWidget.h"

#include "GTMouseDriver.h"
#include "GTKeyboardDriver.h"
#include "api/GTKeyboardUtils.h"
#include <QDebug>
namespace U2 {

#define GT_CLASS_NAME "GTPlainTextEdit"

#define GT_METHOD_NAME ""
void GTPlainTextEdit::setPlainText(U2OpStatus& os, QPlainTextEdit* plainTextEdit, const QString &text) {

    GT_CHECK(plainTextEdit != NULL, "plainTextEdit is NULL");
    
    GTWidget::setFocus(os, plainTextEdit);

    qDebug() << "Test in setPlainTest() = " << text;
    GTKeyboardDriver::keySequence(os, text);
    GTGlobals::sleep(500);


}
#undef GT_METHOD_NAME

//#define GT_METHOD_NAME "clear"
//void GTPlainTextEdit::clear(U2OpStatus& os, QPlainTextEdit* plainTextEdit) {
//
//    GT_CHECK(plainTextEdit != NULL, "plainTextEdit is NULL");
//
//    GTWidget::setFocus(os, plainTextEdit);
//
//    GTKeyboardUtils::selectAll(os);
//    GTGlobals::sleep(100);
//    GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["delete"]);
//    GTGlobals::sleep(1000);
//
//    QString s = plainTextEdit->toPlainText();
//    GT_CHECK(s.isEmpty() == true, "Can't clear text, lineEdit is not empty");
//}
//#undef GT_METHOD_NAME



}
