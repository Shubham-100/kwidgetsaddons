/*  -*- C++ -*-
    This file is part of the KDE libraries
    Copyright (C) 1997 Tim D. Gilman (tdgilman@best.org)
              (C) 1998-2001 Mirko Boehm (mirko@kde.org)
              (C) 2007 John Layt <john@layt.net>
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef KDATETABLE_H
#define KDATETABLE_H

#include <QLineEdit>
#include <QDateTime>

class QMenu;

/**
 * Date selection table.
 * This is a support class for the KDatePicker class.  It just
 * draws the calendar table without titles, but could theoretically
 * be used as a standalone.
 *
 * When a date is selected by the user, it emits a signal:
 * dateSelected(QDate)
 *
 * \image html kdatetable.png "KDE Date Selection Table"
 *
 * @internal
 * @author Tim Gilman, Mirko Boehm
 */
class KDateTable : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(bool popupMenu READ popupMenuEnabled WRITE setPopupMenuEnabled)

public:
    /**
     * The constructor.
     */
    explicit KDateTable(QWidget *parent = nullptr);

    /**
     * The constructor.
     */
    explicit KDateTable(const QDate &, QWidget *parent = nullptr);

    /**
     * The destructor.
     */
    ~KDateTable() override;

    /**
     * Returns a recommended size for the widget.
     * To save some time, the size of the largest used cell content is
     * calculated in each paintCell() call, since all calculations have
     * to be done there anyway. The size is stored in maxCell. The
     * sizeHint() simply returns a multiple of maxCell.
     */
    QSize sizeHint() const override;

    /**
     * Set the font size of the date table.
     */
    void setFontSize(int size);

    /**
     * Select and display this date.
     */
    bool setDate(const QDate &date);

    // KDE5 remove the const & from the returned QDate
    /**
     * @returns the selected date.
     */
    const QDate &date() const;

    /**
     * Enables a popup menu when right clicking on a date.
     *
     * When it's enabled, this object emits a aboutToShowContextMenu signal
     * where you can fill in the menu items.
     */
    void setPopupMenuEnabled(bool enable);

    /**
     * Returns if the popup menu is enabled or not
     */
    bool popupMenuEnabled() const;

    enum BackgroundMode { NoBgMode = 0, RectangleMode, CircleMode };

    /**
     * Makes a given date be painted with a given foregroundColor, and background
     * (a rectangle, or a circle/ellipse) in a given color.
     */
    void setCustomDatePainting(const QDate &date, const QColor &fgColor,
                               BackgroundMode bgMode = NoBgMode, const QColor &bgColor = QColor());

    /**
     * Unsets the custom painting of a date so that the date is painted as usual.
     */
    void unsetCustomDatePainting(const QDate &date);

protected:
    /**
     * calculate the position of the cell in the matrix for the given date.
     * The result is the 0-based index.
     */
    virtual int posFromDate(const QDate &date);

    /**
     * calculate the date that is displayed at a given cell in the matrix. pos is the
     * 0-based index in the matrix. Inverse function to posForDate().
     */
    virtual QDate dateFromPos(int pos);

    void paintEvent(QPaintEvent *e) override;

    /**
     * React on mouse clicks that select a date.
     */
    void mousePressEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

    /**
     * Cell highlight on mouse hovering
     */
    bool event(QEvent *e) override;

Q_SIGNALS:
    /**
     * The selected date changed.
     */
    void dateChanged(const QDate &date);

    /**
     * This function behaves essentially like the one above.
     * The selected date changed.
     * @param cur The current date
     * @param old The date before the date was changed
     */
    void dateChanged(const QDate &cur, const QDate &old);

    /**
     * A date has been selected by clicking on the table.
     */
    void tableClicked();

    /**
     * A popup menu for a given date is about to be shown (as when the user
     * right clicks on that date and the popup menu is enabled). Connect
     * the slot where you fill the menu to this signal.
     */
    void aboutToShowContextMenu(QMenu *menu, const QDate &date);

private:
    class KDateTablePrivate;
    friend class KDateTablePrivate;
    KDateTablePrivate *const d;

    void initWidget(const QDate &date);
    void initAccels();
    void paintCell(QPainter *painter, int row, int col);

    Q_DISABLE_COPY(KDateTable)
};

#endif // KDATETABLE_H
