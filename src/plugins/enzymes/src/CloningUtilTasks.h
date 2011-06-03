/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2011 UniPro <ugene@unipro.ru>
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

#ifndef _U2_CLONING_UTIL_TASKS_H_
#define _U2_CLONING_UTIL_TASKS_H_

#include <U2Algorithm/EnzymeModel.h>
#include "DNAFragment.h"

#include <limits>

#include <U2Core/Task.h>
#include <U2Core/U2Region.h>
#include <U2Core/GUrl.h>

#include <U2Core/AnnotationTableObject.h>

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QMutex>

namespace U2 {


class DNASequenceObject;

class DigestSequenceTask : public Task {
    Q_OBJECT
public:
    DigestSequenceTask(const DNASequenceObject*  dnaObj, AnnotationTableObject* sourceTable, 
        AnnotationTableObject* destTable, const QList<SEnzymeData>& cutSites);
    DigestSequenceTask(const DNASequenceObject*  dnaObj, AnnotationTableObject* destTable, 
        const QList<SEnzymeData>& cutSites);
    virtual void prepare();
    virtual void run();
    virtual QString generateReport() const;
    virtual ReportResult report();

private:
   
    void findCutSites(); 
    void saveResults();
    AnnotationData* createFragment( int pos1, const DNAFragmentTerm& leftTerm,
                                    int pos2, const DNAFragmentTerm& rightTerm );
    bool searchForRestrictionSites;
    bool isCircular;
    U2Region seqRange;
    AnnotationTableObject *sourceObj, *destObj;
    const DNASequenceObject*  dnaObj;
    QList<SEnzymeData> enzymeData;
    QMap<int, SEnzymeData> cutSiteMap;
    QList<SharedAnnotationData> results;

};

struct LigateFragmentsTaskConfig {
    LigateFragmentsTaskConfig() : annotateFragments(false), checkOverhangs(true), makeCircular(false),
    addDocToProject(true), openView(false), saveDoc(false) {}
    GUrl docUrl;
    QString seqName;
    bool annotateFragments;
    bool checkOverhangs;
    bool makeCircular;
    bool addDocToProject;
    bool openView;
    bool saveDoc;
   
};

class DNAAlphabet;

class LigateFragmentsTask : public Task {
    Q_OBJECT
public:
    LigateFragmentsTask(const QList<DNAFragment>& fragments, const LigateFragmentsTaskConfig& cfg );
    Document* getResultDocument() {return resultDoc; }
    void prepare(); 
    void cleanup();

private:
    static QList<Annotation*> cloneAnnotationsInRegion(const U2Region& region, AnnotationTableObject* source, int globalOffset);
    static QList<Annotation*> cloneAnnotationsInFragmentRegion(const DNAFragment& fragment, AnnotationTableObject* source, int globalOffset);
    static Annotation* createSourceAnnotation(int regLen);
    static Annotation* createFragmentAnnotation(const DNAFragment&, int startPos);
    void createDocument(const QByteArray& seq, const QList<Annotation*> annotations);
    void processOverhangs(const DNAFragment& leftFragment, const DNAFragment& rightFragment, QByteArray& overhangAddition);
    bool overhangsAreConsistent(const DNAFragmentTerm& leftTerm, const DNAFragmentTerm& rightTerm);

    QList<DNAFragment> fragmentList;
    QList<Annotation*> annotations;
    LigateFragmentsTaskConfig cfg;
    Document* resultDoc;
    DNAAlphabet* resultAlphabet;
    QMap<Annotation*,int> offsetMap;
    

};


} //namespace

#endif // _U2_CLONING_UTIL_TASKS_H_
