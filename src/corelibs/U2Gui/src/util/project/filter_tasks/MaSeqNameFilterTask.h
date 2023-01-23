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

#include <U2Core/AbstractProjectFilterTask.h>

namespace U2 {

//////////////////////////////////////////////////////////////////////////
/// MaSeqNameFilterTask
//////////////////////////////////////////////////////////////////////////

class MsaSeqNameFilterTask : public AbstractProjectFilterTask {
public:
    MsaSeqNameFilterTask(const ProjectTreeControllerModeSettings& settings, const QList<QPointer<Document>>& docs);

protected:
    bool filterAcceptsObject(GObject* obj);
};

class McaReadNameFilterTask : public AbstractProjectFilterTask {
public:
    McaReadNameFilterTask(const ProjectTreeControllerModeSettings& settings, const QList<QPointer<Document>>& docs);

protected:
    bool filterAcceptsObject(GObject* obj);
};

class McaReferenceNameFilterTask : public AbstractProjectFilterTask {
public:
    McaReferenceNameFilterTask(const ProjectTreeControllerModeSettings& settings, const QList<QPointer<Document>>& docs);

protected:
    bool filterAcceptsObject(GObject* obj);
};

//////////////////////////////////////////////////////////////////////////
/// MaSeqNameFilterTaskFactory
//////////////////////////////////////////////////////////////////////////

class U2GUI_EXPORT MsaSeqNameFilterTaskFactory : public ProjectFilterTaskFactory {
protected:
    AbstractProjectFilterTask* createNewTask(const ProjectTreeControllerModeSettings& settings, const QList<QPointer<Document>>& docs) const;
};

class U2GUI_EXPORT McaReadNameFilterTaskFactory : public ProjectFilterTaskFactory {
protected:
    AbstractProjectFilterTask* createNewTask(const ProjectTreeControllerModeSettings& settings, const QList<QPointer<Document>>& docs) const;
};

class U2GUI_EXPORT McaReferenceNameFilterTaskFactory : public ProjectFilterTaskFactory {
protected:
    AbstractProjectFilterTask* createNewTask(const ProjectTreeControllerModeSettings& settings, const QList<QPointer<Document>>& docs) const;
};

}  // namespace U2
