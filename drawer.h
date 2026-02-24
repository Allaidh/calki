#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QResizeEvent>

class drawer : public QWidget
{
    Q_OBJECT
public:
    explicit drawer(QWidget *parent = nullptr);
    void toggle();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool isOpen;
    void setupUI();

signals:
};

#endif // DRAWER_H
