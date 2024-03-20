#include "infowidget.h"
#include "ui_infowidget.h"
#include<QIcon>

InfoWidget::InfoWidget(QString name) :
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    this->name=name;
    map.insert("跨境电商大数据分析系统","系统致力于整合和分析跨境电商的海量数据，包括客户规模、订单类型、交易行为等，以深度洞察市场趋势和客户行为，并通过实时展示和客户采集管理，为决策者提供全面而及时的数据支持。");
    map.insert("跨境货物通关轨迹追溯查询系统","该系统提供了便捷的货物通关轨迹查询服务，用户可追溯货物通关过程，通过记录查询历史和统计数据，实现对通关情况的数据分析和监控，以确保通关流程的透明度和高效性。");
    map.insert("区港联动业务协同服务平台","此平台旨在实现区域港口业务的资源共享和协同服务，通过统一管理各类资源和业务，提高资源利用效率，并通过实时统计分析，优化业务流程，推动区域港口业务的整体发展。");
    map.insert("数字口岸综合服务平台","数字口岸综合服务平台专注于口岸服务数据的综合分析与管理，深度解析进出口服务、核查服务等数据，提供精准的口岸服务管理和记录，为口岸运营提供科学依据与决策支持。");
    map.insert("通关大数据分析平台","该平台通过深度挖掘口岸服务数据和通关人员信息，实现对通关流程的全面监控与分析，及时预警潜在风险，为通关管理部门提供智能决策和风险评估的支持。");
    map.insert("物流枢纽智能物联协同服务平台","平台主要关注物流枢纽的智能化管理，通过物联数据转化与监控发布，实现对物流信息的智能化处理与监控，为物流枢纽的高效运营提供强有力的技术支持。");
    setWindowTitle("详情");
    setWindowIcon(QIcon(":/img/info2.png"));
    ui->label->setText(this->name);

    ui->textEdit->setText(map.value(this->name));
    ui->textEdit->setReadOnly(true);
}



InfoWidget::~InfoWidget()
{
    delete ui;
}
