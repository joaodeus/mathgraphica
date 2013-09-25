#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include "gui/calculator_gui.h"
#include "gui/equation_gui.h"
#include "gui/systemeq_gui.h"
#include "gui/integral_gui.h"
#include "gui/integraldouble_gui.h"
#include "graph3D/graph3d_opengl.h"
#include "gui/matrix_gui.h"
#include "gui/formulas_gui.h"
#include "graph2D/graph2d_opengl.h"


#define TYPE_EXPRESSION         1
#define TYPE_EQUATION           2
#define TYPE_INTEGRAL           3
#define TYPE_INTEGRAL_DOUBLE    4



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cmdLine->installEventFilter(this);
    ui->listWidget_results_history->installEventFilter(this);

    //---Calculator gui default expression-----
    defaultCalulatorGuiExpression = "";


    //---System of Equation Matrix-------------
    //systemEquationMatrix.SetLinesCols(3,4);
    //systemEquationMatrix.random();
    systemEquationMatrix.SetMatrixRandom(3,4);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_cmdLine_returnPressed()
{    
    QString str_cmd_line = ui->lineEdit_cmdLine->text();

    MyNumber number;
    bool ok = false;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    //check for expressions
    number = calc.isValidExpression(str_cmd_line, ok);
    //if ( calc.isValidExpression(str_cmd_line) )
    if (ok)
    {
        //QString solution = calc.formatResult(calc.SolveExpression(str_cmd_line));
        QString solution = calc.formatResult(number);
        QListWidgetItem *item   = new QListWidgetItem(str_cmd_line,0,TYPE_EXPRESSION);
        QListWidgetItem *item1  = new QListWidgetItem(solution,0,TYPE_EXPRESSION);
        ui->listWidget_results_history->addItem(item);
        ui->listWidget_results_history->addItem(item1);
        ui->listWidget_results_history->scrollToBottom();
    }


    //check for equations
    if (calc.isValidEquation(str_cmd_line))
    {
        //QList<Complexo> equationSolutions = calc.SolveEquation(str_cmd_line);
        QList<Complexo> equationSolutions = calc.m_equation.solveEquation(str_cmd_line);
        if (equationSolutions.size() > 0)
        {
            QListWidgetItem *item = new QListWidgetItem(str_cmd_line,0,TYPE_EQUATION);
            ui->listWidget_results_history->addItem(item);

            for (int i=0;i<equationSolutions.size();i++)
            {
                QListWidgetItem *item1 = new QListWidgetItem(calc.formatResult(equationSolutions.at(i)),0,TYPE_EXPRESSION);
                ui->listWidget_results_history->addItem(item1);
            }
            ui->listWidget_results_history->scrollToBottom();
        }
    }


    if (calc.m_integral.isValidIntegralSintaxe(str_cmd_line))
    {
        QString solution = calc.formatResult(calc.m_integral.solveIntegral());
        QListWidgetItem *item   = new QListWidgetItem(str_cmd_line,0,TYPE_INTEGRAL);
        QListWidgetItem *item1  = new QListWidgetItem(solution,0,TYPE_EXPRESSION);
        ui->listWidget_results_history->addItem(item);
        ui->listWidget_results_history->addItem(item1);                
        ui->listWidget_results_history->scrollToBottom();
    }

    QApplication::restoreOverrideCursor();
}


void MainWindow::on_listWidget_results_history_itemDoubleClicked(QListWidgetItem *item)
{

    if (ui->listWidget_results_history->currentItem()->type() == TYPE_EXPRESSION)
    {
        defaultCalulatorGuiExpression = item->text();
        on_actionCalculator_triggered();
    }

    if (ui->listWidget_results_history->currentItem()->type() == TYPE_EQUATION)
    {
        calc.m_equation.setEquation(item->text());
        on_actionEquation_triggered();
    }


    if (ui->listWidget_results_history->currentItem()->type() == TYPE_INTEGRAL)
    {
        //calc.m_integral.isValidIntegralSintaxe(item->text());
        if (calc.m_integral.setIntegralFromSintaxe(item->text()))
            on_actionIntegral_triggered();
    }

    if (ui->listWidget_results_history->currentItem()->type() == TYPE_INTEGRAL_DOUBLE)
    {
        if (calc.m_integralDouble.setIntegralDoubleFromSintaxe(item->text()))
            on_actionIntegral_double_triggered();
    }



}

