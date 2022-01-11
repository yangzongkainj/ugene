/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2017 UniPro <ugene@unipro.ru>
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

#include "primitives/GTCheckBox.h"

#include "primitives/GTWidget.h"

namespace HI {

#define GT_CLASS_NAME "GTCheckBox"

#define GT_METHOD_NAME "setChecked"
void GTCheckBox::setChecked(GUITestOpStatus &os, QCheckBox *checkBox, bool checked) {
    GT_CHECK(checkBox != nullptr, "QCheckBox == NULL");
    if (checkBox->isChecked() == checked) {  // TODO: this should not be used this way: setChecked() must not be called on the disabled checkbox.
        return;
    }
    GT_CHECK(checkBox->isEnabled(), "QCheckBox is disabled: " + checkBox->objectName());

    if (checked != checkBox->isChecked()) {
        GTWidget::click(os, checkBox, Qt::LeftButton, {5, checkBox->rect().height() / 2});
    }
    // Wait up to 5 seconds for the checked state to be updated.
    bool isChecked = checkBox->isChecked();
    for (int time = 0; time <= 5000 && isChecked != checked; time += 100) {
        GTGlobals::sleep(100);
        isChecked = checkBox->isChecked();
    }
    GT_CHECK(checked == isChecked, "Can't set checked state: " + checkBox->objectName());
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "setChecked"
void GTCheckBox::setChecked(GUITestOpStatus &os, const QString &checkBoxName, bool checked, QWidget *parent) {
    GTCheckBox::setChecked(os, GTWidget::findExactWidget<QCheckBox *>(os, checkBoxName, parent), checked);
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "setChecked"
void GTCheckBox::setChecked(GUITestOpStatus &os, const QString &checkBoxName, QWidget *parent) {
    GTCheckBox::setChecked(os, GTWidget::findExactWidget<QCheckBox *>(os, checkBoxName, parent));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getState"
bool GTCheckBox::getState(GUITestOpStatus &os, QCheckBox const *const checkBox) {
    Q_UNUSED(os);
    GT_CHECK_RESULT(checkBox != NULL, "QCheckBox == NULL", false);
    return checkBox->isChecked();
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getState"
bool GTCheckBox::getState(GUITestOpStatus &os, const QString &checkBoxName, QWidget *const parent) {
    return getState(os, GTWidget::findExactWidget<QCheckBox *>(os, checkBoxName, parent));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "checkState"
void GTCheckBox::checkState(GUITestOpStatus &os, QCheckBox const *const checkBox, const bool expectedState) {
    Q_UNUSED(os);
    GT_CHECK(checkBox != NULL, "QCheckBox == NULL");
    const bool actualState = checkBox->isChecked();
    GT_CHECK(expectedState == actualState, QString("Incorrect checkbox state: expected '%1', got '%2'").arg(expectedState).arg(actualState));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "checkState"
void GTCheckBox::checkState(GUITestOpStatus &os, const QString &checkBoxName, bool expectedState, QWidget *parent) {
    checkState(os, GTWidget::findExactWidget<QCheckBox *>(os, checkBoxName, parent), expectedState);
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME

}  // namespace HI
