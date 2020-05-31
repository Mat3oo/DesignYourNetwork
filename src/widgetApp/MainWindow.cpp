#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SubnetDialog.h"
#include "SubnetButton.h"
#include "NetworkDialog.h"
#include "NetworkButton.h"

#include <QSpinBox>
#include <QLabel>
#include <QtCore>

#include "IPv4parser.h"
#include "SubnetsCalculatorV4.h"

using namespace core;

namespace widgetApp {

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        addressWidget = ui->Address4Widget;

        binaryAddressWidget = ui->BinaryAddress4Widget;

        maskWidget = ui->Mask4Widget;

        binaryMaskWidget = ui->BinaryMask4Widget;

        subnetScrollContent = ui->subnetScroll;
        subnetScrollContent->setLayout(subnetsPanelLayout);

        subnetCountBox = ui->hostNumberSpinBox;

        raportDialog->hide();
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
}

void widgetApp::MainWindow::on_calculateButton_clicked()
{
     mainNetwork.Ip = parser.ipFromString(
                 takeStringFromInputFields(addressWidget));

     mainNetwork.NetMask = parser.ipMaskFromString(
                 takeStringFromInputFields(maskWidget));

     displayInputInBinary(mainNetwork.Ip.get()->asStringBin(),
                          binaryAddressWidget);

     displayInputInBinary(mainNetwork.NetMask.get()->asStringBin(),
                          binaryMaskWidget);

     setSubnetsHostCount();

     calculator.calcSubnets(mainNetwork, subnets);    
}

void widgetApp::MainWindow::setSubnetsHostCount()
{ 
     subnets.clear();

    for (int i = 0; i < subnetCount; i++)
    {
       Subnetv4 subnet;

       subnet.SubName = subnetNames->at(i)->text();
       subnet.HostNumber = spinBoxList->at(i)->value();
       subnets.push_back(std::make_shared<Subnetv4>(subnet));

       for (int i = 0; i < subnet.HostNumber; i++)
       {
           Subnet::Host host;
           subnet.HostsList.push_back(host);
       }
    }
}

void widgetApp::MainWindow::deleteLayoutContent(QWidget *content)
{
    QLayoutItem *child;
    while ((child = content->layout()->takeAt(0)) != NULL)
    {
        if(child->widget() != NULL)
        {
            delete child->widget();
        }
        delete child;
    }
}

QString widgetApp::MainWindow::takeStringFromInputFields(QWidget *inputWidget)
{
    QList<QLineEdit*> inputFields = inputWidget->findChildren<QLineEdit*>();

    QString input= "";

    for (int i = 0; i < inputFields.count(); i++)
    {
        if(inputFields.at(i) != NULL)
        {
            input += inputFields.at(i)->text();
            if(i < inputFields.count() - 1) input += ".";
        }
    }
    return input;
}

void widgetApp::MainWindow::displayInputInBinary(QString input, QWidget *displayWidget)
{
    QList<QLineEdit*> displayFields = displayWidget->findChildren<QLineEdit*>();

    std::string bitsetString = input.toUtf8().constData();

    for (int i = 0; i < displayFields.count(); i++)
    {
        if(displayFields[i] != NULL)
        {
            QString octText = QString::fromStdString(bitsetString.substr(i * 9, 8));
            displayFields[i]->setText(octText);
        }
    }
}

void widgetApp::MainWindow::on_hostNumberSpinBox_valueChanged(int subnetCount)
{
    this->subnetCount = subnetCount;

    spinBoxList->clear();

    subnetNames->clear();

    subnets.clear();

    deleteLayoutContent(subnetScrollContent);

    for (int i = 0; i < subnetCount; i++)
    {
        QHBoxLayout *textLayout = new QHBoxLayout();
        QString labelText = QString::fromStdString("Subnet " + std::to_string(1 + i));
        QLabel *subnetLabel = new QLabel(labelText);
        subnetLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        subnetLabel->setLayout(textLayout);
        subnetLabel->font().bold();
        subnetsPanelLayout->addWidget(subnetLabel);
        QVBoxLayout *subnetLayout = new QVBoxLayout();
        QFrame *subnetFrame = new QFrame();
        subnetFrame->setLayout(subnetLayout);

        QHBoxLayout *frameLayout = new QHBoxLayout();
        QLabel *nameLabel = new QLabel("Subnet name: ");
        nameLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        nameLabel->setMinimumHeight(23);
        QFrame *nameFrame = new QFrame();
        nameFrame->setMinimumHeight(35);
        nameFrame->setLayout(frameLayout);
        QLineEdit *subnetNameLine = new QLineEdit();
        subnetNameLine->setMinimumHeight(23);
        subnetNameLine->setStyleSheet("background-color: rgb(60, 60, 60);\n color: rgb(220, 220, 220)");
        frameLayout->addWidget(nameLabel);
        frameLayout->addWidget(subnetNameLine);
        frameLayout = new QHBoxLayout();
        QFrame *hostCountFrame = new QFrame();
        hostCountFrame->setMinimumHeight(35);
        hostCountFrame->setLayout(frameLayout);

        QLabel *hostNumberLabel = new QLabel("Hosts number: ");
        hostNumberLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        hostNumberLabel->setMinimumHeight(23);
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setRange(0, 999);
        spinBox->setStyleSheet("background-color: rgb(60, 60, 60);\n color: rgb(220, 220, 220)");
        spinBox->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        spinBox->setMinimumHeight(23);
        frameLayout->addWidget(hostNumberLabel);
        frameLayout->addWidget(spinBox);

        subnetFrame->layout()->addWidget(hostCountFrame);

        subnetFrame->layout()->addWidget(nameFrame);

        subnetsPanelLayout->addWidget(subnetFrame);

        subnetNames->append(subnetNameLine);

        spinBoxList->append(spinBox);
    }
}

void widgetApp::MainWindow::on_drawButton_clicked()
{
     graphDialog = new GraphDialog(mainNetwork, subnets, this);
     graphDialog->setGeometry(this->geometry().x() + 390, this->geometry().y() + 60,
                              graphDialog->geometry().width(), graphDialog->geometry().height());
     graphDialog->show();
}

void widgetApp::MainWindow::on_raportButton_clicked()
{
    if(raportDialog->isHidden())
    {
        raportDialog = new RaportDialog(this);
        raportDialog->injectData(mainNetwork, subnets);
        raportDialog->displayNetworkRaport();
        raportDialog->setGeometry(this->geometry().x() + 1180, this->geometry().y() + 60,
                                  raportDialog->geometry().width(), raportDialog->geometry().height());
        raportDialog->show();
    }
    else
    {
        raportDialog->injectData(mainNetwork, subnets);
        raportDialog->displayNetworkRaport();
    }
}
