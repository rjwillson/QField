/***************************************************************************
  rubberband.h - Rubberband

 ---------------------
 begin                : 11.6.2016
 copyright            : (C) 2016 by Matthias Kuhn
 email                : matthias@opengis.ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include <QQuickItem>

class RubberbandModel;
class VertexModel;
class QgsQuickMapSettings;

/**
 * @brief The Rubberband class is used to draw rubber bands on the map canvas.
 * It is aimed to be used with either a VertexModel or a RubberbandModel.
 * Setting one will remove  the former definition of the other.
 */
class Rubberband : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY( RubberbandModel *model READ model WRITE setModel NOTIFY modelChanged )
    Q_PROPERTY( VertexModel *vertexModel READ vertexModel WRITE setVertexModel NOTIFY vertexModelChanged )
    Q_PROPERTY( QgsQuickMapSettings *mapSettings READ mapSettings WRITE setMapSettings NOTIFY mapSettingsChanged )
    //! Color of the main rubberband
    Q_PROPERTY( QColor color READ color WRITE setColor NOTIFY colorChanged )
    //! Line width of the main rubberband
    Q_PROPERTY( qreal width READ width WRITE setWidth NOTIFY widthChanged )
    //! Color of the aleternative rubberband for current point
    Q_PROPERTY( QColor colorCurrentPoint READ colorCurrentPoint WRITE setColorCurrentPoint NOTIFY colorCurrentPointChanged )
    //! Line width  of the aleternative rubberband for current point
    Q_PROPERTY( qreal widthCurrentPoint READ widthCurrentPoint WRITE setWidthCurrentPoint NOTIFY widthCurrentPointChanged )
    //! trace interval in seconds
    Q_PROPERTY( int traceTimeInterval READ traceTimeInterval WRITE setTraceTimeInterval NOTIFY traceTimeIntervalChanged )
    //! trace distance in map units
    Q_PROPERTY( int traceMinimumDistance READ traceMinimumDistance WRITE setTraceMinimumDistance NOTIFY traceMinimumDistanceChanged )
    //! trace distance in map units
    Q_PROPERTY( bool traceConjunction READ traceConjunction WRITE setTraceConjunction NOTIFY traceConjunctionChanged )

  public:
    Rubberband( QQuickItem *parent = nullptr );

    RubberbandModel *model() const;
    void setModel( RubberbandModel *model );

    VertexModel *vertexModel() const;
    void setVertexModel( VertexModel *vertexModel );

    QgsQuickMapSettings *mapSettings() const;
    void setMapSettings( QgsQuickMapSettings *mapSettings );

    //! \copydoc color
    QColor color() const;
    //! \copydoc color
    void setColor( const QColor &color );

    //! \copydoc width
    qreal width() const;
    //! \copydoc width
    void setWidth( qreal width );

    //! \copydoc colorCurrentPoint
    QColor colorCurrentPoint() const;
    //! \copydoc
    void setColorCurrentPoint( const QColor &color );

    //! \copydoc widthCurrentPoint
    qreal widthCurrentPoint() const;
    //! \copydoc widthCurrentPoint
    void setWidthCurrentPoint( qreal width );

    //! \copydoc traceTimeInterval
    int traceTimeInterval() const;
    //! \copydoc traceTimeInterval
    void setTraceTimeInterval( int traceTimeInterval );

    //! \copydoc traceMinimumDistance
    int traceMinimumDistance() const;
    //! \copydoc traceTimeInterval
    void setTraceMinimumDistance( int traceMinimumDistance );

    //! \copydoc traceConjunction
    bool traceConjunction() const;
    //! \copydoc traceConjunction
    void setTraceConjunction( bool traceConjunction );


    Q_INVOKABLE void traceStart();
    Q_INVOKABLE void traceStop();

  signals:
    void modelChanged();
    void vertexModelChanged();
    void mapSettingsChanged();
    //! \copydoc color
    void colorChanged();
    //! \copydoc width
    void widthChanged();
    //! \copydoc colorCurrentPoint
    void colorCurrentPointChanged();
    //! \copydoc widthCurrentPoint
    void widthCurrentPointChanged();
    //! \copydoc traceTimeInterval
    void traceTimeIntervalChanged();
    //! \copydoc traceMinimumDistance
    void traceMinimumDistanceChanged();
    //! \copydoc traceConjunction
    void traceConjunctionChanged();


  private slots:
    void markDirty();
    void tracePositionReceived();
    void traceTimeReceived();

  private:
    QSGNode *updatePaintNode( QSGNode *n, QQuickItem::UpdatePaintNodeData * );

    RubberbandModel *mRubberbandModel = nullptr;
    VertexModel *mVertexModel = nullptr;
    QgsQuickMapSettings *mMapSettings = nullptr;
    bool mDirty = false;
    QColor mColor = QColor( 192, 57, 43, 200 );
    qreal mWidth = 1.8;
    QColor mColorCurrentPoint = QColor( 192, 57, 43, 150 );
    qreal mWidthCurrentPoint = 1.2;

    QTimer *traceTimer = nullptr;
    int mTraceTimeInterval = 0;
    int mTraceMinimumDistance = 0;
    bool mTraceConjunction = true;
    bool mTraceTimeIntervalFulfilled = false;
    bool mTraceMinimumDistanceFulfilled = false;

    void tracePosition();
};


#endif // RUBBERBAND_H
