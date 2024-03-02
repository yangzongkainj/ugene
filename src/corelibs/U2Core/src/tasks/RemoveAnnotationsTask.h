/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2023 UniPro <ugene@unipro.ru>
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

#pragma once

#include <U2Core/AnnotationTableObject.h>
#include <U2Core/Task.h>

namespace U2 {

class U2CORE_EXPORT RemoveAnnotationsTask : public Task {
    Q_OBJECT
public:
    // Removes annotations of specified group, handles multiple annotations ( > 10 000).
    // Also handles situations with locked objects.
    RemoveAnnotationsTask(AnnotationTableObject* ao, const QString& groupName);

    ReportResult report() override;

private:
    QPointer<AnnotationTableObject> aobj;
    QString groupName;
};

}  // namespace U2
