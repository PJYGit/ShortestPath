#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <QMainWindow>

namespace Ui {
class ShortestPath;
}

class ShortestPath : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShortestPath(QWidget *parent = nullptr);
    ~ShortestPath();

    void ReadFiles();

    typedef struct ArcNode
    {
        int   adjvex;
        struct ArcNode  *nextarc;
        int weight;
    } ArcNode;

    typedef struct VNode
    {
        int num;
        struct ArcNode  *firstarc = nullptr;
    } VNode, AdjList[100];

    struct ALGraph
    {
        AdjList  vertices;
        int n;
        int e;
    }G;

    void Dijkstra(ALGraph G, int v0, int path[], int dist[]);

private slots:
    void on_Find_clicked();

private:
    Ui::ShortestPath *ui;
};

#endif // SHORTESTPATH_H
