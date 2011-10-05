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

#ifndef _U2_FASTQ_FORMAT_H_
#define _U2_FASTQ_FORMAT_H_

#include <U2Core/BaseDocumentFormats.h>
#include <U2Core/DocumentModel.h>
#include <QtCore/QStringList>

namespace U2 {

class IOAdapter;

class U2FORMATS_EXPORT FastqFormat : public DocumentFormat {
    Q_OBJECT
public:
    FastqFormat(QObject* p);

    virtual DocumentFormatId getFormatId() const {return BaseDocumentFormats::FASTQ;}

    virtual const QString& getFormatName() const {return fn;}

    virtual DNASequence *loadSequence( IOAdapter* io, U2OpStatus& os);
    
    virtual void storeDocument( Document* d, IOAdapter* io, U2OpStatus& os );

    virtual FormatCheckResult checkRawData(const QByteArray& rawData, const GUrl& = GUrl()) const;

protected:
    virtual Document* loadDocument(IOAdapter* io, const U2DbiRef& dbiRef, const QVariantMap& fs, U2OpStatus& os);

private:
    QString fn;
};

}//namespace

#endif
