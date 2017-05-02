#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 300, 300);
    scene.addLine(0, 0, 200, 200);

    QGraphicsView view(&scene);
    view.setWindowTitle("Graphics View");
    //    view.resize(800, 600);
    view.show();

    return a.exec();
}
