#include "shortestpath.h"
#include "ui_shortestpath.h"
#include <QMessageBox>
#include <QStack>
#define IMPOSSIBLE 100000

int sign[100];

ShortestPath::ShortestPath(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShortestPath)
{
    ui->setupUi(this);

    //读文件
    ReadFiles();
}

ShortestPath::~ShortestPath()
{
    delete ui;
}

void ShortestPath::on_Find_clicked()
{
    //获取出发点和终点
    int from = ui->From->toPlainText().toInt();
    int to = ui->To->toPlainText().toInt();

    //如果输入的数据不正确则提示并return
    if (from < 0 || from > G.n || to < 0 || to > G.n){
        QMessageBox::warning(this, "Warning!", "Invalid Input!");
        ui->From->setPlainText("");
        ui->To->setPlainText("");
        return;
    }

    //因为Dijkstra算法存储路径为反向，故将路径放入栈以实现正向 ··· 1
    QStack<int> path_order;
    path_order.push(to);

    //执行Dijkstra算法
    int path[100];
    int dist[100];
    Dijkstra(G, from, path, dist);

    //同注释 1
    while (path[to] != from){
        to = path[to];
        path_order.push(to);
    }

    //在屏幕上输出最短路径经过的节点顺序
    ui->Path->setPlainText(QString::number(from));
    int now_num = from;
    int lenth = 0;


    //从栈中取出实现调换顺序
    while (path_order.size() != 0) {
        ArcNode *p = G.vertices[now_num].firstarc;
        int temp = path_order.pop();
        now_num = temp;
        QString last = ui->Path->toPlainText();
        last += "->";
        last += QString::number(temp);
        ui->Path->setPlainText(last);

        //计算最短路径总距离
        while (G.vertices[p->adjvex].num != temp) {
            p = p->nextarc;
        }

        lenth += p->weight;

    }
    //输出最短路径总距离
    ui->Lenth->setPlainText(QString::number(lenth) + "m");
}

//Dijkstra算法扩展，寻找两点间最短路径
void ShortestPath::Dijkstra(ALGraph G, int v0, int path[], int dist[]){
    int v;
    for(v = 0; v<G.n; ++v)
    {
        sign[v] = 0;
        dist[v] = IMPOSSIBLE;
        path[v] = -1;
    }
    ArcNode* p;
    p = G.vertices[v0].firstarc;
    while (p != nullptr){
        dist[p->adjvex] = p->weight;
        path[p->adjvex] = v0;
        p = p->nextarc;
    }
    dist[v0] = 0;  sign[v0] = 1;//S集中开始时只有v0
    int i;

    for(i = 1; i<G.n; ++i){
        int min;
        min = IMPOSSIBLE;
        int j;
        for (j = 0; j < G.n; ++j){
            if (sign[j] == 0){
                if (dist[j]<min) {
                    v = j;
                    min = dist[j];
                }
            }
        }
        sign[v] = 1;//将v加入S

        p = G.vertices[v].firstarc;
        int d;
        int q[100];
        for (d = 0; d < G.n; d++){
            q[d] = IMPOSSIBLE;
        }
        while (p != nullptr){
            q[p->adjvex] = p->weight;
            p = p->nextarc;
        }
        for (j = 0; j < G.n; ++j){//调整其余在V-S的点

            if (sign[j] == 0 && (dist[v] + q[j]<dist[j]))
            {
                dist[j] = dist[v] + q[j];
                path[j] = v;
            }
        }


    }
}

//从文件中读取图信息，建立邻接链表
void ShortestPath::ReadFiles(){
    //读取节点个数和编号
    FILE *f = fopen("F:/Qt codes/ShortestPath/Vex.txt", "r");
    fscanf(f, "%d", &G.n);
    int i;
    for (i = 0; i < G.n; i++){
        int j;
        fscanf(f, "%d", &j);
        G.vertices[j].num = j;
        char Temp[100];
    }
    fclose(f);

    //读入边信息并创建邻接链表
    f = fopen("F:/Qt codes/ShortestPath/Edge.txt", "r");
    int k;
    int m;
    int length;
    while (fscanf(f, "%d\t%d\t%d",&k,&m,&length) != EOF){
        ArcNode* newNode;
        newNode = (ArcNode*)malloc(sizeof(ArcNode));
        newNode->adjvex = m;
        newNode->weight = length;
        newNode->nextarc = NULL;
        ArcNode* p = G.vertices[k].firstarc;
        if(p == NULL){//表头结点为空
            G.vertices[k].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
            G.vertices[k].firstarc = newNode;
        }
        else{
            while (p->nextarc != NULL){
                p = p->nextarc;
            }
            p->nextarc = newNode;
        }

        newNode = (ArcNode*)malloc(sizeof(ArcNode));
        newNode->adjvex = k;
        newNode->weight = length;
        newNode->nextarc = NULL;
        p = G.vertices[m].firstarc;
        if (p == NULL){//表头结点为空
            G.vertices[m].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
            G.vertices[m].firstarc = newNode;
        }
        else{
            while (p->nextarc != NULL){
                p = p->nextarc;
            }
            p->nextarc = newNode;
        }
    }
    fclose(f);
}






