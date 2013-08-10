#include "calculator_gui.h"
#include "ui_calculator_gui.h"

Calculator_gui::Calculator_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calculator_gui)
{
    ui->setupUi(this);



    mapper = new QSignalMapper(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_1, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_2, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_3, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_4, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_5, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_6, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_7, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_8, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_9, SIGNAL(clicked()), mapper, SLOT(map()));

    connect(ui->pushButton_pi,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_abs_parentesis,SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_abs, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_par_left, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_par_right, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_power, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_nepper, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_E, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_i, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->pushButton_t, SIGNAL(clicked()), mapper, SLOT(map()));

    connect(ui->pushButton_sum,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_mul,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_div,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_dot,SIGNAL(clicked()),mapper, SLOT(map()));

    connect(ui->pushButton_sinc,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_sin,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_cot,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_csc,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_sec,SIGNAL(clicked()),mapper, SLOT(map()));

    connect(ui->pushButton_sinh,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_cosh,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_tanh,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_coth,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_csch,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_sech,SIGNAL(clicked()),mapper, SLOT(map()));

    connect(ui->pushButton_asin,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_acot,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_acsc,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_asec,SIGNAL(clicked()),mapper, SLOT(map()));

    connect(ui->pushButton_asinh,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_acosh,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_atanh,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_acoth,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_acsch,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_asech,SIGNAL(clicked()),mapper, SLOT(map()));

    connect(ui->pushButton_real,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_imag,SIGNAL(clicked()),mapper, SLOT(map()));

    connect(ui->pushButton_sqrt,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_log,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),mapper, SLOT(map()));
    connect(ui->pushButton_exp,SIGNAL(clicked()),mapper, SLOT(map()));

    mapper->setMapping(ui->pushButton_0,"0");
    mapper->setMapping(ui->pushButton_1,"1");
    mapper->setMapping(ui->pushButton_2,"2");
    mapper->setMapping(ui->pushButton_3,"3");
    mapper->setMapping(ui->pushButton_4,"4");
    mapper->setMapping(ui->pushButton_5,"5");
    mapper->setMapping(ui->pushButton_6,"6");
    mapper->setMapping(ui->pushButton_7,"7");
    mapper->setMapping(ui->pushButton_8,"8");
    mapper->setMapping(ui->pushButton_9,"9");

    mapper->setMapping(ui->pushButton_pi,"pi");
    mapper->setMapping(ui->pushButton_abs_parentesis,"|");
    mapper->setMapping(ui->pushButton_abs,"abs(");
    mapper->setMapping(ui->pushButton_par_left,"(");
    mapper->setMapping(ui->pushButton_par_right,")");
    mapper->setMapping(ui->pushButton_power,"^");
    mapper->setMapping(ui->pushButton_nepper,"e");
    mapper->setMapping(ui->pushButton_E,"E");
    mapper->setMapping(ui->pushButton_i,"i");
    mapper->setMapping(ui->pushButton_t,"t");

    mapper->setMapping(ui->pushButton_sum,"+");
    mapper->setMapping(ui->pushButton_sub,"-");
    mapper->setMapping(ui->pushButton_mul,"*");
    mapper->setMapping(ui->pushButton_div,"/");
    mapper->setMapping(ui->pushButton_dot,".");

    mapper->setMapping(ui->pushButton_sinc,"sinc(");

    mapper->setMapping(ui->pushButton_sin,"sin(");
    mapper->setMapping(ui->pushButton_cos,"cos(");
    mapper->setMapping(ui->pushButton_tan,"tan(");
    mapper->setMapping(ui->pushButton_cot,"cot(");
    mapper->setMapping(ui->pushButton_csc,"csc(");
    mapper->setMapping(ui->pushButton_sec,"sec(");

    mapper->setMapping(ui->pushButton_sinh,"sinh(");
    mapper->setMapping(ui->pushButton_cosh,"cosh(");
    mapper->setMapping(ui->pushButton_tanh,"tanh(");
    mapper->setMapping(ui->pushButton_coth,"coth(");
    mapper->setMapping(ui->pushButton_csch,"csch(");
    mapper->setMapping(ui->pushButton_sech,"sech(");

    mapper->setMapping(ui->pushButton_asin,"asin(");
    mapper->setMapping(ui->pushButton_acos,"acos(");
    mapper->setMapping(ui->pushButton_atan,"atan(");
    mapper->setMapping(ui->pushButton_acot,"acot(");
    mapper->setMapping(ui->pushButton_acsc,"acsc(");
    mapper->setMapping(ui->pushButton_asec,"asec(");

    mapper->setMapping(ui->pushButton_asinh,"asinh(");
    mapper->setMapping(ui->pushButton_acosh,"acosh(");
    mapper->setMapping(ui->pushButton_atanh,"atanh(");
    mapper->setMapping(ui->pushButton_acoth,"acoth(");
    mapper->setMapping(ui->pushButton_acsch,"acsch(");
    mapper->setMapping(ui->pushButton_asech,"asech(");

    mapper->setMapping(ui->pushButton_real,"real(");
    mapper->setMapping(ui->pushButton_imag,"imag(");

    mapper->setMapping(ui->pushButton_sqrt,"sqrt(");
    mapper->setMapping(ui->pushButton_log,"log(");
    mapper->setMapping(ui->pushButton_ln,"ln(");
    mapper->setMapping(ui->pushButton_exp,"exp(");

    //connect(mapper, SIGNAL(mapped(const QString &)), this, SLOT(keyPressed(const QString &)));
    connect(mapper,SIGNAL(mapped(const QString &)), this,SLOT(setTextfromBtnClicked(const QString &)));

    connect(ui->pushButton_del,SIGNAL(clicked()),this,SLOT(clicked_del()));

}

Calculator_gui::~Calculator_gui()
{
    delete mapper;
    delete ui;
}



void Calculator_gui::setTextfromBtnClicked(const QString &str)
{
    ui->lineEdit_calc_expression->setText(ui->lineEdit_calc_expression->text()+str);
}

void Calculator_gui::clicked_del()
{
    QString str;
    str = ui->lineEdit_calc_expression->text();
    str.remove(str.size()-1,1);
    ui->lineEdit_calc_expression->setText(str);
}

QString Calculator_gui::GetLineEditCalcExpression()
{
    return ui->lineEdit_calc_expression->text();
}

void Calculator_gui::SetLineEditCalcExpression(const QString &expression_)
{
    ui->lineEdit_calc_expression->setText(expression_);
}
