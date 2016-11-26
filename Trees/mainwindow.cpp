#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractGraphicsShapeItem>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setVisible(false);

    tree = new RBTree;
    tree->read_file("data.txt");
    tree->write_file("output.txt");
    AVL_tree = new AVLTree("data.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTree(RBTree *_tree)
{
    this->tree = _tree;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //this->draw_RBnode(this->tree->root,this->width() / 2, 40);
    this->draw_AVLNode(this->AVL_tree->root,this->width() / 2, 40);
}

void MainWindow::draw_RBnode(RBNode *node, int x, int y)
{
    if(node == nullptr)
    {
        return;
    }

    QPainter painter(this);
    painter.setPen(Qt::black);
    int step = this->width() / (pow(2,node->level + 1) + 1);

    if(!node->is_leaf())
    {
        if(node->left != nullptr) painter.drawLine(QPoint(x,y),QPoint(x - step / 2,y + 60));
        if(node->right != nullptr) painter.drawLine(QPoint(x,y),QPoint(x + step / 2,y + 60));
    }

    if(node->color == RED)
    {
        painter.setBrush(Qt::red);
        painter.setPen(Qt::black);
    } else
    {
        painter.setBrush(Qt::black);
        painter.setPen(Qt::red);
    }

    QString s;
    s = s.number(node->key);
    painter.drawEllipse(x - 15,y - 15,30,30);
    painter.setPen(Qt::white);
    painter.drawText(QRect(x - 10, y - 10, x + 10, y + 10),s);
    draw_RBnode(node->left,x - step / 2,y + 60);
    draw_RBnode(node->right,x + step / 2, y + 60);
}

void MainWindow::draw_AVLNode(AVLNode *node, int x, int y)
{
    if(node == nullptr)
    {
        return;
    }

    QPainter painter(this);
    painter.setPen(Qt::black);
    int step = this->width() / (pow(2,AVL_tree->root->height - node->height + 1) + 1);

    if(!node->is_leaf())
    {
        if(node->left != nullptr) painter.drawLine(QPoint(x,y),QPoint(x - step / 2,y + 60));
        if(node->right != nullptr) painter.drawLine(QPoint(x,y),QPoint(x + step / 2,y + 60));
    }
    painter.setBrush(Qt::black);
    painter.setPen(Qt::white);

    QString s;
    s = s.number(node->key);
    painter.drawEllipse(x - 15,y - 15,30,30);
    painter.drawText(QRect(x - 10, y - 10, x + 10, y + 10),s);
    draw_AVLNode(node->left,x - step / 2,y + 60);
    draw_AVLNode(node->right,x + step / 2, y + 60);

}

void MainWindow::on_delete_button_clicked()
{
    if(ui->lineEdit_2->text() != "")
    {
        int key = ui->lineEdit_2->text().toInt(0,10);
        tree->remove(key);
        draw();
    }
}

void MainWindow::draw()
{
    update();
}

void MainWindow::on_add_button_clicked()
{
    if(ui->lineEdit->text() != "")
    {
        int key = ui->lineEdit->text().toInt(0,10);
        //this->tree->add(key);

        this->AVL_tree->add(key);
        draw();
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
}

void MainWindow::on_pushButton_clicked()
{
    this->AVL_tree->rotate_right(AVL_tree->root->left);
    draw();
}
