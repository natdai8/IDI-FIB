#include <QDoubleSpinBox>

class MyDoubleSpinBox: public QDoubleSpinBox
{
    Q_OBJECT


    public:

        MyDoubleSpinBox (QWidget *parent);

    public slots:

        void reset();
};
