/*
 * wpa_gui - ScanResults class
 * Copyright (c) 2005-2006, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef SCANRESULTS_H
#define SCANRESULTS_H

#include <QObject>

class ScanResults : public QObject
{
	Q_OBJECT

public:
    ScanResults(QObject *parent = 0);
	~ScanResults();

public slots:

	virtual void updateResults();

	virtual void getResults();
    //virtual void bssSelected(QTreeWidgetItem *sel);

protected slots:


private:

};

#endif /* SCANRESULTS_H */
