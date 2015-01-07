/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2014 UniPro <ugene@unipro.ru>
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

#include "FastQCSupport.h"
#include "java/JavaSupport.h"
#include "perl/PerlSupport.h"

#include <U2Core/AppContext.h>
#include <U2Core/AppSettings.h>
#include <U2Core/DataPathRegistry.h>
#include <U2Core/U2SafePoints.h>
#include <U2Core/U2OpStatusUtils.h>
#include <U2Core/ScriptingToolRegistry.h>

#include <U2Formats/ConvertFileTask.h>

namespace U2 {


FastQCSupport::FastQCSupport(const QString& name, const QString& path) : ExternalTool(name, path)
{
    if (AppContext::getMainWindow()) {
        icon = QIcon(":external_tool_support/images/cmdline.png");
        grayIcon = QIcon(":external_tool_support/images/cmdline_gray.png");
        warnIcon = QIcon(":external_tool_support/images/cmdline_warn.png");
    }

    executableFileName="fastqc";

    validMessage = "FastQC v";
    description = tr("<i>FastQC</i>: A quality control tool for high throughput sequence data.");

    versionRegExp = QRegExp("FastQC v(\\d+.\\d+.\\d+)");
    validationArguments << "-v";
    toolKitName = "FastQC";


    toolRunnerProgramm = ET_PERL;
    dependencies << ET_JAVA;
    dependencies << ET_PERL;
}

}//namespace

