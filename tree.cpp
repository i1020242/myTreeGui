#include "tree.h"

cBST::cBST(QWidget *parent): QWidget(parent)//this point to QWidget
{
    m_root = NULL;
    m_hlayout = new QGridLayout(this);
    m_buttonAdd = new QPushButton(this);
    m_lineEditAdd = new QLineEdit(this);
    m_buttonSmallest = new QPushButton(this);
    m_lineEditSmallest = new QLineEdit(this);
    m_buttonDel = new QPushButton(this);
    m_lineEditDel = new QLineEdit(this);
    m_textEditAdded = new QTextEdit(this);
    m_buttonShow = new QPushButton(this);
    m_textEditShowTree = new QTextEdit(this);
    m_buttonLoadImage = new QPushButton(this);
    m_buttonCreateNewImg = new QPushButton(this);
    m_buttonMakeTree = new QPushButton(this);
    m_lineEditMakeTree = new QLineEdit("21 35 7 9 -7 -9 69 696 -35 99",this);

    m_hlayout->addWidget(m_lineEditAdd,0,0);
    m_hlayout->addWidget(m_buttonAdd,0,1);
    m_hlayout->addWidget(m_lineEditSmallest,1,0);
    m_hlayout->addWidget(m_buttonSmallest,1,1);
    m_hlayout->addWidget(m_lineEditDel,2,0);
    m_hlayout->addWidget(m_buttonDel,2,1);
    m_hlayout->addWidget(m_textEditAdded,0,2);
    m_hlayout->addWidget(m_buttonShow,1,2);
    m_hlayout->addWidget(m_textEditShowTree,2,2);
    m_hlayout->addWidget(m_buttonCreateNewImg,3,0,Qt::AlignCenter);
    m_hlayout->addWidget(m_buttonLoadImage,4,0,Qt::AlignCenter);
    m_hlayout->addWidget(m_lineEditMakeTree,5,0);
    m_hlayout->addWidget(m_buttonMakeTree,5,1);

    m_buttonAdd->setText("Insert key");
    m_buttonSmallest->setText("Smallest Key");
    m_buttonDel->setText("Delete Key");
    m_buttonShow->setText("Show Order");
    m_buttonLoadImage->setText("Load image");
    m_buttonLoadImage->setFixedSize(300,50);
    m_buttonCreateNewImg->setText("Create New Image");
    m_buttonMakeTree->setText("Make Tree");
    QObject::connect(m_buttonAdd,SIGNAL(clicked()),this,SLOT(AddValueSLOT()));
    QObject::connect(m_buttonSmallest,SIGNAL(clicked()),this,SLOT(SmallestValueSLOT()));
    QObject::connect(m_buttonDel,SIGNAL(clicked()),this,SLOT(DeleteValueSLOT()));
    QObject::connect(m_buttonAdd,SIGNAL(clicked()),this,SLOT(AddedValueSLOT()));
    QObject::connect(m_buttonShow,SIGNAL(clicked()),this,SLOT(ShowTreeSLOT()));
    QObject::connect(m_buttonCreateNewImg,SIGNAL(clicked()),this,SLOT(CreateNewImgSLOT()));
    QObject::connect(m_buttonLoadImage,SIGNAL(clicked()),this,SLOT(ShowPicSLOT()));
    QObject::connect(m_lineEditAdd,SIGNAL(returnPressed()),m_buttonAdd,SIGNAL(clicked()));
    QObject::connect(m_buttonMakeTree,SIGNAL(clicked()),this,SLOT(MakeTreeSLOT()));
    QObject::connect(m_lineEditMakeTree,SIGNAL(returnPressed()),m_buttonMakeTree,SIGNAL(clicked()));
    QObject::connect(m_buttonDel,SIGNAL(clicked()),this,SLOT(DeletedValSLOT()));

}

void cBST::AddValueSLOT()
{
    QString sValue = m_lineEditAdd->text();
    int value = sValue.toInt();
    AddLeafValue(value);

}

