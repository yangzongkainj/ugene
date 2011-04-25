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

#ifndef __ZOOMABLE_ASSEMBLY_OVERVIEW_H__
#define __ZOOMABLE_ASSEMBLY_OVERVIEW_H__

#include <QtCore/QSharedPointer>
#include <QtGui/QWidget>

#include <U2Core/U2Region.h>

#include "AssemblyBrowserSettings.h"
#include "CoverageInfo.h"
#include "BackgroundTaskRunner.h"

namespace U2 {

class AssemblyModel;
class AssemblyBrowserUi;
class AssemblyBrowser;


class ZoomableAssemblyOverview: public QWidget {
    Q_OBJECT
public:
    ZoomableAssemblyOverview(AssemblyBrowserUi * ui, bool zoomable = false);
    
    void setScaleType(AssemblyBrowserSettings::OverviewScaleType t);
    AssemblyBrowserSettings::OverviewScaleType getScaleType()const;
    
protected:
    void paintEvent(QPaintEvent * e);
    void resizeEvent(QResizeEvent * e);
    void mousePressEvent(QMouseEvent * me);
    void mouseMoveEvent(QMouseEvent * me);
    void mouseReleaseEvent(QMouseEvent * me);
    void wheelEvent(QWheelEvent * e);

private slots:
    void sl_visibleAreaChanged();
    void sl_redraw();
    void sl_zoomIn(const QPoint & pos);
    void sl_zoomOut(const QPoint & pos);

private:
    qint64 calcXAssemblyCoord(int x) const;
    qint64 calcYAssemblyCoord(int y) const;

    QRect calcCurrentSelection() const;
    U2Region calcVisibleAssemblyRange() const;
    void moveSelectionToPos(QPoint pos, bool moveModel = true);
    void checkedMoveVisibleRange(qint64 newStartPos);
    void checkedSetVisibleRange(qint64 newStartPos, qint64 newLen);

    void connectSlots();
    void initSelectionRedraw();

    void drawAll();
    void drawBackground(QPainter & p);
    void drawSelection(QPainter & p);
    void drawCoordLabels(QPainter & p);

    void launchCoverageCalculation();

private:
    AssemblyBrowserUi * ui;
    AssemblyBrowser * browser;
    QSharedPointer<AssemblyModel> model;

    bool zoomable;
public:
    U2Region visibleRange;
private:
    double zoomFactor;

    QRect cachedSelection;

    QPixmap cachedView;
    bool redrawSelection;

    QPixmap cachedBackground;
    bool redrawBackground;
    BackgroundTaskRunner<CoverageInfo> coverageTaskRunner;

    bool selectionScribbling;
    bool visibleRangeScribbling;
    QPoint visibleRangeLastPos;

    AssemblyBrowserSettings::OverviewScaleType scaleType;

    const static int FIXED_HEIGHT = 70;
    const static double ZOOM_MULT;
};

} //ns

#endif 
