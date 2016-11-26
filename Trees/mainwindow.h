#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "rbnode.h"
#include "rbtree.h"
#include "avlnode.h"
#include "avltree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class RBNode;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTree(RBTree* _tree);
protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void on_delete_button_clicked();
    void draw();

    void on_add_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QMessageBox *message;
    RBTree* tree;
    AVLTree* AVL_tree;
    void draw_RBnode(RBNode* node, int x, int y);
    void draw_AVLNode(AVLNode* node, int x, int y);
};

#endif // MAINWINDOW_H