void cBST::AddLeafValue(int key)
{
    AddLeafValuePrivate(key,m_root);
}

cBST::Node* cBST::CreateNode(int key)
{
    Node* newNode = new Node;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void cBST::AddLeafValuePrivate(int key, Node *Ptr)
{
    if(m_root == NULL) m_root = CreateNode(key);
    else if(key < Ptr->key)
    {
        if(Ptr->left != NULL) AddLeafValuePrivate(key,Ptr->left);
        if(Ptr->left == NULL) Ptr->left = CreateNode(key);
    }
    else if(key > Ptr->key)
    {
        if(Ptr->right != NULL) AddLeafValuePrivate(key,Ptr->right);
        else Ptr->right = CreateNode(key);
    }
    else cout << "Key " << Ptr->key << " already added\n";
}

void cBST::AddedValueSLOT()
{
    QString stringAdd(tr("\nAdd:"));
    m_textEditAdded->insertPlainText(stringAdd);
    m_textEditAdded->insertPlainText(m_lineEditAdd->text() + " ");
}

void cBST::DeletedValSLOT()
{
    QString stringDel(tr("\nDel:"));
    m_textEditAdded->insertPlainText(stringDel);
    m_textEditAdded->insertPlainText(m_lineEditDel->text());
}

void cBST::SmallestValueSLOT()
{
    int key = FindSmallestKey();
    if(key == -1) QMessageBox::warning(this, tr("Binary Tree"), tr("Tree empty"));
    QString value = QString::number(key);//convert num to string
    m_lineEditSmallest->setText(value);
}

int cBST::FindSmallestKey()
{
    if(m_root == NULL) return -1;
    return FindSmallestKeyPrivate(m_root);
}
int cBST::FindSmallestKeyPrivate(Node *Ptr)
{
    if(Ptr->left == NULL) return Ptr->key;
    else if(Ptr->left != NULL) FindSmallestKeyPrivate(Ptr->left);
    else return Ptr->key;
}

void cBST::DeleteValueSLOT()
{
    QString keyDelete = m_lineEditDel->text();
    int key = keyDelete.toInt();
    DeleteKey(key);
}

void cBST::DeleteKey(int key)
{
    DeleteKeyPrivate(key, m_root);
}

void cBST::DeleteKeyPrivate(int key, Node *parent)
{
    if(m_root!=NULL)
    {
        if(key == m_root->key) DeleteRootMatch();

        else if(key < parent->key && parent->left != NULL)
        {
            if(parent->left->key == key) DeleteKeyMatch(parent, parent->left);
            else DeleteKeyPrivate(key, parent->left);
        }
        else if(key > parent->key && parent->right != NULL)
        {
            if(parent->right->key == key) DeleteKeyMatch(parent, parent->right);
            else DeleteKeyPrivate(key, parent->right);
        }
        else QMessageBox::warning(this, tr("Tree"), tr("Find not found"));
    }
    else
        cout << "Tree is empty\n";

}

void cBST::DeleteRootMatch()
{
    Node* Ptr = m_root;
    if(Ptr->left == NULL && Ptr->right == NULL)
    {
        m_root =  NULL;
        delete Ptr;
    }
    else if(Ptr->left!=NULL && Ptr->right == NULL)
    {
        delete Ptr;
        m_root = m_root->left;
    }
    else if(Ptr->left==NULL && Ptr->right != NULL)
    {
        delete Ptr;
        m_root = m_root->right;
    }
    else if(Ptr->left != NULL && Ptr->right !=NULL)
    {
        int smallestRightNode = FindSmallestKeyPrivate(m_root->right);
        DeleteKeyPrivate(smallestRightNode,m_root);
        m_root->key = smallestRightNode;
    }


}

void cBST::DeleteKeyMatch(Node* parent, Node* match)
{
    // 0 child vd 5,7,9->rm 5,9
    if(match->left == NULL && match->right == NULL)
    {
        match->key < parent->key ? parent->left = NULL : parent->right = NULL;
        cout << "Key delete(0 child) " << match->key << " was removed\n";
        delete match;
    }
    else if(match->left != NULL && match->right == NULL)
    {
        match->key < parent->key ? parent->left = match->left : parent->right = match->left;
        cout << "Key delete(1 left child) " << match->key << " has replaced by " << match->left->key << endl;
        match->left = NULL;
        delete match;
    }
    else if(match->left == NULL && match->right != NULL)
    {
        match->key < parent->key ? parent->left = match->right : parent->right = match->right;
        cout << "Key delete(1 r8 child) " << match->key << " has replaced by " << match->right->key << endl;
        match->right = NULL;
        delete match;
    }
    else if(match->left != NULL && match->right !=NULL)
    {
        int smallestInRightChild;
        smallestInRightChild = FindSmallestKeyPrivate(match->right);
        DeleteKeyPrivate(smallestInRightChild, match);
        match->key = smallestInRightChild;
     }
}

void cBST::WalkGraph(Node* ptr, QTextStream &stream)
{
    static int count = 0;
    if(ptr!=NULL)
    {
        stream << "\t" << ptr->key << "[label=\"" << ptr->key<< "\"];" << endl;
        if(ptr->left!=NULL)
        {
            stream << "\t" << ptr->key << "->" << ptr->left->key << ";" << endl;
            WalkGraph(ptr->left, stream);
        }
        else
        {
            stream << "\t" << "null" << count << "[label=\"null\",style=\"filled\"];" << endl;
            stream << "\t" << ptr->key << "->" << "null" << count << endl;
            count++;
        }
        if(ptr->right!=NULL)
        {
            stream << "\t" << ptr->key << "->" << ptr->right->key << ";" << endl;
            WalkGraph(ptr->right, stream);
        }
        else
        {
            stream << "\t" << "null" << count << "[label=\"null\",style=\"filled\"];" << endl;
            stream << "\t" << ptr->key << "->" << "null" << count << endl;
            count++;
        }

    }
}

void cBST::PrepareWalk()
{
    QString fileName = "/home/mrnix/CODE/QT/myTreeGuiTest/BST";
    QFile file(fileName);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << "digraph{" << endl;
        this->WalkGraph(m_root,stream);
        stream << "\n}";
        file.close();
    }
}