void MainWindow::on_listWidget_results_history_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);
    ui->lineEdit_cmdLine->setText(current->text());
}


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (  event->type() == QEvent::KeyPress)
    {

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //qDebug("Ate key press %d - %x", keyEvent->key(), keyEvent->key());
        if ((keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
              && ui->lineEdit_cmdLine->hasFocus())
        {
            ui->listWidget_results_history->setFocus();
            ui->listWidget_results_history->setCurrentRow(ui->listWidget_results_history->count()-1);
        }

        /*Note: 16777220 is the second Enter key from the keyboard*/
        if ((keyEvent->key() == 16777220 || keyEvent->key() == Qt::Key_Enter)
                && ui->listWidget_results_history->hasFocus())
        {
            ui->lineEdit_cmdLine->setFocus();
        }
    }
    // standard event processing
    return QObject::eventFilter(target, event);
}


void MainWindow::on_pushButtonOk_clicked()
{
    on_lineEdit_cmdLine_returnPressed();
}


void MainWindow::on_actionCalculator_triggered()
{
    Calculator_gui *calcGui = new Calculator_gui;

    calcGui->SetLineEditCalcExpression(defaultCalulatorGuiExpression);
    //int deg=calc.getDegreeRadGrad();
    calcGui->setDegreeRadGrad(calc.getDegreeRadGrad());

    if (calcGui->exec() == QDialog::Accepted)
    {
        calc.setDegreeRadGrad(calcGui->getDegreeRadGrad());
        //deg = calcGui->getDegreeRadGrad();
        calc.setDegreeRadGrad(calcGui->getDegreeRadGrad());
        ui->lineEdit_cmdLine->setText(calcGui->GetLineEditCalcExpression());        
        on_lineEdit_cmdLine_returnPressed();

    }

    delete calcGui;
    defaultCalulatorGuiExpression = "";

}

void MainWindow::on_actionGraph_3D_triggered()
{
    Graph3D_OpenGL *graph = new Graph3D_OpenGL ;
    graph->show();
    
}


void MainWindow::on_actionEquation_triggered()
{

    Equation_gui equationGui;

    equationGui.SetLineEdit_fx(calc.m_equation.getEquation_member1());
    equationGui.SetLineEdit_gx(calc.m_equation.getEquation_member2());
    equationGui.SetLineEdit_min(calc.m_equation.getLimitsMin());
    equationGui.SetLineEdit_max(calc.m_equation.getLimitsMax());
    equationGui.SetLineEdit_delta(calc.m_equation.getDelta());
    equationGui.SetLineEdit_precision(calc.m_equation.getPrecision());

    if (equationGui.exec() == QDialog::Accepted)
    {
        calc.m_equation.setLimits(equationGui.GetLineEdit_min(), equationGui.GetLineEdit_max());
        calc.m_equation.setDelta(equationGui.GetLineEdit_delta());
        calc.m_equation.setPrecision(equationGui.GetLineEdit_precision());

        ui->lineEdit_cmdLine->setText(equationGui.GetLineEdit_fx()+"="+equationGui.GetLineEdit_gx());
        on_lineEdit_cmdLine_returnPressed();
    }

}


void MainWindow::on_actionSystem_of_equations_triggered()
{
    SystemEq_gui *systemEq = new SystemEq_gui;

    systemEq->mat = &systemEquationMatrix;
    systemEq->show();

    ////////////////////
//    systemEq_wiget *wid = new systemEq_wiget;
  //  wid->mat = &matrixEquationSystem;
   // wid->show();

}

