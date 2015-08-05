#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include <QFile>
#include <QPlainTextEdit>
#include <QImage>
#include <QLabel>

using namespace std;
class cBST : public QWidget
{
    Q_OBJECT
private:
    struct Node
    {
        int key;
        Node* left;
        Node* right;
    };
    Node* m_root;
    QGridLayout* m_hlayout;
    QPushButton* m_buttonAdd, *m_buttonSmallest,
               *m_buttonDel, *m_buttonShow, *m_buttonLoadImage,
               *m_buttonCreateNewImg, *m_buttonMakeTree;
    QLineEdit* m_lineEditAdd, *m_lineEditSmallest, *m_lineEditDel,
               *m_lineEditMakeTree;
    QTextEdit* m_textEditAdded, *m_textEditShowTree;


    void AddLeafValuePrivate(int key, Node* Ptr);
    Node* CreateNode(int key);
    int FindSmallestKeyPrivate(Node* Ptr);
    void PrintInOrderPrivate(Node* Ptr);
    void DeleteKeyPrivate(int key, Node* parent);
    void DeleteKeyMatch(Node* parent, Node* match);
    void DeleteRootMatch();
    void WalkGraph(Node* ptr, QTextStream& stream);
    void PrepareWalk();
public:
    cBST(QWidget* parent = 0);
    void AddLeafValue(int key);
    int FindSmallestKey();
    void PrintInOrder();
    void DeleteKey(int key);
    void ShowPic();
public slots:
     void AddValueSLOT();//add value from lineedit into tree;
     void SmallestValueSLOT();
     void DeleteValueSLOT();
     void AddedValueSLOT();
     void ShowTreeSLOT();
     void CreateNewImgSLOT();
     void ShowPicSLOT();
     void MakeTreeSLOT();
     void DeletedValSLOT();
};


#endif // TREE_H
