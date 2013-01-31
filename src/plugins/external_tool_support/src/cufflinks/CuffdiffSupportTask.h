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

#ifndef _U2_CUFFDIFFSUPPORTTASK_H_
#define _U2_CUFFDIFFSUPPORTTASK_H_

#include <U2Core/AnnotationData.h>
#include <U2Core/DocumentModel.h>
#include <U2Core/SaveDocumentTask.h>
#include <U2Core/Task.h>

#include <U2Formats/ConvertAssemblyToSamTask.h>

#include <U2Lang/DbiDataHandler.h>

#include "ExternalToolRunTask.h"

namespace U2 {

struct CuffdiffSettings {
    CuffdiffSettings();
    void cleanup();

    enum HitsNorm {
        Total = 0,
        Compatible = 1
    };
    enum Library {
        StandardIllumina = 0,
        dUTP_NSR_NNSR = 1,
        Ligation_StandardSOLiD = 2
    };
    bool timeSeriesAnalysis;
    bool upperQuartileNorm;
    HitsNorm hitsNorm;
    QString fragBiasCorrect;
    bool multiReadCorrect;
    Library libraryType;
    QString maskFile;
    int minAlignmentCount;
    double fdr;
    int maxMleIterations;
    bool emitCountTables;

    QList<Workflow::SharedDbiDataHandler> assemblies;
    QList<SharedAnnotationData> transcript;
    Workflow::DbiDataStorage *storage;
    QString workingDir;
};

struct CuffdiffResult {
    QList<SharedAnnotationData> splicing;
    QList<SharedAnnotationData> promoters;
    QList<SharedAnnotationData> cdsDiff;
    QList<SharedAnnotationData> cdsExp;
    QList<SharedAnnotationData> cdsFpkm;
    QList<SharedAnnotationData> tssExp;
    QList<SharedAnnotationData> tssFpkm;
    QList<SharedAnnotationData> genesExp;
    QList<SharedAnnotationData> genesFpkm;
    QList<SharedAnnotationData> isomorfsExp;
    QList<SharedAnnotationData> isomorfsFpkm;
};

class CuffdiffSupportTask : public Task {
    Q_OBJECT
private:
    class LogParser : public ExternalToolLogParser {
    public:
        LogParser();
        void parseErrOutput(const QString &partOfLog);
    };

public:
    CuffdiffSupportTask(const CuffdiffSettings &settings);

    void prepare();
    QList<Task*> onSubTaskFinished(Task *subTask);
    ReportResult report();
    CuffdiffResult takeResult();

private:
    CuffdiffSettings settings;
    QString workingDir;
    QStringList assemblyUrls;
    QString transcriptUrl;
    QScopedPointer<CuffdiffResult> result;

    QScopedPointer<Document> transcriptDoc;
    QList<Task*> saveTasks;

    QScopedPointer<ExternalToolLogParser> logParser;
    ExternalToolRunTask *diffTask;

private:
    ConvertAssemblyToSamTask * createAssemblyTask(const Workflow::SharedDbiDataHandler &id, const QString &url);
    Task * createTranscriptTask();

    void addTranscriptObject();
    void createTranscriptDoc();
    Task * createCuffdiffTask();
    void readResult();
    QList<SharedAnnotationData> readFile(const QString &fileName, const DocumentFormatId &format);
    void setupWorkingDir();
};


} // U2

#endif // _U2_CUFFDIFFSUPPORTTASK_H_
