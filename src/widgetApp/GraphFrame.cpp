#include "GraphFrame.h"
#include "SubnetButton.h"
#include "NetworkButton.h"

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include "core/INetwork.h"

GraphFrame::GraphFrame(NetworkButton *networkButton, QList<SubnetButton*> subnetButtons,
           QWidget *scrollArea, bool draw, float gridSize, float scale,
           QWidget *parent) : QFrame(parent){

     this->networkButton = networkButton;
     this->subnetButtons = subnetButtons;
     this->scrollArea = scrollArea;
     this->draw = draw;
     this->gridSize = gridSize;
     this->scale = scale;
}

void GraphFrame::paintEvent(QPaintEvent * event){
    QFrame::paintEvent(event);

    QPainter painter = QPainter(this);
    QPen pen = QPen(QColor(38,94,84).lighter());
    painter.setPen(pen);

    if(draw)
    {
        for(int i = 0 ; i < scrollArea->width() * (2 + subnetButtons.count()); i += 30 * gridSize)
        {
            painter.drawLine(QPoint(0, i), QPoint(scrollArea->height() * (2 + subnetButtons.count()), i));
        }

        for(int i = 0 ; i < scrollArea->height() * (2 + subnetButtons.count()); i += 30 * gridSize)
        {
            painter.drawLine(QPoint(i, 0), QPoint(i, scrollArea->width() * (subnetButtons.count() + 2)));
        }
    }

    pen.setColor(QColor(255,255,255));
    pen.setWidth(3 * scale);
    painter.setPen(pen);

    for(int i = 0; i < static_cast<int>(subnetButtons.size()); i++)
    {
         QPoint a = networkButton->mapTo(this, networkButton->rect().center());
         QPoint b = networkButton->mapTo(this, QPoint(0, networkButton->rect().center().y()));
         QPoint c = subnetButtons.at(i)->mapTo(this, QPoint(subnetButtons.at(i)->rect().center().x(), 0));
         QPoint d = QPoint(c.x(), b.y());

         painter.drawLine(a, d);
         painter.drawLine(d, subnetButtons.at(i)->mapTo(this, subnetButtons.at(i)->rect().center()));
    }
}