void MainWindow::on_actionIntegral_triggered()
{
    Integral_gui integral;

    integral.SetLowerLimit(calc.m_integral.getLowerLimit());
    integral.SetUpperLimit(calc.m_integral.getUpperLimit());
    integral.SetNumberOfIntervals(calc.m_integral.getNumberOfIntervals());
    integral.SetIntegralExpression(calc.m_integral.getIntegralExpression());

    if (integral.exec() == QDialog::Accepted)
    {
        calc.m_integral.setLimits(integral.GetLowerLimit(),integral.GetUpperLimit());
        calc.m_integral.setNumberOfIntervals(integral.GetNumberOfIntervals());
        calc.m_integral.setIntegralExpression(integral.GetIntegralExpression());
        ui->lineEdit_cmdLine->setText(calc.m_integral.getIntegral_Sintaxe());
        on_lineEdit_cmdLine_returnPressed();
    }
}


void MainWindow::on_actionIntegral_double_triggered()
{
    //Complexo z = calc.m_integralDouble.solveIntegralDouble();

    IntegralDouble_gui integralD;

    integralD.setInnerLimits(calc.m_integralDouble.getInnerLowerLimit(),
                             calc.m_integralDouble.getInnerUpperLimit());
    integralD.setOuterLimits(calc.m_integralDouble.getOuterLowerLimit(),
                             calc.m_integralDouble.getOuterUpperLimit());
    integralD.setVaribles(calc.m_integralDouble.getVariableInner(),
                          calc.m_integralDouble.getVariableOuter());
    integralD.setNumberOfIntervals(calc.m_integralDouble.getNumberOfIntervals());
    integralD.setIntegralDoubleExpression(calc.m_integralDouble.getIntegralDoubleExpression());


    if (integralD.exec() == QDialog::Accepted)
    {
        calc.m_integralDouble.setOuterLimits(integralD.getOuterLowerLimit(), integralD.getOuterUpperLimit());
        calc.m_integralDouble.setInnerLimits(integralD.getInnerLowerLimit(), integralD.getInnerUpperLimit());
        calc.m_integralDouble.setVaribles(integralD.getInnerVarible(), integralD.getOuterVarible());
        calc.m_integralDouble.setNumberOfIntervals(integralD.getNumberOfIntervals());
        calc.m_integralDouble.setIntegralDoubleExpression(integralD.getIntegralDoubleExpression());


        //ui->lineEdit_cmdLine->setText(calc.m_integralDouble.getIntegralDoubleExpression());

        //on_lineEdit_cmdLine_returnPressed();
        QString integralSintaxe = calc.m_integralDouble.getIntegralDouble_Sintaxe();
        QString solution = calc.formatResult(calc.m_integralDouble.solveIntegralDouble());
        QListWidgetItem *item   = new QListWidgetItem(integralSintaxe,0,TYPE_INTEGRAL_DOUBLE);
        QListWidgetItem *item1  = new QListWidgetItem(solution,0,TYPE_EXPRESSION);
        ui->listWidget_results_history->addItem(item);
        ui->listWidget_results_history->addItem(item1);
        ui->listWidget_results_history->scrollToBottom();
    }
}

void MainWindow::on_actionMatrix_triggered()
{
    Matrix_gui *matrix_gui = new Matrix_gui;

    matrix_gui->mat1            = &mat1;
    matrix_gui->mat2            = &mat2;
    matrix_gui->mat3            = &mat3;
    matrix_gui->mat_copy_paste  = &mat_copy_paste;

    matrix_gui->show();
}

void MainWindow::on_actionFormulas_triggered()
{
    Formulas_gui *formulas = new Formulas_gui(0, &calc);
    formulas->show();
}

void MainWindow::on_actionGraph_2D_triggered()
{
    Graph2D m_graph2D(&calc);
    m_graph2D.setInterval(-50,50);
    m_graph2D.setDelta(0.1);
    m_graph2D.setGraph2DExpression("cos(2*x)");
    m_graph2D.setupGraph();

    Graph2D_OpenGL *graph2DWindow = new Graph2D_OpenGL(&calc);

    graph2DWindow->addGraph2D(m_graph2D);
    graph2DWindow->show();
}
