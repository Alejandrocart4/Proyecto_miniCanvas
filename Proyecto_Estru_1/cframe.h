#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
//#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

/*protected:
    void resizeEvent(QResizeEvent *event) override;*/


private slots:
    void on_btnsalir_clicked();

private:
    Ui::cframe *ui;
};
#endif // CFRAME_H
