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

#include "BuiltInDistanceAlgorithms.h"
#include "MsaDistanceAlgorithm.h"

namespace U2 {

// Hamming algorithm is based on Hamming distance between sequences
class U2ALGORITHM_EXPORT MsaDistanceAlgorithmFactoryHammingRevCompl : public MsaDistanceAlgorithmFactory {
    Q_OBJECT
public:
    MsaDistanceAlgorithmFactoryHammingRevCompl(QObject* p = nullptr);

    MsaDistanceAlgorithm* createAlgorithm(const Msa& ma, QObject* parent) override;

    QString getDescription() const override;

    QString getName() const override;
};

class U2ALGORITHM_EXPORT MsaDistanceAlgorithmHammingRevCompl : public MsaDistanceAlgorithm {
    Q_OBJECT
public:
    MsaDistanceAlgorithmHammingRevCompl(MsaDistanceAlgorithmFactoryHammingRevCompl* f, const Msa& ma)
        : MsaDistanceAlgorithm(f, ma) {
    }

    void run() override;
};

}  // namespace U2
