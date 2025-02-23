#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>

class LupiDPI : public QWidget {
    Q_OBJECT  // Обязательно для классов, использующих Qt-сигналы и слоты

public:
    explicit LupiDPI(QWidget *parent = nullptr);
};

// Реализация конструктора
LupiDPI::LupiDPI(QWidget *parent) : QWidget(parent) {
    setFixedSize(400, 580);
    setWindowTitle("Lupi DPI Bypass");

    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QPushButton *startBtn = new QPushButton("Launch DPI Bypass");
    QPushButton *installBtn = new QPushButton("Install Bypass Service");
    QPushButton *removeBtn = new QPushButton("Remove Bypass Service");
    QPushButton *stopBtn = new QPushButton("Stop DPI Bypass");
    QPushButton *infoBtn = new QPushButton("Guide");

    QComboBox *altStarts = new QComboBox();
    altStarts->addItem("Default (Russia)", "general.bat");
    altStarts->addItem("Default (Iran)", "iran.bat");
    altStarts->addItem("Alt Launch 1", "alt1.bat");
    altStarts->addItem("Alt Launch 2", "alt2.bat");
    altStarts->addItem("Alt Launch 3", "alt3.bat");
    altStarts->addItem("Alt Launch 4", "alt4.bat");

    layout->addWidget(startBtn);
    layout->addWidget(altStarts);
    layout->addWidget(installBtn);
    layout->addWidget(removeBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(infoBtn);

    connect(startBtn, &QPushButton::clicked, this, [=]() {
        // Здесь можно добавить логику запуска
    });

    connect(installBtn, &QPushButton::clicked, this, []() {
        // Установка сервиса обхода DPI
    });

    connect(removeBtn, &QPushButton::clicked, this, []() {
        // Удаление сервиса обхода DPI
    });

    connect(stopBtn, &QPushButton::clicked, this, []() {
        // Остановка сервиса обхода DPI
    });

    connect(infoBtn, &QPushButton::clicked, this, []() {
        QMessageBox::information(nullptr, "Guide", "Инструкция по использованию...");
    });
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LupiDPI window;
    window.show();
    return app.exec();
}

// Необходимая директива для корректной работы MOC
#include "main.moc"
