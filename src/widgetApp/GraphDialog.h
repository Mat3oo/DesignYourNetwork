#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QFrame>

#include "NetworkDialog.h"
#include "SubnetDialog.h"
#include "HostDialog.h"
#include "SubnetsCalculatorV4.h"

using namespace core;

namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT

public:

    explicit GraphDialog(Networkv4 mainNetwork,
        std::vector<std::shared_ptr<Subnet>> subnets, QWidget *parent = nullptr);
    ~GraphDialog();


private slots:

     void on_networkButton_clicked(Networkv4 network);

     void on_subnetButton_clicked(std::shared_ptr<Subnet> subnet);

     void on_hostButton_clicked(Subnet::Host host);

     void on_coloredGraphcheckBox_clicked(bool checked);

     void on_verticalViewButton_clicked(bool checked);

     void on_horizontalViewButton_clicked(bool checked);

     void on_scaleSlider_sliderMoved(int position);

     void on_hostNames_toggled(bool checked);

     void on_subnetAddresses_toggled(bool checked);

     void on_networkAddress_toggled(bool checked);

private:

    Ui::GraphDialog *ui;

    bool isVertical = false;
    bool isColored = false;
    bool showsHostNames = false;
    bool showsSubnetAddresses = false;
    bool showsNetworkAddress = false;

    float scale = 1.0f;

    NetworkDialog networkDialog;

    SubnetDialog subnetDialog;

    HostDialog hostDialog;

    QWidget *subnetScrollContent;
    QWidget *subnetGraphContent;
    QFrame *subnetsGraphFrame; 

    Networkv4 mainNetwork;

    std::vector<std::shared_ptr<Subnet>> subnets;

    QHBoxLayout *graphPanelLayout = new QHBoxLayout();

    void drawNetworkGraph();
};

#endif // GRAPHDIALOG_H