void cBST::ShowPic()
{
    QProcess* process = new QProcess;
    this->PrepareWalk();
    process->start("dot -Tpng /home/mrnix/CODE/QT/myTreeGuiTest/BST -o /home/mrnix/CODE/QT/myTreeGuiTest/BST.png");
}

void cBST::ShowTreeSLOT()
{
    PrintInOrder();
}

void cBST::PrintInOrder()
{
    QString stringShow(tr("\nTravel Tree: \n"));
    m_textEditShowTree->insertPlainText(stringShow);
    PrintInOrderPrivate(m_root);
}
void cBST::PrintInOrderPrivate(Node *Ptr)
{
    if(m_root == NULL) QMessageBox::warning(this,tr("Application"),tr("Tree empty"));
    if(Ptr->left != NULL) PrintInOrderPrivate(Ptr->left);
    QString stringKey = QString::number(Ptr->key);
    m_textEditShowTree->insertPlainText(stringKey + " ");
    if(Ptr->right != NULL) PrintInOrderPrivate(Ptr->right);
}

void cBST::CreateNewImgSLOT()
{
    ShowPic();
}

void cBST::ShowPicSLOT()//??@@
{
    QPixmap pm("/home/mrnix/CODE/QT/myTreeGuiTest/BST.png");
    QLabel *label = new QLabel;
    label->setPixmap(pm);
    label->show();
}

void cBST::MakeTreeSLOT()
{
    QVector<int> numVector;
    QString stringMakeTree = m_lineEditMakeTree->text();
    QStringList stringList = stringMakeTree.split(" ",QString::KeepEmptyParts);
    foreach (QString num, stringList) {
            numVector.append(num.toInt());
    }
    for(auto it = numVector.begin(); it!=numVector.end(); it++)
    {
        AddLeafValue(*it);
    }
}



